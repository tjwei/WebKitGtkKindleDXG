/*
 * Copyright (c) 2006-2009 Openismus GmbH
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

#include "gtkimcontextchewing.h"
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkimmodule.h>
#include <config.h>

#define AUTOMATIC_COMPOSE_TIMEOUT 1 /* seconds */
#define CONFIGURATION_FILENAME CHEWING_CONFDIR G_DIR_SEPARATOR_S "im-chewing.conf"

/* This contains rows of characters that can be entered by pressing
 * a particular key repeatedly.  Each row has one key (such as GDK_a),
 * and an array of character strings, such as "a".
 */
typedef struct
{
  gchar **characters; /* array of strings */
  gsize n_characters; /* number of strings in the array */
}
KeySequence;

static GObjectClass *im_context_chewing_parent_class = NULL;
static GType         im_context_chewing_type = 0;

static void im_context_chewing_class_init (GtkImContextChewingClass *klass);
static void im_context_chewing_init (GtkImContextChewing *self);
static void im_context_chewing_finalize (GObject *obj);

static void load_config (GtkImContextChewing *self);

static gboolean vfunc_filter_keypress (GtkIMContext *context,
                                       GdkEventKey  *event);
static void vfunc_reset (GtkIMContext *context);
static void vfunc_get_preedit_string (GtkIMContext   *context,
                                      gchar         **str,
                                      PangoAttrList **attrs,
                                      gint           *cursor_pos);
#define SELKEYS 9
static int selKey_define[ SELKEYS+1 ] = {'a','s','d','f','g','h','j','k','l',0};
/* Notice that we have a *_register_type(GTypeModule*) function instead of a
 * *_get_type() function, because we must use g_type_module_register_type(),
 * providing the GTypeModule* that was provided to im_context_init(). That
 * is also why we are not using G_DEFINE_TYPE().
 */
void
gtk_im_context_chewing_register_type (GTypeModule* type_module)
{
  static const GTypeInfo im_context_chewing_info =
    {
      sizeof (GtkImContextChewingClass),
      (GBaseInitFunc) NULL,
      (GBaseFinalizeFunc) NULL,
      (GClassInitFunc) &im_context_chewing_class_init,
      NULL,
      NULL,
      sizeof (GtkImContextChewing),
      0,
      (GInstanceInitFunc) &im_context_chewing_init,
      0,
    };

  im_context_chewing_type =
    g_type_module_register_type (type_module,
                                 GTK_TYPE_IM_CONTEXT,
                                 "GtkImContextChewing",
                                 &im_context_chewing_info, 0);
}

GType
gtk_im_context_chewing_get_type (void)
{
  g_assert (im_context_chewing_type != 0);

  return im_context_chewing_type;
}

static void
key_sequence_free (gpointer value)
{
  KeySequence *seq = value;

  if (seq != NULL)
    {
      g_strfreev (seq->characters);
      g_slice_free (KeySequence, seq);
    }
}

static void
im_context_chewing_class_init (GtkImContextChewingClass *klass)
{
  GtkIMContextClass *im_context_class;

  /* Set this so we can use it later: */
  im_context_chewing_parent_class = g_type_class_peek_parent (klass);

  /* Specify our vfunc implementations: */
  im_context_class = GTK_IM_CONTEXT_CLASS (klass);
  im_context_class->filter_keypress = &vfunc_filter_keypress;
  im_context_class->reset = &vfunc_reset;
  im_context_class->get_preedit_string = &vfunc_get_preedit_string;
 
  G_OBJECT_CLASS (klass)->finalize = &im_context_chewing_finalize;
}

static void
im_context_chewing_init (GtkImContextChewing *self)
{
  /*self->key_sequences = g_hash_table_new_full (&g_direct_hash, &g_direct_equal,
                                               NULL, &key_sequence_free);
  load_config (self);*/
	g_print("init chewing\n");
	self->commit_string=NULL;
	self->im_state=0;
	g_signal_emit_by_name (self, "preedit-end");
	if(self->ctx==NULL){
  	chewing_Init("/mnt/us/chewing/data/", "/mnt/us/chewing/user/");
	self->ctx=chewing_new();
	chewing_set_KBType(self->ctx, chewing_KBStr2Num((char *)"KB_HSU"));
	chewing_set_candPerPage(self->ctx,9);
	chewing_set_maxChiSymbolLen(self->ctx, 16);
	chewing_set_addPhraseDirection(self->ctx,1);
	chewing_set_selKey(self->ctx, selKey_define, 10);
	chewing_set_spaceAsSelection(self->ctx, 1);
	}

}

