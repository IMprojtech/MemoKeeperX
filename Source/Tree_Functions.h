
/*! Contiene le funzioni utili per manipolare i nodi del albero compreso il salvataggio e carico da file !*/

#include "Tree_Header.h"

//----- Libera Memoria-----

void FreeTree(TreeNode *root) {

    if (root == NULL) {
        return;
    }

    FreeTree(root->firstChild);
    FreeTree(root->nextSibling);
    free(root);
    root = NULL;
}

//----- Controlli sui Nodi -----

//! Funzione ausiliaria per verificare la presenza di tag duplicati nell'albero
void CheckDuplicate(TreeNode *root, char *key, FindFunction find, int *cont) {
    if (root == NULL) {
        return;
    }

    if (find(root, key) == 0) {
        (*cont)++;
    }

    CheckDuplicate(root->firstChild, key, find, cont);
    CheckDuplicate(root->nextSibling, key, find, cont);
}

//! Funzione ausiliaria per verificare se un nodo è discendente di un altro nodo
int IsDescendant(TreeNode *potentialDescendant, TreeNode *ancestor) {
  while (potentialDescendant != NULL) {
    if (potentialDescendant == ancestor) {
      return 1;  
    }

    potentialDescendant = potentialDescendant->firstChild;

  }

  return 0; 
}

//----- Ricerca -----

int FindTagNode(TreeNode *node, char *tag) {
    return strncasecmp(node->data.tag, tag, strlen(tag));
}

int FindHashNode(TreeNode *node, char *hash) {
    return strncasecmp(node->data.hash, hash, strlen(hash));
}

int FindDateNode(TreeNode *node, char *date) {
    return strncasecmp(node->data.date, date, strlen(date));
}

TreeNode *FindNode(TreeNode *root, char *key, FindFunction find) {
    if (root == NULL) {
        return NULL;
    }

    if (find(root, key) == 0) {
        return root;
    }

    TreeNode *result = FindNode(root->firstChild, key, find);
    if (result == NULL) {
        result = FindNode(root->nextSibling, key, find);
    }

    return result;
}

TreeNode *FindPreviousSibling(TreeNode *root, TreeNode *node) {
	
    if (root == NULL) {
        return NULL;
    }

    if (root->nextSibling == node || root->firstChild == node){
        return root;
    }

    TreeNode *result = FindPreviousSibling(root->firstChild,node);
    if (result == NULL) {
        result = FindPreviousSibling(root->nextSibling, node);
    }

    return result;
}	
 
//----- Gestione Albero -----

TreeNode *InsertNode(TreeNode *currentNode, BlockInfo data) {

    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));

    newNode->data        = data;
    newNode->firstChild  = NULL;
    newNode->nextSibling = NULL;

    if (currentNode == NULL) {
        return newNode;
    }

    if (currentNode->firstChild == NULL) {
        currentNode->firstChild = newNode;
    }

    else {
        TreeNode *sibling = currentNode->firstChild;
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = newNode;
    }
    return currentNode;
}

TreeNode *RemoveNode(TreeNode *root, char *hash) {

    if (root == NULL) {
        return NULL;
    }

    if (strncasecmp(root->data.hash, hash, strlen(hash)) == 0) {
        TreeNode *newRoot = root->nextSibling;
        free(root);
        return newRoot;
    }

    TreeNode *currentSibling  = root;
    TreeNode *previousSibling = NULL;

    while (currentSibling != NULL &&
           strncasecmp(currentSibling->data.hash, hash, strlen(hash)) != 0) {
        previousSibling = currentSibling;
        currentSibling  = currentSibling->nextSibling;
    }

    if (currentSibling != NULL) {
        if (previousSibling != NULL) {
            previousSibling->nextSibling = currentSibling->nextSibling;
        }
        free(currentSibling);
    }

    root->firstChild  = RemoveNode(root->firstChild, hash);
    root->nextSibling = RemoveNode(root->nextSibling, hash);

    return root;
}

TreeNode *CopySubTree(TreeNode *subtree) {
    if (subtree == NULL) {
        return NULL;
    }

    TreeNode *copy = malloc(sizeof(TreeNode));
    copy->data = subtree->data;
    copy->firstChild = CopySubTree(subtree->firstChild);
    copy->nextSibling = CopySubTree(subtree->nextSibling);

    return copy;
}

void SwapNodes( TreeNode *previous, TreeNode *current, TreeNode *next) {
    if ( current == NULL || next == NULL)
        Error(ErrorMoveNode, "");

    if (previous->firstChild == current) {
        current->nextSibling = next->nextSibling;
        next->nextSibling = current;
        previous->firstChild = next;
    } else {
        current->nextSibling = next->nextSibling;
        next->nextSibling = current;
        previous->nextSibling = next;
    }
}

