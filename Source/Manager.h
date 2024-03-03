
/* Contiene le funzioni di primo avvio e di gestione file  */

void SetWrite(void){
  
int size = sizeof (DefaultFile);
int check;	
 
if ((PtrFile = fopen (DefaultFile, "r")) == NULL ){
	if ((PtrFile = fopen (DefaultFile, "w")) == NULL ) Error(ErrorCreationFile,"");}
fclose( PtrFile );
   
if ((PtrFile = fopen (Setting, "w")) == NULL ) Error(ErrorCreationFile,""); 
 
fseek(PtrFile,0,SEEK_END); 
check=fwrite( DefaultFile,size, 1, PtrFile );
fclose( PtrFile );

if (check == 0) Error(ErrorWriteFile,"");}

void SetRead(void){
  
int size = sizeof (DefaultFile);

if ((PtrFile = fopen (Setting, "r")) == NULL ) Error(ErrorCreationFile,""); 
 
fseek(PtrFile,0,SEEK_SET); 
fread( DefaultFile, size, 1, PtrFile );
fclose( PtrFile );}

void Crea_Directory(char *name){
mkdir(name, S_IWUSR|S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);}    

int Primo_Avvio(void){
 
Crea_Directory(Direct); 

if ((PtrFile = fopen (Setting, "r")) == NULL ){ 
	if ((PtrFile = fopen (Setting, "wb+")) == NULL )Error(ErrorCreationFile,"");}
fclose( PtrFile );   
   
if ((PtrFile = fopen (DefaultFile, "r")) == NULL ){
	if ((PtrFile = fopen (DefaultFile, "wb+")) == NULL )Error(ErrorCreationFile,"");}
fclose( PtrFile );   
 
SetWrite();   
return 0;}       
  
void Save(void){
 
int size = sizeof (NotesData);
int check;	

if ((PtrFile = fopen (DefaultFile, "rb+")) == NULL ) Error(ErrorOpenFile,""); 
if (NDat.Index==0){
	fseek(PtrFile,0,SEEK_END); 
	NDat.Index=((ftell(PtrFile)/size)+1); 
	time (&rawtime);	
	ptm = localtime(&rawtime);
	strftime(NDat.Data, sizeof(NDat.Data), "%d/%m/%Y", ptm);} 

else{
	fseek(PtrFile,(NDat.Index-1)*size,SEEK_SET); 
	memset(&NDat,0,sizeof (NotesData));}
 
check=fwrite( &NDat,size, 1, PtrFile );
fclose( PtrFile );

if (check == 0) Error(ErrorWriteFile,"");}

void Rebuild(void){
  
FILE *In;  FILE *Out;

int size = sizeof (NotesData);
int check,i,x=0;

char tmp[201];

strcpy(tmp,DefaultFile);
strcat(tmp,".tmp");	
rename(DefaultFile,tmp);

if ((In = fopen (tmp, "r")) == NULL ) Error(ErrorCreationFile,""); 
if ((Out = fopen (DefaultFile, "w")) == NULL ) Error(ErrorCreationFile,""); 

fseek(In,0,SEEK_END); 
i=(ftell(In)/size); 

while (x!=i) {
	fseek(PtrFile,x*size,SEEK_SET); 
	fread(  &NDat, size, 1, In ); 
	if(NDat.Index!=0){ 
		fseek(Out,0,SEEK_END); 
		NDat.Index=((ftell(Out)/size)+1); 
		check=fwrite( &NDat,size, 1, Out );
		if (check == 0) Error(ErrorWriteFile,"");}
	x++;}

fclose( In );
fclose( Out );
check = remove(tmp);
     
if (check != 0)Error(ErrorDellFile,"");}
