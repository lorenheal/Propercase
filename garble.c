#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

/************************************************************
 * garble.c
 * 
 * Generates a bunch of Englishy words that probably
 * aren't in the dictionary. 
 *
 * Marginally useful to test text filters.
 ************************************************************/

 /*
 * There are no command line options. It might be kind to 
 * default to spitting out 10 random wordishes or something, and
 * to put a message like this in a help screen.
 *
 * I chose not to look up words in /usr/share/dict/words
 *
 * To get real words, just grep roots from there.
 *
 * Also, the roots are all Greek and Latin; Germanic roots
 * are not listed.
 * 
 * To make the output more friendly, pipe it through 
 * head, tail, fmt or sort -R.
 */


char *roots[] = {
"",
"ambi",
"aqua",
"aud",
"bene",
"cent",
"circum",
"contra",
"counter",
"dict",
"duc",
"duct",
"fac",
"form",
"fort",
"fract",
"ject",
"jud",
"mal",
"mater",
"mit",
"mort",
"multi",
"pater",
"port",
"rupt",
"scrib",
"scribe",
"sect",
"sec",
"sent",
"spect",
"struct",
"vid",
"vis",
"voc",
"anthropo",
"auto",
"bio",
"chron",
"dyna",
"dys",
"gram",
"graph",
"hetero",
"homo",
"hydr",
"hypo",
"logy",
"meter",
"metr",
"micro",
"mis",
"miso",
"mono",
"morph",
"nym",
"phil",
"phobia",
"phon",
"photo",
"phos",
"pseudo",
"psycho",
"scope",
"techno",
"tele",
"therm"
};

char *prefixes[] = {
"",
"anti",
"de",
"dis",
"en",
"em",
"fore",
"in",
"im",
"in",
"im",
"il",
"ir",
"inter",
"mid",
"mis",
"non",
"over",
"pre",
"re",
"semi",
"sub",
"super",
"trans",
"un",
"under"
};

char *suffixes[] = {
"",
"able",
"ible",
"al",
"ial",
"ed",
"en",
"er",
"or",
"er",
"est",
"ful",
"ic",
"ing",
"ion",
"tion",
"ation",
"tion",
"ity",
"ty",
"ive",
"ative",
"itive",
"less",
"ly",
"ment",
"ness",
"ous",
"eous",
"ious",
"s",
"es",
"y"
};



/************************************************************
 * What this does
 Create a bunch of Englishy words
 ************************************************************/

 int rootmax = 68;
 int sufmax = 33;
 int premax = 25;

int
main(int argc, char **argv)
	{
	int r, s, p;

	for (r = 0; r < rootmax; r++)
		{
		for (s = 0; s < sufmax; s++)
			{
			for (p = 0; p < premax; p++)
				{
				printf("%s%s%s\n",prefixes[p], roots[r], suffixes[s]);
				}
			}
		}
	return(0);
	}

/************************************************************
 * end main()
 ************************************************************/

/************************************************************
 * end
 ************************************************************/
