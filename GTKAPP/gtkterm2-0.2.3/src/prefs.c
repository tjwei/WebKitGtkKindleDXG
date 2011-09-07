#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkprivate.h>

#include <vte/vte.h>

#include "prefs.h"

gtkTermPref* gtkTermPref_init(void)
{
	gtkTermPref* pref;

	pref = (gtkTermPref*) malloc(sizeof(gtkTermPref));

	pref->notebook = NULL;
	pref->nbpage = 0;
	pref->notebookPanel = 2;
	pref->terminalScrollbar = 2;
	pref->maxScrollbackBuffer = 999;
	pref->quitPRGonExitLastTerminal = TRUE;
	pref->showTabsByOneTerminal = FALSE;
	pref->scrollOnKeyStroke = TRUE;
	pref->scrollOnOutput = FALSE;
	pref->blink = TRUE;
	pref->beep = TRUE;
	pref->termX = 80;
	pref->termY = 25;
	pref->winPosX = 0;
	pref->winPosY = 0;
	pref->opacity = 0;
	pref->transparent = FALSE;
	pref->stealth = FALSE;
	pref->login_shell = FALSE;
	pref->fullscreen = FALSE;

	pref->fore[0].red =   0xcccc;
	pref->fore[0].green = 0xcccc;
	pref->fore[0].blue =  0xcccc;
	
	pref->back[0].red =   0x0000;
	pref->back[0].green = 0x0000;
	pref->back[0].blue =  0x0000;

	pref->colors[0].red   = 0x0000;
	pref->colors[0].green = 0x0000;
	pref->colors[0].blue  = 0x0000;

	pref->colors[1].red   = 0xaaaa;
	pref->colors[1].green = 0x0000;
	pref->colors[1].blue  = 0x0000;
	
	pref->colors[2].red   = 0x0000;
	pref->colors[2].green = 0xaaaa;
	pref->colors[2].blue  = 0x0000;
	
	pref->colors[3].red   = 0xaaaa;
	pref->colors[3].green = 0x5555;
	pref->colors[3].blue  = 0x0000;
	
	pref->colors[4].red   = 0x6666;
	pref->colors[4].green = 0x6666;
	pref->colors[4].blue  = 0xffff;
	
	pref->colors[5].red   = 0xaaaa;
	pref->colors[5].green = 0x0000;
	pref->colors[5].blue  = 0xaaaa;
	
	pref->colors[6].red   = 0x0000;
	pref->colors[6].green = 0xaaaa;
	pref->colors[6].blue  = 0xaaaa;
	
	pref->colors[7].red   = 0xcccc;
	pref->colors[7].green = 0xcccc;
	pref->colors[7].blue  = 0xcccc;

	pref->colors[8].red   = 0x5555;
	pref->colors[8].green = 0x5555;
	pref->colors[8].blue  = 0x5555;

	pref->colors[9].red   = 0xffff;
	pref->colors[9].green = 0x5555;
	pref->colors[9].blue  = 0x5555;

	pref->colors[10].red   = 0x5555;
	pref->colors[10].green = 0xffff;
	pref->colors[10].blue  = 0x5555;

	pref->colors[11].red   = 0xffff;
	pref->colors[11].green = 0xffff;
	pref->colors[11].blue  = 0x5555;

	pref->colors[12].red   = 0x5555;
	pref->colors[12].green = 0x5555;
	pref->colors[12].blue  = 0xffff;

	pref->colors[13].red   = 0xffff;
	pref->colors[13].green = 0x5555;
	pref->colors[13].blue  = 0xffff;

	pref->colors[14].red   = 0x5555;
	pref->colors[14].green = 0xffff;
	pref->colors[14].blue  = 0xffff;

	pref->colors[15].red   = 0xffff;
	pref->colors[15].green = 0xffff;
	pref->colors[15].blue  = 0xffff;

	strncpy(pref->terminalFont, "Terminal 8", MAX_LINE_LENGTH - 1);
	strncpy(pref->worldClass, "-A-Za-z0-9/_:.,?+%=", MAX_LINE_LENGTH - 1);
	
	pref->mprefSize = 0;
	pref->mpref = NULL;
	
	gtkTermMPref_init(pref);

	return pref;
}

