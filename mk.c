
/* Programma per la gestione delle note, permette di prendere, organizzare e catalogare appunti
*  direttamente dal terminale linux e ritrovarli rapidamente grazie all' ausilio di tag;
*  permette inoltre di linkare interi file per poterli visualizzare a piacimento */

#include <stdio.h>
#include "Source/Global.h"
 
int main(int argc, char **argv){
	
memset(&NDat,0,sizeof (NotesData));

Start_System_Check();
printf("%s",Font); 
 
Scanner(argc, argv); 
return 0;}