TreeNode *MoveNode(TreeNode *root, char *keyDestination, char *keySource, FindFunction find) {
 
    TreeNode *sourceNode = FindNode(root, keySource, find);
    
    if (sourceNode == NULL)
        Error("source", ErrorFindNode);    

    if (strncasecmp(keyDestination,"up",strlen(keyDestination)) == 0) {  // Move Up
		TreeNode *previusNode = FindPreviousSibling(root, sourceNode);
		TreeNode *previuspreviusNode = FindPreviousSibling(root, previusNode);

		if (previusNode == NULL || previusNode->firstChild == sourceNode)
			Error(ErrorMoveNode, "");
	
		SwapNodes(previuspreviusNode, previusNode,  sourceNode);		
	
	} 
    else if (strncasecmp(keyDestination,"down",strlen(keyDestination)) == 0) {  // Move Down
		TreeNode *previusNode = FindPreviousSibling(root, sourceNode);

		if (sourceNode->nextSibling == NULL)
			Error(ErrorMoveNode, "");

		SwapNodes(previusNode,sourceNode, sourceNode->nextSibling);
    } 
    else {

		TreeNode *nodeDestination = FindNode(root, keyDestination, find);

		if (nodeDestination == NULL)
			Error("destination", ErrorFindNode);

		if (IsDescendant(sourceNode, nodeDestination)) {
			Error(ErrorMoveNode, "");
		}

		TreeNode *newNode = malloc(sizeof(TreeNode));
		newNode->data = sourceNode->data;
		newNode->firstChild = CopySubTree(sourceNode->firstChild);
		newNode->nextSibling = NULL;

		root = RemoveNode(root, keySource);

		if (nodeDestination->firstChild == NULL) {
			nodeDestination->firstChild = newNode;
		} 
		else {
			TreeNode *sibling = nodeDestination->firstChild;
			while (sibling->nextSibling != NULL) {
				sibling = sibling->nextSibling;
			}
			sibling->nextSibling = newNode;
		}
	}

return root;
}
    
//----- Salva e Carica Albero -----

void WriteTree(TreeNode *root) {
    if (root == NULL) {
        fprintf(PtrFileTree, "%s\n", STRNODENULL);
        return;
    }

    fprintf(PtrFileTree, "%s\n%ld %ld %s %s %s\n", STRNODE, root->data.start,
            root->data.end, root->data.hash, root->data.tag, root->data.date);
    WriteTree(root->firstChild);
    WriteTree(root->nextSibling);
}

TreeNode *ReadTree(void) {
    BlockInfo data;
    char      opt[8];

    if (fscanf(PtrFileTree, "%7s", opt) != 1) {
        return NULL;
    }

    if (strcmp(opt, STRNODENULL) == 0) {
        return NULL;
    }

    if (strcmp(opt, STRNODE) == 0) {
        if (fscanf(PtrFileTree, "%ld %ld %40s %23s %19[^\n]", &data.start,
                   &data.end, data.hash, data.tag, data.date) != 5) {
            return NULL;
        }

        TreeNode *root = InsertNode(NULL, data);

        if (root == NULL)
            Error(ErrorReadTree, "");

        root->firstChild  = ReadTree();
        root->nextSibling = ReadTree();
        return root;
    }

    return NULL;
}

void SaveToFile(TreeNode *root) {

    if ((PtrFileTree = fopen(File_Note, "rb+")) == NULL)
        Error(ErrorOpenFile, "");

    fseek(PtrFileTree, 0, SEEK_END);
    fprintf(PtrFileTree, "\n %s \n", DELIMITER);
    WriteTree(root);
    fclose(PtrFileTree);
}

int FindDelimiter(void) {
    fseek(PtrFileTree, 0, SEEK_END);

    long position = ftell(PtrFileTree);

    while (position >= 0) {
        fseek(PtrFileTree, position, SEEK_SET);
        char ch = fgetc(PtrFileTree);

        if (ch == ' ' || ch == '\n') {
            char word[100];
            fscanf(PtrFileTree, "%s", word);
            if (strcmp(word, DELIMITER) == 0)
                return position;
        }
        position--;
    }
    Error(ErrorDelimiterTree, "");
    return -1;
}

TreeNode *LoadFromFile(TreeNode *root) {

    if ((PtrFileTree = fopen(File_Note, "rb")) == NULL)
        Error(ErrorOpenFile, "");

    fseek(PtrFileTree, 0, SEEK_END);
    int check = ftell(PtrFileTree);

    if (check > 0) {
        FindDelimiter();
        root = ReadTree();
        fclose(PtrFileTree);
    } else {
        fclose(PtrFileTree);
        strcpy(data.tag, INITIAL_TAG);
        root           = InsertNode(root, data);
        root->data.end = -1;
    }
    return root;
}

