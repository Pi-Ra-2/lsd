#include <stdio.h>
#include "errors.h"
#include "help.h"

int
printError(int errorCode, char *pName)
{
	switch (errorCode)
	{
	        case USAGE_ERROR:
		    usage(pName);
		    //returUSAGE_ERROR);
		    break;
	        case FILE_OPEN_ERROR:
		    fprintf(stderr, "Error: can't open the file\n");
		    //exit(FILE_OPEN_ERROR);
		    break;
                case MEM_ALLOC_ERROR:
		    fprintf(stderr, "Error: Unable to allocate memory\n");
		    //exit(MEM_ALLOC_ERROR);
		    break;
	        default:
		    fprintf(stderr, "An unknown error has ocurred, please report\n");
		    //exit(UNKNOWN_ERROR);
                    break;
	}
        return errorCode;
}
