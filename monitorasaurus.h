// Haleah Mauck
// 2/24/2026
// CS-314-006
// Lab4 monitorasaurus
// hmauck@pdx.edu
// this is the header file for the monitorasaurus program



#define OPTIONS "icwvh"
#define NICE_INCREMENT 10


#ifdef NOISY_DEBUG 
# define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__)
#else // NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif // NOISY_DEBUG

static int v = 0;
