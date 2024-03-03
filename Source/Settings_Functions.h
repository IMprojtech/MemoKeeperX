
/*! Contiene le funzioni per la creazione, scrittura e lettura del file contenente le impostazioni di default
 *  e i rispettivi controlli da effettuare !*/

#include "Settings_Header.h"

void HomeUser(void) { DirHome = getenv("HOME"); }

void MakeDir(char *name) {
    mkdir(name,
          S_IWUSR | S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
}

void SetRead(void) {

    char buf[SizeBuf];

    if ((PtrFileSet = fopen(Setting, "r")) == NULL)
        Error(ErrorOpenFile, Setting);

    while (!feof(PtrFileSet)) {
        fscanf(PtrFileSet, "%s", buf);

        if (buf[0] == '#') {
            fgets(buf, SizeBuf - 1, PtrFileSet);
        } else if (strcmp("Editor=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Editor, buf, sizeof(Editor));
        } else if (strcmp("Font=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Font, buf, sizeof(Font));
        } else if (strcmp("Color_Hash=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Color_Hash, buf, sizeof(Color_Hash));
        } else if (strcmp("Color_Date=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Color_Date, buf, sizeof(Color_Date));
        } else if (strcmp("Color_Tag=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Color_Tag, buf, sizeof(Color_Tag));
        } else if (strcmp("Color_Note=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Color_Note, buf, sizeof(Color_Note));
        } else if (strcmp("Color_File=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Color_File, buf, sizeof(Color_File));
        } else if (strcmp("Color_Memo=", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(Color_Memo, buf, sizeof(Color_Memo));
        }

        else if (strcmp("$", buf) == 0) {
            fscanf(PtrFileSet, "%s", buf);
            strncpy(File_Note, buf, sizeof(File_Note));
        }
    }

    fclose(PtrFileSet);
}

void SetWrite(void) {

    if ((PtrFileSet = fopen(Setting, "r")) == NULL) {
        if ((PtrFileSet = fopen(Setting, "w")) == NULL)
            Error(ErrorCreationFile, Setting);

        fprintf(PtrFileSet, "\n# !! DO NOT MANUALLY EDIT THIS FILE !!\n\n");

        fprintf(PtrFileSet, "\n# Editor  (VIM,LESS,CAT,NUL)\n");
        fprintf(PtrFileSet, " Editor= %-10s\n", Editor);

        fprintf(PtrFileSet, "\n# Font  (GRS,NML,NUL)\n");
        fprintf(PtrFileSet, " Font= %-10s\n", Font);

        fprintf(PtrFileSet,
                "\n# Color  (RED,GRN,YEL,BLU,BLK,MAG,CYN,WHT,NUL)\n");
        fprintf(PtrFileSet, " Color_Hash= %-10s\n", Color_Hash);
        fprintf(PtrFileSet, " Color_Date= %-10s\n", Color_Date);
        fprintf(PtrFileSet, " Color_Tag= %-10s\n", Color_Tag);
        fprintf(PtrFileSet, " Color_Note= %-10s\n", Color_Note);
        fprintf(PtrFileSet, " Color_File= %-10s\n", Color_File);
        fprintf(PtrFileSet, " Color_Memo= %-10s\n", Color_Memo);

        fprintf(PtrFileSet, "\n$ %-100s ## Notes file in use%.80s\n", File_Note,
                " ");

        fprintf(PtrFileSet, "\n# Here you can indicate the file to use\n");
        fprintf(PtrFileSet, " FileNote= %s ## General Notes%-150s\n", File_Note,
                " ");
        Help();
    }

    fclose(PtrFileSet);
}

void Check_Color(char *_str, bool _out) {

    if (strcasecmp("RED", _str) == 0) {
        if (_out == true)
            strcpy(_str, RED);
    } else if (strcasecmp("GRN", _str) == 0) {
        if (_out == true)
            strcpy(_str, GRN);
    } else if (strcasecmp("YEL", _str) == 0) {
        if (_out == true)
            strcpy(_str, YEL);
    } else if (strcasecmp("BLU", _str) == 0) {
        if (_out == true)
            strcpy(_str, BLU);
    } else if (strcasecmp("BLK", _str) == 0) {
        if (_out == true)
            strcpy(_str, BLK);
    } else if (strcasecmp("MAG", _str) == 0) {
        if (_out == true)
            strcpy(_str, MAG);
    } else if (strcasecmp("CYN", _str) == 0) {
        if (_out == true)
            strcpy(_str, CYN);
    } else if (strcasecmp("WHT", _str) == 0) {
        if (_out == true)
            strcpy(_str, WHT);
    } else if (strcasecmp("NUL", _str) == 0) {
        if (_out == true)
            strcpy(_str, NUL);
    } else
        Error(ErrorColorSet, _str);
}

void Check_Font(char *_str, bool _out) {

    if (strcasecmp("GRS", _str) == 0) {
        if (_out == true)
            strcpy(_str, GRS);
    } else if (strcasecmp("NML", _str) == 0) {
        if (_out == true)
            strcpy(_str, NML);
    } else if (strcasecmp("NUL", _str) == 0) {
        if (_out == true)
            strcpy(_str, NUL);
    } else
        Error(ErrorFontSet, _str);
}

void Check_Editor(char *_str) {

    if (strcasecmp("VIM", _str) != 0 && strcasecmp("NANO", _str) != 0 &&
        strcasecmp("NUL", _str) != 0) {
        Error(ErrorEditorSet, _str);
    }
}
