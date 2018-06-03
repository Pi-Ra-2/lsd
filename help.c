#include <stdio.h>
#include "help.h"

void
usage(char *pName)
{
	fprintf(stderr, "Usage: %s [options] filename\n", pName);
	printf("Try %s -h for more help\n\n", pName);
}

void
printHelp(char *pName, float version, char *auth)
{
	printf("\n%s:\n", pName);
	printf("the Linux Simple Dump command dumps decimal or hexadecimal values of file and each\n");
	printf("printable character. An # char substitutes each no printable char.\n");
	printf("No printable character it's usually a carriage return '\\n' (with value 10 in decimal)\n");
	printf("in a plain text file, but can be another one. You can see in the hexa|decimal values\n\n");
	printf("Usage:\n%s [options] file\n\n", pName);
	printf("Options:\n");
	printf("    -h          Prints this help\n");
	printf("    -b N        Dump only the N plus 8 bytes\n");
	printf("    -g N        Print output bytes in groups of N. Not implemented yet\n");
	printf("    -t d|x      Print output in (d)ecimal, he(x)adecimal or (c)har type\n");
	printf("If no options are introduced, %s dumps the entire file with decimal values\n\n", pName);
	printf("%s is released under the GPL license. Feel free to copy, modify or redistribute it\n", pName);
	printf("%s version %3.2f\n", pName, version);
	printf("(C) 2018 %s\n\n", auth);
}
