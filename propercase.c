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
* propercase - Make text the desired case
*/

char *Helptext = "\
-h  this help \n\
-p  Proper case (the default)\n\
-a  ALL CAPS \n\
-B  B A N N E R \n\
-l  lower case \n\
-r  RAnSom caSe \n\
-t  Title Case \n\
-z  laZy case (do nothing) \n\
-n  treat newlines as start \n\
With -g, arg is the incoming word separator, space by default\n\
With -b, arg is the string to put between words, if any.\n\
with -x,  arg character output padding string \n";

char *OptString = "haBlprtzx:g:b:n";

char *NULLString = "";
char Propercase(int, int , char );
char ALLCAPScase(int, int , char);
char B_N_R_case(int, int , char);
char lowercase(int, int , char);
char rAnSomcase(int, int , char);
char Titlecase(int, int , char);
char lazycase(int, int , char );
int issep(char, char *);
void help(char *progname, char *optstring, char *helptext);
void getopthelp(char *optstring);


int
main(int argc, char **argv)
{
char (*func)(int lpos, int wpos, char curchar);
int opt;
int resetting = false; /* are we starting over at newlines? */
int linepos = 0; /* position from start of whole line */
int pos = 0; /*  position from start of current word */
char *betwixt = " "; /* string to put between output words */
char *betwchar = " "; /* string to put between output chars */
int use_betwchar = false; /* printing separator between characters  */
char *grep = " "; /*  string that marks input words */
char inc, outc; /* input, output character */

/* get input */
func = &Propercase;
while((opt = getopt(argc, argv, OptString)) != -1) 
	{
	switch(opt)
		{
		case 'a': func = &ALLCAPScase; /* all letters capped */
			break;
		case 'B': func = &B_N_R_case; /* all letters capped */
			use_betwchar = true;;
			break;
		case 'l': func = &lowercase; /* no caps */
			break;
		case 'p': func = &Propercase; /* Only first letter capped */
			break;
		case 'r': func = &rAnSomcase; /* rAndomISh LetterS CApped */
			break;
		case 't': func = &Titlecase; /* each first letter capped */
			break;
		case 'z': func = &lazycase; /* change no letters */
			break;
		case 'n': resetting = true; /* newline resets */
			break;
		case 'x':  /* separator between chars, if any */
			if (!optarg || *optarg =='\0')
				{
				betwchar = "_";
				}
			else
				{
				betwchar = strdup(optarg);
				}
			break;
		case 'g':  /* grep for this separator on the input */
			if (!optarg || *optarg =='\0')
				{
				help(argv[0], OptString, Helptext );
				exit(2);
				}
			else
				{
				grep = strdup(optarg);
				if(!sscanf(optarg,"%s",grep))
					{
					help(argv[0], OptString, Helptext);
					exit(3);
					}
				}
			break;
		case 'b':  /* blank separator string */
			if (!optarg || *optarg =='\0')
				{
				betwixt = NULLString;
				}
			else
				{
				betwixt = strdup(optarg);
				}
			break;
		case 'h': ;
			default:
			help(argv[0], OptString, Helptext);
			exit(1);
			break;
		}

	}
/*
*transform
*/
for(pos = 0; (inc = getchar()) != EOF; linepos++,pos++)
	{
	if((inc == '.' || inc == '!' || inc == '?')
		|| ((resetting == true ) && inc == '\n'))
		{
		linepos = pos = -1;
		}
	if(issep(inc, grep))
		{
		pos = -1;
		if(linepos == 0) linepos = -1;
		if(betwixt && *betwixt)
		 printf("%s", betwixt);
		}
	else if((outc=func(linepos, pos, inc)) != '\0')
		{
		putchar(outc);
		if(use_betwchar) 
			printf("%s", betwchar);
		}
	}
/* printf("\n"); */
return(0);
}

int
issep(char inc, char *grep)
{
/* return(grep && (inc == *grep));*/
int ret;
for( ret = false; grep && *grep; grep++)
	{
	if(inc == *grep) 
		{
		ret = true;
		break;
		}
	}
return(ret);
}

char
Propercase(int linepos, int pos, char inc)
{
char ret = tolower(inc);
if(linepos == 0)
	{
	ret = toupper(ret);
	}
return ret;
}

char lazycase(int linepos, int pos, char inc)
{
char ret = inc;
return(ret);
}

char lowercase(int linepos, int pos, char inc)
{
char ret = tolower(inc);
return ret;
}

char Titlecase(int linepos, int pos, char inc)
{
char ret = tolower(inc);
if(pos == 0)
	{
	ret = toupper(ret);
	}
return ret;
}

char ALLCAPScase(int linepos, int pos, char inc)
{
char ret = toupper(inc);
return ret;
}

char B_N_R_case(int linepos, int pos, char inc)
{
char ret = toupper(inc);
return ret;
}

char rAnSomcase(int linepos, int pos, char inc)
{
char ret = inc;
int r;
r = ((pos + 1) * (linepos + 1) ) + inc + pos + linepos;
r %= 3;

switch(r)
	{
	case 0: ret = tolower(ret);  break;
	case 1: ret = toupper(ret) ; break;
	case 2: if(inc %2 == 0)
			ret = tolower(ret);
		else
			ret = toupper(ret);
		break;
	};
if(linepos == 0)
	ret = toupper(ret); 
return (ret);
}


void help(char *progname, char *optstring, char *helptext)
{
printf("Usage:\n%s ", progname);
getopthelp(optstring);
printf("%s\n", helptext);
}

/*
* getopthelp - decode and display getopt(3) options 
* -- optstring is a string of getopt(3) options
*    like "abc:def". 
*/

void 
getopthelp(char *optstring)
	{
	int i;
	int grouping = false;
	char *s, c; 
	s = strdup(optstring);
	for(i = 0; (c = s[i]) != 0; i++)
		{
		if(isalpha(c))
			{
			if(s[i+1] == ':')
				{
				if(grouping)
					{
					printf("] "); 
					grouping = false;
					}
				printf("-%c arg ", c); 
				}
			else	
				{
				if(!grouping)
					{
					printf("-[");
					grouping = true;
					}
				printf("%c", c);
				}
			}
		else 
			{
			if(grouping) printf("] "); 
			grouping = false;
			}
		}
	if(grouping) { printf("] "); grouping = false; }
	printf("[args ...]\n");
	free(s);
	}

