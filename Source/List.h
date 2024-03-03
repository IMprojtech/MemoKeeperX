
/* Contiene funzioni utilizate per trovare e ordinare i dati in una lista 
 * e prepararli per la stampa*/

struct nodiLista {   
	int code;
	char str[100];
	struct nodiLista *prosPtr;
}; 
 
typedef struct nodiLista NodiLista;  
typedef NodiLista *NodiListaPtr;  
 
typedef struct{
	int code;
	char str[100];
} TempData;
   
 TempData Tmp;

int Empty (NodiListaPtr sPtr ){ 
return sPtr == NULL;} 

int Insert (NodiListaPtr *sPtr, char string[], int code){

NodiListaPtr newPtr; 
NodiListaPtr currPtr; 
NodiListaPtr prevPtr; 

newPtr = malloc(sizeof( NodiLista ));

if (newPtr != NULL){ 
	strcpy (newPtr->str,string); 
	newPtr->code=code;
	newPtr->prosPtr = NULL;
	prevPtr = NULL;
	currPtr = *sPtr;

	if(Vbit[5]=='i'){
		while (currPtr != NULL && strcasecmp (currPtr->str,string)>0){ 
			prevPtr = currPtr;
			currPtr = currPtr->prosPtr;}}
  
	else{
		while (currPtr != NULL && strcasecmp (currPtr->str,string)<0){ 
			prevPtr = currPtr;
			currPtr = currPtr->prosPtr;}}  
      
	if (prevPtr == NULL){ 
		newPtr->prosPtr = *sPtr;
		*sPtr = newPtr;}
	
	else{
		prevPtr->prosPtr = newPtr;
		newPtr->prosPtr = currPtr;}} 
  
else return 1;
return 0;}

void DeleteList(NodiListaPtr *sPtr){
	
NodiListaPtr tempPtr;

while ( !Empty( *sPtr ) ) {
	tempPtr = *sPtr;
	*sPtr = ( *sPtr )->prosPtr;
	free( tempPtr );}}
   
void Trova(int x){
 
if ((PtrFile = fopen (DefaultFile, "rb")) == NULL )Error(ErrorOpenFile,"");
 
fseek(PtrFile,x*sizeof (NotesData),SEEK_SET);
fread( &NDat, sizeof (NotesData), 1, PtrFile );
fclose( PtrFile );}

void PrintList (NodiListaPtr sPtr ){ 
  
if ( sPtr != NULL ){
	while ( sPtr != NULL ) { 
		Trova((sPtr->code)-1); PrintDat();
		sPtr = sPtr->prosPtr;}}}

void PrintListTag(NodiListaPtr sPtr){
 
while ( sPtr != NULL ) {
	if (strcmp(sPtr->str,NDat.Tag) != 0){
		strncpy(NDat.Tag,sPtr->str,sizeof(NDat.Tag));
		PrintDat();} sPtr = sPtr->prosPtr;}}
   
void PrintNotesTag(NodiListaPtr sPtr,char key[]){
 
while ( sPtr != NULL ) { 
	if (strcasecmp(sPtr->str,key) == 0){
		Trova((sPtr->code)-1); PrintDat();}
	sPtr = sPtr->prosPtr;}}

int Note_Research(int cont,char key[]){

int size = sizeof (NotesData);   
int x=0; 

char num[10];

NodiListaPtr startPtr = NULL; 
   
if ((PtrFile = fopen (DefaultFile, "rb+")) == NULL ) Error(ErrorOpenFile,"");

while (!feof(PtrFile)){
	fseek(PtrFile,x*size,SEEK_SET); 
	fread( &NDat, size, 1, PtrFile );	
	if (NDat.Index != 0){ 
		if (cont==1) Insert( &startPtr,  NDat.Tag, NDat.Index); 
		if (cont==2) Insert( &startPtr, NDat.Data, NDat.Index); 
		if (cont==3){	sprintf(num, "%d", NDat.Index); Insert( &startPtr, num, NDat.Index);} 
		if (cont==4) Insert( &startPtr, NDat.Tag, NDat.Index);} 
	x++; memset(&NDat,0,size);}
fclose( PtrFile );

if(cont==4) PrintListTag (startPtr);
else if (cont==3) PrintList(startPtr);
else if(cont==2  || cont==1 )PrintNotesTag(startPtr,key);
 
DeleteList(&startPtr);
return 0;}	
