/* See LICENSE file for copyright and license details. */

/* special command for directories */
static const char *dircmd = "st -e noice %s";

static const Pair pairs[] = {
	/*  regex                                           action */
	{ "\\.pdf$",                                        "zathura %s"          }, // pdf
	{ "\\.(jpg|png|tiff|gif)$",                         "nsxiv -a %s"         }, // image
	{ "\\.(avi|mp4|m4v|mkv|mov|wmv)$",                  "mpv %s"              }, // video
	{ "\\.(opus|mp3|ogg|flac)$",                        "mpv %s"              }, // audio
	{ "\\.(html|svg)$",                                 "firefox %s"          }, // local html and svg
	{ "^(http://|https://)",                            "firefox %s"          }, // web URI link
  { "(^magnet:\?|\\.torrent$)",                       "aria2c %s"           }, // magnet/torrent URI link
  { "^steam:\?",                                      "steam %s"            }, // steam URI link
//	{ "(^magnet:\?|\\.torrent$)",                       "transmission-gtk %s" }, // magnet/torrent URI link
//	{ "^steam:\?",                                      "steam %s"            }, // steam URI link
//	{ "^zoommtg:\?",                                    "zoom %s"             }, // zoom URI link
//	{ "^slack:\?",                                      "slack %s"            }, // slack URI link
};
