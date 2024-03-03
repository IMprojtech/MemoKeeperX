
/*! Contiene la funzione Start_System_Check per verificare la corritteza del file di setup e controllare l'esistenza il file note
 *  e Set per modificare il file di setup !*/

#include "Settings_Functions.h"

void Start_System_Check(void) {

    HomeUser();

    strcpy(Setting, DirHome);
    strcat(Setting, Dir);
    MakeDir(Setting);
    strcat(Setting, SetFile);
    strcpy(File_Note, DirHome);
    strcat(File_Note, DefaultFile);

    SetWrite();
    SetRead();

    Check_Editor(Editor);
    Check_Font(Font, true);

    Check_Color(Color_Hash, true);
    Check_Color(Color_Date, true);
    Check_Color(Color_Tag, true);
    Check_Color(Color_Note, true);
    Check_Color(Color_File, true);
    Check_Color(Color_Memo, true);

    if ((PtrFileSet = fopen(File_Note, "rb")) == NULL) {
        if ((PtrFileSet = fopen(File_Note, "wb")) == NULL)
            Error(ErrorCreationFile, File_Note);
    } // crea il file di note

    fclose(PtrFileSet);
}

void Set(char *_Command, int _val, char *_Input) {

    int i = 0;

    char buf[SizeBuf];

    memset(&buf, 0, sizeof(buf));

    if ((PtrFileSet = fopen(Setting, "r+")) == NULL)
        Error(ErrorOpenFile, Setting);
    if (strcmp(_Command, "AddFile") == 0) {
        fseek(PtrFileSet, 0, SEEK_END);
        printf("\nEnter the full file path.\n You can use ## symbols followed "
               "by a comment.\n  Syntax: /path/file ## comment\n--> %s%s",
               NML, GRS);

        while ((buf[i] = getchar()) != '\n' || i >= sizeof(buf))
            i++;
        if (i > strlen(buf) - 1)
            Error(ErrorOverflow, "");
        if (i > 1) {
            buf[i] = '\0';
            fprintf(PtrFileSet, " FileNote= %-150s\n", buf);
        }
    }

    else if (strcmp(_Command, "ShowFile") == 0) {
        printf("\n%sNote file in use %s%s\n\n", Color_Note, Color_File,
               File_Note);
        while (!feof(PtrFileSet)) {
            if (strcmp("FileNote=", buf) == 0) {
                fscanf(PtrFileSet, "%s", buf);
                printf("%s%-2d %s%s", Color_Hash, i, Color_File, buf);
                i++;
                fscanf(PtrFileSet, "%s", buf);
                if (strcmp("##", buf) == 0) {
                    fgets(buf, 100, PtrFileSet);

                    char *end = buf + strlen(buf) - 1;
                    while (end > buf && isspace((unsigned char)*end))
                        end--; // rimuovo eventuali spazzi alla fine della stringa
                    *(end + 1) = '\0';

                    printf(" %s%s\n", Color_Note, buf);
                    fscanf(PtrFileSet, "%s", buf);
                } else
                    printf("\n");
            }

            else
                fscanf(PtrFileSet, "%s", buf);
        }
        printf("\n");
    }

    else if (strcmp(_Command, "SetFile") == 0) {
        while (!feof(PtrFileSet)) {
            if (strcmp("FileNote=", buf) == 0) {
                fscanf(PtrFileSet, "%s", buf);
                if (_val == i) {
                    strcpy(File_Note, buf);
                    break;
                } else {
                    fscanf(PtrFileSet, "%s", buf);
                    i++;
                }
            } else
                fscanf(PtrFileSet, "%s", buf);
        }

        memset(&buf, 0, sizeof(buf));
        fseek(PtrFileSet, 0, SEEK_SET);

        while (!feof(PtrFileSet)) {
            fscanf(PtrFileSet, "%s", buf);
            if (strcmp("$", buf) == 0)
                break;
        }

        fseek(PtrFileSet, ftell(PtrFileSet) - 2, SEEK_SET);
        fprintf(PtrFileSet, "\n$ %-100s ## Notes file in use%.80s\n", File_Note,
                " ");
    }

    else if (strncmp(_Command, "Color_", 6) == 0) {
        while (!feof(PtrFileSet)) {
            if (strcmp(_Command, buf) == 0) {
                Check_Color(_Input, false);
                fprintf(PtrFileSet, " %-10s\n", _Input);
                break;
            } else
                fscanf(PtrFileSet, "%s", buf);
        }
    }

    else if (strcmp(_Command, "Font=") == 0) {
        Check_Font(_Input, false);
        while (!feof(PtrFileSet)) {
            if (strcmp(_Command, buf) == 0) {
                fprintf(PtrFileSet, " %-10s\n", _Input);
                break;
            } else
                fscanf(PtrFileSet, "%s", buf);
        }
    }

    else if (strcmp(_Command, "Editor=") == 0) {
        Check_Editor(_Input);
        while (!feof(PtrFileSet)) {
            if (strcmp(_Command, buf) == 0) {
                fprintf(PtrFileSet, " %-10s\n", _Input);
                break;
            } else
                fscanf(PtrFileSet, "%s", buf);
        }
    }

    else
        Error(ErrorOptionSet, _Command);
    fclose(PtrFileSet);
    exit(0);
}
