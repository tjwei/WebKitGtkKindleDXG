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


#include "gqview.h"
#include "remote.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <errno.h>


#define SERVER_MAX_CLIENTS 8

#define REMOTE_SERVER_BACKLOG 4


#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX 108
#endif


typedef struct _RemoteClient RemoteClient;
struct _RemoteClient {
	gint fd;
	gint channel_id;
	RemoteConnection *rc;
};


static gboolean remote_server_client_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
	RemoteClient *client = data;
	RemoteConnection *rc;

	rc = client->rc;

	if (condition & G_IO_IN)
		{
		GList *queue = NULL;
		GList *work;
		gchar *buffer = NULL;
		GError *error = NULL;
		guint termpos;

		while (g_io_channel_read_line(source, &buffer, NULL, &termpos, &error) == G_IO_STATUS_NORMAL)
			{
			if (buffer)
				{
				buffer[termpos] = '\0';

				if (strlen(buffer) > 0)
					{
					queue = g_list_append(queue, buffer);
					}
				else
					{
					g_free(buffer);
					}

				buffer = NULL;
				}
			}

		if (error)
			{
			printf("error reading socket: %s\n", error->message);
			g_error_free(error);
			}

		work = queue;
		while (work)
			{
			gchar *command = work->data;
			work = work->next;

			if (rc->read_func) rc->read_func(rc, command, rc->read_data);
			g_free(command);
			}

		g_list_free(queue);
		}

	if (condition & G_IO_HUP)
		{
		rc->clients = g_list_remove(rc->clients, client);

		if (debug)
			{
			printf("HUP detected, closing client.\n");
			printf("client count %d\n", g_list_length(rc->clients));
			}

		g_source_remove(client->channel_id);
		close(client->fd);
		g_free(client);
		}

	return TRUE;
}

static void remote_server_client_add(RemoteConnection *rc, int fd)
{
	RemoteClient *client;
	GIOChannel *channel;

	if (g_list_length(rc->clients) > SERVER_MAX_CLIENTS)
		{
		printf("maximum remote clients of %d exceeded, closing connection\n", SERVER_MAX_CLIENTS);
		close(fd);
		return;
		}

	client = g_new0(RemoteClient, 1);
	client->rc = rc;
	client->fd = fd;

	channel = g_io_channel_unix_new(fd);
	client->channel_id = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, G_IO_IN | G_IO_HUP,
						 remote_server_client_cb, client, NULL);
	g_io_channel_unref(channel);

	rc->clients = g_list_append(rc->clients, client);
	if (debug) printf("client count %d\n", g_list_length(rc->clients));
}

static void remote_server_clients_close(RemoteConnection *rc)
{
	while (rc->clients)
		{
		RemoteClient *client = rc->clients->data;

		rc->clients = g_list_remove(rc->clients, client);

		g_source_remove(client->channel_id);
		close(client->fd);
		g_free(client);
		}
}

static gboolean remote_server_read_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
	RemoteConnection *rc = data;
	int fd;
	unsigned int alen;

	fd = accept(rc->fd, NULL, &alen);
	if (fd == -1)
		{
		printf("error accepting socket: %s\n", strerror(errno));
		return TRUE;
		}

	remote_server_client_add(rc, fd);

	return TRUE;
}

static gint remote_server_exists(const gchar *path)
{
	RemoteConnection *rc;

	/* verify server up */
	rc = remote_client_open(path);
	remote_close(rc);

	if (rc) return TRUE;

	/* unable to connect, remove socket file to free up address */
	unlink(path);
	return FALSE;
}

RemoteConnection *remote_server_open(const gchar *path)
{
	RemoteConnection *rc;
	struct sockaddr_un addr;
	gint sun_path_len;
	int fd;
	GIOChannel *channel;

	if (remote_server_exists(path))
		{
		printf("Address already in use: %s\n", path);
		return NULL;
		}

	fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (fd == -1) return NULL;

	addr.sun_family = AF_UNIX;
	sun_path_len = MIN(strlen(path) + 1, UNIX_PATH_MAX);
	strncpy(addr.sun_path, path, sun_path_len);
	if (bind(fd, &addr, sizeof(addr)) == -1 ||
	    listen(fd, REMOTE_SERVER_BACKLOG) == -1)
		{
		printf("error subscribing to socket: %s\n", strerror(errno));
		close(fd);
		return NULL;
		}

	rc = g_new0(RemoteConnection, 1);
	rc->server = TRUE;
	rc->fd = fd;
	rc->path = g_strdup(path);

	rc->read_func = NULL;
	rc->read_data = NULL;

	rc->clients = NULL;

	channel = g_io_channel_unix_new(rc->fd);
	rc->channel_id = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, G_IO_IN,
					     remote_server_read_cb, rc, NULL);
	g_io_channel_unref(channel);

	return rc;
}

void remote_server_subscribe(RemoteConnection *rc, RemoteReadFunc *func, gpointer data)
{
	if (!rc || !rc->server) return;

	rc->read_func = func;
	rc->read_data = data;
}


RemoteConnection *remote_client_open(const gchar *path)
{
	RemoteConnection *rc;
	struct stat st;
	struct sockaddr_un addr;
	gint sun_path_len;
	int fd;

	if (stat(path, &st) != 0 || !S_ISSOCK(st.st_mode)) return NULL;

	fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (fd == -1) return NULL;

	addr.sun_family = AF_UNIX;
	sun_path_len = MIN(strlen(path) + 1, UNIX_PATH_MAX);
	strncpy(addr.sun_path, path, sun_path_len);
	if (connect(fd, &addr, sizeof(addr)) == -1)
        	{
		if (debug) printf("error connecting to socket: %s\n", strerror(errno));
	        close(fd);
        	return NULL;
	        }

	rc = g_new0(RemoteConnection, 1);
	rc->server = FALSE;
	rc->fd = fd;
	rc->path = g_strdup(path);

	return rc;
}

static sig_atomic_t sigpipe_occured = FALSE;

static void sighandler_sigpipe(int sig)
{
	sigpipe_occured = TRUE;
}

gint remote_client_send(RemoteConnection *rc, const gchar *text)
{
	struct sigaction new_action, old_action;
	gint ret = FALSE;

	if (!rc || rc->server) return FALSE;
	if (!text) return TRUE;

	sigpipe_occured = FALSE;

	new_action.sa_handler = sighandler_sigpipe;
	sigemptyset (&new_action.sa_mask);
	new_action.sa_flags = 0;

	/* setup our signal handler */
	sigaction (SIGPIPE, &new_action, &old_action);

	if (write(rc->fd, text, strlen(text)) == -1 ||
	    write(rc->fd, "\n", 1) == -1)
		{
		if (sigpipe_occured)
			{
			printf("SIGPIPE writing to socket: %s\n", rc->path);
			}
		else
			{
			printf("error writing to socket: %s\n", strerror(errno));
			}
		ret = FALSE;;
		}
	else
		{
		ret = TRUE;
		}

	/* restore the original signal handler */
	sigaction (SIGPIPE, &old_action, NULL);

	return ret;
}

void remote_close(RemoteConnection *rc)
{
	if (!rc) return;

	if (rc->server)
		{
		remote_server_clients_close(rc);

		g_source_remove(rc->channel_id);
		unlink(rc->path);
		}

	close(rc->fd);

	g_free(rc->path);
	g_free(rc);
}


