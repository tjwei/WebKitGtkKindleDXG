/*
 * Copyright (C) 2009 Lab126.
 *
 */

//ToDo: remove
#define USE_SYSTEM_MALLOC 1

#include "cairo_widget.h"


#define USE_SYSTEM_MALLOC 1 // Defined so that new operators do not get redeclared for this file

#include <libintl.h>
#include <runtime/InitializeThreading.h>
#include <glib.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>

#include "config.h"
#include <webkit/webkit.h>
#include "GraphicsContext.h"
#include "SharedBuffer.h"
#include "BitmapImage.h"
#include "Font.h"
#include "Logging.h"
#include "Document.h"
#include "CSSFontSelector.h"

using namespace WebCore;


static void gtk_cairo_class_init(GtkCairoClass *klass);
static void gtk_cairo_init(GtkCairo *cairo);
static void gtk_cairo_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static void gtk_cairo_realize(GtkWidget *widget);
static gboolean gtk_cairo_expose(GtkWidget *widget, GdkEventExpose *event);
static void gtk_cairo_destroy(GtkObject *object);

#define DEFAULT_ROOT_DIR "./"

// Directories containing the test suites
static const char *g_testDirectories[eCairoTestLast] = {
    "default",
    "images",
    "text"
};

static const char *g_testNames[eCairoTestLast] = {
    "Default",
    "Images",
    "Simple Text"
};

// Maximum length for absolute path of test files
#define MAX_PATH_FILENAME 500

// Signals
enum {
  TEST_COMPLETED_SIGNAL,
  LAST_SIGNAL
};
static guint gtk_cairo_signals[LAST_SIGNAL] = { 0 };


GtkType 
gtk_cairo_get_type(void) 
{
    static GtkType gtk_cairo_type = 0;
    
    if (!gtk_cairo_type) {
        static const GtkTypeInfo gtk_cairo_info = {
            (char *) "GtkCairo",
            sizeof(GtkCairo),
            sizeof(GtkCairoClass),
            (GtkClassInitFunc) gtk_cairo_class_init,
            (GtkObjectInitFunc) gtk_cairo_init,
            NULL,
            NULL,
            (GtkClassInitFunc) NULL
        };
        gtk_cairo_type = gtk_type_unique(GTK_TYPE_WIDGET, &gtk_cairo_info);
    }       
    return gtk_cairo_type;
}

static void 
gtk_cairo_free_file(gpointer data, gpointer userdata) 
{
    if (data) {
        free(data);
    }
}

void 
gtk_cairo_set_test_suite(GtkCairo *cairo, TestNameEnum test) 
{
    cairo->currentTestSuite = test;
    cairo->testIndex = 0;
    cairo->testCompleted = FALSE;
    cairo->suiteTime = 0;
    cairo->currentIteration = 0;
    cairo->currentIterationSum = 0;
    cairo->currentIterationSum2 = 0;

    if (cairo->timerId >= 0) {
        g_source_remove(cairo->timerId);
        cairo->timerId = -1;
    }
    if (cairo->files) {
        g_ptr_array_foreach(cairo->files, gtk_cairo_free_file, NULL);
        g_ptr_array_free(cairo->files, TRUE);
        cairo->files = 0;
    }
    if (!cairo->files) {
        cairo->files = g_ptr_array_new();
    }

    // Retrieve the list of files for this particular test suite
    if (test > eCairoTestDefault && test < eCairoTestLast) {
        char dirName[MAX_PATH_FILENAME];
        strcpy(dirName, cairo->rootDir);
        strcpy(dirName+strlen(cairo->rootDir), g_testDirectories[test]);
        DIR *dp = opendir (dirName);
        if (dp) {
            struct dirent *ep;
            int len = strlen(dirName);
            dirName[len++] = '/';
                
            while (ep = readdir (dp)) {
                if (ep->d_name[0] != '.') {
                    char *name = (char *) malloc((len+strlen(ep->d_name)+1)*sizeof(char));
                    if (name) {
                        strcpy(dirName+len, ep->d_name);
                        strcpy(name, dirName);
                        g_ptr_array_add(cairo->files, name);
                    }
                }
            }
            closedir (dp);
        } else {
            fprintf(stderr, "Couldn't open the directory %s\n", dirName);
        }

        printf("\nTest suite %s\n", g_testNames[test]);
    }

    // should be done by invalidating with gtk_cairo_paint(GTK_WIDGET(cairo));
}

GtkWidget * gtk_cairo_new() 
{
   return GTK_WIDGET(gtk_type_new(gtk_cairo_get_type()));
}

