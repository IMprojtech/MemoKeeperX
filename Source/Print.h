
/* Contiene le funzioni che si occupano di stampare a video i dati */

void Help(void){
 
printf("%sNAME%s\n    %s - %s\n\n",GRS,NML,ALIAS,NAME);	

printf("%sSYNOPSIS%s\n    %s [OPTION]... [FILE]...\n"
					 "    %s [OPTION]... [STRING]...\n\n",GRS,NML,ALIAS,ALIAS);

printf("%sDESCRIPTION%s\n    Manages and organizes notes, uses tags that allow you to filter searches and link external clipboard files\n\n",GRS,NML);

printf("    --help   \n\n");

printf("    -t o --tag    insert tag, default \"T01\"\n");
printf("    -a o --append    attach file\n");
printf("    -s o --show    show tags used\n");
printf("    -p o --print    print notes\n"); 
printf("    -r o --remove    remove notes\n");
printf("    -i o --invert    inverted print\n");
printf("    -x o --index    indexed notes\n");   
printf("    -e o --Extended    extended print (date, path)\n");
printf("    -d o --date    find date\n");
printf("    -f o --file    print file\n");
printf("    -F o --filePath    print path file\n\n");

printf("    +(n) print file\n\n");

printf("    --rebuild    rebuilds the notes file\n\n");
 
printf("%sSETTING%s\n    Modify the behavior and appearance of the program.\n    You can switch and recall different note files for better organization. \n\n",GRS,NML);  
  
printf("    --setting    shows the path to the setup file \"~/.config/MemoK.conf\"\n");
printf("    --addfile    add a new notes file\n");
printf("    --showfile    shows a list of existing note files\n");
printf("    --setfile    set the specified file\n");

printf("    --editor    set a different editor (Vim,Cat,Less,Nul)\n"); 
printf("    --font    set a different font (GRS,NML)\n");
printf("    --color_[camp    camp is the variable to set (index,tag,dete,note,file)\n");
printf("                     you can set the colors (Red,Grn,Yel,Blu,Blk,Mag,Cyn,Wht,Nul)\n\n");

printf("%sEXAMPLE:%s\n",GRS,NML);
printf("    %s -t T02 \"notes\"   %s->%s    adds a note tagged h02\n",ALIAS,GRS,NML);
printf("    %s -t T02 \"notes\" -a \"file.txt\"   %s->%s    adds a file with tag h02\n",ALIAS,GRS,NML);
printf("    %s -t T02   %s->%s    print all notes tagged h02\n",ALIAS,GRS,NML);
printf("    %s -d 01/01/2023   %s->%s    print all notes date h02\n",ALIAS,GRS,NML);
printf("    %s -f 5   %s->%s    print the file with index 5\n",ALIAS,GRS,NML);
printf("    %s +5   %s->%s    print the file with index 5\n",ALIAS,GRS,NML);
printf("    %s -F 5   %s->%s    print the path file with index 5\n",ALIAS,GRS,NML);
printf("    %s -s   %s->%s    shows all tags used\n",ALIAS,GRS,NML);
printf("    %s -r 5   %s->%s    remove the file with index 5\n",ALIAS,GRS,NML);
printf("    %s --rebuild   %s->%s    rebuilds the notes file\n\n",ALIAS,GRS,NML);

printf("    %s --setting   %s->%s    shows the path to the setup file file\n",ALIAS,GRS,NML);
printf("    %s --addfile   %s->%s    set up a new notes file\n",ALIAS,GRS,NML);
printf("    %s --showfile   %s->%s    generates a list with the inserted note files (shows an index that will be used to set that file)\n",ALIAS,GRS,NML);
printf("    %s --setfile 5   %s->%s    set the file with index 5 in use\n",ALIAS,GRS,NML);

printf("    %s --editor vim  %s->%s    set VIM as the default editor\n",ALIAS,GRS,NML);
printf("    %s --font grs  %s->%s    set the output bold \n",ALIAS,GRS,NML);
printf("    %s --color_index wht  %s->%s    sets the index color to white\n\n",ALIAS,GRS,NML);
 
printf("%sAUTHOR%s\n    Written by IMprojtech\n\n",GRS,NML);

printf("%sVERSION%s\n    %s\n\n",GRS,NML,VER);}

void PrintDat(void){
if(NDat.Index==0)printf(" %s%-20s %s%-11s %s%s %s%s\n",Color_Tag,NDat.Tag,Color_Date,NDat.Data,Color_Note,NDat.Note,Color_File,NDat.Link_File);   
else if (Extended==true) printf(" %s%-4d %s%-20s %s%-11s %s%s %s%s\n",Color_Index,NDat.Index,Color_Tag,NDat.Tag,Color_Date,NDat.Data,Color_Note,NDat.Note,Color_File,NDat.Link_File);
else  printf(" %s%-4d %s%-20s %s%s %s%s\n",Color_Index,NDat.Index,Color_Tag,NDat.Tag,Color_Note,NDat.Note,Color_File,strlen(NDat.Link_File)==0 ? "" : "#");}

void PrintFile(void){ 
 
if (strcasecmp(Editor,"Vim")==0){execl("/bin/vim","vim",NDat.Link_File,NULL);} 
else if (strcasecmp(Editor,"Cat")==0){execl("/bin/cat","cat",NDat.Link_File,NULL);} 
else if (strcasecmp(Editor,"Less")==0){execl("/bin/less","less",NDat.Link_File,NULL);} 

else if (strcasecmp(Editor,"Nul")==0){
	
	FILE *input;
	
	int ch;	
	
	if ((input = fopen (NDat.Link_File, "rb")) == NULL ) Error(ErrorOpenFile,"");	
	ch = fgetc(input); printf("\n");

	while (!feof(input)) {
		printf("%c",ch);
		ch = fgetc(input);}  
	
	printf("\n");  
	fclose(input);}}	
	
void PrintPathFile(void){
printf("%s\n",NDat.Link_File);}
	
