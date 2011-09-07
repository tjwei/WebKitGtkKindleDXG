/*
 * Copyright (C) 2009 Lab126.
 *
 * Tests are run through the expose event mechanism.
 * When a test suite is set through gtk_cairo_set_test_suite, iteration is done through each test by the creation of an expose event.
 */
 
#ifndef cairo_widget_h
#define cairo_widget_h

#include <gtk/gtk.h>
#include <cairo.h>
#include "KindleProfiling.h"

G_BEGIN_DECLS

#define GTK_CAIRO(obj) GTK_CHECK_CAST(obj, gtk_cairo_get_type (), GtkCairo)
#define GTK_CAIRO_CLASS(klass) GTK_CHECK_CLASS_CAST(klass, gtk_cairo_get_type(), GtkCairoClass)
#define GTK_IS_CAIRO(obj) GTK_CHECK_TYPE(obj, gtk_cairo_get_type())

typedef struct _GtkCairo GtkCairo;
typedef struct _GtkCairoClass GtkCairoClass;

typedef enum {
    eCairoTestDefault,
    eCairoTestImages,
    eCairoTestSimpleText,
    eCairoTestLast
} TestNameEnum;

struct _GtkCairo {
  GtkWidget     widget;

  // Public
  float         interval; /** The following expose event will only be emitted after the provided interval. Defaults to 0. */
  char         *rootDir;  /** Set the root dir of test files (containing images/text, etc. directories. The root path is just a reference, and it does not get freed when widget is destroyed. Defaults to "./". */
  int           iterationCount; /** Number of iteration for each file from which a mean and a standard deviation are calculated if > 1 */

  // Private
  TestNameEnum  currentTestSuite;
  int           testIndex;
  guint         timerId;
  GPtrArray    *files;
  float         suiteTime;
  int           currentIteration;
  float         currentIterationSum;   // Used to compute the mean
  float         currentIterationSum2;  // Used to compute std deviation
  gboolean      testCompleted;
};

struct _GtkCairoClass {
  GtkWidgetClass parent_class;
};

GtkType gtk_cairo_get_type(void);
void gtk_cairo_set_test_suite(GtkCairo *cairo, TestNameEnum test);
GtkWidget * gtk_cairo_new();

G_END_DECLS

#endif /* cairo_widget_h */

