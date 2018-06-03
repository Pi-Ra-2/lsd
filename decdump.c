/*
 * decdump.c
 *
 * Linux Simple Dump
 * (c) A. Jiménez, 2018
 *
 * Main file for the lsd program, a Linux Simple Dump command 
 * lsd dumps a file in decimal, hexadecimal or char mode
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

#define SHOWCHARS 8
char *auth = "A.Jiménez";
float version = 1.01;

int
main (int argc, char **argv)
{
	int  tflag = 0, bflag = 0, hflag = 0;
	int bytes = 0;
	int c;
	char *dumpType = NULL;
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
        while ((c = getopt(argc, argv, "+hb:t:")) != -1)
        {
		switch(c)
		{
		        case 'h':
			        hflag = 1;
				break;
		        case 'b':
				bflag = 1;
				bytes = optarg;
				break;
		        case 't':
				dumpType = optarg;
				break;
		        case '?':
				if (optopt == 't')
				{
					fprintf(stderr, "Option -%c requires an argument\n", optopt);
					usage(progName);
					return USAGE_ERROR;
				}
				else if (isprint(optopt))
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
		printHelp(progName, version, auth);
		return 0;
	}
        FILE *infile;
        if ((infile = fopen(filename, "r")) == NULL)
        {
	        return printError(MEM_ALLOC_ERROR, progName);
        }
        c = 0;
        int cols = 0;
        
        printf("\n");
	int bytesPrinted = 0;
	unsigned char buffer[8];

	printf("address    |  values                            | chars\n");
	printf("==========================================================\n");
        while (!feof(infile))
        {
		fread(buffer, sizeof(char), 8, infile);
		for (int i = 0; i < 8; i++)
		{
			if (buffer[i] == EOF)
			{
				buffer[i] = '*';
			}
		}
		printf("%.10x |  ", bytesPrinted);
		cols = cols + 14;
		for (int i = 0; i < 8; i++)
		{
		        printf("%.3d ", buffer[i]);
			cols = cols + 4;
		}
		printf("  | ");
		for (int i = 0; i < 8; i++)
		{
			if (isprint(buffer[i]))
			{
	                        printf("%c", buffer[i]);
				cols = cols + 8;
			}
			else
			{
				printf("#");
			}
		}
		if (cols >= 60)
		{
			printf("\n");
			cols = 0;
		}
		bytesPrinted = bytesPrinted + 8;
		      
        }
        printf("\n");
        fclose(infile);

        return 0;
}

