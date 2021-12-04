/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
//static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
//static const unsigned int systrayspacing = 6;   /* systray spacing */
//static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
//static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 8;        /* vertical padding for statusbar */
static const int vertpad            = 6;
static const int sidepad            = 6; 
static const char *fonts[]          = { "Hack:size=11","fontawesome:size=10" };
static const char dmenufont[]       = "Hack:size=11";
static const char col_gray1[]       = "#343434";
//static const char col_gray1[]       = "#000000";
//static const char col_gray2[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#ffffff";
static const char col_gray4[]       = "#ffffff";
static const char col_gray5[]       = "#aaaaaa";
static const char col_cyan[]        = "#7000A5"; 
//static const char col_cyan[]        = "#026000";
//0xce
static const unsigned int baralpha = 0xce;
static const unsigned int borderalpha = OPAQUE; 
//#include "/home/jan/.cache/wal/colors-wal-dwm.h"

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray3  }, //col_gray5
};
static const unsigned int alphas[][3]      = {
        /*               fg      bg        border     */
        [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
        [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

// Media keys
#include <X11/XF86keysym.h>

static const char *upvol[]   = { "/home/jan/git/upvol",   NULL };
static const char *downvol[] = { "/home/jan/git/downvol",   NULL };
static const char *mutevol[] = { "/usr/bin/amixer", "-D", "pulse", "sset", "Master", "toggle",   NULL };
static const char *mutemic[] = { "/usr/bin/amixer", "-D", "pulse", "sset", "Capture", "toggle",    NULL };
static const char *statusreload[] = { "/usr/bin/python3", "/home/jan/git/i3-status-reload.py",   NULL };
static const char *lock[] = { "/usr/bin/i3lock", "-i", "/home/jan/Obrázky/wall5.png",   NULL };
static const char *dwmkill[] = { "/usr/bin/killall", "dwm", NULL };
static const char *playpause[] = { "/usr/bin/playerctl", "play-pause",   NULL };
static const char *screenshot[] = { "/home/jan/git/scrotcmd", NULL };
static const char *scrarea[] = { "/home/jan/git/scrotcmds", NULL };

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
        { "|M|",      centeredmaster },
        { ">M>",      centeredfloatingmaster },
        { "D_D",      doubledeck },
        { "[D]",      deck },
        { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "/home/jan/git/roficommand", NULL };
static const char *termcmd[]  = { "mate-terminal", NULL };
static const char *editor[] = { "mate-terminal", "-e", "vim" , NULL };
static const char *files[] = { "mate-terminal", "-e", "mc" , NULL };
static const char *trayer[] = { "/home/jan/git/trayercmd", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = statusreload } },
	{ 0,                            XF86XK_AudioMute, spawn, {.v = statusreload } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = statusreload   } },
        { 0,                            XF86XK_AudioPlay,   spawn, {.v = playpause } },
        { 0,                            XF86XK_AudioPlay,   spawn, {.v = statusreload } },
        { 0,                            XK_Print,  spawn,          {.v = screenshot } },
        { 0|ShiftMask,                  XK_Print,  spawn,          {.v = scrarea } },
        { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = dwmkill } },
        { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lock  } },
        { Mod1Mask,                     XK_F10,    spawn,          {.v = mutemic } },
        { Mod1Mask,                     XK_F10,    spawn,          {.v = statusreload } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = editor } },
	{ MODKEY,                       XK_a,      spawn,          {.v = files } },
        { MODKEY|ShiftMask,             XK_a,      spawn,          {.v = trayer } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
        { MODKEY|ShiftMask,             XK_c,      setlayout,      {.v = &layouts[4]} },
        { MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1  } },
        { MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1  } },
        { MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_uacute,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_uacute,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_plus,                      0)
	TAGKEYS(                        XK_ecaron,                      1)
	TAGKEYS(                        XK_scaron,                      2)
	TAGKEYS(                        XK_ccaron,                      3)
	TAGKEYS(                        XK_rcaron,                      4)
	TAGKEYS(                        XK_zcaron,                      5)
	TAGKEYS(                        XK_yacute,                      6)
	TAGKEYS(                        XK_aacute,                      7)
	TAGKEYS(                        XK_iacute,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

