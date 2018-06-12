#include <stdio.h>
#include "help.h"
#include "lsd.h"

void
usage(char *pName)
{
	fprintf(stderr, "Usage: %s [options] filename\n", pName);
	printf("Try %s -h for more help\n\n", pName);
}

void
printHelp(char *pName)
{
	printf("\n%s:\n", pName);
	printf("the Linux Simple Dump command dumps decimal or hexadecimal values of file and each\n");
	printf("printable character. An # char substitutes each no printable char.\n");
	printf("Newline and tab characters are represented by \"\\n\" and \"\\t\" respectively \n\n");
	printf("Usage:\n%s [options] file\n\n", pName);
	printf("Options:\n");
	printf("    -h          Prints this help\n");
	printf("    -b N        Dump only N rows of 8 bytes\n");
	printf("    -d          Print output values in decimal\n");
	printf("    -x          Print output values in hexadecimal\n");
	printf("If no options are introduced, %s dumps the entire file with decimal values\n\n", pName);
	printf("Examples:\n");
	printf("%s -x -d -b 10 /etc/dictionaries-common/words\n", pName);
	printf("output the 80 first bytes in \"words\" file in decimal and hexadecimal form\n\n");
	printf("%s is released, with no warranty, under the GPL license. Feel free to copy, \n", pName);
	printf("modify or redistribute it\n");
	printf("\nPlease send comments, reports and contributions to " LSD_REPO "\n");
	printf("%s version " VERSION "\n", pName);
	printf("(C) 2018 " AUTHOR "\n\n");
}
