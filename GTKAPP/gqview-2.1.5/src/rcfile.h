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


#ifndef RCFILE_H
#define RCFILE_H


gchar *quoted_value(const gchar *text);

void save_options(void);
void load_options(void);


#endif

