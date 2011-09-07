/*
 * Copyright (C) 2006, 2007 Apple Inc.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
/* <lab126> <tjw>*/
#include <libsoup/soup.h>
#include <gdk/gdkkeysyms.h>
#include <unistd.h>
#include <getopt.h>
int gScreenWidth = 824;
int gScreenHeight = 1200;
/* </tjw></lab126> */

static GtkWidget* main_window;
static GtkWidget* uri_entry;
static GtkWidget* toolbar;
static GtkWidget* scrolled_window;
static GtkStatusbar* main_statusbar;
static WebKitWebView* web_view;
static gchar* main_title;
static guint status_context_id;
static void
activate_uri_entry_cb (GtkWidget* entry, gpointer data)
{
    const gchar* uri = gtk_entry_get_text (GTK_ENTRY (entry));
    g_assert (uri);
    if (g_strstr_len(uri, 30, ":/"))
    	webkit_web_view_load_uri (web_view, uri);
    else {	
    GString *string=g_string_new("http://");
    g_string_append(string, uri);
    gchar *http_uri=g_string_free(string,FALSE);
    	webkit_web_view_load_uri (web_view, http_uri);
    g_free(http_uri);
   }
}

static void status_printf(const gchar *fmt, ...){
	va_list arg_ptr;
	GString *gstr=g_string_sized_new(0);
	va_start(arg_ptr, fmt);
	g_string_vprintf(gstr,fmt, arg_ptr);
    	gtk_statusbar_pop (main_statusbar, status_context_id);
   	gchar *text= g_string_free(gstr,false);
   	gtk_statusbar_push (main_statusbar, status_context_id, text);
   	g_free(text);
}
static void
link_hover_cb (WebKitWebView* page, const gchar* title, const gchar* link, gpointer data)
{
    /* underflow is allowed */
    if (link) 
	   status_printf("%s", link);
    else
    	   gtk_statusbar_pop (main_statusbar, status_context_id);
}

static gpointer 
create_web_view_cb (WebKitWebView* page, const gchar* title, const gchar* link, gpointer data)
{
	return web_view;
}

/* <lab126> */
static void
link_focus_cb (WebKitWebView* page, const gchar* title, const gchar* link, const gchar* id, gpointer data)
{
    printf("href: %s id: %s\n", link ? link : "none", id ? id : "none");
}
/* </lab126> */

static void
title_change_cb (WebKitWebView* web_view, WebKitWebFrame* web_frame, const gchar* title, gpointer data)
{
    if (main_title)
        g_free (main_title);
    main_title = g_strdup (title);
    /*update_title (GTK_WINDOW (main_window));*/
}

static void
notify_load_status_cb (WebKitWebView* web_view, GParamSpec* pspec, gpointer data)
{
    if (webkit_web_view_get_load_status (web_view) == WEBKIT_LOAD_COMMITTED) {
        WebKitWebFrame* frame = webkit_web_view_get_main_frame (web_view);
        const gchar* uri = webkit_web_frame_get_uri (frame);
        if (uri)
            gtk_entry_set_text (GTK_ENTRY (uri_entry), uri);
    }
    /*else if (webkit_web_view_get_load_status (web_view) == WEBKIT_LOAD_FINISHED) 	
	status_printf("Load finished");*/
}
static char statusChar[8]="-\\|/-\\|/";
static int statusCharIndex=0;
static void
notify_progress_cb (WebKitWebView* web_view, GParamSpec* pspec, gpointer data)
{
    gdouble load_progress = webkit_web_view_get_progress (web_view);
    if (load_progress < 100){
	statusCharIndex=(statusCharIndex+1)%8;
	status_printf("Loading (%4.1f%%) %c", load_progress, statusChar[statusCharIndex]);
   }
	else
	status_printf("Loading Completed");
}

static void
destroy_cb (GtkWidget* widget, gpointer data)
{
    gtk_main_quit ();
}

static void
go_back_cb (GtkWidget* widget, gpointer data)
{
    webkit_web_view_go_back (web_view);
}

static void
go_forward_cb (GtkWidget* widget, gpointer data)
{
    webkit_web_view_go_forward (web_view);
}