gtkTermMPref* gtkTermMPref_init(gtkTermPref* pref)
{
	pref->mprefSize++;
	pref->mpref = (gtkTermMPref**) realloc(pref->mpref, sizeof(gtkTermMPref*) * (pref->mprefSize + 1));
	pref->mpref[pref->mprefSize] = (gtkTermMPref*) malloc(sizeof(gtkTermMPref));

	pref->mpref[pref->mprefSize]->match[0] = '\0';
	pref->mpref[pref->mprefSize]->scrollOnKeyStroke = TRUE;
	pref->mpref[pref->mprefSize]->scrollOnOutput = FALSE;
	pref->mpref[pref->mprefSize]->beep = TRUE;
	pref->mpref[pref->mprefSize]->blink = TRUE;
	strncpy(pref->mpref[pref->mprefSize]->worldClass, "-A-Za-z0-9/_:.,?+%=", MAX_LINE_LENGTH - 1);

	pref->mpref[pref->mprefSize]->fore[0].red =   0xcccc;
	pref->mpref[pref->mprefSize]->fore[0].green = 0xcccc;
	pref->mpref[pref->mprefSize]->fore[0].blue =  0xcccc;
	
	pref->mpref[pref->mprefSize]->back[0].red =   0x0000;
	pref->mpref[pref->mprefSize]->back[0].green = 0x0000;
	pref->mpref[pref->mprefSize]->back[0].blue =  0x0000;
	
	pref->mpref[pref->mprefSize]->colors[0].red   = 0x0000;
	pref->mpref[pref->mprefSize]->colors[0].green = 0x0000;
	pref->mpref[pref->mprefSize]->colors[0].blue  = 0x0000;

	pref->mpref[pref->mprefSize]->colors[1].red   = 0xaaaa;
	pref->mpref[pref->mprefSize]->colors[1].green = 0x0000;
	pref->mpref[pref->mprefSize]->colors[1].blue  = 0x0000;
	
	pref->mpref[pref->mprefSize]->colors[2].red   = 0x0000;
	pref->mpref[pref->mprefSize]->colors[2].green = 0xaaaa;
	pref->mpref[pref->mprefSize]->colors[2].blue  = 0x0000;
	
	pref->mpref[pref->mprefSize]->colors[3].red   = 0xaaaa;
	pref->mpref[pref->mprefSize]->colors[3].green = 0x5555;
	pref->mpref[pref->mprefSize]->colors[3].blue  = 0x0000;
	
	pref->mpref[pref->mprefSize]->colors[4].red   = 0x6666;
	pref->mpref[pref->mprefSize]->colors[4].green = 0x6666;
	pref->mpref[pref->mprefSize]->colors[4].blue  = 0xffff;
	
	pref->mpref[pref->mprefSize]->colors[5].red   = 0xaaaa;
	pref->mpref[pref->mprefSize]->colors[5].green = 0x0000;
	pref->mpref[pref->mprefSize]->colors[5].blue  = 0xaaaa;
	
	pref->mpref[pref->mprefSize]->colors[6].red   = 0x0000;
	pref->mpref[pref->mprefSize]->colors[6].green = 0xaaaa;
	pref->mpref[pref->mprefSize]->colors[6].blue  = 0xaaaa;
	
	pref->mpref[pref->mprefSize]->colors[7].red   = 0x0000;
	pref->mpref[pref->mprefSize]->colors[7].green = 0xcccc;
	pref->mpref[pref->mprefSize]->colors[7].blue  = 0x0000;
	
	pref->mpref[pref->mprefSize]->colors[8].red   = 0x5555;
	pref->mpref[pref->mprefSize]->colors[8].green = 0x5555;
	pref->mpref[pref->mprefSize]->colors[8].blue  = 0x5555;

	pref->mpref[pref->mprefSize]->colors[9].red   = 0xffff;
	pref->mpref[pref->mprefSize]->colors[9].green = 0x5555;
	pref->mpref[pref->mprefSize]->colors[9].blue  = 0x5555;

	pref->mpref[pref->mprefSize]->colors[10].red   = 0x5555;
	pref->mpref[pref->mprefSize]->colors[10].green = 0xffff;
	pref->mpref[pref->mprefSize]->colors[10].blue  = 0x5555;

	pref->mpref[pref->mprefSize]->colors[11].red   = 0xffff;
	pref->mpref[pref->mprefSize]->colors[11].green = 0xffff;
	pref->mpref[pref->mprefSize]->colors[11].blue  = 0x5555;

	pref->mpref[pref->mprefSize]->colors[12].red   = 0x5555;
	pref->mpref[pref->mprefSize]->colors[12].green = 0x5555;
	pref->mpref[pref->mprefSize]->colors[12].blue  = 0xffff;

	pref->mpref[pref->mprefSize]->colors[13].red   = 0xffff;
	pref->mpref[pref->mprefSize]->colors[13].green = 0x5555;
	pref->mpref[pref->mprefSize]->colors[13].blue  = 0xffff;

	pref->mpref[pref->mprefSize]->colors[14].red   = 0x5555;
	pref->mpref[pref->mprefSize]->colors[14].green = 0xffff;
	pref->mpref[pref->mprefSize]->colors[14].blue  = 0xffff;

	pref->mpref[pref->mprefSize]->colors[15].red   = 0xffff;
	pref->mpref[pref->mprefSize]->colors[15].green = 0xffff;
	pref->mpref[pref->mprefSize]->colors[15].blue  = 0xffff;

	/*
	pref->mpref[pref->mprefSize]->red[0]  = 0x0000;
	pref->mpref[pref->mprefSize]->red[1]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->red[2]  = 0x0000;
	pref->mpref[pref->mprefSize]->red[3]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->red[4]  = 0x0000;
	pref->mpref[pref->mprefSize]->red[5]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->red[6]  = 0x0000;
	pref->mpref[pref->mprefSize]->red[7]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->red[8]  = 0x5555;
	pref->mpref[pref->mprefSize]->red[9]  = 0xffff;
	pref->mpref[pref->mprefSize]->red[10] = 0x5555;
	pref->mpref[pref->mprefSize]->red[11] = 0xffff;
	pref->mpref[pref->mprefSize]->red[12] = 0x5555;
	pref->mpref[pref->mprefSize]->red[13] = 0xffff;
	pref->mpref[pref->mprefSize]->red[14] = 0x5555;
	pref->mpref[pref->mprefSize]->red[15] = 0xffff;
	pref->mpref[pref->mprefSize]->red[16] = 0x0000;
	pref->mpref[pref->mprefSize]->red[17] = 0x0000;

	pref->mpref[pref->mprefSize]->grn[0]  = 0x0000;
	pref->mpref[pref->mprefSize]->grn[1]  = 0x0000;
	pref->mpref[pref->mprefSize]->grn[2]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->grn[3]  = 0x5555;
	pref->mpref[pref->mprefSize]->grn[4]  = 0x0000;
	pref->mpref[pref->mprefSize]->grn[5]  = 0x0000;
	pref->mpref[pref->mprefSize]->grn[6]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->grn[7]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->grn[8]  = 0x5555;
	pref->mpref[pref->mprefSize]->grn[9]  = 0x5555;
	pref->mpref[pref->mprefSize]->grn[10] = 0xffff;
	pref->mpref[pref->mprefSize]->grn[11] = 0xffff;
	pref->mpref[pref->mprefSize]->grn[12] = 0x5555;
	pref->mpref[pref->mprefSize]->grn[13] = 0x5555;
	pref->mpref[pref->mprefSize]->grn[14] = 0xffff;
	pref->mpref[pref->mprefSize]->grn[15] = 0xffff;
	pref->mpref[pref->mprefSize]->grn[16] = 0xffff;
	pref->mpref[pref->mprefSize]->grn[17] = 0x0000;

	pref->mpref[pref->mprefSize]->blu[0]  = 0x0000;
	pref->mpref[pref->mprefSize]->blu[1]  = 0x0000;
	pref->mpref[pref->mprefSize]->blu[2]  = 0x0000;
	pref->mpref[pref->mprefSize]->blu[3]  = 0x0000;
	pref->mpref[pref->mprefSize]->blu[4]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->blu[5]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->blu[6]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->blu[7]  = 0xaaaa;
	pref->mpref[pref->mprefSize]->blu[8]  = 0x5555;
	pref->mpref[pref->mprefSize]->blu[9]  = 0x5555;
	pref->mpref[pref->mprefSize]->blu[10] = 0x5555;
	pref->mpref[pref->mprefSize]->blu[11] = 0x5555;
	pref->mpref[pref->mprefSize]->blu[12] = 0xffff;
	pref->mpref[pref->mprefSize]->blu[13] = 0xffff;
	pref->mpref[pref->mprefSize]->blu[14] = 0xffff;
	pref->mpref[pref->mprefSize]->blu[15] = 0xffff;
	pref->mpref[pref->mprefSize]->blu[16] = 0x0000;
	pref->mpref[pref->mprefSize]->blu[17] = 0x0000;
*/
	return pref->mpref[pref->mprefSize];
}

