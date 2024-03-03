
/* Contiene le funzioni di gestione file  */
  
void Save(void){ 
 
int size = sizeof (NotesData);
int check;	

if ((PtrFile = fopen (File_Note, "rb+")) == NULL ) Error(ErrorOpenFile,""); 

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

void Rebuild(void){ // ricostruisce il file di note per eliminare spazi inutilizzati lasciati dalla cancellazione di note
	
FILE *In;  FILE *Out;

int size = sizeof (NotesData);
int check,i,x=0;

char tmp[201];

strcpy(tmp,File_Note);
strcat(tmp,".tmp");	
rename(File_Note,tmp);

if ((In = fopen (tmp, "r")) == NULL ) Error(ErrorCreationFile,""); 
if ((Out = fopen (File_Note, "w")) == NULL ) Error(ErrorCreationFile,""); 

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
