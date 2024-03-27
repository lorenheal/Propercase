#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#ifndef true
#define true (1)
#define false (0)
#endif


/*
* casecount - count upper/lower/special chars
*/

#define DEBUG(X) ((X)&&(0)) /* {(1),(0)} turns {on,off} debugging */

char buf[1024];

void * xmalloc(unsigned int );

#define OptString ("")
char * NULLString = "";

void help(char *progname) 
{ 
printf("Usage:\n%s  \n", progname); 
printf("...where \"x\" is one of %s\n", OptString); 
}

int
main(int argc, char **argv)
{
int inc;
int other;
int up;
int low;
int total;
total = low = up = other = 0;
while((inc = getchar()) != EOF)
	{
	total++;
	if(isupper(inc)) 
		up++;
	else if(islower(inc)) 
		low++;
	else 
		other++;
	}
printf("up:%d\t(%f)\nlow:%d\t(%f)\nother:%d\t(%f)\ntotal:%d (%d)\n",
	up, (double) (100*up)/total, low, (double) (100*low)/total, other,(double)  (100*other)/total, total, up+low+other);
return(0);
}


void * 
xmalloc(unsigned int request)
{
void *ret = NULL;
if(!(ret = malloc(request)))
	{
	perror("Memory alloc fail.");
	exit(1);
	}
return(ret);
}

