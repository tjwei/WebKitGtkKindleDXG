
#ifndef __gdk_marshal_MARSHAL_H__
#define __gdk_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:OBJECT (./gdkmarshalers.list:1) */
#define gdk_marshal_VOID__OBJECT	g_cclosure_marshal_VOID__OBJECT

/* VOID:BOOLEAN (./gdkmarshalers.list:2) */
#define gdk_marshal_VOID__BOOLEAN	g_cclosure_marshal_VOID__BOOLEAN

/* VOID:OBJECT,POINTER (./gdkmarshalers.list:3) */
extern void gdk_marshal_VOID__OBJECT_POINTER (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);

G_END_DECLS

#endif /* __gdk_marshal_MARSHAL_H__ */

