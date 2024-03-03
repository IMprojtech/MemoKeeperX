
/*! Contiene le funzioni per la stampa dei dati e dei nodi!*/

#define BRANCH(depth)                                                          \
    for (int i = 0; i < depth; i++)                                            \
        printf("%s%s├──%s", NML, WHT, Font);
#define BRANCH_SPACE(depth)                                                    \
    for (int i = 0; i < depth; i++)                                            \
        printf("%s%s│  %s", NML, WHT, Font);

//----- Stampa NDat -----

void Print(TreeNode *root, int depth) {

    if (FilePath == true)
        printf("%s\n", NDat.Link_File);

    else if (File == true)
        PrintFile();

    else if (Memo == false) {
        BRANCH(depth);
        printf("%s%s%s %s%s ", Font, Color_Tag, root->data.tag, Color_Note,
               NDat.Comment);
        if (Extended == false) {
            if (strlen(NDat.Link_File) != 0)
                printf("%s# ", Color_File);
            if (NDat.Memo != NULL) {
                if (strlen(NDat.Memo) != 0)
                    printf("%s# ", Color_Memo);
            }
            printf("%s\n", NML);
        } else {
            if (strlen(NDat.Link_File) != 0)
                printf("%s%s ", Color_File, NDat.Link_File);
            if (NDat.Memo != NULL) {
                if (strlen(NDat.Memo) != 0)
                    printf("%s# ", Color_Memo);
            }
            printf("%s%s %s%s%s\n", Color_Hash, root->data.hash, Color_Date,
                   root->data.date, NML);
        }
    }

    else {
        BRANCH_SPACE(depth);
        printf("\n");
        BRANCH(depth);
        printf("%s%s[%s]%s\n", Font, Color_Tag, root->data.tag, NML);

        if (strlen(NDat.Comment) != 0) {
            BRANCH_SPACE(depth);
            printf("%s%s%s%s\n", Font, Color_Note, NDat.Comment, NML);
        }

        if (NDat.Memo != NULL) {
            if (strlen(NDat.Memo) != 0) {
                BRANCH_SPACE(depth);

                char *ptr = NDat.Memo;

                while (*ptr != '\0') {
                    if (*ptr != '\n') {
                        printf("%s%s%c%s", Font, Color_Memo, *ptr, NML);
                    } else {
                        printf("\n");
                        BRANCH_SPACE(depth);
                    }
                    ptr++;
                }
                printf("\n");
            }
        }

        if (strlen(NDat.Link_File) != 0) {
            BRANCH_SPACE(depth);
            printf("%s%s%s%s\n", Font, Color_File, NDat.Link_File, NML);
        }

        if (Extended == true) {

            if (strlen(root->data.hash) > 1) {
                BRANCH_SPACE(depth);
                printf("%s%s%s%s\n", Font, Color_Hash, root->data.hash, NML);
            }

            if (strlen(root->data.date) > 1) {
                BRANCH_SPACE(depth);
                printf("%s%s%s%s\n", Font, Color_Date, root->data.date, NML);
            }
        }
    }
}

void NDatPrintAll(TreeNode *root, int depth) {

    if (root == NULL) {
        return;
    }

    ReadNDat(root->data.start, root->data.end);

    Print(root, depth);

    NDatPrintAll(root->firstChild, depth + 1);
    NDatPrintAll(root->nextSibling, depth);
}

void NDatPrintFind(TreeNode *root, char *key, FindFunction find) {

    if (root == NULL) {
        return;
    }

    if (find(root, key) == 0) {
        ReadNDat(root->data.start, root->data.end);
        Print(root, 0);
    }

    NDatPrintFind(root->firstChild, key, find);
    NDatPrintFind(root->nextSibling, key, find);
}

//----- Stampa Albero -----

void PrintFindNode(TreeNode *root, char *key, FindFunction find) {

    if (root == NULL) {
        return;
    }

    if (find(root, key) == 0) {
        ReadNDat(root->data.start, root->data.end);
        printf("%s%s%s %s%s %s%s%s\n", Font, Color_Tag, root->data.tag,
               Color_Hash, root->data.hash, Color_File,
               strlen(NDat.Link_File) != 0 ? "#" : "", NML);
    }

    PrintFindNode(root->firstChild, key, find);
    PrintFindNode(root->nextSibling, key, find);
}

void PrintTree(TreeNode *root, int depth) {

    if (root == NULL) {
        return;
    }

    BRANCH(depth);

    printf("%s%s%s %s%s%s\n", Font, Color_Tag, root->data.tag, Color_Hash,
           Extended == false ? "" : root->data.hash, NML);

    PrintTree(root->firstChild, depth + 1);
    PrintTree(root->nextSibling, depth);
}

void PrintChildren(TreeNode *parentNode) {

    if (parentNode == NULL || parentNode->firstChild == NULL) {
        return;
    }

    ReadNDat(parentNode->data.start, parentNode->data.end);
    Print(parentNode, 0);
    NDatPrintAll(parentNode->firstChild, 1);
}
