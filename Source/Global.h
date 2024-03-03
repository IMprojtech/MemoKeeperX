
/*! Contiene librerie e variabili globali usate nel programma !*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define GRS "\e[1m"
#define NML "\e[0m"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define BLK "\x1B[30m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define NUL ""

typedef struct { //! Notes
    char  Tag[24];
    char  Comment[501];
    char  Link_File[201];
    char  Date[20];
} NotesData;

NotesData NDat = {0};

char *Memo;

char In_Hash[42];
char In_Tag[50];
char In_Date[20];

char Parent_Hash[42];

char DefaultTag[] = {"T01"};

bool Map      = false;
bool Mem      = false;
bool Show     = false;
bool Write    = false;
bool Remove   = false;
bool File     = false;
bool FilePath = false;
bool Extended = false;
bool Organize = false;
bool Modify = false;

#include "Header.h"
#include "Error.h"
#include "Settings_Processing.c"
#include "Arguments_Processing.c"
#include "Tree_Processing.c"
#include "File_Operations.h"
#include "General_Functions.h"
#include "Map.c"
