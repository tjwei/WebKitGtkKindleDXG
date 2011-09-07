/*
 * GQview
 * (C) 2004 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#ifndef REMOTE_H
#define REMOTE_H


typedef struct _RemoteConnection RemoteConnection;

typedef void RemoteReadFunc(RemoteConnection *rc, const char *text, gpointer data);

struct _RemoteConnection {
	gint server;
	int fd;
	gchar *path;

	gint channel_id;
	RemoteReadFunc *read_func;
	gpointer read_data;

	GList *clients;
};
                                                                                                                        
                                                                                                                        
RemoteConnection *remote_server_open(const gchar *path);
void remote_server_subscribe(RemoteConnection *rc, RemoteReadFunc *func, gpointer data);

RemoteConnection *remote_client_open(const gchar *path);
gint remote_client_send(RemoteConnection *rc, const gchar *text);

void remote_close(RemoteConnection *rc);


#endif

