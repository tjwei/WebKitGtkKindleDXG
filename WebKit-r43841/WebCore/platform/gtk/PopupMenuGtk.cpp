/*
 * This file is part of the popup menu implementation for <select> elements in WebCore.
 *
 * Copyright (C) 2006, 2007, 2008 Apple Inc. All rights reserved.
 * Copyright (C) 2006 Michael Emmel mike.emmel@gmail.com
 * Copyright (C) 2008 Collabora Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "PopupMenu.h"

#include "CString.h"
#include "FrameView.h"
#include "HostWindow.h"
#include "PlatformString.h"
#include <gtk/gtk.h>

namespace WebCore {

PopupMenu::PopupMenu(PopupMenuClient* client)
    : m_popupClient(client)
    , m_popup(0)
{
}

PopupMenu::~PopupMenu()
{
    if (m_popup)
        g_object_unref(m_popup);
}

void PopupMenu::show(const IntRect& rect, FrameView* view, int index)
{
    ASSERT(client());

    if (!m_popup) {
        m_popup = GTK_MENU(gtk_menu_new());
        g_object_ref_sink(G_OBJECT(m_popup));
        g_signal_connect(m_popup, "unmap", G_CALLBACK(menuUnmapped), this);
// <lab126>
        g_signal_emit_by_name(view->hostWindow()->platformWindow(), "drop-down-menu", m_popup);
// </lab126>
    } else
        gtk_container_foreach(GTK_CONTAINER(m_popup), reinterpret_cast<GtkCallback>(menuRemoveItem), this);


    int x, y, wHeight;
    gdk_window_get_origin(GTK_WIDGET(view->hostWindow()->platformWindow())->window, &x, &y);
    gdk_window_get_geometry(GTK_WIDGET(view->hostWindow()->platformWindow())->window, NULL, NULL, NULL, &wHeight, NULL);
    m_menuPosition = view->contentsToWindow(rect.location());
  //  m_menuPosition = IntPoint(m_menuPosition.x() + x, m_menuPosition.y() + y + rect.height());
    m_indexMap.clear();

    const int size = client()->listSize();
    for (int i = 0; i < size; ++i) {
        GtkWidget* item;
        if (client()->itemIsSeparator(i)) {
            item = gtk_separator_menu_item_new();
        } else {
            item = gtk_menu_item_new_with_label(client()->itemText(i).utf8().data());
        }

        m_indexMap.add(item, i);
        g_signal_connect(item, "activate", G_CALLBACK(menuItemActivated), this);

        // FIXME: Apply the PopupMenuStyle from client()->itemStyle(i)
        gtk_widget_set_sensitive(item, client()->itemIsEnabled(i));
        gtk_menu_shell_append(GTK_MENU_SHELL(m_popup), item);
        gtk_widget_show(item);
    }

    gtk_menu_set_active(m_popup, index);


    // The size calls are directly copied from gtkcombobox.c which is LGPL
    GtkRequisition requisition;
    gtk_widget_set_size_request(GTK_WIDGET(m_popup), -1, -1);
    gtk_widget_size_request(GTK_WIDGET(m_popup), &requisition);
    gtk_widget_set_size_request(GTK_WIDGET(m_popup), MAX(rect.width(), requisition.width), -1);
    // <lab126>: Position the menu items such that there are no empty spaces and also make sure that 
    // the previously selected item stays visible. 
    if ( requisition.height > wHeight) {
        GList* children = GTK_MENU_SHELL(m_popup)->children;
        GtkWidget* item = reinterpret_cast<GtkWidget*>(children->data);
        GtkRequisition itemRequisition;
        gtk_widget_get_child_requisition(item, &itemRequisition);
        int itemHeight = itemRequisition.height;
        // Move the items up until the indexed item fits in to the visible part of the window
        // Count out the two scoll items from the window height
        if ( ( itemHeight * ( index + 1 ) ) >  ( wHeight -  (2 * itemHeight ) ) ) {
            int itemsToRemove = ( ( (itemHeight * index  ) -   ( wHeight -  (2 * itemHeight ) )  ) / itemHeight );
            if (size)
                m_menuPosition.setY(y - ( ( itemsToRemove + 1 ) * itemHeight ) );

        } else
               // Place the first item at the top of window
               m_menuPosition.setY(y);

    }

    // </lab126> 
    gtk_menu_popup(m_popup, NULL, NULL, reinterpret_cast<GtkMenuPositionFunc>(menuPositionFunction), this, 0, gtk_get_current_event_time());
}

void PopupMenu::hide()
{
    ASSERT(m_popup);
    gtk_menu_popdown(m_popup);
}

void PopupMenu::updateFromElement()
{
    client()->setTextFromItem(client()->selectedIndex());
}

bool PopupMenu::itemWritingDirectionIsNatural()
{
    return true;
}

void PopupMenu::menuItemActivated(GtkMenuItem* item, PopupMenu* that)
{
    ASSERT(that->client());
    ASSERT(that->m_indexMap.contains(GTK_WIDGET(item)));
    that->client()->valueChanged(that->m_indexMap.get(GTK_WIDGET(item)));
}

void PopupMenu::menuUnmapped(GtkWidget*, PopupMenu* that)
{
    ASSERT(that->client());
    that->client()->hidePopup();
}

void PopupMenu::menuPositionFunction(GtkMenu*, gint* x, gint* y, gboolean* pushIn, PopupMenu* that)
{
    *x = that->m_menuPosition.x();
    *y = that->m_menuPosition.y();
    *pushIn = true;
}

void PopupMenu::menuRemoveItem(GtkWidget* widget, PopupMenu* that)
{
    ASSERT(that->m_popup);
    gtk_container_remove(GTK_CONTAINER(that->m_popup), widget);
}

}

