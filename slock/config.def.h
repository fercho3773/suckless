/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup"; // use "nobody" for arch

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
};

static const int failonclear = 1;       /* treat clear input like a wrong password */
static const int timeoffset = 2400;     /* second until "*command" */
static const int runonce = 0;           /* should [command] only run once*/
static const char *command = "loginctl hibernate";

static const int failcount = 8;         /* failed attempts until [failcommand]*/
static const char *failcommand = "loginctl reboot";

/* Password command */
static const secretpass scom[] = {
	{ "poweroff",  "loginctl poweroff"},
};

#define PIXELATION
#define BLUR
static const int blurRadius = 30;
static const int pixelSize = 60;

static const int controlkeyclear = 0;   /* allow control key to trigger fail on clear */
static const int monitortime = 40;      /* seconds before monitor shuts down */
static const int timetocancel = 2;      /* seconds to cancel lock with mouse */
