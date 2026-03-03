// R Jesse Chaney
// rchaney@pdx.edu

// Include guards!!!
#ifndef _MONITORASAURUS_H
# define _MONITORASAURUS_H

// This is the, arbitary, value i use for what i read with fgets().
# define MAX_LINE_LEN 5000

// This is the command sent to popen(). there are a couple of other
// examples on here you can play with. Just be sure to leave the last
// one defined when you submit your assignment.
# ifndef CMD
//#  define CMD "free -m"
//#  define CMD "uptime"
//#  define CMD "ps aux | grep ${LOGNAME} | sort -nrk 3,3 | head -n 5"
#  define CMD "ps augx --sort=-pcpu | head -n 20"
# endif // CMD

# define OPTIONS "i:c:w:vh"

// This is the default value use between updates to the display.
// 2 seconds.
# define DEFAULT_INTERVAL 2

// I don't allow the interval to be less than 1 second. technically, we could
// go into some number of nanoseconds. i'm not going there.
# define MIN_INTERVAL 1

// The maximum interval between updates.
# define MAX_INTERVAL 10

// If the user enters something really wacked out for the count of the
// number of times to update the display (like something that is not a
// number or a negative value), i just fallback to this.
# define FALLBACK_COUNT 5

// This means the user must press Control-c to exit.
# define INFINITE_COUNT 0

// The maximum width of a string to print to the screen. If the string
// returned from reading output from popen() exceeds this value,
// truncate it.
# define DEFAULT_COLS 100

// This is the value you pass to printf() to clear the screen each time
// before an display update.
# define CLEAR_SCREEN "\033[2J\033[H"

#endif // _MONITORASAURUS_H