static void
gtk_cairo_class_init(GtkCairoClass *klass) 
{
    GtkWidgetClass *widget_class;
    GtkObjectClass *object_class;
        
    widget_class = (GtkWidgetClass *) klass;
    object_class = (GtkObjectClass *) klass;
    
    widget_class->realize = gtk_cairo_realize;
    widget_class->size_allocate = gtk_cairo_size_allocate;
    widget_class->expose_event = gtk_cairo_expose;
    
    object_class->destroy = gtk_cairo_destroy;

    /**
     * Emitted when the current test is completed.
     */
    gtk_cairo_signals[TEST_COMPLETED_SIGNAL] = g_signal_new("test-completed",
            G_TYPE_FROM_CLASS(klass),
            (GSignalFlags)G_SIGNAL_RUN_LAST, // G_SIGNAL_NO_HOOKS
            0,
            NULL,
            NULL,
            g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE , 0);
}

void 
webkit_init() 
{
    static bool isInitialized = false;
    if (isInitialized)
        return;
    isInitialized = true;

    //bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");

    // Needs to be added to pass the asserts checking whether it is executed in main thread
    JSC::initializeThreading();
    WebCore::InitializeLoggingChannelsIfNecessary();
}

static void
gtk_cairo_init(GtkCairo *cairo) 
{
    cairo->interval = 0;
    cairo->rootDir = (char *) DEFAULT_ROOT_DIR;
    cairo->currentTestSuite = eCairoTestDefault;
    cairo->testIndex = 0;
    cairo->testCompleted = FALSE;
    cairo->files = 0;
    cairo->timerId = -1;
    cairo->suiteTime = 0;
    cairo->currentIteration = 0;
    cairo->currentIterationSum = 0;
    cairo->currentIterationSum2 = 0;
    
    // Initialize webkit for things that may be used by tests
    webkit_init();
}

static void
gtk_cairo_size_allocate(GtkWidget *widget, GtkAllocation *allocation) 
{
    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CAIRO(widget));
    g_return_if_fail(allocation != NULL);
    
    widget->allocation = *allocation;
    
    if (GTK_WIDGET_REALIZED(widget)) {
        gdk_window_move_resize(
            widget->window,
            allocation->x, allocation->y,
            allocation->width, allocation->height
        );
    }
}

static void
gtk_cairo_realize(GtkWidget *widget) 
{
    GdkWindowAttr attributes;
    guint attributes_mask;
    
    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_CAIRO(widget));
    
    GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);
    
    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
    
    attributes.wclass = GDK_INPUT_OUTPUT;
    attributes.event_mask = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;
    
    attributes_mask = GDK_WA_X | GDK_WA_Y;
    
    widget->window = gdk_window_new(gtk_widget_get_parent_window (widget), &attributes, attributes_mask);
    
    gdk_window_set_user_data(widget->window, widget);
    
    widget->style = gtk_style_attach(widget->style, widget->window);
    gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);
}

static void 
gtk_cairo_draw_text(GraphicsContext *gc, const String& text, unsigned int length, int fontSize, int line) 
{
    // Need to create an empty document so that a CSSSelector can be created
    PassRefPtr<Document> document(Document::create(0));

    // Create the Font selector using this document
    PassRefPtr<CSSFontSelector> fontSelector = CSSFontSelector::create(document.get());

    // Use Arial as font family
    FontFamily family;
    family.setFamily("arial");

    // Create a font description to then assign to the font object
    FontDescription fontDescription = FontDescription();
    fontDescription.setFamily(family);
    fontDescription.setComputedSize(fontSize);
    fontDescription.setSpecifiedSize(fontSize);
    fontDescription.setWeight(FontWeightNormal);
    fontDescription.setGenericFamily(FontDescription::SansSerifFamily);
    fontDescription.setKeywordSize(4);

    // Create the font and initialize it 
    static Font font(fontDescription, 0, 0);
    font.update(fontSelector);

    const UChar* string = text.characters();

    // When rtl has to be added, configure in TextRun constructor
    // TextRun textRun(string, length, 0, 0, 0, rtl, override, false, false);
    TextRun textRun(string, length);
    font.drawText(gc, textRun, FloatPoint(0, line*fontSize), 0, -1);

//    c->drawBidiText(font, textRun, location);
}

/**
 * Invalidate the main window to cause an expose event and a repaint
 */
