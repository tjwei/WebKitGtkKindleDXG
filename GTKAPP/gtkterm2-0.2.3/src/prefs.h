
#ifndef __PREFS_H_
#define __PREFS_H_

#define MAX_LINE_LENGTH 512

typedef struct _MPREF gtkTermMPref;
struct _MPREF
{
	char match[MAX_LINE_LENGTH];
	char worldClass[MAX_LINE_LENGTH];
	int scrollOnKeyStroke;
	int scrollOnOutput;
	int blink;
	int beep;
	GdkColor colors[16];
	GdkColor fore[1];
	GdkColor back[1];
};

typedef struct _PREF gtkTermPref;
struct _PREF
{
	GtkWidget* notebook;
	gint nbpage;

	GtkPositionType notebookPanel;
	GtkPositionType terminalScrollbar;
	int maxScrollbackBuffer;
	int quitPRGonExitLastTerminal;
	int showTabsByOneTerminal;
	int scrollOnKeyStroke;
	int scrollOnOutput;
	int blink;
	int beep;
	int termX;
	int termY;
	int login_shell;
	int fullscreen;
	int winPosX;
	int winPosY;
	int transparent;
	int stealth;
	float opacity;
	GdkColor colors[16];
	GdkColor fore[1];
	GdkColor back[1];
	char terminalFont[MAX_LINE_LENGTH];
	char worldClass[MAX_LINE_LENGTH];
	gtkTermMPref **mpref;
	int mprefSize;

	GSList* termProp;
};

gtkTermPref* gtkTermPref_get (void);
gtkTermMPref* gtkTermMPref_init(gtkTermPref* pref);
int gtkTermFindMPref(char *matchstr, gtkTermPref *pref);
void gtkTermSetMPref(GtkWidget *term, gtkTermPref *pref, int i);


#endif
