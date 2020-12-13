#include <stdio.h>
#include <stdlib.h>

#define RESET_COLOR_INDEX 4

char COLOR_CODES[5][255] =
{
	"\033[1m\033[30m",		// Bold BLACK
	"\033[1m\033[31m",		// Bold RED
	"\033[1m\033[32m",		// Bold GREEN
	"\033[1m\033[34m",		// Bold BLUE
	"\x1B[0m"				// Reset
};

int main (int argc, char *argv[])
{
    //code here
    return 0;
}