static gboolean 
gtk_cairo_invalidate_window(void *voidWidget) 
{
    g_return_val_if_fail(voidWidget != NULL, FALSE);
    g_return_val_if_fail(GTK_IS_WIDGET(voidWidget), FALSE);
    GtkWidget *widget = GTK_WIDGET(voidWidget);
    GdkRegion *region = gdk_drawable_get_clip_region(widget->window);
    gdk_window_invalidate_region(widget->window, region, TRUE);
    gdk_window_process_updates(widget->window, TRUE);
    return FALSE;
}

static void
gtk_cairo_paint_images(GtkCairo *widget, GdkEventExpose *event) 
{
    cairo_t* cr = gdk_cairo_create(GTK_WIDGET(widget)->window);
    cairo_set_source_rgb(cr, 255, 255, 255);
    cairo_paint(cr);
    GraphicsContext ctx(cr);
    cairo_destroy(cr);
    ctx.setGdkExposeEvent(event);

    // First, run the specified number of iterations for the current test
    if (widget->currentIteration < widget->iterationCount) {
        widget->currentIteration++;
    } else {
        widget->testIndex++;
        widget->currentIteration = 1;
    }

    // Check whether the end of the suite is reached
    if (!widget->files || widget->testIndex >= (int) widget->files->len) {
        widget->testCompleted = TRUE;
        printf("  Test suite completed in %.3fs (%d files)\n", widget->suiteTime, widget->files->len);
        g_signal_emit(GTK_OBJECT(widget), gtk_cairo_signals[TEST_COMPLETED_SIGNAL], 0);
        return;
    }

    const char *szFileName = (const char *) g_ptr_array_index(widget->files, widget->testIndex);
    // Print on last iteration
    if (widget->iterationCount > 1 && widget->currentIteration == widget->iterationCount) {
        printf("  Testing %s", szFileName);
    }

    kindle_stats.totalImageRenderingTime = 0;

    // Open the image file and store its data 
    PassRefPtr<SharedBuffer> fileContent = SharedBuffer::createWithContentsOfFile(szFileName);
    if (!fileContent) {
        fprintf(stderr, "Could not load: %s\n", szFileName);
    } else {
        RefPtr<BitmapImage> image = BitmapImage::create();
        image->setData(fileContent, true);
        ctx.drawImage(image.get(), IntPoint(10, 10));
    }

    // When several iteration of same test is executed, compute the mean and std deviation
    if (widget->iterationCount > 1) {
        if (widget->currentIteration < widget->iterationCount) {
			widget->currentIterationSum += kindle_stats.totalImageRenderingTime;
			widget->currentIterationSum2 += kindle_stats.totalImageRenderingTime * kindle_stats.totalImageRenderingTime;
        } else {
            float mean = widget->currentIterationSum/widget->iterationCount;
            printf(" in %.3fs (stdDev: %.3fs)\n", mean, sqrt(widget->currentIterationSum2/widget->iterationCount-(mean * mean)));
        }
    } else {
        printf(" in %.3fs\n", kindle_stats.totalImageRenderingTime);
    }
    widget->suiteTime += kindle_stats.totalImageRenderingTime;

    if (widget->interval >= 0) {
        widget->timerId = g_timeout_add((guint) widget->interval*1000, gtk_cairo_invalidate_window, widget);
    } else {
        gtk_cairo_invalidate_window(GTK_WIDGET(widget));
    }
}

