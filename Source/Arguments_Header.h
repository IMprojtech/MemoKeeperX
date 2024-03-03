
/*! Contiene gli identificatori le strutture e le tabelle di compatibilità 
 * 	che permettono il controllo degli argomenti passati al programma !*/
 
#include <getopt.h>

#define LONG_SIZE 14
#define SHORT_SIZE 11

//----------- Long Argument

enum{ // Long Cases 
	LONG_OPT_HELP = 0, 		// 1
	LONG_OPT_SETTING,		// 2
	LONG_OPT_ADDFILE,		// 3
	LONG_OPT_SHOWFILE,		// 4
	LONG_OPT_SETFILE,		// 5
	LONG_OPT_COLOR_HASH,	// 6
	LONG_OPT_COLOR_DATE,	// 7
	LONG_OPT_COLOR_TAG,		// 8
	LONG_OPT_COLOR_NOTE, 	// 9
	LONG_OPT_COLOR_FILE,	// 10
	LONG_OPT_COLOR_MEMO,	// 11
	LONG_OPT_FONT,			// 12
	LONG_OPT_EDITOR,		// 13
	LONG_OPT_MAP			// 14
};

const struct option long_options[] = { // Struct Long Cases
	{"setting", no_argument, NULL, LONG_OPT_SETTING},
	{"help", no_argument, NULL, LONG_OPT_HELP}, 
	{"addfile", no_argument, NULL, LONG_OPT_ADDFILE},
	{"showfile", no_argument, NULL, LONG_OPT_SHOWFILE},
	{"setfile", required_argument, NULL, LONG_OPT_SETFILE},        
	{"color_hash", required_argument, NULL, LONG_OPT_COLOR_HASH},
	{"color_date", required_argument, NULL, LONG_OPT_COLOR_DATE},
	{"color_tag", required_argument, NULL, LONG_OPT_COLOR_TAG},
	{"color_note", required_argument, NULL, LONG_OPT_COLOR_NOTE},
	{"color_file", required_argument, NULL, LONG_OPT_COLOR_FILE},
	{"color_memo", required_argument, NULL, LONG_OPT_COLOR_MEMO},        
	{"font", required_argument, NULL, LONG_OPT_FONT},
	{"editor", required_argument, NULL, LONG_OPT_EDITOR},      
    {"map", no_argument, NULL, LONG_OPT_MAP},               
	{NULL, 0, NULL, 0}
};

bool CompatibleLongOptions[][LONG_SIZE] = { // Boolean Compatibility Table
  //   1   	    2        3        4        5        6        7        8        9       10       11       12       13	   14
	{false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false}, // 1
	{false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false}, // 2
	{false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false}, // 3
	{false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false}, // 4
    {false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false}, // 5
    {false,   false,   false,   false,   false,   false,   true,    true,    true,    true,    true,    true,    true,    false}, // 6
    {false,   false,   false,   false,   false,   true,    false,   true,    true,    true,    true,    true,    true,    false}, // 7
    {false,   false,   false,   false,   false,   true,    true,    false,   true,    true,    true,    true,    true,    false}, // 8 
    {false,   false,   false,   false,   false,   true,    true,    true,    false,   true,    true,    true,    true,    false}, // 9
    {false,   false,   false,   false,   false,   true,    true,    true,    true,    false,   true,    true,    true,    false}, // 10
    {false,   false,   false,   false,   false,   true,    true,    true,    true,    true,    false,   true,    true,    false}, // 11
    {false,   false,   false,   false,   false,   true,    true,    true,    true,    true,    true,    false,   true,    false}, // 12
    {false,   false,   false,   false,   false,   true,    true,    true,    true,    true,    true,    true,    false,   false}, // 13
    {false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false,   false}  // 14
};

//----------- Short Argument

enum{ // Short Cases 
	SHORT_OPT_REMOVE = 0,	// 1
	SHORT_OPT_HASH,			// 2
	SHORT_OPT_FILE,			// 3
	SHORT_OPT_PATHFILE,		// 4
	SHORT_OPT_DATE,			// 5
	SHORT_OPT_TAG,			// 6
	SHORT_OPT_APPEND,		// 7
	SHORT_OPT_SHOW,			// 8			
	SHORT_OPT_EXTEND,		// 9
	SHORT_OPT_WRITE,		// 10
	SHORT_OPT_MEMO			// 11
};	

const char* short_options = "rh:fFd:t:a:sewM"; // Array Short Cases

bool CompatibleShortOptions[][SHORT_SIZE] = { // Short Cases
  //   1  	    2        3        4        5        6        7        8        9       10       11  
	{false,   true,    false,   false,   false,   true,    false,   false,   false,   false,   false}, // 1
	{true,    false,   true,    true,    false,   false,   false,   false,   true,    false,   true},  // 2
	{false,   true,    false,   false,   false,   true,    false,   false,   false,   false,   false}, // 3
	{false,   true,    false,   false,   false,   true,    false,   false,   false,   false,   false}, // 4
    {false,   false,   false,   false,   false,   false,   false,   false,   true,    false,   true},  // 5
    {true,    false,   true,    true,    false,   false,   true,    false,   true,    true,    true},  // 6
    {false,   false,   false,   false,   false,   true,    false,   false,   false,   true,    true},  // 7
    {false,   false,   false,   false,   false,   false,   false,   false,   true,    false,   false}, // 8 
    {false,   true,    false,   false,   true,    true,    false,   true,    false,   false,   true},  // 9
    {false,   false,   false,   false,   false,   true,    true,    false,   false,   false,   true},  // 10
	{false,   true,    false,   false,   true,    true,    true,    false,   true,    true,    false}  // 11

};

//-------------------------

bool LongOptions[LONG_SIZE] = {false}; // Options Long
bool ShortOptions[SHORT_SIZE] = {false}; // Options Short
