
/*! Contiene le funzioni di scrittura, lettura e gestione del file note
 *  contiene anche la funzione di lettura dei file linkati sulle note
 *  In oltre Edit si occupa di gestire l'editor usato per scrivere con -M !*/

#include <sys/wait.h>

void ReadNDat(int start, int end) {
    FILE *In;

    if ((In = fopen(File_Note, "rb")) == NULL)
        Error(ErrorCreationFile, "");

    fseek(In, start, SEEK_SET);
    if (end > 0) {
        fread(&NDat, sizeof(NotesData), 1, In);
        size_t memoLength = end - start - sizeof(NotesData);
        NDat.Memo         = (char *)malloc(memoLength * sizeof(char));
        fread(NDat.Memo, memoLength, 1, In);
    }

    fclose(In);
}

void CopyNDat(NotesData *dest, NotesData *src) {

    strcpy(dest->Tag, src->Tag);
    strcpy(dest->Comment, src->Comment);
    strcpy(dest->Link_File, src->Link_File);
    strcpy(dest->Date, src->Date);

    if (src->Memo != NULL) {
        dest->Memo = malloc(strlen(src->Memo) + 1);
        if (dest->Memo != NULL) {
            strcpy(dest->Memo, src->Memo);
        } else {
            Error(ErrorMemory, "");
        }
    } else
        dest->Memo = NULL;
}

void ReadFile(FILE *In, int start, int end) {

    fseek(In, start, SEEK_SET);

    memset(&NDat, 0, sizeof(NotesData));
    if (NDat.Memo != NULL) {
        free(NDat.Memo);
        NDat.Memo = NULL;
    }

    if (end > 0) {
        fread(&NDat, sizeof(NotesData), 1, In);
        size_t memoLength = end - start - sizeof(NotesData);
        NDat.Memo         = (char *)malloc(memoLength * sizeof(char));
        fread(NDat.Memo, memoLength, 1, In);
    }
}

void WriteFile(FILE *Out, TreeNode *root) {
    int check = 0;

    root->data.start = ftell(Out);

    check = fwrite(&NDat, sizeof(NotesData), 1, Out);
    if (check == 0)
        Error(ErrorWriteFile, "");

    if (NDat.Memo != NULL) {
        check = fwrite(NDat.Memo, strlen(NDat.Memo) + 1, 1, Out);
        if (check == 0)
            Error(ErrorWriteFile, "");
    }

    root->data.end = ftell(Out);
}

void ScrollTree(TreeNode *root, NotesData *tmp, FILE *In, FILE *Out) {

    if (root == NULL) {
        return;
    }

    if (root->data.end == 0) {
        CopyNDat(&NDat, tmp);
    }

    else {
        ReadFile(In, root->data.start, root->data.end);
    }

    if (root->data.end != -1) {
        WriteFile(Out, root);
    }

    ScrollTree(root->firstChild, tmp, In, Out);
    ScrollTree(root->nextSibling, tmp, In, Out);
}

void Save(NotesData *tmp) {

    FILE *In;
    FILE *Out;

    char old[201];

    strcpy(old, File_Note);
    strcat(old, "_old");
    rename(File_Note, old);

    if ((In = fopen(old, "rb")) == NULL)
        Error(ErrorCreationFile, "");
    if ((Out = fopen(File_Note, "wb")) == NULL)
        Error(ErrorCreationFile, "");

    ScrollTree(root, tmp, In, Out);

    fclose(In);
    fclose(Out);
}

void Edit(void) {

    if (strcasecmp(Editor, "Nul") == 0) {
        DinamicWrite();
        return;
    }

    FILE *tempFile;

    if ((tempFile = fopen("Edit.tmp", "w+")) == NULL) {
        Error(ErrorCreationFile, "");
    }

    fclose(tempFile);
    pid_t pid = fork();

    if (pid == 0) {
        if (strcasecmp(Editor, "Vim") == 0) {
            execl("/bin/vim", "vim", "Edit.tmp", NULL);
        } else if (strcasecmp(Editor, "Nano") == 0) {
            execl("/bin/nano", "nano", "Edit.tmp", NULL);
        }
    }

    else if (pid > 0) {
        wait(NULL);
    } else {
        Error(ErrorProcess, "");
    }

    if ((tempFile = fopen("Edit.tmp", "r")) == NULL) {
        Error(ErrorOpenFile, "");
    }

    size_t newSize = 0;
    int    ch;

    while ((ch = fgetc(tempFile)) != EOF) {
        newSize++;
    }

    NDat.Memo = (char *)malloc((newSize + 2) * sizeof(char));

    if (NDat.Memo == NULL) {
        Error(ErrorMemory, "");
    }

    rewind(tempFile);

    int i;

    for (i = 0; i < newSize; ++i) {
        ch           = fgetc(tempFile);
        NDat.Memo[i] = ch;
    }

    NDat.Memo[i] = '\0';

    fclose(tempFile);
    remove("Edit.tmp");
}

void PrintFile(void) {

    if (strcasecmp(Editor, "Vim") == 0) {
        execl("/bin/vim", "vim", NDat.Link_File, NULL);
    } else if (strcasecmp(Editor, "Nano") == 0) {
        execl("/bin/cat", "cat", NDat.Link_File, NULL);
    } else if (strcasecmp(Editor, "Nul") == 0) {
        FILE *input;
        int   ch;

        if ((input = fopen(NDat.Link_File, "rb")) == NULL)
            Error(ErrorOpenFile, "");
        ch = fgetc(input);
        printf("\n");
        while (!feof(input)) {
            printf("%c", ch);
            ch = fgetc(input);
        }

        printf("\n");
        fclose(input);
    }
}