static void
im_context_chewing_finalize (GObject *obj)
{
  GtkImContextChewing *self;

  self = GTK_IM_CONTEXT_CHEWING (obj);

  chewing_delete(self->ctx);
  chewing_Terminate();
  self->ctx=NULL;
  free(self->commit_string);
  self->commit_string=NULL;
  (*im_context_chewing_parent_class->finalize) (obj);
}


GtkIMContext *
gtk_im_context_chewing_new (void)
{
  return (GtkIMContext *)g_object_new (GTK_TYPE_IM_CONTEXT_CHEWING, NULL);
}




/* Finish composing, provide the character, and clear our compose buffer.
 */
static void
send_commit_string (GtkImContextChewing *im_context)
{
  /* Clear the compose buffer, so we are ready to compose the next character.
   * Note that if we emit "preedit-changed" after "commit", there's a segfault/
   * invalid-write with GtkTextView in gtk_text_layout_free_line_display(), when
   * destroying a PangoLayout (this can also be avoided by not using any Pango
   * attributes in get_preedit_string(). */

  /* Provide the character to GTK+ */
  if(im_context->commit_string)
  	g_signal_emit_by_name (im_context, "commit", im_context->commit_string);
}


#if 0
inline int imbar_draw_selection(int x){
	char key[2]=" ";
	stringstream s;
	s << "選擇("<< (chewing_cand_CurrentPage(ctx)+1)<<"/" << chewing_cand_TotalPage(ctx)  <<"):";
	x=draw_str(im_pix,x,28, s);
	chewing_cand_Enumerate(ctx);
	int choices_per_page=chewing_cand_ChoicePerPage(ctx); 
	for(int i=0;chewing_cand_hasNext(ctx) && (i< choices_per_page);i++, x+=12){
		s.str("");
		s << (char) selKey_define[i] << chewing_cand_String(ctx);
		x=draw_str(im_pix,x,28, s);
	}
	return x;
}
#endif
static int handle_chewing_im(GtkImContextChewing *im_context, GdkEventKey *event){
	ChewingContext *ctx=im_context->ctx;
	int alt=event->state&GDK_MOD1_MASK;
	int shift=event->state&GDK_SHIFT_MASK;
	int buffer_is_empty=chewing_buffer_Len(ctx)==0 && chewing_get_phoneSeqLen(ctx)==0;
	guint keycode=event->keyval;
	g_print("alt=%d shift=%d keycode=%x im_state=%x\n", alt,shift,keycode, im_context->im_state);
	if(im_context->im_state==0){
		if( (alt  || shift) && keycode==GDK_space){
			im_context->im_state=1;
	   		g_signal_emit_by_name (im_context, "preedit-start");
			return TRUE;
		}
		else 
			return FALSE;
	}
	switch(keycode){
		case GDK_Return: 
			if(buffer_is_empty) return FALSE;			
			chewing_handle_Enter(ctx);break;
		case GDK_space:
			if((alt||shift) && keycode==GDK_space){
				im_context->im_state=0;
	   			g_signal_emit_by_name (im_context, "preedit-end");
				return TRUE;
			}	
			/*		
			else if(shift){
				//chewing_handle_ShiftSpace(ctx);
				 chewing_set_ShapeMode(ctx,!chewing_get_ShapeMode(ctx));
			}*/
			else
				chewing_handle_Space(ctx);
			break;
		case GDK_Delete: 
			chewing_handle_Del(ctx);break;
		case GDK_BackSpace: 
			if(buffer_is_empty) return FALSE;			
			chewing_handle_Backspace(ctx);
						break;
		case GDK_Left: 
			chewing_handle_Left(ctx);break;
		case GDK_Right: 
			chewing_handle_Right(ctx);break;
		case GDK_Up: chewing_handle_Up(ctx);break;
		case GDK_Down: chewing_handle_Down(ctx);break;
		case GDK_Control_R: 
		case GDK_Control_L: 
			//switch between KB_HSU and KB_HANYU_PINGYIN
			chewing_set_KBType(ctx, chewing_get_KBType(ctx)^8);
			break;
		case GDK_KP_Tab: 			
			chewing_handle_Capslock(ctx);break;
		default:
			{
      			guint32  keyval_uchar = gdk_keyval_to_unicode (event->keyval);
              		gchar keyval_utf8[7];
              		gint  length=0;
      			if (keyval_uchar != 0)
              			length = g_unichar_to_utf8 (keyval_uchar, keyval_utf8);
			if(length==1)
				chewing_handle_Default(ctx, keyval_utf8[0]);
			else return FALSE;
			}
	}
	if(chewing_commit_Check(ctx)){
			if(im_context->commit_string)
				free(im_context->commit_string);
			im_context->commit_string=chewing_commit_String(ctx);			
			send_commit_string(im_context);
	}
        g_signal_emit_by_name (im_context, "preedit-changed");
	return TRUE;
}

