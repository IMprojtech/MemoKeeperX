
/** Contiene le funzioni per le impostazioni di base **/

void HomeUser(void){  
DirHome = getenv("HOME");}

void MakeDir(char *name){ 
mkdir(name, S_IWUSR|S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);}    
  
void SetRead(void){ 

char buf[201];
 
if ((PtrFile = fopen (Setting, "r")) == NULL ) Error(ErrorOpenFile,Setting); 
 
while(!feof(PtrFile)){ fscanf(PtrFile,"%s", buf);
	if(buf[0]=='#') fgets(buf,200,PtrFile);

	else if (strcmp("Editor=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Editor,buf,sizeof(Editor));}
	else if (strcmp("Font=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Font,buf,sizeof(Font));}
	else if (strcmp("Color_Index=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Color_Index,buf,sizeof(Color_Index));}
	else if (strcmp("Color_Date=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Color_Date,buf,sizeof(Color_Date));}
	else if (strcmp("Color_Tag=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Color_Tag,buf,sizeof(Color_Tag));}
	else if (strcmp("Color_Note=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Color_Note,buf,sizeof(Color_Note));}
    else if (strcmp("Color_File=",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(Color_File,buf,sizeof(Color_File));}

	else if (strcmp("$",buf) == 0){ fscanf(PtrFile,"%s", buf); strncpy(File_Note,buf,sizeof(File_Note));}}
  
fclose( PtrFile );}
	
void SetWrite(void){ 

if ((PtrFile = fopen (Setting, "r")) == NULL ){ 
	if ((PtrFile = fopen (Setting, "w")) == NULL ) Error(ErrorCreationFile,Setting); 

	fprintf(PtrFile,"\n# !! DO NOT MANUALLY EDIT THIS FILE !!\n\n");
	
	fprintf(PtrFile,"\n# Editor  (VIM,LESS,CAT,NUL)\n");
	fprintf(PtrFile," Editor= %-10s\n",Editor);

	fprintf(PtrFile,"\n# Font  (GRS,NML,NUL)\n");
	fprintf(PtrFile," Font= %-10s\n",Font);

	fprintf(PtrFile,"\n# Color  (RED,GRN,YEL,BLU,BLK,MAG,CYN,WHT,NUL)\n");
	fprintf(PtrFile," Color_Index= %-10s\n",Color_Index);
	fprintf(PtrFile," Color_Date= %-10s\n",Color_Date);
	fprintf(PtrFile," Color_Tag= %-10s\n",Color_Tag);
	fprintf(PtrFile," Color_Note= %-10s\n",Color_Note);
	fprintf(PtrFile," Color_File= %-10s\n",Color_File);

	fprintf(PtrFile,"\n$ %-100s ## Notes file in use%.80s\n",File_Note," ");

	fprintf(PtrFile,"\n# Here you can indicate the file to use\n");
	fprintf(PtrFile," FileNote= %s ## General Notes%-150s\n",File_Note," ");
	Help();}

fclose (PtrFile);}
   
void Check_Color(char *_str,bool _out){ 
	        
switchs (_str){
	icases("RED") if (_out==true) strcpy(_str,RED);  break;
	icases("GRN") if (_out==true) strcpy(_str,GRN);  break;
	icases("YEL") if (_out==true) strcpy(_str,YEL);  break;
	icases("BLU") if (_out==true) strcpy(_str,BLU);  break;
	icases("BLK") if (_out==true) strcpy(_str,BLK);  break;
	icases("MAG") if (_out==true) strcpy(_str,MAG);  break;
	icases("CYN") if (_out==true) strcpy(_str,CYN);  break;
	icases("WHT") if (_out==true) strcpy(_str,WHT);  break;       
	icases("NUL") if (_out==true) strcpy(_str,NUL);  break;
 
	defaults Error(ErrorColorSet,_str);break;}
switchs_end; }   
   
void Check_Font(char *_str,bool _out){ 
	        
switchs (_str){
	icases("GRS") if (_out==true) strcpy(_str,GRS);  break;
	icases("NML") if (_out==true) strcpy(_str,NML);  break;
	icases("NUL") if (_out==true) strcpy(_str,NUL);  break;
  
	defaults Error(ErrorFontSet,_str); break;}
switchs_end; }
   
void Check_Editor(char *_str){ 
	        
switchs (_str){
	icases("VIM") break;
	icases("LESS") break;
	icases("CAT") break;
	icases("NUL") break;

	defaults Error(ErrorEditorSet,_str); break;}
switchs_end; }
    
void Start_System_Check(void){ 

HomeUser(); 
 
strcpy(Setting,DirHome); strcat(Setting,Dir); 
MakeDir(Setting); strcat(Setting,SetFile); 
strcpy(File_Note,DirHome); strcat(File_Note,DefaultFile); 

SetWrite(); SetRead();

Check_Editor(Editor);
Check_Font(Font,true);

Check_Color(Color_Index,true);
Check_Color(Color_Date,true);
Check_Color(Color_Tag,true);
Check_Color(Color_Note,true);
Check_Color(Color_File,true);
    
if ((PtrFile = fopen (File_Note, "r")) == NULL ){
	if ((PtrFile = fopen (File_Note, "w")) == NULL ) Error(ErrorCreationFile,File_Note);} // crea il file di note
	
fclose( PtrFile );}       

void Set(char *_Command, int _val, char *_Input){ 
 
int i=0;	

char buf[200];

memset(&buf,0,sizeof (buf));

if ((PtrFile = fopen (Setting, "r+")) == NULL ) Error(ErrorOpenFile,Setting); 
if (strcmp(_Command,"AddFile") == 0) {  fseek(PtrFile,0,SEEK_END);
	printf ("\nEnter the full file path.\n You can use ## symbols followed by a comment.\n  Syntax: /path/file ## comment\n--> %s%s",NML,GRS);	
	
	while ((buf[i] = getchar()) != '\n' || i >= sizeof(buf)) i++;
	if(i>strlen(buf)-1) Error(ErrorOverflow,"");
	if(i>1){buf[i]='\0'; fprintf(PtrFile," FileNote= %-150s\n",buf);}}

else if (strcmp(_Command,"ShowFile") == 0) { 
	printf("\n%sNote file in use %s%s\n\n",Color_Note,Color_File,File_Note); 
	while(!feof(PtrFile)){ 
		if (strcmp("FileNote=",buf) == 0){ fscanf(PtrFile,"%s", buf); printf("%s%-2d %s%s",Color_Index,i,Color_File,buf); i++; fscanf(PtrFile,"%s", buf);
			if (strcmp("##",buf) == 0){ fgets(buf,100,PtrFile); printf(" %s%s\n",Color_Note,buf); fscanf(PtrFile,"%s", buf);}
			else printf("\n");}	
   
	else fscanf(PtrFile,"%s", buf);}
	printf("\n");} 
 
else if (strcmp(_Command,"SetFile") == 0) { 
	while(!feof(PtrFile)){ 
		if (strcmp("FileNote=",buf) == 0){ fscanf(PtrFile,"%s", buf);  
			if (_val == i){ strcpy (File_Note,buf); break;} 
			else{ fscanf(PtrFile,"%s", buf); i++;}}
		else fscanf(PtrFile,"%s", buf);}

	memset(&buf,0,sizeof (buf));	
	fseek(PtrFile,0,SEEK_SET);

	while(!feof(PtrFile)){ fscanf(PtrFile,"%s", buf);
		if (strcmp("$",buf) == 0)break;}	

	fseek(PtrFile,ftell(PtrFile)-2,SEEK_SET);
	fprintf(PtrFile,"\n$ %-100s ## Notes file in use%.80s\n",File_Note," ");}

else if (strncmp(_Command,"Color_",6) == 0) { 
	while(!feof(PtrFile)){ 
		if (strcmp(_Command,buf) == 0){ Check_Color(_Input,false);	
		fprintf(PtrFile," %-10s\n",_Input); break;}	
	else fscanf(PtrFile,"%s", buf);}}

else if (strcmp(_Command,"Font=") == 0) { Check_Font(_Input,false);
	while(!feof(PtrFile)){ 
		if (strcmp(_Command,buf) == 0){
		fprintf(PtrFile," %-10s\n",_Input); break;}	
	else fscanf(PtrFile,"%s", buf);}}

else if (strcmp(_Command,"Editor=") == 0) { Check_Editor(_Input);
	while(!feof(PtrFile)){ 
		if (strcmp(_Command,buf) == 0){
		fprintf(PtrFile," %-10s\n",_Input); break;}	
	else fscanf(PtrFile,"%s", buf);}}

else Error(ErrorOptionSet,_Command);
fclose( PtrFile );}
