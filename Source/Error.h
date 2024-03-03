
/* Contiene le definizioni di errore e la funzione 
 * usata per terminare il programma con 
 * il relativo messaggio */

 #define ErrorWriteFile  "file write failed"
 #define ErrorCreationFile  "file creation failed"
 #define ErrorOpenFile  "file opening failed"
 #define ErrorDellFile  "file deletion failed"

 #define ErrorOptionSet  "illegal set option code"
 #define ErrorColorSet  "Error in settings file; illegal Color"  
 #define ErrorFontSet  "Error in settings file; illegal Font"   
 #define ErrorEditorSet  "Error in settings file; illegal Editor"  
  
 #define ErrorArgument  "argument error"
 #define ErrorSintax  "syntax error"
 #define ErrorOption  "illegal option code" 
 #define ErrorOverflow  "overflow"
 #define ErrorLogic  "missing note"

void Error(char str1[],char str2[]){
fprintf(stderr, "%s%s[ERROR]%s %s %s\n",RED,GRS,NML,str1,str2);
exit(EXIT_FAILURE);}