/* <lab126> */
static bool SendMouseClick() {
  GdkEvent* event = gdk_event_new(GDK_BUTTON_PRESS);
  event->button.send_event = true;
  event->button.time = g_get_real_time();
  gint x, y;
  gint origin_x, origin_y;
  GdkModifierType modifier;
  /*GdkWindow *gdkwin=gdk_window_at_pointer(NULL,NULL);*/
  GtkWidget* grab_widget = gtk_grab_get_current();
  if (grab_widget) {
    printf("win grabbed\n");
    event->button.window = grab_widget->window;
    gdk_window_get_pointer(event->button.window, &x, &y, NULL);
  } else {
    event->button.window=GTK_WIDGET(web_view)->window;
  }

  g_object_ref(event->button.window);
  gdk_window_get_origin(event->button.window, &origin_x, &origin_y);
  gdk_window_get_pointer(event->button.window, &x, &y, &modifier);
  printf("button event x=%d y=%d org_x=%d org_y=%d modifier=%x\n",x,y,origin_x,origin_y, modifier);
  event->button.x = x;
  event->button.y = y;
  event->button.x_root = x + origin_x;
  event->button.y_root = y + origin_y;
  event->button.axes = NULL;
  event->button.state = modifier;
  event->button.button = 1;
  event->button.device = gdk_device_get_core_pointer();

  event->button.type = GDK_BUTTON_PRESS;
  gdk_event_put(event);

  /* Also send a release event.*/
  GdkEvent* release_event = gdk_event_copy(event);
  release_event->button.type = GDK_BUTTON_RELEASE;
  release_event->button.time++;
  gdk_event_put(release_event);

  gdk_event_free(event);
  gdk_event_free(release_event);

  return false;
}

static void mouse_move(int dx, int dy){
                GdkDisplay *display=gdk_display_get_default();
                GdkScreen *screen=gdk_screen_get_default();
		gint x,y,wx,wy, win_x,win_y;
		GdkWindow *win=gdk_window_at_pointer(&win_x,&win_y);
		gdk_window_get_pointer(win,&win_x,&win_y,NULL);
		gdk_window_get_origin (win,&wx,&wy);
		printf("mouse move from %d %d ",wx+win_x,wy+win_y);		
		printf(" (winpos %d %d)",wx,wy);
		x=wx+win_x+dx;
		y=wy+win_y+dy;		
		printf(" to %d %d\n",x,y);
		gdk_display_warp_pointer(display,screen ,
                                 x,y);
}
typedef unsigned char           u_char;
typedef unsigned short          u_short;
typedef unsigned int            u_int;
typedef unsigned long           u_long;
/*#include <linux/types.h>*/
#include <sys/ioctl.h>
#include <fcntl.h>
#include <directfb.h>
#include <linux/fb.h>
#include <linux/einkfb.h>

typedef void (*DirectFB_AddDirtyRectangle_Fct) (const DFBRectangle *rect);
extern void kindle_set_dirty_rectangle_cb(DirectFB_AddDirtyRectangle_Fct fct);
extern DirectFB_AddDirtyRectangle_Fct kindle_get_dirty_rectangle_cb();
extern DFBResult kindle_get_framebuffer(u8 **fb, u8 **virtualFb, int *width, int *height);
static int fd=-1;
static int dirtyCount=0;
static void myDirtyRectUpdate(int x1,int y1,int x2,int y2,fx_type fxtype){
	u8 *fb, *vfb, *src,*dst;
	int fb_w,fb_h;
	int ret;
	int x,y;
	int fullupdateThreshold;
	update_area_t data;
	ret=kindle_get_framebuffer(&fb,&vfb, &fb_w, &fb_h);
	fullupdateThreshold=fb_w*fb_h*20;
	if(ret!=0) return;
	int diff;	
	unsigned int a,b; 
	x1=(x1>>1)<<1;
	if(x2&1) x2++;
	if(x2>fb_w) x2=fb_w;
	if(y2>fb_h) y2=fb_h;
	if(x1<0) x1=0;
	if(y1<0) y1=0;
	#define NEXT_BYTE { \
			       a=*(src++);\
			       b=*(src++);\
                               *(dst++)=(a&0xf0)|(b>>4);}
	
	if(x2-x1==fb_w) {
	   diff=y1*fb_w;
	   src=vfb+diff;
	   dst=fb+(diff/2);	   
	   for(y=y1;y<y2;y++)
		for(x=0;x<fb_w;x+=2) 
			NEXT_BYTE		
	}
	else{
	   for(y=y1;y<y2;y++){
		diff=y*fb_w+x1;
	   	src=vfb+diff;
	   	dst=fb+(diff/2);
		for(x=x1;x<x2;x+=2) NEXT_BYTE
	   }
	}
	if(fd==-1)
		fd = open("/dev/fb/0",O_RDWR);
	if(fxtype==fx_update_partial) dirtyCount+=(x2-x1)*(y2-y1);
	if(dirtyCount>fullupdateThreshold){
		printf("full update ---------------------------------------------------------------\n");
		dirtyCount=0;
		data.x1=0;
		data.y1=0;
		data.x2=fb_w;
		data.y2=fb_h;
		data.which_fx=fx_update_full;
		data.buffer = NULL;
		ioctl(fd,FBIO_EINK_UPDATE_DISPLAY_AREA,&data);	
	}
	else{
		data.x1=x1;
		data.y1=y1;
		data.x2=x2;
		data.y2=y2;
		data.which_fx=fxtype;
		data.buffer = NULL;
		ioctl(fd,FBIO_EINK_UPDATE_DISPLAY_AREA,&data);	
	}
}

