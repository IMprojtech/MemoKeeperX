
/* Contiene librerie e variabili globali usate nel programma*/

#include <regex.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>                  
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

 #define NAME  "MemoKeeper"
 #define ALIAS  "mk"  
 #define VER  "2.0"
 
 #define Dir   "/.config" 
 #define SetFile   "/MemoK.conf"
 #define DefaultFile  "/Notes.Dat"
   
 #define GRS   "\e[1m"
 #define NML   "\e[0m"
 #define RED   "\x1B[31m"
 #define GRN   "\x1B[32m"
 #define YEL   "\x1B[33m"
 #define BLU   "\x1B[34m"
 #define BLK   "\x1B[30m"
 #define MAG   "\x1B[35m"
 #define CYN   "\x1B[36m"
 #define WHT   "\x1B[37m"
 #define NUL   ""

char Editor[10]={"NUL"};
char Font[10]={"GRS"};

char Color_Index[10]={"RED"};
char Color_Date[10]={"GRN"};
char Color_Tag[10]={"YEL"};
char Color_Note[10]={"WHT"};
char Color_File[10]={"BLU"};

typedef struct{  //! Notes
	int Index;
	char Tag[21]; 
	char Note[501];				
	char Link_File[201];
	char Data[12]; 
} NotesData;

NotesData NDat;

char *DirHome; 
char Setting[151]={'\0'};
char File_Note[151]={'\0'};
  
char DefaultTag[21]={"T01"};

char bit=' '; 

bool Extended=false;
bool Invert=false;
 
FILE *PtrFile;  
	
time_t rawtime;
struct tm *ptm;

#include "Error.h"
#include "Switchs.h"
#include "Print.h"
#include "Setting.h"
#include "Manager.h" 
#include "List.h"
#include "Logic.h"