static void
gtk_cairo_paint_simple_text(GtkCairo *widget, GdkEventExpose *event) 
{
    size_t bytes;
    char *buffer = 0;
    FILE *file;
    char *start, *end, *endBuffer;
    int line = 1;

    cairo_t* cr = gdk_cairo_create(GTK_WIDGET(widget)->window);
    cairo_set_source_rgb(cr, 255, 255, 255);
    cairo_paint(cr);
    GraphicsContext ctx(cr);
    cairo_destroy(cr);
    ctx.setGdkExposeEvent(event);

    // First, run the specified number of iterations for the current test
    if (widget->currentIteration < widget->iterationCount) {
        widget->currentIteration++;
    } else {
        widget->testIndex++;
        widget->currentIteration = 1;
    }

    // Check whether the end of the suite is reached
    if (!widget->files || widget->testIndex >= (int) widget->files->len) {
        widget->testCompleted = TRUE;
        printf("  Test suite completed in %.3fs (%d files)\n", widget->suiteTime, widget->files->len);
        g_signal_emit(GTK_OBJECT(widget), gtk_cairo_signals[TEST_COMPLETED_SIGNAL], 0);
        return;
    }

    // Open test file and extract string
    const char *szFileName = (const char *) g_ptr_array_index(widget->files, widget->testIndex);
    if (!szFileName) {
        fprintf(stderr, "gtk_cairo_paint_simple_text: No file specified\n");
        goto cleanup;
    }

    file = fopen(szFileName, "r");
    if (!file) {
        fprintf(stderr, "gtk_cairo_paint_simple_text: Failed to open %s\n", szFileName);
        goto cleanup;
    }

    struct stat statResult;
    if (stat(szFileName, &statResult)) {
        fprintf(stderr, "gtk_cairo_paint_simple_text: Could not stat %s\n", szFileName);
        goto cleanup;
    }

    if (statResult.st_size <= 0) {
        fprintf(stderr, "gtk_cairo_paint_simple_text: Empty file %s\n", szFileName);
        goto cleanup;
    }

    buffer = (char *) calloc(sizeof(char), statResult.st_size);
    if (!buffer) {
        fprintf(stderr, "gtk_cairo_paint_simple_text: Could not allocate memeory %s: %dB\n", szFileName, (int) statResult.st_size);
        goto cleanup;
    }
    bytes = fread(buffer, sizeof(char), statResult.st_size, file);

    // Print on last iteration
    if (widget->iterationCount > 1 && widget->currentIteration == widget->iterationCount) {
        printf("  Testing %s", szFileName);
    }

    kindle_stats.totalSimpleTextRenderingTime = 0;

    // Process the content taking into account the new line characters
    start = end = buffer;
    endBuffer = buffer+bytes;
    do {
        while (end < endBuffer && *end != '\n') {
            end++;
        }
        gtk_cairo_draw_text(&ctx, start, end-start, 12, line);
        start = ++end;
        line++;
    } while (start < endBuffer);

cleanup:
    if (file) {
        fclose(file);
    }
    if (buffer) {
        free(buffer);
    }

    // When several iteration of same test is executed, compute the mean and std deviation
    if (widget->iterationCount > 1) {
        if (widget->currentIteration < widget->iterationCount) {
        widget->currentIterationSum += kindle_stats.totalSimpleTextRenderingTime;
        widget->currentIterationSum2 += kindle_stats.totalSimpleTextRenderingTime * kindle_stats.totalSimpleTextRenderingTime;
        } else {
            float mean = widget->currentIterationSum/widget->iterationCount;
            printf(" in %.3fs (stdDev: %.3fs)\n", mean, sqrt(widget->currentIterationSum2/widget->iterationCount-(mean*mean)));
        }
    } else {
        printf(" in %.3fs\n", kindle_stats.totalSimpleTextRenderingTime);
    }
    widget->suiteTime += kindle_stats.totalSimpleTextRenderingTime;

    if (widget->interval >= 0) {
        widget->timerId = g_timeout_add((guint) widget->interval*1000, gtk_cairo_invalidate_window, widget);
    } else {
        gtk_cairo_invalidate_window(GTK_WIDGET(widget));
    }
}

static gboolean
gtk_cairo_expose(GtkWidget *widget, GdkEventExpose *event) 
{
    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(GTK_IS_CAIRO(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    // Select the right test to paint
    switch (GTK_CAIRO(widget)->currentTestSuite) {
        case eCairoTestDefault: 
            // Write some text explaining the possible choices
            printf("To start the tests, you need to select q: images, w: text\n");
            break;
        case eCairoTestImages:
            gtk_cairo_paint_images(GTK_CAIRO(widget), event);
            break;
        case eCairoTestSimpleText:
            gtk_cairo_paint_simple_text(GTK_CAIRO(widget), event);
            break;
    }
    
    return FALSE;
}

static void
gtk_cairo_destroy(GtkObject *object) 
{
    GtkCairo *cairo;
    GtkCairoClass *klass;
    
    g_return_if_fail(object != NULL);
    g_return_if_fail(GTK_IS_CAIRO(object));
    
    klass = (GtkCairoClass *) gtk_type_class(gtk_widget_get_type());
    
    if (GTK_OBJECT_CLASS(klass)->destroy) {
        (* GTK_OBJECT_CLASS(klass)->destroy) (object);
    }

    cairo = GTK_CAIRO(object);
    if (cairo->timerId >= 0) {
        g_source_remove(cairo->timerId);
        cairo->timerId = -1;
    }
    if (cairo->files) {
        g_ptr_array_foreach(cairo->files, gtk_cairo_free_file, NULL);
        g_ptr_array_free(cairo->files, TRUE);
        cairo->files = 0;
    }
}

