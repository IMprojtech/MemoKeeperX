
/*! Contiene funzioni generali !*/

#include <openssl/sha.h>

void Help(void){
printf("\n%sNAME%s\n    %s - %s\n\n",GRS,NML,ALIAS,NAME);	

printf("%sSYNOPSIS%s\n    %s [OPTION]... [FILE]...\n"
					 "    %s [OPTION]... [STRING]...\n\n",GRS,NML,ALIAS,ALIAS);

printf("%sDESCRIPTION%s\n" 
"        \"MemoKeeperX\" alias \"mkx\" is a command-line Linux application\n"
"        designed to streamline the management and organization of notes and crucial information.\n"
"        It provides an intuitive interface for input, categorization, and display of notes,\n"
"        allowing users to create a hierarchical structure using personalized tags.\n\n",GRS,NML);

printf("%sCOMMAND LIST%s\n"
"    --help   \n\n"

"    -w    write note\n"
"    -t    insert tag, default \"T01\"\n"
"    -a    attach file\n"
"    -s    show tags used\n"
"    -o    organize tags\n"
"    -m    modification\n"
"    -r    remove notes\n"
"    -h    note identifier hash\n" 
"    -e    extended print \n"
"    -d    find date\n"
"    -f    print file\n"
"    -F    print path file\n"
"    -P    data protection\n"
"    -X    write or read Memo\n\n",GRS,NML);

printf("%sSETTING%s\n"
"    Modify the behavior and appearance of the program.\n"
"    You can switch and recall different note files for better organization. \n\n"  
  
"    --setting    shows the path to the setup file \"~/.config/%s\"\n"
"    --addfile    add a new notes file\n"
"    --showfile    shows a list of existing note files\n"
"    --setfile    set the specified file\n"
"    --backup    create a backup copy of the file\n"

"    --editor    set a different editor (Vim,Nano,Nul)\n" 
"    --font    set a different font (GRS,NML)\n"
"    --color_[camp    camp is the variable to set (hash,tag,dete,note,file,memo)\n"
"                     you can set the colors (Red,Grn,Yel,Blu,Blk,Mag,Cyn,Wht,Nul)\n\n",GRS,NML,SetFile);

printf("%sEXAMPLE:%s\n",GRS,NML);
printf("    %s -t T02 -w \"notes\"   %s->%s    adds a note with tag T02\n"
       "		You can nest tags directly using \"><\" characters\n"
       "		  Example:\n"
       "		-t \"T01<T02\" -w \"notes\" -> will create a T02 tag inside the T01 tag\n"
       "		the same way\n"
       "		-t \"T02>T01\" -w \"notes\" -> will create a T02 tag inside the T01 tag\n\n",ALIAS,GRS,NML);
       
printf("    %s -t T02 -w \"notes\" -a \"file.txt\"   %s->%s    adds a note and file with tag T02\n",ALIAS,GRS,NML);
printf("    %s -t T02 -w \"notes\" -a \"file.txt\" -X   %s->%s    adds a note, file and Memo with tag T02\n",ALIAS,GRS,NML);
printf("    %s -t T02 -w \"notes\" -a \"file.txt\" -XP   %s->%s    add a note, a file and a Memo with T02 tag and protect the data\n",ALIAS,GRS,NML);

printf("    %s   %s->%s    print all notes \n",ALIAS,GRS,NML);
printf("    %s -e   %s->%s    prints all notes in long format \n",ALIAS,GRS,NML);
printf("    %s -X   %s->%s    Print all notes including Memo \n",ALIAS,GRS,NML);
printf("    %s -eXP   %s->%s    Print all notes including Memos and protected notes \n",ALIAS,GRS,NML);
printf("    %s -t T02   %s->%s    print all notes with tag h02\n",ALIAS,GRS,NML);
printf("    %s -h [5dca...]   %s->%s    prints the specific note with the hash 5dca...\n",ALIAS,GRS,NML);
printf("    %s -d 2023-01-01   %s->%s    print all notes date 2023-01-01\n"
       "		The search by date also takes time parameters such as:\n"
       "		H for hours, D for days, M for months, you can specify a value followed by a letter to filter the results\n"
       "		  Example:\n"
       "		-d 1h -> will show notes from the last hour onwards\n"
       "		-d 1d -> notes from the previous day onwards\n"
       "		-d 1m -> notes from the previous month onwards\n\n",ALIAS,GRS,NML);

printf("    %s -fh [5dca...]   %s->%s    print the file with hash 5dca...\n",ALIAS,GRS,NML);
printf("    %s -ft T02   %s->%s    print the file with tag T02\n",ALIAS,GRS,NML);
printf("    %s -Fh [5dca...]   %s->%s    print the path file with hash 5dca...\n",ALIAS,GRS,NML);
printf("    %s -Ft T02   %s->%s    print the path file with tag T02\n",ALIAS,GRS,NML);

printf("    %s -s   %s->%s    shows all tag structure\n",ALIAS,GRS,NML);

printf("    %s -Prt T02   %s->%s    removes the T02 tag\n",ALIAS,GRS,NML);
printf("    %s -Prh [5dca...]   %s->%s    removes the 5dca... hash\n"
       "		ATTENTION removing a node also recursively deletes its subnodes\n"
       "		├──T01 Hi 1\n"
       "		├──├──T02 Hi 2\n"
       "		Deleting T02 will only delete T02 as there are no subnodes\n"
       "		By eliminating T01, T02 will also be eliminated as it is a subnode of T01\n",ALIAS,GRS,NML);
printf("        NOTE -Pr.. is used because the remove operation is a protected operation\n\n");

printf("    %s -Po [5dca...] [7f54...]   %s->%s    move the 5dca... node inside the 7f54 node\n",ALIAS,GRS,NML);
printf("    %s -Po [5dca...] up  %s->%s    move the 5dca... node up\n",ALIAS,GRS,NML);
printf("    %s -Po [5dca...] down  %s->%s    move the 5dca... node down\n",ALIAS,GRS,NML);
printf("    %s -Po [5dca...] .  %s->%s    move the 5dca... node in root \".\"\n",ALIAS,GRS,NML);
printf("         NOTE -Po is used because the move operation is a protected operation\n\n");

printf("    %s -m [5dca...] -w \"notes\"   %s->%s    edit the note of node 5dca... \n",ALIAS,GRS,NML);
printf("    %s -m [5dca...] -a \"file.txt\"  %s->%s    edit the link file of node 5dca... \n",ALIAS,GRS,NML);
printf("    %s -m [5dca...] -X  %s->%s    edit the memo of node 5dca... \n",ALIAS,GRS,NML);
printf("    %s -m [5dca...] -t  %s->%s    edit the tag of node 5dca... \n",ALIAS,GRS,NML);
printf("         NOTE -P for protected data\n\n");

printf("    %s --setting   %s->%s    shows the path to the setup file file\n",ALIAS,GRS,NML);
printf("    %s --addfile   %s->%s    set up a new notes file\n",ALIAS,GRS,NML);
printf("    %s --showfile   %s->%s    generates a list with the inserted note files (shows an index that will be used to set that file)\n",ALIAS,GRS,NML);
printf("    %s --setfile 5   %s->%s    set the file with index 5 in use\n",ALIAS,GRS,NML);

printf("    %s --editor vim  %s->%s    set VIM as the default editor\n",ALIAS,GRS,NML);
printf("    %s --font grs  %s->%s    set the output bold \n",ALIAS,GRS,NML);
printf("    %s --color_hash wht  %s->%s    sets the hash color to white\n\n",ALIAS,GRS,NML);
 
printf("%sAUTHOR%s\n    Written by  Catoni Mirko (IMprojtech)\n\n",GRS,NML);

printf("%sVERSION%s\n    %s\n\n",GRS,NML,VER);}

