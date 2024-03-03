
/*! Contiene la funzione principale per la gestione degli argomenti,
 *  utilizza la libreria getopt !*/

/* Lo scopo del primo ciclo for ed effetuare 2 passaggi al interno degli argomenti passati
 * al primo passaggio si effettua un controllo per definirne la correttezza e compatibilità fra loro
 * il secondo passaggio richiama le funzioni specifiche per l'argomento */

// optind=1; serve per reinizializzare la variabile prima del secondo passaggio di getopt

#include "Arguments_Functions.h"

void ProcessArguments(int argc, char *argv[]) {

    int opt;
    opterr = 0; // disabilita la stampa automatica degli errori di getopt

    for (int i = 0; i < 2; i++) {
        optind = 1;
        while ((opt = getopt_long(argc, argv, short_options, long_options,
                                  NULL)) != -1) {
            switch (opt) {

                //----------Long Cases
            case LONG_OPT_HELP:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_HELP);
                else {
                    Help();
                    exit(0);
                }
                break;

            case LONG_OPT_SETTING:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_SETTING);
                else {
                    printf("%s\n", Setting);
                    exit(0);
                }
                break;

            case LONG_OPT_ADDFILE:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_ADDFILE);
                else {
                    Set("AddFile", 0, NULL);
                    exit(0);
                }
                break;

            case LONG_OPT_SHOWFILE:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_SHOWFILE);
                else {
                    Set("ShowFile", 0, NULL);
                    exit(0);
                }
                break;

            case LONG_OPT_SETFILE:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_SETFILE);
                else {
                    Set("SetFile", atoi(optarg), NULL);
                    exit(0);
                }
                break;

            case LONG_OPT_COLOR_HASH:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_COLOR_HASH);
                else
                    Set("Color_Hash=", 0, optarg);
                break;

            case LONG_OPT_COLOR_DATE:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_COLOR_DATE);
                else
                    Set("Color_Date=", 0, optarg);
                break;

            case LONG_OPT_COLOR_TAG:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_COLOR_TAG);
                else
                    Set("Color_Tag=", 0, optarg);
                break;

            case LONG_OPT_COLOR_NOTE:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_COLOR_NOTE);
                else
                    Set("Color_Note=", 0, optarg);
                break;

            case LONG_OPT_COLOR_FILE:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_COLOR_FILE);
                else
                    Set("Color_File=", 0, optarg);
                break;

            case LONG_OPT_COLOR_MEMO:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_COLOR_MEMO);
                else
                    Set("Color_Memo=", 0, optarg);
                break;

            case LONG_OPT_FONT:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_FONT);
                else
                    Set("Font=", 0, optarg);
                break;

            case LONG_OPT_EDITOR:
                if (i == 0)
                    CheckLongCompatibility(LONG_OPT_EDITOR);
                else
                    Set("Editor=", 0, optarg);
                break;

            case LONG_OPT_BACKUP:
                if (i == 0) 
                    CheckLongCompatibility(LONG_OPT_BACKUP);
                else                  
					Backup();
                break;

                //----------Short Cases
            case 'r':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_REMOVE);
                    Remove = true;
                }
                break;

            case 'h':
                if (i == 0)
                    CheckShortCompatibility(SHORT_OPT_HASH);
                else
                    LoadStruct(In_Hash, optarg, sizeof(In_Hash) - 1);
                break;

            case 'f':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_FILE);
                    File = true;
                }
                break;

            case 'F':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_PATHFILE);
                    FilePath = true;
                }
                break;

            case 'd':
                if (i == 0)
                    CheckShortCompatibility(SHORT_OPT_DATE);
                else
                    LoadStruct(In_Date, optarg, sizeof(In_Date) - 1);
                break;

            case 't':
                if (i == 0)
                    CheckShortCompatibility(SHORT_OPT_TAG);
                else
                    LoadStruct(In_Tag, optarg, sizeof(In_Tag) - 1);
                break;

            case 'a':
                if (i == 0)
                    CheckShortCompatibility(SHORT_OPT_APPEND);
                else
                    LoadStruct(NDat.Link_File, optarg,
                               sizeof(NDat.Link_File) - 1);
                break;

            case 's':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_SHOW);
                    Show = true;
                }
                break;

            case 'e':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_EXTEND);
                    Extended = true;
                }
                break;

            case 'w':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_WRITE);
                    Write = true;
                }
                break;

			case 'o':
                if (i == 0){
                    CheckShortCompatibility(SHORT_OPT_ORGANIZE); 
                  	Organize = true;
				}                              
				else {
	       			LoadStruct(In_Hash, argv[--optind], sizeof(In_Hash) - 1);
					LoadStruct(Parent_Hash, argv[++optind], sizeof(Parent_Hash) - 1); 
				}	  	
                break;     

			case 'm':
                if (i == 0)
                    CheckShortCompatibility(SHORT_OPT_MODIFY);
                else{
                    LoadStruct(In_Hash, optarg, sizeof(In_Hash) - 1);
					Modify = true;    
				}	            
                break;

            case 'X':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_MEMO);
                    Mem = true;
                }
                break;

            case 'P':
                if (i == 0) {
                    CheckShortCompatibility(SHORT_OPT_PROTECT);
                    Protect = true;
                }
                break;
                
            case '?':
                if (optopt != 0)
                    Error(ErrorArgument, "");
                else
                    Error(ErrorOption, "");
                break;
            }
        }

        if (optind < argc && Write == false && Organize == false )
            Error(ErrorArgument, "");
    }

    if (Write == true ) {
        for (int j = optind; j < argc; j++) {
            LoadComment(NDat.Comment, argv[j], sizeof(NDat.Comment) - 1);
        } 
    }
    if (Organize == true) { 
		if (argc != 4)
 			Error(ErrorArgument, "");
		if (Protect != true)
			Error(ErrorArgument, "protected use \"-Po\"");
	}
}
