Propercase 
This little C program filters ASCII text on the command line to put it into various forms.
It was designed to create titles for DVD and Blu-Ray disks. Sometimes the title embedded in a DVD will have cruft characters, embedded spaces, or have funky capitalization.

Along the way, it got the ability to format the text in a variety of ways. All of this can be done with sed scripts, but those can get awkward.

propercase.c
propercase -[haBlprtz] -x arg -g arg -b arg -[n] 
-h  this help 
-p  Proper case (the default)
-a  ALL CAPS 
-B  B A N N E R 
-l  lower case 
-r  RAnSom caSe 
-t  Title Case 
-z  laZy case (do nothing) 
-n  treat newlines as start 
With -g, arg is the incoming word separator, space by default
With -b, arg is the string to put between words, if any.
with -x,  arg character output padding string 

casecount.c  
This is a simple program to count the uppercase, lowercase, and special characters in the input stream.

garble.c
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

$ ./garble | sort -R | fmt -60 | head
decontrament emtechnoeous imhomoeous imhomoeous forenymment
nondynament midfacing renymial emjectment midsectty
supersentous unscribity informty informty irscribety
premonoeous transmonoor uncontraer uncontraer preaquation
preaquation unmicroed immisoor immisoor midscribless
inbeneible inbeneible inmisoed inmisoed inscribeious
inscribeious mislogyy nonjecteous overfractative
midscribest deteleest forevidic prestructs ilphotoen
irmortly disscribeer disscribeer nonmicroly foregraphous
overaquaative midjection nonautoed enchronity enmultiible


dvdback 
# This is a bash script to create isos from a stack of DVDs. 
# Created on Ubuntu 22 and tested on 23.
# It relies on findmnt(1), ddrescue(1), and propercase(1). 
# findmnt(1) should be on every Linux system.
# (optional) ddrescue is available at https://www.gnu.org/software/ddrescue/
# (optional) propercase is at https://github.com/lorenheal/Propercase
#