void HashToString(const unsigned char *hash, size_t length) {
    for (size_t i = 0; i < length; i++) {
        sprintf(In_Hash + i * 2, "%02x", hash[i]);
    }
    In_Hash[length * 2] = '\0';
}

void GenerateSHA1(const NotesData *data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    unsigned char buffer[sizeof(NotesData)];
    memcpy(buffer, data, sizeof(NotesData));

    SHA1(buffer, sizeof(NotesData), hash);
    HashToString(hash, SHA_DIGEST_LENGTH);
}

void LoadStruct(char *_dest, char _src[], int size) {
    if (strlen(_dest) + strlen(_src) > size)
        Error(ErrorOverflow, "");
    else
        strcpy(_dest, _src);
}

void LoadComment(char *_dest, char _src[], int size) {
    if (strlen(_dest) + strlen(_src) > size)
        Error(ErrorOverflow, "");
    else {
        strcat(_dest, _src);
        strcat(_dest, " ");
    }
}

void Tokenizer(char *_Tag, char *_InTag) {
    char *token = strtok(In_Tag, "<>");

    if (token != NULL) {
        strcpy(_Tag, token);

        token = strtok(NULL, "<>");
        if (token != NULL) {
            strcpy(_InTag, token);
            return;
        }
    }
}

void Analyze_String_Tag(char *_InTag) {

    if (strchr(In_Tag, '<') != NULL && strchr(In_Tag, '>') != NULL)
        Error(ErrorArgument, In_Tag);
    else if (strchr(In_Tag, '<') != NULL)
        Tokenizer(_InTag, NDat.Tag);
    else if (strchr(In_Tag, '>') != NULL)
        Tokenizer(NDat.Tag, _InTag);
    else
        strcpy(NDat.Tag, In_Tag);
    return;
}

void DinamicWrite(void) {

    int max_length = 160;
    int length     = 0;
    int ch;

    Memo = (char *)malloc(max_length * sizeof(char));

    if (Memo == NULL) {
        Error(ErrorMemory, "");
    }

    printf("termina inserimento con CTRL+D\n");

    while ((ch = getchar()) != EOF) {
        Memo[length] = ch;
        length++;

        if (length >= max_length) {
            max_length *= 2;
            Memo = (char *)realloc(Memo, max_length * sizeof(char));

            if (Memo == NULL) {
                Error(ErrorMemory, "");
            }
        }
    }

    Memo[length] = '\0';	
}

void TakeTime(void) {
    time_t     currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    strftime(NDat.Date, sizeof(NDat.Date), "%Y-%m-%d %H:%M:%S", localTime);
}

