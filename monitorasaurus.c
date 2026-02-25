// Haleah Mauck
// 2/24/2026
// CS-314-006
// Lab4 monitorasaurus
// hmauck@pdx.edu
// this is the implementation file for the monitorasaurus program
 
//valgrind --leak-check=full --show-leak-kinds=all
 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

static int v = 0;

int main(int argc, char * argv[]) {

    int refreshInterval = 2;
    int refreshCount = 0;
    int width = 100;

    {

        int opt -1;
        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
                case 'i':
                    refreshInterval = optarg;
                     break;
                case 'c':
                    refreshCount = optarg;
                    break;
                case 'w':
                    width = optarg;
                    break;
                case 'v':
                    v = 1;
                    break;
                case 'h':
                    printf("Usage: monitorasaurus -[i:c:w:vh]\n");
                    printf("        -i #    set the refresh interval, in seconds. Default is 2.\n");
                    printf("        -c #    set the count of how many times the output will refresh before exiting.\n");
                    printf("                Default is 0 (don't stop).\n");
                    printf("        -w #    set the width of text to display. Default is 100.");
                    printf("        -v      minimal verbose output\n");
                    printf("        -h      show this amazing help and exit\n");
                    exit(EXIT_SUCCESS);
                    break;
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
    }
}










    exit(EXIT_SUCCESS);


}
  