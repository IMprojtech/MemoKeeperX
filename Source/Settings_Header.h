
/*! Contiene le definizioni e le variabili usate per le impostazioni del programma !*/

#include <regex.h>
#include <sys/stat.h>

// Anagrafica programma
#define NAME "MemoKeeperX"
#define ALIAS "mkx"
#define VER "3.2"

// File di default
#define Dir "/.config"
#define SetFile "/MemoKX.conf"
#define DefaultFile "/Notes_Map.X"

// Dimenzioni campi
#define SizeDefaultSet 11
#define SizePathFiles 201
#define SizeBuf 201

// Impostazioni di default
char  HashPass[65] = {'\0'};

char Editor[SizeDefaultSet]     = {"NUL"};
char Font[SizeDefaultSet]       = {"GRS"};
char Color_Hash[SizeDefaultSet] = {"RED"};
char Color_Date[SizeDefaultSet] = {"GRN"};
char Color_Tag[SizeDefaultSet]  = {"YEL"};
char Color_Note[SizeDefaultSet] = {"WHT"};
char Color_File[SizeDefaultSet] = {"BLU"};
char Color_Memo[SizeDefaultSet] = {"CYN"};

char *DirHome;
char  Setting[SizePathFiles]   = {'\0'};
char  File_Note[SizePathFiles] = {'\0'};

FILE *PtrFileSet;
