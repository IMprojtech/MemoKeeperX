
/*! Contiene alcune dichiarazioni di funzioni, per evitare errori di dipendenze !*/

// General_Functions.h
void Help(void);
void hashToString(const unsigned char *hash, size_t length);
void GenerateSHA1(const NotesData *data);
void LoadStruct(char *_dest, char _src[], int size);
void LoadComment(char *_dest, char _src[], int size);
void Tokenizer(char *_Tag, char *_InTag);
void Analyze_String_Tag(char *_InTag);
void DinamicWrite(void);
void TakeTime(void);

// File_Operations.h
void ReadNDat(int start, int end);
void CopyNDat(NotesData *dest, NotesData *src);
void Save(NotesData *tmp);
void Edit(void);
void PrintFile(void);