static void einkfb_full_update(int x1,int y1,int x2, int y2){
	myDirtyRectUpdate(x1,y1,x2,y2,fx_flash);
/*	ioctl(fd,FBIO_EINK_UPDATE_DISPLAY_AREA,&data);	*/
}
static void myDirtyRectHandler(const DFBRectangle *rect){
	int x2=rect->x+rect->w;
	int y2=rect->y+rect->h;
	myDirtyRectUpdate(rect->x,rect->y,x2,y2,fx_update_partial);
}
static char num_symbol_tbl[10]=")!@#$%^&*(";
static gboolean
key_event_cb (GtkWidget *window,
              GdkEventKey *event)
{
    bool bHandled = false;
printf("Key press %d\n", event->keyval);
    /* Event requiring a modifier */
    guint keyval = event->keyval;
   if (event->state & GDK_SHIFT_MASK){ /*Shift Mask*/
		if(keyval<=GDK_9 && keyval>=GDK_0){			
			keyval=event->keyval=num_symbol_tbl[keyval-GDK_0];
			event->state^=GDK_SHIFT_MASK;
		}
}
    if(keyval==GDK_KP_Tab) keyval=event->keyval=GDK_Tab;
    if (event->state & GDK_MOD1_MASK) { /* ALT_MASK */
        if (keyval == GDK_z) { /* ALT+z -> zoom out */
            webkit_web_view_set_zoom_level(web_view, webkit_web_view_get_zoom_level(web_view) * 0.8);
            bHandled = true;
        } else if (keyval == GDK_a) { /* ALT+a -> zoom in */
            webkit_web_view_set_zoom_level(web_view, webkit_web_view_get_zoom_level(web_view) * 1.2);
            bHandled = true;
	} else if (keyval == GDK_x) { /* ALT+x -> exit */
		gtk_main_quit();
		bHandled = true;
	} else if (keyval == GDK_l) { /* ALT+l -> Refresh screen */
			einkfb_full_update(0,0,gScreenWidth,gScreenHeight);
			bHandled = true;
	} else if (keyval == GDK_s) { /* ALT+s -> snap shot */
			u8 *fb, *vfb, *src,*dst;
			int fb_w,fb_h,i;
			int ret;
			ret=kindle_get_framebuffer(&fb,&vfb, &fb_w, &fb_h);
			GdkPixbuf *pixbuf= gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, 824,1200);
			dst=gdk_pixbuf_get_pixels(pixbuf);
			for(i=0;i<824*1200;i++)
				dst[3*i]=dst[3*i+1]=dst[3*i+2]=255-vfb[i];						
			gdk_pixbuf_savev(pixbuf, "/tmp/tmp.png", "png",  NULL, NULL, NULL);
			g_object_unref(pixbuf); 
			bHandled = true;
	}
	else if (keyval == GDK_w) { /* ALT+w -> startWan */
			system("/usr/sbin/startWan");
			bHandled = true;
	}
    }
   else if (event->state & GDK_SHIFT_MASK){
	if (keyval == GDK_Home) { /* SHIFT+HOME -> Reload */
		webkit_web_view_reload (web_view);		
		bHandled = true;
	}
         if (keyval == GDK_Up) { 
		mouse_move(0,-24);
		bHandled = true;
	}
         else if (keyval == GDK_Down) { 
		mouse_move(0,24);
		bHandled = true;
	}
         else if (keyval == GDK_Right) { 
		mouse_move(16,0);
		bHandled = true;
	}
         else if (keyval == GDK_Left) { 
		mouse_move(-16, 0);
		bHandled = true;
	}
  }
   else{
		if (keyval == GDK_Home) { /* Go back to first element in history */
			WebKitWebBackForwardList *pHistory = webkit_web_view_get_back_forward_list (web_view);
			gint steps = webkit_web_back_forward_list_get_back_length (pHistory);
			webkit_web_view_go_back_or_forward (web_view, -steps);
			bHandled = true;
		}
		else if (keyval == GDK_Select) { 
			SendMouseClick();
			bHandled=true;
		}
		else if (keyval == 0xffc8 /*Back*/) { 			
    			webkit_web_view_go_back (web_view);
			bHandled=true;
		}
		else if (keyval == GDK_Menu) { 			    			
    			gtk_widget_grab_focus (GTK_WIDGET (uri_entry));
			bHandled=true;
		}
    }

    return bHandled;
}

