/* See LICENSE file for copyright and license details. */

/* 
 * special command for directories
 */

static const char *dircmd = "st -e fm %s";

/*  regex, actions */
static const Pair pairs[] = {
// text files
{ "\\.(txt|qmd|tex)$",  "st -e vim %s"  },
// epub reader
{"\\.epub$",  "bookokrat --zen-mode %s"},
// pdf reader
{ "\\.(pdf|epub)$", "zathura %s"  }, 
// image
{ "\\.(jpg|png|tiff|gif)$",
"feh %s"  }, 
// video
{"\\.(avi|mp4|m4v|mkv|mov|wmv)$",
"mpv %s"  },
// audio
{ "\\.(opus|mp3|ogg|flac)$",
"mpv %s"  },
// local html
{ "\\.(html|svg)$", "firefox %s" },
// web link URI
{ "^(http://|https://)", "firefox %s" },
// magnet and torrent
{ "(^magnet:\?|\\.torrent$)", "aria2c %s" },
// steam URI
{ "^steam:\?", "steam %s" },
// magnet/torrent URI link
//	{ "(^magnet:\?|\\.torrent$)", "transmission-gtk %s" },
// zoom URI
{ "^zoommtg:\?", "zoom %s"},
// slack URI
{ "^slack:\?", "slack %s" },
};
