
/*! Contiene le definizioni di errore e le funzioni
 *  Error e Alert usate per segnalare errori o avvisi !*/

#define ErrorWriteFile "file write failed"
#define ErrorCreationFile "file creation failed"
#define ErrorOpenFile "file opening failed"
#define ErrorDellFile "file deletion failed"

#define ErrorOptionSet "illegal set option code"
#define ErrorColorSet "in settings file; illegal Color"
#define ErrorFontSet "in settings file; illegal Font"
#define ErrorEditorSet "in settings file; illegal Editor"

#define ErrorArgument "argument error"
#define ErrorSintax "syntax error"
#define ErrorOption "illegal option code"
#define ErrorOverflow "overflow"
#define ErrorLogic "missing note"

#define ErrorReadTree "insert node"
#define ErrorDelimiterTree "tree not found"
#define ErrorFindNode "node no found"
#define ErrorMoveNode "unable to move the node"

#define ErrorDuplicate "duplicate hash"
#define ErrorFound "not found"
#define ErrorMissing "missing"

#define ErrorMemory "memory allocation"

#define ErrorProcess "process"

#define ErrorProtect "protected"
#define ErrorPassword "invalid password"

void Error(char str1[], char str2[]) {
    fprintf(stderr, "\r%s%s[ERROR]%s %s %s\n", RED, GRS, NML, str1, str2);
    exit(EXIT_FAILURE);
}

void Alert(char str1[], char str2[]) {
    printf("%s%s[WARNING]%s %s %s [Y/n]\n", RED, GRS, NML, str1, str2);
    char ch = getchar();

    if (ch == 'n' || ch == 'N') {
        exit(0);
    }
}