#if 0
void exit(int __status);

static void
link_edge_reached_cb (GtkWidget* widget, GtkDirectionType direction, gpointer data) {
    printf("Edge reached after: %s\n", direction == GTK_DIR_LEFT ? "left" : ((direction == GTK_DIR_RIGHT)? "right" : (direction == GTK_DIR_UP ? "up" : "down")));
}

static gboolean
key_event_cb (GtkWidget *window,
              GdkEventKey *event)
{

    /* Example on how to overwrite default WebKit behavior for keyboard
     * events, it's possible to modify the event and continue it's
     * propagation (returning FALSE) or just doing something else and
     * stop the propagation (returning TRUE).
	 */

	/* To remove once the key mapping in X is fixed */
#if defined(__arm__) && !defined(DIRECTFB)
	switch (event->hardware_keycode) {
		case 0x64: event->keyval = GDK_Select; break;
		case 0x82: event->keyval = GDK_Up; break;
		case 0x83: event->keyval = GDK_Down; break;
		case 0x84: event->keyval = GDK_Page_Down; break;
		case 0x75: event->keyval = GDK_Page_Up; break;
        case 0x62: event->keyval = GDK_Tab; break; 
	}
#endif

	/* Keys that have been handled in this function are not dispatched to the DOM */
	bool bHandled = false;
printf("Key press\n");
	/* Event requiring a modifier */
	guint keyval = event->keyval;
	if (event->state & GDK_SHIFT_MASK) {
		if (keyval == GDK_Home) { /* SHIFT+HOME -> Reload */
			webkit_web_view_reload (web_view);		
			bHandled = true;
		}
	} else if (event->state & GDK_MOD1_MASK) { /* ALT_MASK */
		if (keyval == GDK_F11) { /* ALT+BACK -> Forward */
			webkit_web_view_go_forward (web_view);
			bHandled = true;
		} else if (keyval == GDK_l) { /* ALT+l -> Refresh screen */
			system("echo 2 > /proc/eink_fb/update_display");
			bHandled = true;
		} else if (keyval == GDK_1) { /* ALT+1 -> reset focus */
            webkit_web_view_focus(web_view, eFocusReset);
			bHandled = true;
		} else if (keyval == GDK_2) { /* ALT+2 -> hide focus */
            webkit_web_view_focus(web_view, eFocusHide);
			bHandled = true;
		} else if (keyval == GDK_3) { /* ALT+3 -> show focus*/
            webkit_web_view_focus(web_view, eFocusShow);
			bHandled = true;
        } else if (keyval == GDK_4) { /* ALT+4 -> zoom in */
            webkit_web_view_set_zoom_level(web_view, webkit_web_view_get_zoom_level(web_view) * 0.8);
            bHandled = true;
        } else if (keyval == GDK_5) { /* ALT+5 -> zoom out */
            webkit_web_view_set_zoom_level(web_view, webkit_web_view_get_zoom_level(web_view) * 1.2);
            bHandled = true;
        } 
	} else if (event->state == 0) {
		if (keyval == GDK_Home) { /* Go back to first element in history */
			WebKitWebBackForwardList *pHistory = webkit_web_view_get_back_forward_list (web_view);
			gint steps = webkit_web_back_forward_list_get_back_length (pHistory);
			webkit_web_view_go_back_or_forward (web_view, -steps);
			bHandled = true;
		}
	}

	return bHandled;
}

