
/*! Contiene alcune dichiarazioni di funzioni, per evitare errori di dipendenze !*/

// General_Functions.h
void Help(void);
void HashToString(const unsigned char *hash, size_t length);
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
void CopyMemo(char **dest, char **src);
void Save(NotesData *tmpNDat,char **Memo);
void Edit(void);
void PrintFile(void);
void Backup(void);

// Protect.h
void WriteKey(char *password,int size);
void KeyGenerateSHA1(const char *input, char *output);
void Crypt(const char *password);
void Decrypt(const char *password);
void Mask(void);

