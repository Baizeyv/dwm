/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 35, .gappx = 35};
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 0;        /* 1 means master-area is initially on the right */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char statussep         = ';';      /* separator between status bars */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char buttonbar[]       = " ";
static const int startontag         = 0;        /* 0 means no tag active on start */
static const int user_bh            = 22;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Hasklug Nerd Font:size=11" };
static const char dmenufont[]       = "Hasklug Nerd Font:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#cd69af";
/* static const char col_cyan[]        = "#37474F"; */
static const char col_border[]      = "#cd69af";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border  },
};

static const char *const autostart[] = {
    "sh", "/home/baizeyv/willGit/dwm/script/autostart/autostart.sh", NULL,
    /* "polybar", "example", NULL, */
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "\uf120 ", "\uf7ae ", "\uf121 ", "\uf04b ", "\ue62e ", "\uf251 ", "\ue727 ", "\uf537 ", "\uf684 " };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* launcher commands (They must be NULL terminated) */
static const char* surf[]      = { "surf", "baidu.com", NULL };
static const char* ranger[]    = { "st", "-e", "ranger", NULL };

static const Launcher launchers[] = {
       /* command       name to display */
	{ surf,           "" },
	{ ranger,         "" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title       tags mask     isfloating canfocus   monitor  floatcenterrule(1 center)   float x,y,w,h     floatborderpx */
	{ "Gimp",                NULL,       NULL,       0,            1,         1,         -1,            1,                   50,50,500,500,      1 },
	{ "firefox",             NULL,       NULL,       1 << 8,       1,         1,         -1,            1,                   50,50,500,500,      1 },
    { "Polybar",             NULL,       NULL,       0,            1,         0,         -1,            0,                   50,50,500,500,      1 },
	{ "netease-cloud-music", NULL,       NULL,       1 << 3,       1,         1,         -1,            1,                   50,50,500,500,      1 },
    { "xdman-Main",          NULL,       NULL,       0,            1,         1,         -1,            1,                   50,50,500,500,      1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */
static int attachbelow = 1;    /* 1 means attach after the currently active window */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */


#include "tatami.c"
#include "fibonacci.c"
#include "tcl.c"
#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "|+|",      tatami },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
 	{ "|||",      tcl },
	{ "###",      horizgrid },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *termcmd2[]  = { "alacritty", NULL };
static const char *layoutmenu_cmd = "/home/baizeyv/willGit/dwm/script/layout/layoutmenu.sh";
static const char *rootRightClk[] = { "/home/baizeyv/NEW/xmenuScripts/rootRightClk.sh", NULL};
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *chooseLayout[] = { "/home/baizeyv/willGit/dwm/script/layout/chooselayout.sh", NULL};
static const char *start[] = { "/home/baizeyv/willGit/UsefulScript/START.sh", NULL};
static const char *update[] = { "/home/baizeyv/willGit/dwm/script/start/rightClk.sh", NULL};

static const char *volmute[] = { "/home/baizeyv/willGit/dwm/script/operate/vol-toggle.sh", NULL };
static const char *volup[] = { "/home/baizeyv/willGit/dwm/script/operate/vol-up.sh", NULL };
static const char *voldown[] = { "/home/baizeyv/willGit/dwm/script/operate/vol-down.sh", NULL };

#include "tagall.c"
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function                argument */
	{ MODKEY,                       XK_p,      spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,                  {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,                  {.v = termcmd2 } },
	{ MODKEY|ControlMask,           XK_k,      spawn,                  {.v = chooseLayout } },
	{ MODKEY,                       XK_F1,     spawn,                  {.v = volmute } },
	{ MODKEY,                       XK_F2,     spawn,                  {.v = voldown } },
	{ MODKEY,                       XK_F3,     spawn,                  {.v = volup } },
	{ MODKEY,                       XK_b,      togglebar,              {0} },
	{ MODKEY,                       XK_n,      focusstackvis,          {.i = +1 } },
	{ MODKEY,                       XK_e,      focusstackvis,          {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_n,      movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_e,      movestack,              {.i = -1 } },
	{ MODKEY|ControlMask,           XK_n,      focusstackhid,          {.i = +1 } },
	{ MODKEY|ControlMask,           XK_e,      focusstackhid,          {.i = -1 } },
	{ MODKEY,                       XK_a,      incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_s,      incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_i,      setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,               {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_i,      setcfact,               {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,               {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,                   {0} },
	{ MODKEY,                       XK_Tab,    view,                   {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,             {0} },
	{ ControlMask,                  XK_F1,     setlayout,              {.v = &layouts[0]} },
	{ ControlMask,                  XK_F2,     setlayout,              {.v = &layouts[1]} },
	{ ControlMask,                  XK_F3,     setlayout,              {.v = &layouts[2]} },
	{ ControlMask,                  XK_F4,     setlayout,              {.v = &layouts[3]} },
	{ ControlMask,                  XK_F5,     setlayout,              {.v = &layouts[4]} },
	{ ControlMask,                  XK_F6,     setlayout,              {.v = &layouts[5]} },
	{ ControlMask,                  XK_F7,     setlayout,              {.v = &layouts[6]} },
	{ ControlMask,                  XK_F8,     setlayout,              {.v = &layouts[7]} },
	{ ControlMask,                  XK_F9,     setlayout,              {.v = &layouts[8]} },
	{ ControlMask,                  XK_F10,    setlayout,              {.v = &layouts[9]} },
	{ MODKEY,                       XK_space,  setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,         {0} },
	{ MODKEY,                       XK_w,      togglesticky,           {0} },
	{ MODKEY,                       XK_0,      view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,                 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_z,      show,                   {0} },
	{ MODKEY,                       XK_z,      hide,                   {0} },
	{ MODKEY|ControlMask,           XK_m,      togglealttag,           {0} },
    { MODKEY|ShiftMask,             XK_Tab,    toggleAttachBelow,      {0} },
	{ MODKEY,                       XK_grave,  togglescratch,          {.v = scratchpadcmd } },
	{ MODKEY,                       XK_minus,  setgaps,                {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,                {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,                {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,                {.i = GAP_TOGGLE} },
	{ MODKEY,		                XK_k,      cyclelayout,            {.i = -1 } },
	{ MODKEY,                       XK_m,      cyclelayout,            {.i = +1 } },
	{ MODKEY,                       XK_l,      viewtoleft,             {0} },
	{ MODKEY,                       XK_u,      viewtoright,            {0} },
	{ MODKEY|ShiftMask,             XK_l,      tagtoleft,              {0} },
	{ MODKEY|ShiftMask,             XK_u,      tagtoright,             {0} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,             {0} },
	{ MODKEY,                       XK_f,      togglefullscr,          {0} },
	{ MODKEY,                       XK_r,      togglermaster,          {0} },
    { MODKEY|ControlMask,           XK_space,  focusmaster,            {0} },
	{ MODKEY|Mod1Mask,              XK_space,  togglealwaysontop,      {0} },
	{ MODKEY,                       XK_o,      winview,                {0} },
	{ ControlMask|ShiftMask,        XK_F1,     tagall,                 {.v = "F1"} },
	{ ControlMask|ShiftMask,        XK_F2,     tagall,                 {.v = "F2"} },
	{ ControlMask|ShiftMask,        XK_F3,     tagall,                 {.v = "F3"} },
	{ ControlMask|ShiftMask,        XK_F4,     tagall,                 {.v = "F4"} },
	{ ControlMask|ShiftMask,        XK_F5,     tagall,                 {.v = "F5"} },
	{ ControlMask|ShiftMask,        XK_F6,     tagall,                 {.v = "F6"} },
	{ ControlMask|ShiftMask,        XK_F7,     tagall,                 {.v = "F7"} },
	{ ControlMask|ShiftMask,        XK_F8,     tagall,                 {.v = "F8"} },
	{ ControlMask|ShiftMask,        XK_F9,     tagall,                 {.v = "F9"} },
	{ MODKEY|ShiftMask,             XK_F1,     tagall,                 {.v = "1"} },
	{ MODKEY|ShiftMask,             XK_F2,     tagall,                 {.v = "2"} },
	{ MODKEY|ShiftMask,             XK_F3,     tagall,                 {.v = "3"} },
	{ MODKEY|ShiftMask,             XK_F4,     tagall,                 {.v = "4"} },
	{ MODKEY|ShiftMask,             XK_F5,     tagall,                 {.v = "5"} },
	{ MODKEY|ShiftMask,             XK_F6,     tagall,                 {.v = "6"} },
	{ MODKEY|ShiftMask,             XK_F7,     tagall,                 {.v = "7"} },
	{ MODKEY|ShiftMask,             XK_F8,     tagall,                 {.v = "8"} },
	{ MODKEY|ShiftMask,             XK_F9,     tagall,                 {.v = "9"} },
	{ MODKEY|ShiftMask,             XK_x,      killunsel,              {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,                   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,                   {1} }, 
	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
	TAGKEYS(                        XK_7,                               6)
	TAGKEYS(                        XK_8,                               7)
	TAGKEYS(                        XK_9,                               8)
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkButton,		    0,		Button1,	spawn,		{.v = start } },
	{ ClkButton,		    0,		Button3,	spawn,		{.v = update } },
	{ ClkRootWin,		    0,		Button3,	spawn,		{.v = rootRightClk } },
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, {.v = &scrollargs[0]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, {.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, {.v = &scrollargs[2]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, {.v = &scrollargs[3]} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            setlayout,      {.v = &layouts[0]} },
	{ 2,            setlayout,      {.v = &layouts[1]} },
	{ 3,            setlayout,      {.v = &layouts[2]} },
	{ 4,            setlayout,      {.v = &layouts[3]} },
	{ 5,            setlayout,      {.v = &layouts[4]} },
	{ 6,            setlayout,      {.v = &layouts[5]} },
	{ 7,            setlayout,      {.v = &layouts[6]} },
	{ 8,            setlayout,      {.v = &layouts[7]} },
	{ 9,            setlayout,      {.v = &layouts[8]} },
	{ 10,           setlayout,      {.v = &layouts[9]} },
	{ 11,            quit,      {0} }, /* close signal */
	{ 12,            quit,      {1} }, /* restart signal */
};