/* Use this function for any keys that can be overridden by webkit (in other words JavaScript) */
static gboolean
key_event_after_cb (GtkWidget *window,
					GdkEventKey *event)
{
	/* Keys that have been handled in this function are not dispatched to the DOM */
	bool bHandled = false;

	/* Event requiring a modifier */
	guint keyval = event->keyval;
	if (event->state == 0) {
		if (keyval == GDK_F11) {  
			webkit_web_view_go_back (web_view);
			bHandled = true;
		}
	}

	return bHandled;
}
#endif 
static void
download_notify_progress_cb (GObject* object, GParamSpec* pspec, gpointer data)
{
    WebKitDownload* download = WEBKIT_DOWNLOAD(object);
    gdouble download_progress = 100*webkit_download_get_progress (download);
    if (download_progress < 100){
	statusCharIndex=(statusCharIndex+1)%8;
        status_printf ("Downloaded (%4.1f%%) %c", download_progress, statusChar[statusCharIndex]);
   }
	else
        status_printf ("Download completed");
}

static void
download_notify_status_cb(GObject* object, GParamSpec* pspec, gpointer data)
{
    WebKitDownload* download = WEBKIT_DOWNLOAD(object);
    switch (webkit_download_get_status(download)) {
    case WEBKIT_DOWNLOAD_STATUS_FINISHED:
	g_print("finished\n");
	break;
    case WEBKIT_DOWNLOAD_STATUS_ERROR:
	g_print("error\n");
        break;
    case WEBKIT_DOWNLOAD_STATUS_CANCELLED:
	g_print("cancelled\n");
        break;
    default:
        break;
    }
}
gboolean            download_error_cb                      (WebKitDownload *download,
                                                        gint            error_code,
                                                        gint            error_detail,
                                                        gchar          *reason,
                                                        gpointer        user_data)   {
		g_print("download error %d %d %s\n", error_code, error_detail, reason);
	return TRUE;
}
static gboolean
download_requested_cb(WebKitWebView* web_view,
                      WebKitDownload* download,
                      gpointer data)
{
   GString *gstr=g_string_new("/mnt/us/documents/download/");
    g_print("download request %s\n", webkit_download_get_suggested_filename(download));
    g_string_append(gstr,  webkit_download_get_suggested_filename(download));
    gchar *uri_str=g_string_free(gstr,FALSE);
    gchar *uri = g_filename_to_uri(uri_str, NULL, NULL);
    g_free(uri_str);
     if (uri)
            webkit_download_set_destination_uri(download, uri);
    else
	return FALSE;
    g_free(uri);
    g_signal_connect(download, "notify::progress",
                     G_CALLBACK(download_notify_progress_cb), NULL);
    g_signal_connect(download, "notify::status",
                     G_CALLBACK(download_notify_status_cb), NULL);
    g_signal_connect(download, "error",
                     G_CALLBACK(download_error_cb), NULL);
    return TRUE;
}
gboolean mime_policy_decision_cb (WebKitWebView *web_view, WebKitWebFrame *frame,
WebKitNetworkRequest *request, gchar *mimetype, WebKitWebPolicyDecision
*policy_decision)
{
if (webkit_web_view_can_show_mime_type (WEBKIT_WEB_VIEW (web_view),mimetype))
        return FALSE;
webkit_web_policy_decision_download (policy_decision);
webkit_web_view_stop_loading (WEBKIT_WEB_VIEW (web_view));
return TRUE;
}
/* </lab126> */
gboolean            load_error_cb                      (WebKitWebView  *web_view,
                                                        WebKitWebFrame *web_frame,
                                                        gchar          *uri,
                                                        gpointer        web_error,
                                                        gpointer        user_data)  {
	status_printf("Failed to load %s\n", uri);
}
static GtkWidget*
create_browser ()
{
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    GtkWidget *tmp=webkit_web_view_new();
    web_view = WEBKIT_WEB_VIEW (tmp);
    gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view));
    g_signal_connect (web_view, "title-changed", G_CALLBACK (title_change_cb), web_view);
    g_signal_connect (web_view, "notify::load-status", G_CALLBACK (notify_load_status_cb), web_view);
    g_signal_connect (web_view, "notify::progress", G_CALLBACK (notify_progress_cb), web_view);
    g_signal_connect (web_view, "hovering-over-link", G_CALLBACK (link_hover_cb), web_view);
    g_signal_connect (web_view, "focus-on-link", G_CALLBACK (link_focus_cb), web_view);    
    g_signal_connect(web_view, "create-web-view", G_CALLBACK(create_web_view_cb), web_view);
    g_signal_connect(web_view, "download-requested", G_CALLBACK(download_requested_cb),web_view);
    g_signal_connect(web_view,"mime-type-policy-decision-requested", G_CALLBACK(mime_policy_decision_cb),web_view);
    g_signal_connect(web_view,"load-error", G_CALLBACK(load_error_cb),web_view);
	/* <lab126> */
	g_signal_connect (web_view, "key-press-event", G_CALLBACK (key_event_cb), web_view);
