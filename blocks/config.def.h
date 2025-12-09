#define CONFIG_H

#define DELIMITER " / "               // Delimiter for blocks.
#define MAX_BLOCK_OUTPUT_LENGTH 40    // Ammount of Unicode characters a block can output.
#define CLICKABLE_BLOCKS 0            // Blocks are clickable.
#define LEADING_DELIMITER 0           // Control whether a leading delimiter should be prepended to the status.
#define TRAILING_DELIMITER 0          // Control whether a trailing delimiter should be appended to the status

// icon, sh, time interval, signal
#define BLOCKS(X)             \
X("",   "sb-volume", 							                                   1, 1) \
X("",   "sb-screen", 							                                   2, 2) \
X("",	  "sb-battery",   		                                         5, 3) \
X("",   "sb-cpu",                                                    8, 4) \
X("",   "sb-ram",                                                    5, 5) \
X("",	  "sb-internet", 	                                            10, 6) \
X("",   "sb-nettraf", 		                                           3, 7) \
X("",   "date '+%Y-%b-%d-%a %H:%M' ",                               15, 8) \