static gboolean
vfunc_filter_keypress (GtkIMContext *context, GdkEventKey *event)
{
  GtkIMContextClass      *parent;
  GtkImContextChewing *im_context;

  im_context = GTK_IM_CONTEXT_CHEWING (context);
  if (event->type == GDK_KEY_PRESS)
    {
      g_print("key pressed %x\n",event->keyval);
      if (handle_chewing_im(im_context, event))
		return TRUE;
      guint32  keyval_uchar = gdk_keyval_to_unicode (event->keyval);
      /* Convert to a string for accept_character(). */
      if (keyval_uchar != 0)
            {
              /* max length of UTF-8 sequence = 6 + 1 for NUL termination */
              gchar keyval_utf8[7];
              gint  length;

              length = g_unichar_to_utf8 (keyval_uchar, keyval_utf8);
              keyval_utf8[length] = '\0';
 	      g_signal_emit_by_name (im_context, "commit", keyval_utf8);

              return TRUE; /* key handled */
      }

    }
  parent = (GtkIMContextClass *)im_context_chewing_parent_class;

  /* The default implementation just returns FALSE, but it is generally
   * a good idea to call the base class implementation: */
  if (parent->filter_keypress)
    return (*parent->filter_keypress) (context, event);

  return FALSE;
}

static void
vfunc_reset (GtkIMContext *context)
{
	g_print("reset\n");
}

static void
vfunc_get_preedit_string (GtkIMContext   *context,
                          gchar         **str,
                          PangoAttrList **attrs,
                          gint           *cursor_pos)
{
  GtkImContextChewing *im_context  = GTK_IM_CONTEXT_CHEWING (context);
  ChewingContext *ctx=im_context->ctx;
  int cur=chewing_cursor_Current(ctx);
  gchar *buffer=chewing_buffer_String(ctx);	
  gchar *buffer2=g_utf8_offset_to_pointer(buffer, cur);
  int buffer_len1=buffer2-buffer;
  int nZuin;
  char *zuin=chewing_zuin_String(ctx, &nZuin);	
  int len_bytes=im_context->im_state==1 ? strlen(buffer)+strlen(zuin)+1 : 0;

  /* Show the user what character he will get if he accepts: */
  if (str != NULL)
    {
	if(len_bytes>0){
  	GString *gstr=g_string_new_len(buffer, buffer_len1);
  	g_string_append(gstr, zuin);
  	g_string_append(gstr, " ");
  	g_string_append(gstr, buffer2);
        *str=g_string_free(gstr, FALSE);
	}
	else 
		*str=g_strdup("");
    }

  free(buffer);
  free(zuin);
  /* Underline it, to show the user that he is in compose mode: */
  if (attrs != NULL)
    {
      *attrs = pango_attr_list_new ();

      if (len_bytes > 0)
        {
          PangoAttribute *attr;

          attr = pango_attr_underline_new (PANGO_UNDERLINE_SINGLE);
          attr->start_index = 0;
          attr->end_index = len_bytes;
          pango_attr_list_insert (*attrs, attr);
        }
    }

  if (cursor_pos)
    *cursor_pos = len_bytes>0 ? cur+nZuin :0;
}

