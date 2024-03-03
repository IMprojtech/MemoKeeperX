
/* Contiene funzioni di logica per interpretare i dati 
 * e verificare gli errori */

/*! il vettore Vbit viene usato da controllo per la sintassi !*/

void Controll(void){ // controlla la sintassi inserita e richiama l'operazione da effettuare
  
char key[21];  
  
if (Vbit[0]=='W' && (strlen (NDat.Note)!=0 || strlen (NDat.Link_File)!=0)){
	if (strlen(NDat.Tag)==0)strcpy(NDat.Tag,DefaultTag);
	Save();}
  
else if (Vbit[0]=='p'){ 
	if (Vbit[1]=='x'){Trova((NDat.Index)-1);PrintDat();}
	else if (Vbit[2]=='t'){strcpy(key,NDat.Tag); Note_Research(1,key);}
	else if (Vbit[3]=='d'){strcpy(key,NDat.Data); Note_Research(2,key);}
    else {Note_Research(3,NULL);}}
  
else if (Vbit[6]=='f'){Trova((NDat.Index)-1);PrintFile();}				
else if (Vbit[0]=='s'){Note_Research(4,NULL);}	
else if (Vbit[7]=='r'){ Save();}
  
else Error(ErrorSintax,"");}

void LoadVbit(int x,char ch){ 
if (Vbit[x]==' ') Vbit[x]=ch;
else Error(ErrorLogic,"");} 

void LoadStuctChar(char *_dest,char _src[],int size){ 
if(_src==NULL)Error(ErrorArgument,"");
else if(strlen (_src)>size) Error(ErrorOverflow,"");
else strncpy(_dest,_src,size);} 
  
void LoadStuctInt(char _src[]){
if(_src==NULL)Error(ErrorArgument,"");  
else NDat.Index=atoi(_src);}

void LoadNote(char *_dest,char _src[],int size){
if(strlen(_dest)+strlen(_src)>size) Error(ErrorOverflow,"");
else{  strcat(_dest,_src); strcat (_dest," ");}}
  
void Scanner(int argc, char **argv){ // fa una scanzione degli argomenti passati dal terminale e verifica che non ci siano argomenti errati 
	
int i,j; 
int length; 

char ch; 

for (i=1; i<argc; i++){     	
	switch (argv[i][0]){
		case '-': length=strlen(argv[i]);
			for(j=1; j<length; ++j){ ch=argv[i][j];
				switch (ch){
	
					case 'p': LoadVbit(0,ch); break; 
					case 's': LoadVbit(0,ch);  break;
					case 'x': LoadVbit(1,ch); LoadStuctInt(argv[++i]); break; 
					case 't': LoadVbit(2,ch); LoadStuctChar(NDat.Tag,argv[++i],sizeof(NDat.Tag)-1);break; 
					case 'd': LoadVbit(3,ch); LoadStuctChar(NDat.Data,argv[++i],sizeof(NDat.Data)-1); break;
					case 'a': LoadVbit(4,ch); LoadStuctChar(NDat.Link_File,argv[++i],sizeof(NDat.Link_File)-1); break; 
					case 'f': LoadVbit(6,ch); LoadStuctInt(argv[++i]); break;
					case 'r': LoadVbit(7,ch); LoadStuctInt(argv[++i]); break;   
					case 'i': LoadVbit(5,ch); break;   
               
					case '-': switchs(argv[i]){

						cases("--setting") printf("%s\n",Setting); exit(0); break;
						cases("--rebuild") Rebuild(); exit(0); break;
						cases("--help") Help(); exit(0); break;
                        cases("--print") LoadVbit(0,'p'); j=length; break;
						cases("--show")  LoadVbit(0,'s'); j=length; break;
						cases("--index") LoadVbit(1,'x'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--tag") LoadVbit(2,'t'); LoadStuctChar(NDat.Tag,argv[++i],sizeof(NDat.Tag)-1); j=length; break;
						cases("--date") LoadVbit(3,'d'); LoadStuctChar(NDat.Data,argv[++i],sizeof(NDat.Data)-1); j=length; break;
						cases("--append") LoadVbit(4,'a'); LoadStuctChar(NDat.Link_File,argv[++i],sizeof(NDat.Link_File)-1); j=length; break;
						cases("--file") LoadVbit(6,'f'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--remove") LoadVbit(7,'r'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--invert") LoadVbit(5,'i'); j=length; break;
			
						defaults Error(ErrorOption,argv[i]); j=length; break;}
					switchs_end; break;
 
				default: Error(ErrorOption,argv[i]); break;}}
			break;
     
	default: LoadNote(NDat.Note,argv[i],sizeof(NDat.Note)-1); break; }}

if (argc < 2 ) Vbit[0]='p'; 
else if (Vbit[0]==' ') Vbit[0]='W';
Controll();}

