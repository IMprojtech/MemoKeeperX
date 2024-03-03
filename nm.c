
/* Programma per la gestione delle note, permette di prendere, organizzare e catalogare appunti
*  direttamente dal terminale linux e ritrovarli rapidamente grazie all' ausilio di tag;
*  permette inoltre di linkare interi file per poterli visualizzare a piacimento */

#include <stdio.h>
#include "Source/Global.h"
 
int main(int argc, char **argv){
	
memset(&NDat,0,sizeof (NotesData));

Direct = getenv("HOME"); strcat(Direct,Dir); 
strcpy(Setting,Direct); strcat(Setting,SetFile);
strcpy(DefaultFile,Direct); strcat(DefaultFile,FileNotes); 

if ((PtrFile = fopen (Setting, "r")) == NULL ){ 
	Primo_Avvio(); Help(); exit(0); }
 
else{ fclose( PtrFile );
	if (argc < 2 ){ Help(); return 0;}
	SetRead(); Scanner(argc, argv);}	

return 0;}

