/* Copyright (C) 2006 Openismus GmbH
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GTK_IM_CONTEXT_CHEWING_H__
#define __GTK_IM_CONTEXT_CHEWING_H__

#include <gtk/gtk.h>
#include <chewing/chewingio.h>
#include <chewing/chewing.h>

G_BEGIN_DECLS

#define GTK_TYPE_IM_CONTEXT_CHEWING            (gtk_im_context_chewing_get_type ())
#define GTK_IM_CONTEXT_CHEWING(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_IM_CONTEXT_CHEWING, GtkImContextChewing))
#define GTK_IM_CONTEXT_CHEWING_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_IM_CONTEXT_CHEWING, GtkImContextChewingClass))
#define GTK_IS_IM_CONTEXT_CHEWING(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_IM_CONTEXT_CHEWING))
#define GTK_IS_IM_CONTEXT_CHEWING_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_IM_CONTEXT_CHEWING))
#define GTK_IM_CONTEXT_CHEWING_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_IM_CONTEXT_CHEWING, GtkImContextChewingClass))

typedef struct _GtkImContextChewing GtkImContextChewing;

/* This input method allows multi-press character input, like that found on
 * mobile phones.
 *
 * This is based on GtkImContextSimple, which allows "compose" based on
 * sequences of characters.  But instead the character sequences are defined
 * by lists of characters for a key, so that repeated pressing of the same key
 * can cycle through the possible output characters, with automatic choosing
 * of the character after a time delay.
 */
struct _GtkImContextChewing
{
  /*< private >*/
  GtkIMContext parent;

  gchar *commit_string;
  ChewingContext *ctx;
  int im_state;

  
};


typedef struct _GtkImContextChewingClass  GtkImContextChewingClass;

struct _GtkImContextChewingClass
{
  GtkIMContextClass parent_class;
};

void gtk_im_context_chewing_register_type (GTypeModule* type_module);
GType gtk_im_context_chewing_get_type (void);
GtkIMContext *gtk_im_context_chewing_new (void);
#define CHEWING_CONFDIR "/usr/local/etc/chewing"
#define CHEWING_LOCALEDIR "/usr/local/share/locale"
G_END_DECLS

#endif /* __GTK_IM_CONTEXT_CHEWING_H__ */
