
/*! Contiene le strutture e le variabili usate la creazione e gestione del albero !*/

#define STRNODE "*NODE*"
#define STRNODENULL "*NULL*"
#define DELIMITER "*====*"
#define INITIAL_TAG "/"

typedef struct {
    long start;
    long end;
    char hash[42];
    char tag[24];
    char date[20];
} BlockInfo;

typedef struct TreeNode {
    BlockInfo        data;
    struct TreeNode *firstChild;
    struct TreeNode *nextSibling;
} TreeNode;

typedef int (*FindFunction)(TreeNode *, char *);

FILE *PtrFileTree;

TreeNode    *root = NULL;
BlockInfo    data = {0, 0, ".", ".", "."};
FindFunction find;
