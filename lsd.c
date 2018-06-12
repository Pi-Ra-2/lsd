/*
 * lsd.c
 *
 * Linux Simple Dump
 * (c) A. Jiménez, 2018
 *
 * Main file for the lsd program, a Linux Simple Dump command 
 * lsd dumps a file in decimal or hexadecimal mode
 *
 * lsd [option] filename 
 *
 * Try lsd -h for help
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "errors.h"
#include "help.h"
#include "lsd.h"

#define SHOWCHARS 8
int bflag = 0;

void decDump(FILE *in, int maxBytes);
void hexDump(FILE *in, int maxBytes);

int
main (int argc, char **argv)
{
	int dflag = 0, xflag = 0, hflag = 0;
	int c;
	int bytes = 0;
	char *progName;
	progName = argv[0];

	for(char *pp = progName; *pp;)
	{
		if (*pp++ == '/')
		{
			progName = pp++;
		}
        }
        if (argc < 2)
        {
                usage(progName);
                return USAGE_ERROR;
        }
        opterr = 0;
        while ((c = getopt(argc, argv, "+hdxb:")) != -1)
        {
		switch(c)
		{
		        case 'h':
			        hflag = 1;
				break;
		        case 'b':
				bflag = 1;
				bytes = atoi(optarg);
				break;
		        case 'd':
				dflag = 1;
				break;
		        case 'x':
				xflag = 1;
			        break;
		        case '?':
				if (isprint(optopt))
				{
					fprintf(stderr, "Unknown option '-%c'\n", optopt);
					usage(progName);
					return USAGE_ERROR;
				}
				else
				{
					fprintf(stderr, "Unknown option character \\x%x\n", optopt);
				}
		        default:
				abort();
		}
		
			
        }

        char *filename = argv[optind];

	if (hflag == 1)
	{
		printHelp(progName);
		return 0;
	}
	if (xflag == 0 && dflag == 0)
	{
		dflag = 1;
	}
	
        FILE *infile;
        if ((infile = fopen(filename, "r")) == NULL)
        {
	        return printError(FILE_OPEN_ERROR, progName);
        }

	if (dflag == 1)
	{
                decDump(infile, bytes);
	}
	if (xflag == 1)
	{
		hexDump(infile, bytes);
	}

        fclose(infile);

        return 0;
}

void
decDump(FILE *in, int maxBytes)
{
	int bytesPrinted = 0;
	
        int cols = 0;
	unsigned char buffer[8];
	printf("\n                       DECIMAL DUMP                   \n");
	printf("==================================================================\n");
	printf("address    |  values                            | chars\n");
	printf("==================================================================\n");
        while (!feof(in))
        {
		memset(buffer, 0, sizeof(char) * 8);
		fread(buffer, sizeof(char), 8, in);
		bytesPrinted += 8;
		for (int i = 0; i < 8; i++)
		{
			if (buffer[i] == EOF)
			{
				buffer[i] = '*';
			}
		}
		printf(COLOR_BLUE "%.10x" RESET_COLOR " |  ", bytesPrinted);
		cols = cols + 14;
		for (int i = 0; i < 8; i++)
		{
		        printf(COLOR_YELLOW "%.3d " RESET_COLOR, buffer[i]);
			cols = cols + 4;
		}
		printf("  | ");
		for (int i = 0; i < 8; i++)
		{
			if (isprint(buffer[i]))
			{
	                        printf("%c" COLOR_RED "." RESET_COLOR, buffer[i]);
				cols = cols + 16;
			}
			else
			{
			        switch (buffer[i])
				{
				        case '\n':
					        printf(COLOR_YELLOW "\\n"COLOR_RED"." RESET_COLOR);
						break;
				        case '\t':
					        printf(COLOR_YELLOW "\\t"COLOR_RED"." RESET_COLOR);
						break;
				        default:
						printf(COLOR_YELLOW "#"COLOR_RED"." RESET_COLOR);
						break;
					
				}
				cols = cols + 3;
			}
		}
		if (cols >= 60)
		{
			printf("\n");
			cols = 0;
		}

		if ((bflag == 1) && (bytesPrinted >= maxBytes * 8))
		{
			break;
		}
	        
		      
        }
        printf("\n");
	printf("%d bytes dumped\n\n", bytesPrinted);
	rewind(in);
}

void
hexDump(FILE *in, int maxBytes)
{
	int bytesPrinted = 0;
	
        int cols = 0;
	unsigned char buffer[8];
	printf("\n                         HEX DUMP                    \n");
	printf("==================================================================\n");
	printf("address    |  values                            | chars\n");
	printf("==================================================================\n");
        while (!feof(in))
        {
		memset(buffer, 0, sizeof(char) * 8);
		fread(buffer, sizeof(char), 8, in);
		bytesPrinted += 8;
		for (int i = 0; i < 8; i++)
		{
			if (buffer[i] == EOF)
			{
				buffer[i] = '*';
			}
		}
		printf(COLOR_BLUE "%.10x" RESET_COLOR " |  ", bytesPrinted);
		cols = cols + 14;
		for (int i = 0; i < 8; i++)
		{
		        printf(COLOR_YELLOW "%.2x  " RESET_COLOR, buffer[i]);
			cols = cols + 3;
		}
		printf("  | ");
		for (int i = 0; i < 8; i++)
		{
			if (isprint(buffer[i]))
			{
	                        printf("%c" COLOR_RED "." RESET_COLOR, buffer[i]);
				cols = cols + 16;
			}
			else
			{
				switch (buffer[i])
				{
				        case '\n':
					        printf(COLOR_YELLOW "\\n"COLOR_RED"." RESET_COLOR);
						break;
				        case '\t':
					        printf(COLOR_YELLOW "\\t"COLOR_RED"." RESET_COLOR);
						break;
				        default:
					        printf(COLOR_YELLOW "#"COLOR_RED"." RESET_COLOR);
						break;
				}
				cols = cols + 3;
			}
		}
		if (cols >= 60)
		{
			printf("\n");
			cols = 0;
		}
		if ((bflag == 1) && (bytesPrinted >= maxBytes * 8))
		{
			break;
		}
		      
        }
        printf("\n");
	printf("%d bytes dumped\n\n", bytesPrinted);
	rewind(in);
}
