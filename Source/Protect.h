
/*! Contiene funzioni per la protezione delle note private !*/

#include <openssl/sha.h>
#include <termios.h>
#include <time.h>

void WriteKey(char *password,int size) {
  
    struct termios oldt, newt;
    
    printf("Key: ");
    fflush(stdout);

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;  // Disabilita l'eco dell'input
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    fgets(password, size, stdin);

    size_t length = strlen(password);
    if (length > 0 && password[length - 1] == '\n') {
        password[length - 1] = '\0';
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
    printf("\r    \r");
}

void KeyGenerateSHA1(const char *input, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

	SHA256((const unsigned char *)input, sizeof(input), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }

    output[2 * SHA256_DIGEST_LENGTH] = '\0';
}

void GenerateKey(char key[],char *iv,int size,int iteractions){

	char *ptrKey=key;
	char *ptrIv=iv;
	int tmp;
	int i=0;	

	for(int iter = 0;iter < iteractions;iter++){
		while(i!=size){ 
			tmp = (*iv + *key);
			if (tmp > 0x7E) 
				tmp -= 0x7E;
			Key[i] = (char)tmp;
			i++;
			key++; iv++;	

			if (*key=='\0') 
				key=ptrKey;
				 
			if (*iv=='\0') 
				iv=ptrIv;	
		}
		i=0;
	}
	Key[i] ='\0';
}

void GenerateRandomIV(char *iv, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // Caratteri disponibili
    int charsetSize = sizeof(charset) - 1;

    srand((unsigned int)time(NULL)); 

    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % charsetSize;
        iv[i] = charset[randomIndex];
    }

    iv[length] = '\0';
}

void CryptDat(char *key,char *str,int len){
	char *ptrkey;
	int tmp;
	int i=0;	
	
	ptrkey=key;

	while(i!=len){ 
		tmp = (*str + *key);
		if (tmp > 0x7E) 
			tmp -= 0x7E;
		*str = (char)tmp;
		i++;
		key++; str++;	

		if (*key=='\0') 
			key=ptrkey; 
	}
}

void DecryptDat(char *key,char *str,int len){
	char *ptrkey;
	int tmp;
	int i=0;
 	
	ptrkey=key;

	while(i!=len){ 
		tmp = (*str - *key);
		if (tmp<0x0) tmp += 0x7E;
			*str = (char)tmp;
		i++;
		key++; str++;

		if (*key=='\0') 
			key=ptrkey;
	}
}

void Crypt(const char *password) {
	NDat.Protection=true;
	GenerateRandomIV(NDat.Iv,sizeof(NDat.Iv)-1);
	GenerateKey(Key,NDat.Iv,sizeof(Key)-1,10);	
	
	CryptDat(Key,NDat.Comment,strlen(NDat.Comment));	
	CryptDat(Key,NDat.Link_File,strlen(NDat.Link_File));	
	if(Memo!=NULL)
		CryptDat(Key,Memo,strlen(Memo));	

}

void Decrypt(const char *password) {
	GenerateKey(Key,NDat.Iv,sizeof(Key)-1,10);	
		
	DecryptDat(Key,NDat.Comment,strlen(NDat.Comment));	
	DecryptDat(Key,NDat.Link_File,strlen(NDat.Link_File));	
	if(Memo!=NULL)
		DecryptDat(Key,Memo,strlen(Memo));	

}

void Mask(void){
	strcpy(NDat.Comment, "*****");
    strcpy(NDat.Link_File, "*****");
    if(Memo!=NULL)
		 strcpy(Memo, "*****");
    
}


