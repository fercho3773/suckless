/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* Helper macros for spawning shell commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/dash", "-c", cmd, NULL } } /* spawn shell in pre dwm-5.0*/
#define CMD(...)   { .v = (const char*[]){ __VA_ARGS__, NULL } }
/* Commands */
#define killdwm     "killall dwmblocks mydwm feh redshift picom dunst pipewire pipewire-pulse wireplumber xclip"
#define shotfull    "xfce4-screenshooter --fullscreen --mouse"
#define shotcrop    "xfce4-screenshooter --region --mouse" /* --region --mouse --clipboard --fullscreen */
#define termcmd     "st"  /* st urxvt */
#define lockcmd     "slock"
#define launchcmd   "dmenu_run"
//#define scratchcmd1 "st -n spterm -g 120x34"
#define brightup    "brightnessctl s 3%+"
#define brightdown  "brightnessctl s 3%- --min-value=100"

// alsa
#define volup "amixer sset Master 2%+"
#define voldown "amixer sset Master 2%-"
#define micmute "amixer set Capture toggle"
#define volmute "amixer sset Master toggle"

/*  pipewire or pulseaudio
#define volup       "wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%+ --limit 1"
#define voldown     "wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%-"
#define micmute     "wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle"
#define volmute     "wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle"
*/

/* dmenu stuff */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };

/* font and colors */
static const char *fonts[] = { 
  "FiraCode Nerd Font:regular:size=12",
  "Font Awesome:regular:size=18",
  "Symbols Nerd Font:regular:size=16"
};

static char whi[]       = "#eeeeee";
static char blk[]       = "#0f0f0f";
static char red[]       = "#f44633";
static char grn[]       = "#9ece6a";
static char gr2[]       = "#565f89";

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 24;  /* snap pixel */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const int statusmon               = 0;   /* -1 all monitors, 'A' active, 0 specific by index */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

static int tagindicatortype     = INDICATOR_TOP_BAR;  /* See patch/bar_indicators.h for options */
static int tiledindicatortype   = INDICATOR_NONE;
static int floatindicatortype   = INDICATOR_TOP_LEFT_SQUARE;

static char *colors[][4] = {
	/* [name]  foreground background border float */
	[SchemeNorm]         = { red,  blk, gr2, grn },
	[SchemeSel]          = { red,  blk, gr2, grn },
	[SchemeTitleNorm]    = { red,  blk, gr2, grn },
	[SchemeTitleSel]     = { red,  blk, gr2, grn },
	[SchemeTagsNorm]     = { red,  blk, gr2, grn },
	[SchemeTagsSel]      = { red,  blk, gr2, grn },
	[SchemeHidNorm]      = { red,  blk, gr2, grn },
	[SchemeHidSel]       = { red,  blk, gr2, grn },
	[SchemeUrg]          = { whi,  blk, red, grn },
};

static const char *scratchcmd1[] = {"st", "-n", "spterm", "-g", "150x45", NULL};
static Sp scratchpads[] = { {"spterm", scratchcmd1 }, /* name cmd */ };
//static const char *scratchcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL};

static char *tagicons[][NUMTAGS] = {
[DEFAULT_TAGS]        = { "1", "2", "3", "4", "5", "6", "7", "8", "9" },
//	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F", "G", "H", "I" },
//	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>" },
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG",     .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY",    .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR",    .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH",     .isfloating = 1)
	RULE(.class     = "Gimp",           .tags = 1 << 4)
	RULE(.class     = "Firefox",        .tags = 1 << 2)
  RULE(.instance  = "sttmux",         .tags = 1 )
	RULE(.instance  = "spterm",         .tags = SPTAG(0), .isfloating = 1)
};

static const char buttonbar[]  = "";
static const BarRule barrules[] = {
	/* monitor, bar, alignment, widthfn, drawfn, clickfn, hoverfn, name */
	//{  0, 0, BAR_ALIGN_LEFT,   width_tags,      draw_tags,      click_tags,      NULL, "tags"         },
  {  0, 0, BAR_ALIGN_LEFT,   width_stbutton,  draw_stbutton,  click_stbutton,  NULL, "statusbutton" },
	{  0, 0, BAR_ALIGN_LEFT,   width_tags,      draw_tags,      click_tags,      NULL, "tags"         },
	{  0, 0, BAR_ALIGN_LEFT,   width_ltsymbol,  draw_ltsymbol,  click_ltsymbol,  NULL, "layout"       },
  {  0, 0, BAR_ALIGN_RIGHT,  width_systray,   draw_systray,   click_systray,   NULL, "systray"      },
	{  0, 0, BAR_ALIGN_RIGHT,  width_status2d,  draw_status2d,  click_status2d,  NULL, "dwmblocks"    },
	{  0, 0, BAR_ALIGN_NONE,   width_wintitle,  draw_wintitle,  click_wintitle,  NULL, "windowtitle"  },
};

