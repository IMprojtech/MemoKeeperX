
/* Contiene le definizioni di errore e la funzione 
 * usata per terminare il programma con 
 * il relativo messaggio */

 #define ErrorWriteFile  "file write failed"
 #define ErrorCreationFile  "file creation failed"
 #define ErrorOpenFile  "file opening failed"
 #define ErrorDellFile  "file deletion failed"
  
 #define ErrorArgument  "argument error"
 #define ErrorSintax  "syntax error"
 #define ErrorOption  "illegal option code" 
 #define ErrorOverflow  "overflow"
 #define ErrorLogic  "repeated or unexpected options"

void Error(char str1[],char str2[]){
fprintf(stderr, "%s%s[ERROR]%s %s %s\n",RED,GRS,NML,str1,str2);
exit(EXIT_FAILURE);}
