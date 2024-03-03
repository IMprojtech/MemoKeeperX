
/* Contiene librerie e variabili globali usate nel programma*/

#include <regex.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>                  
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

 #define NAME  "Note Management"
 #define ALIAS  "nm"  
 #define VER  "1.1"
 
 #define Dir  "/.config" 
 #define SetFile  "/nm.conf" 
 #define FileNotes  "/Notes.Dat"
   
 #define GRS  "\e[1m"
 #define NML  "\e[0m"
 #define RED  "\x1B[31m"
 #define GRN  "\x1B[32m"
 #define YEL  "\x1B[33m"
 #define BLU  "\x1B[34m"
 #define BLK  "\x1B[30m"
 #define MAG  "\x1B[35m"
 #define CYN  "\x1B[36m"
 #define WHT  "\x1B[37m"

typedef struct{  //! Notes
	int Index;
	char Tag[21]; 
	char Note[501];				
	char Link_File[201];
	char Data[12]; 
} NotesData;

NotesData NDat;

char *Direct; 
char Setting[201]={'\0'};
char DefaultFile[201]={'\0'};
char DefaultTag[21]={"T01"};

char Vbit[8]={"        "}; 

FILE *PtrFile;  
	
time_t rawtime;
struct tm *ptm;

#include "Error.h"
#include "Switchs.h"
#include "Print.h"
#include "Manager.h" 
#include "List.h"
#include "Logic.h"
