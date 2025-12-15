/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */
// #include "themes/red.h"
	
static const char black[]   = "#1a1b26";
static const char red[]     = "#ff4433";	

static int topbar = 1;/* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = { "FiraCode Nerd Font:style:regular:size=12" };
static const char *prompt      = NULL; /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = { // * foreground background 
	[SchemeNorm]    = { red, black },
	[SchemeSel]     = { red, black },
	[SchemeOut]     = { red, black },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines = 0;

//Characters not considered part of a word while deleting words,for example: " /?\"&[]"
static const char worddelimiters[] = " ";