int gtkTermPref_save(gtkTermPref* pref, GString *path)
{
	FILE* gtkTermRC_FP;
	int i;

	gtkTermRC_FP = fopen (path->str, "w");
	if(!gtkTermRC_FP)
	{
		g_error("GtkTerm could not write the pref: %s", path->str);
		return FALSE;
	}
	fprintf(gtkTermRC_FP, "##\n# 1=RIGHT, 2=TOP, 3=BOTTOM, 4=LEFT\n##\n");
	fprintf(gtkTermRC_FP, "notebookPanel=%d\n\n", pref->notebookPanel);
	fprintf(gtkTermRC_FP, "##\n# 0=HIDDEN, 1=LEFT, 2=RIGHT\n##\n");
	fprintf(gtkTermRC_FP, "terminalScrollbar=%d\n\n", pref->terminalScrollbar);
	fprintf(gtkTermRC_FP, "##\n# 0=NO SCROLLBAR\n##\n");
	fprintf(gtkTermRC_FP, "maxScrollbackBuffer=%d\n\n", pref->maxScrollbackBuffer);
	fprintf(gtkTermRC_FP, "##\n# 0=FALSE, 1=TRUE\n##\n");
	fprintf(gtkTermRC_FP, "quitPRGonExitLastTerminal=%d\n\n", pref->quitPRGonExitLastTerminal);
	fprintf(gtkTermRC_FP, "##\n# 0=FALSE, 1=TRUE\n##\n");
	fprintf(gtkTermRC_FP, "showTabsByOneTerminal=%d\n\n", pref->showTabsByOneTerminal);
	fprintf(gtkTermRC_FP, "##\n#A Font name: use gnome-font-properties to look at available fonts\n##\n");
	fprintf(gtkTermRC_FP, "terminalFont=%s\n\n", pref->terminalFont);
	fprintf(gtkTermRC_FP, "##\n# Separator for marking with mouse\n##\n");
	fprintf(gtkTermRC_FP, "worldClass=%s\n\n", pref->worldClass);
	fprintf(gtkTermRC_FP, "##\n# 0=FALSE, 1=TRUE\n##\n");
	fprintf(gtkTermRC_FP, "scrollOnKeyStroke=%d\n\n", pref->scrollOnKeyStroke);
	fprintf(gtkTermRC_FP, "##\n# 0=FALSE, 1=TRUE\n##\n");
	fprintf(gtkTermRC_FP, "scrollOnOutput=%d\n\n", pref->scrollOnOutput);
	fprintf(gtkTermRC_FP, "##\n# 0=FALSE, 1=TRUE\n##\n");
	fprintf(gtkTermRC_FP, "blink=%d\n\n", pref->blink);
	fprintf(gtkTermRC_FP, "##\n# 0=FALSE, 1=TRUE\n##\n");
	fprintf(gtkTermRC_FP, "beep=%d\n\n", pref->beep);
	fprintf(gtkTermRC_FP, "##\n# x y Default Terminal Size in pix\n##\n");
	fprintf(gtkTermRC_FP, "terminalSize=%d %d\n\n", pref->termX, pref->termY);
	fprintf(gtkTermRC_FP, "##\n# NEW COLOR Definition\n##\n");
	fprintf(gtkTermRC_FP, "red=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->back[0].red, pref->fore[0].red, pref->colors[0].red, pref->colors[1].red, pref->colors[2].red, pref->colors[3].red, pref->colors[4].red, pref->colors[5].red, pref->colors[6].red, pref->colors[7].red, pref->colors[8].red, pref->colors[9].red, pref->colors[10].red, pref->colors[11].red, pref->colors[12].red, pref->colors[13].red, pref->colors[14].red, pref->colors[15].red);
	fprintf(gtkTermRC_FP, "grn=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->back[0].green, pref->fore[0].green, pref->colors[0].green, pref->colors[1].green, pref->colors[2].green, pref->colors[3].green, pref->colors[4].green, pref->colors[5].green, pref->colors[6].green, pref->colors[7].green, pref->colors[8].green, pref->colors[9].green, pref->colors[10].green, pref->colors[11].green, pref->colors[12].green, pref->colors[13].green, pref->colors[14].green, pref->colors[15].green);
	fprintf(gtkTermRC_FP, "blu=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n\n", pref->back[0].blue, pref->fore[0].blue, pref->colors[0].blue, pref->colors[1].blue, pref->colors[2].blue, pref->colors[3].blue, pref->colors[4].blue, pref->colors[5].blue, pref->colors[6].blue, pref->colors[7].blue, pref->colors[8].blue, pref->colors[9].blue, pref->colors[10].blue, pref->colors[11].blue, pref->colors[12].blue, pref->colors[13].blue, pref->colors[14].blue, pref->colors[15].blue);
	fprintf(gtkTermRC_FP, "##\n# COLOR Definition\n##\n");
	//fprintf(gtkTermRC_FP, "red=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->red[0], pref->red[1], pref->red[2], pref->red[3], pref->red[4], pref->red[5], pref->red[6], pref->red[7], pref->red[8], pref->red[9], pref->red[10], pref->red[11], pref->red[12], pref->red[13], pref->red[14], pref->red[15], pref->red[16], pref->red[17]);
	//fprintf(gtkTermRC_FP, "grn=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->grn[0], pref->grn[1], pref->grn[2], pref->grn[3], pref->grn[4], pref->grn[5], pref->grn[6], pref->grn[7], pref->grn[8], pref->grn[9], pref->grn[10], pref->grn[11], pref->grn[12], pref->grn[13], pref->grn[14], pref->grn[15], pref->grn[16], pref->grn[17]);
	//fprintf(gtkTermRC_FP, "blu=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n\n", pref->blu[0], pref->blu[1], pref->blu[2], pref->blu[3], pref->blu[4], pref->blu[5], pref->blu[6], pref->blu[7], pref->blu[8], pref->blu[9], pref->blu[10], pref->blu[11], pref->blu[12], pref->blu[13], pref->blu[14], pref->blu[15], pref->blu[16], pref->blu[17]);
	fprintf(gtkTermRC_FP, "\n##\n# First section\n##\n");

	if(pref->mprefSize > 0 && pref->mpref != NULL)
	{
		for(i=1; i<=pref->mprefSize; i++)
		{
			//if(pref->mpref[i]->match[0] != '\0')
			//{
				fprintf(gtkTermRC_FP, "[section]\n");
				fprintf(gtkTermRC_FP, "match=%s\n", pref->mpref[i]->match);
				fprintf(gtkTermRC_FP, "worldClass=%s\n", pref->mpref[i]->worldClass);
				fprintf(gtkTermRC_FP, "scrollOnKeyStroke=%d\n", pref->mpref[i]->scrollOnKeyStroke);
				fprintf(gtkTermRC_FP, "scrollOnOutput=%d\n", pref->mpref[i]->scrollOnOutput);
				fprintf(gtkTermRC_FP, "beep=%d\n", pref->mpref[i]->beep);
				fprintf(gtkTermRC_FP, "blink=%d\n", pref->mpref[i]->blink);
				fprintf(gtkTermRC_FP, "red=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->mpref[i]->back[0].red, pref->mpref[i]->fore[0].red, pref->mpref[i]->colors[0].red,   pref->mpref[i]->colors[1].red, pref->mpref[i]->colors[2].red, pref->mpref[i]->colors[3].red, pref->mpref[i]->colors[4].red, pref->mpref[i]->colors[5].red, pref->mpref[i]->colors[6].red, pref->mpref[i]->colors[7].red, pref->mpref[i]->colors[8].red, pref->mpref[i]->colors[9].red, pref->mpref[i]->colors[10].red, pref->mpref[i]->colors[11].red, pref->mpref[i]->colors[12].red, pref->mpref[i]->colors[13].red, pref->mpref[i]->colors[14].red, pref->mpref[i]->colors[15].red);
				fprintf(gtkTermRC_FP, "grn=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->mpref[i]->back[0].green, pref->mpref[i]->fore[0].green, pref->mpref[i]->colors[0].green, pref->mpref[i]->colors[1].green, pref->mpref[i]->colors[2].green, pref->mpref[i]->colors[3].green, pref->mpref[i]->colors[4].green, pref->mpref[i]->colors[5].green, pref->mpref[i]->colors[6].green, pref->mpref[i]->colors[7].green, pref->mpref[i]->colors[8].green, pref->mpref[i]->colors[9].green, pref->mpref[i]->colors[10].green, pref->mpref[i]->colors[11].green, pref->mpref[i]->colors[12].green, pref->mpref[i]->colors[13].green, pref->mpref[i]->colors[14].green, pref->mpref[i]->colors[15].green);
				fprintf(gtkTermRC_FP, "blu=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n\n", pref->mpref[i]->back[0].blue, pref->mpref[i]->fore[0].blue, pref->mpref[i]->colors[0].blue, pref->mpref[i]->colors[1].blue, pref->mpref[i]->colors[2].blue, pref->mpref[i]->colors[3].blue, pref->mpref[i]->colors[4].blue, pref->mpref[i]->colors[5].blue, pref->mpref[i]->colors[6].blue, pref->mpref[i]->colors[7].blue, pref->mpref[i]->colors[8].blue, pref->mpref[i]->colors[9].blue, pref->mpref[i]->colors[10].blue, pref->mpref[i]->colors[11].blue, pref->mpref[i]->colors[12].blue, pref->mpref[i]->colors[13].blue, pref->mpref[i]->colors[14].blue, pref->mpref[i]->colors[15].blue);
				//fprintf(gtkTermRC_FP, "red=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->mpref[i]->red[0], pref->mpref[i]->red[1], pref->mpref[i]->red[2], pref->mpref[i]->red[3], pref->mpref[i]->red[4], pref->mpref[i]->red[5], pref->mpref[i]->red[6], pref->mpref[i]->red[7], pref->mpref[i]->red[8], pref->mpref[i]->red[9], pref->mpref[i]->red[10], pref->mpref[i]->red[11], pref->mpref[i]->red[12], pref->mpref[i]->red[13], pref->mpref[i]->red[14], pref->mpref[i]->red[15], pref->mpref[i]->red[16], pref->mpref[i]->red[17]);
				//fprintf(gtkTermRC_FP, "grn=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n",   pref->mpref[i]->grn[0], pref->mpref[i]->grn[1], pref->mpref[i]->grn[2], pref->mpref[i]->grn[3], pref->mpref[i]->grn[4], pref->mpref[i]->grn[5], pref->mpref[i]->grn[6], pref->mpref[i]->grn[7], pref->mpref[i]->grn[8], pref->mpref[i]->grn[9], pref->mpref[i]->grn[10], pref->mpref[i]->grn[11], pref->mpref[i]->grn[12], pref->mpref[i]->grn[13], pref->mpref[i]->grn[14], pref->mpref[i]->grn[15], pref->mpref[i]->grn[16], pref->mpref[i]->grn[17]);
				//fprintf(gtkTermRC_FP, "blu=0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x 0x%04x\n\n", pref->mpref[i]->blu[0], pref->mpref[i]->blu[1], pref->mpref[i]->blu[2], pref->mpref[i]->blu[3], pref->mpref[i]->blu[4], pref->mpref[i]->blu[5], pref->mpref[i]->blu[6], pref->mpref[i]->blu[7], pref->mpref[i]->blu[8], pref->mpref[i]->blu[9], pref->mpref[i]->blu[10], pref->mpref[i]->blu[11], pref->mpref[i]->blu[12], pref->mpref[i]->blu[13], pref->mpref[i]->blu[14], pref->mpref[i]->blu[15], pref->mpref[i]->blu[16], pref->mpref[i]->blu[17]);
			//}
		}
	}

	fclose (gtkTermRC_FP);

	return TRUE;
}

int gtkTermPref_free(gtkTermPref* pref)
{
	int i;

	for(i=0; i<pref->mprefSize; i++)
	{
		free(pref->mpref[i]);
	}

	free(pref->mpref);
	free(pref);
	pref = NULL;

	return TRUE;
}

gtkTermPref* gtkTermPref_get (void)
{
	FILE* gtkTermRC;
	GString* gtktermrc_file;
	gtkTermPref* pref;
	char tmp[MAX_LINE_LENGTH];
	char* worldClass;
	int i=0;
	int* blink;
	int* beep;
	int* scrollOnOutput;
	int* scrollOnKeyStroke;
	GdkColor *colors;
	GdkColor *fore;
	GdkColor *back;

	pref = gtkTermPref_init();

	gtktermrc_file = g_string_new( "hallo" );
	g_string_sprintf(gtktermrc_file, "%s/.gtkterm2rc", getenv("HOME"));

	gtkTermRC = fopen (gtktermrc_file->str, "r");
	if(!gtkTermRC)
	{
		g_warning("gtkterm2rc File dose not exists: %s\n", gtktermrc_file->str);
		if(gtkTermPref_save(pref, gtktermrc_file) == FALSE)
		{
			gtkTermPref_free(pref);
			g_string_free(gtktermrc_file, TRUE);
			exit(-1);
		}
		else if(!(gtkTermRC = fopen (gtktermrc_file->str, "r")))
		{
			g_warning("gtkterm2rc File dose not exists: %s\n", gtktermrc_file->str);
			exit(-1);
		}
	}

	blink = &pref->blink;
	beep  = &pref->beep;
	scrollOnOutput = &pref->scrollOnOutput;
	scrollOnKeyStroke = &pref->scrollOnKeyStroke;
	worldClass = pref->worldClass;

	colors = (GdkColor *) &pref->colors;
	back   = (GdkColor *) &pref->back;
	fore   = (GdkColor *) &pref->fore;
	
	while (!feof (gtkTermRC))
	{
		fgets(tmp, MAX_LINE_LENGTH - 1, gtkTermRC);
		if(tmp[0] != '#' && tmp[0] != '\n' && tmp[0] != ' ')
		{
			if(strstr(tmp, "[section]"))
			{
				i++;
				if(i > pref->mprefSize)
				{
					gtkTermMPref_init(pref);
				}
				blink = &pref->mpref[i]->blink;
				beep  = &pref->mpref[i]->beep;
				scrollOnOutput = &pref->mpref[i]->scrollOnOutput;
				scrollOnKeyStroke = &pref->mpref[i]->scrollOnKeyStroke;
				worldClass = pref->mpref[i]->worldClass;
				
				colors = (GdkColor *) &pref->mpref[i]->colors;
				back   = (GdkColor *) &pref->mpref[i]->back;
				fore   = (GdkColor *) &pref->mpref[i]->fore;
			}
			if(strstr(tmp, "notebookPanel"))
			{
				sscanf(tmp + 14, "%d", (int *) &pref->notebookPanel);
			}
			if(strstr(tmp, "terminalScrollbar"))
			{
				sscanf(tmp + 18, "%d", (int *) &pref->terminalScrollbar);
			}
			if(strstr(tmp, "maxScrollbackBuffer"))
			{
				sscanf(tmp + 20, "%d", (int *) &pref->maxScrollbackBuffer);
			}
			if(strstr(tmp, "quitPRGonExitLastTerminal"))
			{
				sscanf(tmp + 26, "%d", (int *) &pref->quitPRGonExitLastTerminal);
			}
			if(strstr(tmp, "showTabsByOneTerminal"))
			{
				sscanf(tmp + 22, "%d", (int *) &pref->showTabsByOneTerminal);
			}
			if(strstr(tmp, "terminalFont"))
			{
				sscanf(tmp + 13, "%[0123456789 abcdefghijklmnopqrstuwvxyzABCDEFGHIJKLMNOPQRSTUWVXYZ]", pref->terminalFont);
			}
			if(strstr(tmp, "worldClass"))
			{
				sscanf(tmp + 11, "%s", worldClass);
			}
			if(strstr(tmp, "scrollOnOutput"))
			{
				sscanf(tmp + 15, "%d", scrollOnOutput);
			}
			if(strstr(tmp, "scrollOnKeyStroke"))
			{
				sscanf(tmp + 18, "%d", scrollOnKeyStroke);
			}
			if(strstr(tmp, "blink"))
			{
				sscanf(tmp +  6, "%d", blink);
			}
			if(strstr(tmp, "beep"))
			{
				sscanf(tmp +  5, "%d", beep);
			}
			if(strstr(tmp, "terminalSize"))
			{
				sscanf(tmp + 13, "%d %d", (int *) &pref->termX, (int *) &pref->termY);
			}
			if(strstr(tmp, "red"))
			{
				sscanf(tmp + 4, "%hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi", &back[0].red, &fore[0].red, &colors[0].red, &colors[1].red, &colors[2].red, &colors[3].red, &colors[4].red, &colors[5].red, &colors[6].red, &colors[7].red, &colors[8].red, &colors[9].red, &colors[10].red, &colors[11].red, &colors[12].red, &colors[13].red, &colors[14].red, &colors[15].red);
			}
			if(strstr(tmp, "grn"))
			{
				sscanf(tmp + 4, "%hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi", &back[0].green, &fore[0].green, &colors[0].green, &colors[1].green, &colors[2].green, &colors[3].green, &colors[4].green, &colors[5].green, &colors[6].green, &colors[7].green, &colors[8].green, &colors[9].green, &colors[10].green, &colors[11].green, &colors[12].green, &colors[13].green, &colors[14].green, &colors[15].green);
			}
			if(strstr(tmp, "blu"))
			{
				sscanf(tmp + 4, "%hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi %hi", &back[0].blue, &fore[0].blue, &colors[0].blue, &colors[1].blue, &colors[2].blue, &colors[3].blue, &colors[4].blue, &colors[5].blue, &colors[6].blue, &colors[7].blue, &colors[8].blue, &colors[9].blue, &colors[10].blue, &colors[11].blue, &colors[12].blue, &colors[13].blue, &colors[14].blue, &colors[15].blue);
			}
			if(strstr(tmp, "match"))
			{
				sscanf(tmp + 6, "%s", pref->mpref[i]->match);
			}
		}
	}

	fclose(gtkTermRC);
	if(gtkTermPref_save(pref, gtktermrc_file) == FALSE)
	{
		gtkTermPref_free(pref);
		g_string_free(gtktermrc_file, TRUE);
		exit(-1);
	}
	g_string_free(gtktermrc_file, TRUE);

	return pref;
}

int gtkTermFindMPref(char *matchstr, gtkTermPref *pref)
{
	int i;

	for(i=1; i<=pref->mprefSize; i++)
	{
		if(strstr(matchstr, pref->mpref[i]->match))
		{
			return i;
		}
	}
	return -1;
}

void gtkTermSetMPref(GtkWidget *term, gtkTermPref *pref, int i)
{
	gpointer termPref;

	if((termPref = gtk_object_get_data(GTK_OBJECT(term), "mpref")) == NULL)
	{
		gtk_object_set_data(GTK_OBJECT(term), "mpref", GINT_TO_POINTER(-1));
		termPref = GINT_TO_POINTER(-1);
	}

	if(GPOINTER_TO_INT(termPref) != i)
	{
		if(i == -1)
		{
			vte_terminal_set_audible_bell(VTE_TERMINAL(term), pref->beep);
			vte_terminal_set_cursor_blinks(VTE_TERMINAL(term), pref->blink);
			vte_terminal_set_colors(VTE_TERMINAL(term), &pref->fore[0], &pref->back[0], pref->colors, 16);
			vte_terminal_set_scroll_on_output(VTE_TERMINAL(term), pref->scrollOnOutput);
			vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL(term), pref->scrollOnKeyStroke);
			vte_terminal_set_word_chars (VTE_TERMINAL(term), pref->worldClass);
		}
		else
		{
			vte_terminal_set_audible_bell(VTE_TERMINAL(term), pref->mpref[i]->beep);
			vte_terminal_set_cursor_blinks(VTE_TERMINAL(term), pref->mpref[i]->blink);
			vte_terminal_set_colors(VTE_TERMINAL(term), &pref->mpref[i]->fore[0], &pref->mpref[i]->back[0], pref->mpref[i]->colors, 16);
			vte_terminal_set_scroll_on_output(VTE_TERMINAL(term), pref->mpref[i]->scrollOnOutput);
			vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL(term), pref->mpref[i]->scrollOnKeyStroke);
			vte_terminal_set_word_chars (VTE_TERMINAL(term), pref->mpref[i]->worldClass);
		}
		gtk_object_set_data(GTK_OBJECT(term), "mpref", GINT_TO_POINTER(i));
	}
}