#if 0
	g_signal_connect_after (web_view, "key-press-event", G_CALLBACK (key_event_after_cb), web_view);
    g_signal_connect (web_view, "link-edge-reached", G_CALLBACK (link_edge_reached_cb), web_view);
#endif
    /* Set settings preferences */
/*    This turns on the caret display within the web page.
      However, it creates a conflict with the code that handles link walking out of text input*/
    WebKitWebSettings *web_settings = webkit_web_view_get_settings (web_view);
    /*g_object_set(G_OBJECT (web_settings), "enable-caret-browsing", TRUE, NULL);*/
    g_object_set(G_OBJECT (web_settings), "tab-key-cycles-through-elements", TRUE, NULL);
    g_object_set(G_OBJECT (web_settings), "default-encoding", "utf8", NULL);
    return scrolled_window;
}

static GtkWidget*
create_statusbar ()
{
    main_statusbar = GTK_STATUSBAR (gtk_statusbar_new ());
    status_context_id = gtk_statusbar_get_context_id (main_statusbar, "Link Hover");

    return (GtkWidget*)main_statusbar;
}

static GtkWidget*
create_toolbar ()
{
    toolbar = gtk_toolbar_new ();

    gtk_toolbar_set_orientation (GTK_TOOLBAR (toolbar), GTK_ORIENTATION_HORIZONTAL);
    gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH_HORIZ);

    GtkToolItem* item;

    /* the back button */
    item = gtk_tool_button_new_from_stock (GTK_STOCK_GO_BACK);
    g_signal_connect (G_OBJECT (item), "clicked", G_CALLBACK (go_back_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1);

    /* The forward button */
    item = gtk_tool_button_new_from_stock (GTK_STOCK_GO_FORWARD);
    g_signal_connect (G_OBJECT (item), "clicked", G_CALLBACK (go_forward_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1);

    /* The URL entry */
    item = gtk_tool_item_new ();
    gtk_tool_item_set_expand (item, TRUE);
    uri_entry = gtk_entry_new ();
    gtk_container_add (GTK_CONTAINER (item), uri_entry);
    g_signal_connect (G_OBJECT (uri_entry), "activate", G_CALLBACK (activate_uri_entry_cb), NULL);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1);

    /* The go button */
    item = gtk_tool_button_new_from_stock (GTK_STOCK_OK);
    g_signal_connect_swapped (G_OBJECT (item), "clicked", G_CALLBACK (activate_uri_entry_cb), (gpointer)uri_entry);
    gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1);

    return toolbar;
}

static GtkWidget*
create_window ()
{
    GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
/* <lab126> */
	/* Take the whole screen size */
    GtkWindow *gtkwindow = GTK_WINDOW(window);
	GdkScreen* screen = gtk_window_get_screen(gtkwindow);
	gtk_window_set_default_size (gtkwindow, gScreenWidth ? gScreenWidth : gdk_screen_get_width(screen), gScreenHeight ? gScreenHeight : gdk_screen_get_height(screen));
/* </lab126> */
    gtk_widget_set_name (window, "GtkLauncher");
    g_signal_connect (window, "destroy", G_CALLBACK (destroy_cb), NULL);

    return window;
}
static char *xfsn=NULL;
static char *user_agent=
"Mozilla/5.0 (compatible; Linux 2.6.22) AppleWebKit/528.5+ (KHTML, like Gecko, Safari/528.5+) Kindle/2.5 (screen 824x1200; rotate)";
/*
User-Agent of Kindle DX Web Browser
"Mozilla/4.0 (compatible; Linux 2.6.22) NetFront/3.4 Kindle/2.5 (screen 824x1200; rotate)";*/

