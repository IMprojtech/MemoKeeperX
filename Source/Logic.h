
/* Contiene funzioni di logica per interpretare i dati 
 * e verificare gli errori */

/*! il vettore bit viene usato da controllo per la sintassi !*/

void Controll(void){ // controlla la sintassi inserita e richiama l'operazione da effettuare
  
char key[21];  
  
if (bit=='W'){
	if (strlen(NDat.Tag)==0)strcpy(NDat.Tag,DefaultTag);
	Save();}
 
else if (bit=='p'){
	if(strlen (NDat.Tag) != 0){strcpy(key,NDat.Tag); Note_Research(1,key);}
	else {Note_Research(3,NULL);}}

else if (bit=='s'){Note_Research(4,NULL);}	
else if (bit=='r'){ Save();}
else if (bit=='x'){Trova((NDat.Index)-1);PrintDat();}  
else if (bit=='f'){Trova((NDat.Index)-1);PrintFile();}
else if (bit=='F'){Trova((NDat.Index)-1);PrintPathFile();}
else if (bit=='d'){strcpy(key,NDat.Data); Note_Research(2,key);}

else Error(ErrorSintax,"");}

void Loadbit(char ch){ 
if (bit==' ') bit=ch;
else Error(ErrorOption,"");} 

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
		case '+': Loadbit ('f'); LoadStuctInt(argv[i]); break;
	  
	    case '-': length=strlen(argv[i]);
			for(j=1; j<length; ++j){ ch=argv[i][j];
				switch (ch){
	
					case 's': Loadbit(ch);  break;
					case 'r': Loadbit(ch); LoadStuctInt(argv[++i]); break;   
					case 'x': Loadbit(ch); LoadStuctInt(argv[++i]); break; 
					case 'f': Loadbit(ch); LoadStuctInt(argv[++i]); break;
					case 'F': Loadbit(ch); LoadStuctInt(argv[++i]); break;
					case 'd': Loadbit(ch); Extended=true;  LoadStuctChar(NDat.Data,argv[++i],sizeof(NDat.Data)-1); break;
					case 't': LoadStuctChar(NDat.Tag,argv[++i],sizeof(NDat.Tag)-1);break; 
					case 'a': LoadStuctChar(NDat.Link_File,argv[++i],sizeof(NDat.Link_File)-1); break; 
					case 'i': Invert=true; break;   
					case 'e': Extended=true; break;
               
					case '-': switchs(argv[i]){

						cases("--addfile") Set("AddFile",0,NULL); exit(0); break;  
						cases("--showfile") Set("ShowFile",0,NULL); exit(0); break;  
						cases("--setfile") Set("SetFile",atoi(argv[2]),NULL); exit(0); break;  
 
						cases("--color_index") Set("Color_Index=",0,argv[2]); exit(0); break;  
						cases("--color_date") Set("Color_Date=",0,argv[2]); exit(0); break;  
						cases("--color_tag") Set("Color_Tag=",0,argv[2]); exit(0); break;  
						cases("--color_note") Set("Color_Note=",0,argv[2]); exit(0); break;  
						cases("--color_file") Set("Color_File=",0,argv[2]); exit(0); break;  
						cases("--color_other") Set("Color_Other=",0,argv[2]); exit(0); break;  

						cases("--font") Set("Font=",0,argv[2]); exit(0); break;  
						cases("--editor") Set("Editor=",0,argv[2]); exit(0); break;  
 
						cases("--setting") printf("%s\n",Setting); exit(0); break;
						cases("--rebuild") Rebuild(); exit(0); break;
						cases("--help") Help(); exit(0); break;
						
						cases("--show")  Loadbit('s'); j=length; break;
						cases("--remove") Loadbit('r'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--index") Loadbit('x'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--file") Loadbit('f'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--filepath") Loadbit('F'); LoadStuctInt(argv[++i]); j=length; break;
						cases("--date") Loadbit('d'); Extended=true; LoadStuctChar(NDat.Data,argv[++i],sizeof(NDat.Data)-1); j=length; break;
						cases("--tag")  LoadStuctChar(NDat.Tag,argv[++i],sizeof(NDat.Tag)-1); j=length; break;
						cases("--append")  LoadStuctChar(NDat.Link_File,argv[++i],sizeof(NDat.Link_File)-1); j=length; break;
					   
						cases("--invert") Invert=true; j=length; break;
						cases("--extended") Extended=true; j=length; break;

						defaults Error(ErrorOption,argv[i]); j=length; break;}
					switchs_end; break;
 
				default: Error(ErrorOption,argv[i]); break;}}
			break;
     
	default: LoadNote(NDat.Note,argv[i],sizeof(NDat.Note)-1); break; }}

if (strlen (NDat.Note) == 0 && bit==' ' && strlen (NDat.Link_File) == 0)  bit='p';
else if (bit!=' ' && strlen (NDat.Note) != 0 ) Error(ErrorOption,argv[i]);
else if (strlen (NDat.Note) == 0 && strlen (NDat.Link_File) != 0 ) Error(ErrorLogic,"");
else if (bit==' ') bit='W';
Controll();}
