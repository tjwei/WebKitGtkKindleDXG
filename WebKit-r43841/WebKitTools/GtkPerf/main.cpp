/*
 * Copyright (C) 2009 Lab126.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include <unistd.h>
#include <getopt.h>

#include "cairo_widget.h"

// Maximum length for absolute path of test files
#define MAX_PATH_FILENAME 500

static GtkWidget* main_window = 0;
static GtkWidget* main_container = 0;
static char       g_test_file_path[MAX_PATH_FILENAME];
static float      g_test_interval;
static int        g_iteration_count;
static gboolean   g_automatic_run;

static void
destroy_cb (GtkWidget* widget, gpointer data) 
{
    gtk_main_quit ();
}

static void test_completed_cb(GtkCairo *widget);

/*********************************************************************
   Test functions to move somewhere else !
 *********************************************************************/

/**
 * Invalidate the main window to cause an expose event and a repaint
 */
static void 
invalidate_window(GtkWidget *widget) 
{
    GdkRegion *region = gdk_drawable_get_clip_region(widget->window);
    gdk_window_invalidate_region(widget->window, region, TRUE);
    gdk_window_process_updates(widget->window, TRUE);
}

static void 
render_buttons(int columns, int rows) 
{
    // Create the container where tests are rendered to
    /* GtkWidget* main_container = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (main_container), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add (GTK_CONTAINER (main_window), GTK_WIDGET (main_container));
    */

    // This packs the button into a gtk container. 
    if (main_container) {gtk_widget_destroy(main_container);}
    main_container = gtk_table_new(rows, columns, TRUE);
    gtk_container_add(GTK_CONTAINER(main_window), main_container);

    char name[20] = {'b', 't', 'n'};
    int index = 0;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            sscanf(name+3, "%d", &index);
            index++;
            GtkWidget *button = gtk_button_new_with_label(name);
            gtk_table_attach((GtkTable *) main_container, button, j, j+1, i, i+1, (GtkAttachOptions) (GTK_EXPAND|GTK_FILL), (GtkAttachOptions) (GTK_EXPAND|GTK_FILL), 1, 1);
       }
    }

    // Stat collection
    //kindle_stats.totalRenderingTime = 0;
    //kindle_stats.totalBlitTime = 0;
    gtk_widget_show_all(main_container);

// ToDo: wrong location to measure the rendering time.
   // printf("\nTest suite Buttons (%dx%d)\n", rows, columns);
//    printf("  Test suite completed in %.3fs (Rendering: %.3fs, Blit: %.3fs)\n", 
     //      kindle_stats.totalRenderingTime+kindle_stats.totalBlitTime, 
     //      kindle_stats.totalRenderingTime, 
     //      kindle_stats.totalBlitTime);
}

void 
render_cairo(TestNameEnum testName) 
{
    if (main_container && !GTK_IS_CAIRO(main_container)) {
        gtk_widget_destroy(main_container);
        main_container = 0;
    }
    if (!main_container) {
        main_container = gtk_cairo_new();
        GTK_CAIRO(main_container)->interval = g_test_interval;
        GTK_CAIRO(main_container)->rootDir = g_test_file_path;
        GTK_CAIRO(main_container)->iterationCount = g_iteration_count;
        g_signal_connect (main_container, "test-completed", G_CALLBACK (test_completed_cb), main_container);

        gtk_container_add(GTK_CONTAINER(main_window), main_container);
        gtk_widget_show_all(main_container);
    }
    gtk_cairo_set_test_suite(GTK_CAIRO(main_container), testName);

    // Start tests
    invalidate_window(main_container);
}

void
render_non_cairo() 
{
    render_buttons(10, 20);
}

static gboolean
key_event_cb (GtkWidget *window, GdkEventKey *event) 
{
    // On key press launch the different tests 
    // Could be replaced by a combo box
    switch (event->keyval) {
        case GDK_q: render_non_cairo(); break;
        case GDK_w: render_cairo(eCairoTestImages); break;
        case GDK_e: render_cairo(eCairoTestSimpleText); break;
    }

	return FALSE;
}

static void 
test_completed_cb(GtkCairo *widget) 
{
    if (g_automatic_run) {
        if (widget->currentTestSuite+1 < eCairoTestLast) {
            render_cairo((TestNameEnum) (widget->currentTestSuite+1));
        } else {
            // Run non cairo tests
            render_non_cairo();
        }
    }    
}

static gboolean
start_automatic_test(void *data)
{
    render_cairo((TestNameEnum) (eCairoTestDefault+1));
    return FALSE;
}

int
main (int argc, char* argv[]) 
{
    int opt;
    opterr = 0;

    // Default values
    int screenWidth = 600;
    int screenHeight = 800;
    strcpy(g_test_file_path, "./");
    g_test_interval = 1;
    g_iteration_count = 1;
    g_automatic_run = TRUE;

    while ((opt = getopt (argc, argv, "d:w:h:p:i:c:m")) != -1) {
        switch (opt) {
            case 'd':
                if (!strcmp(optarg, "turing")) {
                    screenWidth = 600;
                    screenHeight = 800;
                } else if (!strcmp(optarg, "nell")) {
                    screenWidth = 824;
                    screenHeight = 1200;
                }
                break;
            case 'w': screenWidth = atoi(optarg); break;
            case 'h': screenHeight = atoi(optarg); break;
            case 'p': strcpy(g_test_file_path, optarg); break;
            case 'i': g_test_interval = atof(optarg); break;
            case 'c': g_iteration_count = atoi(optarg); if (g_iteration_count < 1) {g_iteration_count = 1;} break;
            case 'm': g_automatic_run = FALSE; break;
            case '?': 
                fprintf(stderr, "Usage: GtkPerf [-d turing|nell] [-w width] [-h height] [-p path to test files] [-i wait interval between each tests] [-c number of iterations per test] [-m]\n");
                fprintf(stderr, "  -m by default the tests are automatically run in sequence. etting this flag turns on the interactive mode where key presses start a specific test suite\n");
                exit (1);
            default: break;
        }
    }

    gtk_init (&argc, &argv);
    if (!g_thread_supported ())
        g_thread_init (NULL);

/*    gdk_window_set_debug_updates(true); */

    // Create the main window
    main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    // Take the whole screen size 
    GdkScreen* screen = gtk_window_get_screen(GTK_WINDOW(main_window));
    gtk_window_set_default_size (GTK_WINDOW (main_window), screenWidth ? screenWidth : gdk_screen_get_width(screen), screenHeight ? screenHeight : gdk_screen_get_height(screen));
    gtk_widget_set_name (main_window, "GtkPerf");

    g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (destroy_cb), NULL);
	g_signal_connect (G_OBJECT (main_window), "key-press-event", G_CALLBACK (key_event_cb), main_window);

    gtk_widget_grab_focus (GTK_WIDGET (main_window));
    gtk_widget_show_all (main_window);

    // Start with first cairo test when in automatic mode
    if (g_automatic_run) {
        g_timeout_add(10, start_automatic_test, 0);
    }

    // Ask for the performance information to be collected
    //kindle_debug_flags = Kindle_Debug_Perf | Kindle_Debug_Perf_Details;
    //kindle_start_time();

    gtk_main ();
    return 0;
}