void                request_started                      (SoupSession *session,
                                                        SoupMessage *msg,
                                                        SoupSocket  *socket,
                                                        gpointer     user_data)     {
	if(xfsn){
	soup_message_headers_append (msg->request_headers,"x-fsn", xfsn);
	soup_message_headers_append (msg->request_headers,"x-appNamespace", "WEB_BROWSER");
	soup_message_headers_append (msg->request_headers,"x-appId","Kindle_2.5");
        }
	if(soup_message_headers_get_one (msg->request_headers,"User-Agent")){
		soup_message_headers_replace (msg->request_headers,"User-Agent",user_agent);
	}
	else{
		soup_message_headers_append (msg->request_headers,"User-Agent",user_agent);
	}
	soup_message_headers_append (msg->request_headers,"Accept-Language", "zh-tw en");
}
int
main (int argc, char* argv[])
{
	/* <lab126> */
	int opt;
    opterr = 0;
	while ((opt = getopt (argc, argv, "d:w:h:")) != -1) {
		switch (opt) {
		case 'd':
				if (!strcmp(optarg, "turing")) {
					gScreenWidth = 600;
					gScreenHeight = 800;
				} else if (!strcmp(optarg, "nell")) {
					gScreenWidth = 824;
					gScreenHeight = 1200;
				}
				break;
			case 'w': gScreenWidth = atoi(optarg); break;
			case 'h': gScreenHeight = atoi(optarg); break;
			case '?':
				fprintf(stderr, "Usage: GtkLauncher [-d turing] [-w width] [h height] [uri]\n");
				fprintf(stderr, "-d turing sets width/height to turing screen size\n");
				exit (1);
			default: break;
		}
	}
	/* </lab126> */
/*    <tjw>*/
    char* proxy=getenv("http_proxy");
    if(getenv("user_agent"))
	user_agent=getenv("user_agent");
    if(getenv("x_fsn"))
	xfsn=getenv("x_fsn");
    else{
	printf("please set enviroment variable x_fsn\n");
    }
/*</tjw>*/
    gtk_init (&argc, &argv);
    if (!g_thread_supported ()){
	printf("g_thread\n");
        g_thread_init (NULL);
      }
    kindle_set_dirty_rectangle_cb(myDirtyRectHandler);

    /*gdk_window_set_debug_updates(true); */
    GtkWidget* vbox = gtk_vbox_new (FALSE, 0);

/* ToFix: the toolbar creates an issue with the highlight */
    gtk_box_pack_start (GTK_BOX (vbox), create_toolbar (), FALSE, FALSE, 0); 
    gtk_box_pack_start (GTK_BOX (vbox), create_browser (), TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), create_statusbar (), FALSE, FALSE, 0);

    main_window = create_window ();
    gtk_container_add (GTK_CONTAINER (main_window), vbox);
    webkit_web_view_set_full_content_zoom(web_view, 1);
    SoupSession* session = webkit_get_default_session();
    if(proxy) {
       printf("Setting proxy as %s\n", proxy);
       SoupURI* pURI = soup_uri_new(proxy);
       g_object_set(G_OBJECT(session), "proxy-uri", pURI, NULL );
       if (pURI) soup_uri_free(pURI);
       g_object_set(G_OBJECT(session), "ssl-strict", FALSE, NULL );
    } else {
       printf("Proxy is not set\n");
    }
    g_signal_connect(G_OBJECT(session), "request-started", G_CALLBACK(request_started), NULL);    
    gchar *uri = (gchar*) (optind < argc ? argv[optind] : "http://www.google.com/");
    webkit_web_view_open (web_view, uri);
    gtk_widget_grab_focus (GTK_WIDGET (web_view));
    gtk_widget_show_all (main_window);
    gtk_main ();
    return 0;
}