/* layout(s) */
static const float mfact        = 0.5;        /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;          /* number of clients in master area */
static const int resizehints    = 0;          /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0;          /* 1 will force focus on the fullscreen window */
static const int refreshrate    = 60;         /* refresh rate (per second) for client move/resize */

#define FORCE_VSPLIT 1 /* 0 or 1, for nrowgrid , keep */

static const Layout layouts[] = {             /* symbol     arrange function */
	{ "===",      nrowgrid },                   /* first entry is default */
	{ "[F]",      NULL },                       /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
  { "[]=",      tile },
};

static const Key keys[] = {
	/* modifier, key, function, argument */
  { MODKEY|ControlMask,  XK_l,      spawn,    SHCMD(lockcmd)      },    /* commands    */
	{ MODKEY,              XK_r,      spawn,    SHCMD(launchcmd)    },
	{ MODKEY,              XK_Return, spawn,    SHCMD(termcmd)      },
  {0,   XF86XK_AudioLowerVolume,    spawn,    SHCMD(voldown)      },    /* laptop keys */
	{0,   XF86XK_AudioMute,           spawn,    SHCMD(volmute)      },
  {0,   XF86XK_AudioMicMute,        spawn,    SHCMD(micmute)      },
	{0,   XF86XK_AudioRaiseVolume,    spawn,    SHCMD(volup)        },
	{0,		XF86XK_MonBrightnessUp,     spawn,	  SHCMD(brightup)     },
	{0,		XF86XK_MonBrightnessDown,   spawn,	  SHCMD(brightdown)   },
  { MODKEY,              XK_u,      spawn,    SHCMD(shotfull)     },    /* screenshot  */
  { MODKEY|ControlMask,  XK_u,      spawn,    SHCMD(shotcrop)     },
  // toggles
  // { MODKEY,                     XK_f,          togglefullscr,      {0} },
  { MODKEY,                     XK_b,          togglebar,             {0} },
  { MODKEY,                     XK_t,          toggleview,            {0} },
  // kill client, restart dwm, kill dwm
	{ MODKEY,           XK_q,  killclient,  {0} },
  { MODKEY|ShiftMask, XK_m,  restart,     {0} },
  { MODKEY|ControlMask, XK_Delete, spawn, SHCMD(killdwm) },
	// layouts : 0-nrowgrid, 1-floating , 2-monocle, 3-dwindle, 4-tile
  { MODKEY,                       XK_n,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_comma,      setlayout,              {.v = &layouts[3]} },
  { MODKEY,                       XK_period,     setlayout,              {.v = &layouts[4]} },
  { MODKEY,                       XK_minus,      setlayout,              {.v = &layouts[1]} },
  //
  { MODKEY,                       XK_q,          killclient,             {0} },
  { MODKEY,                       XK_p,          togglefloating,         {0} },
  // scratchpad
	{ MODKEY|ControlMask,           XK_s,          setscratch,             {.ui = 0 } },
	{ MODKEY,                       XK_s,          togglescratch,          {.ui = 0 } },
  //
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY,                       XK_d,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_f,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_z,          zoom,                   {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	// { MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	// { MODKEY,                       XK_space,      setlayout,              {0} },
	// { MODKEY,                       XK_p,          togglefloating,         {0} },
	// { MODKEY,                       XK_grave,      togglescratch,          {.ui = 0 } },
	// { MODKEY|ControlMask,           XK_grave,      setscratch,             {.ui = 0 } },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~SPTAGMASK } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~SPTAGMASK } },
	{ MODKEY|ControlMask,           XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     focusmon,               {.i = +1 } },
  // { MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
  //	
  TAGKEYS( XK_1, 0)	TAGKEYS( XK_2, 1)	TAGKEYS( XK_3, 2)	TAGKEYS( XK_4, 3) TAGKEYS( XK_5, 4)
	TAGKEYS( XK_6, 5) TAGKEYS( XK_7, 6) TAGKEYS( XK_8, 7) TAGKEYS( XK_9, 8)
};

/*  Button definitions
*      click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin
*      ClkTagBar: , ClkLtSymbol: , ClkLtSymbol: , ClkStatusText: , ClkWinTitle: , ClkClientWin: , ClkRootWin:  
*      Button1: , Button2: , Button3
*/
static const Button buttons[] = {
	/* click                event mask           button          function        argument */
  // { ClkButton,            0,                   Button1,        spawn,          {.v = dmenucmd } },
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	// { ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	// { ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

