
#include "Tree_Functions.h"
#include "Tree_Functions_Print.h"
#include "Search_Date_Process.c"

void ProcessTree(void) {

	if(Protect == true){
		char TmpHashPass[65];
	
		WriteKey(Key,sizeof(Key));
		KeyGenerateSHA1(Key,TmpHashPass);
		
		if (strcmp(TmpHashPass,HashPass)!=0)
			Error(ErrorPassword,"");
	}
	
	if (Modify == true) {
		
		NotesData tmpNDat={0};
		char *tmpMemo=NULL;
	
		if(Write == true)
			strcpy(tmpNDat.Comment,NDat.Comment);
		
		if(strlen(NDat.Link_File)!=0)
			strcpy(tmpNDat.Link_File,NDat.Link_File);

		int cont=0;
		find     = FindHashNode;        
        
        CheckDuplicate(root, In_Hash, find, &cont);      
        if (cont > 1)
			Error(ErrorDuplicate, "");	    		
		
		find = FindHashNode;
		TreeNode *node = FindNode(root, In_Hash, find);
		
		if (node == NULL){
			Error(ErrorFound,"");
		}	
		
			ReadNDat(node->data.start,node->data.end);	
			
			if(NDat.Protection == true){
				if(Protect == true)
					Decrypt(Key);
				else
					Error(ErrorProtect,"");
			}
			
			node->data.start=0;
			node->data.end=0;
			
			if(strlen(tmpNDat.Comment)!=0)
				strcpy(NDat.Comment,tmpNDat.Comment);
		
			if(strlen(tmpNDat.Link_File)!=0)
				strcpy(NDat.Link_File,tmpNDat.Link_File);
			
			if(strlen(In_Tag)!=0){
				strcpy(NDat.Tag,In_Tag);
				strcpy(node->data.tag,In_Tag);
			}	
					
			if (Mem == true) 
				Edit();
		
			if(Protect == true)
				Crypt(Key);

			CopyNDat(&tmpNDat, &NDat);
			CopyMemo(&tmpMemo, &Memo);		
		
			Save(&tmpNDat,&tmpMemo);
			SaveToFile(root); 
		
		}
		
    else if (Write == true) {
        NotesData tmpNDat;
        char *tmpMemo=NULL;
        if (Mem == true) {
            Edit();
        }

        char parentTag[24] = {"\0"};

        if (strlen(In_Tag) == 0)
            strcpy(NDat.Tag, DefaultTag);
        else
            Analyze_String_Tag(parentTag);

        TakeTime();
        GenerateSHA1(&NDat);

        strcpy(data.tag, NDat.Tag);
        strcpy(data.date, NDat.Date);
        strcpy(data.hash, In_Hash);

		if(Protect == true)	
			Crypt(Key);

        CopyNDat(&tmpNDat, &NDat);
        CopyMemo(&tmpMemo, &Memo);

        if (strlen(parentTag) == 0)
            root = InsertNode(root, data);
        else {
            int cont = 0;
            find     = FindTagNode;

            CheckDuplicate(root, parentTag, find, &cont);
            if (cont > 1) {
                int cont = 0;
                Alert("ambiguous tag\n", "do you want to specify a hash?");
                PrintFindNode(root, parentTag, find);
                printf("Enter hash ->");
                scanf("%40s", In_Hash);
                find = FindHashNode;
                CheckDuplicate(root, In_Hash, find, &cont);
                if (cont > 1)
                    Error(ErrorDuplicate, "");
                else {
                    TreeNode *parentNode = FindNode(root, In_Hash, find);
                    if (parentNode == NULL)
                        Error(In_Hash, ErrorFound);
                    else {
                        InsertNode(parentNode, data);
                    }
                }
            } else {
                TreeNode *parentNode = FindNode(root, parentTag, find);
                if (parentNode == NULL)
                    Error(parentTag, ErrorFound);
                else {
                    InsertNode(parentNode, data);
                }
            }
        }
        Save(&tmpNDat,&tmpMemo);
        SaveToFile(root);
    }

    else if (Remove == true) {
		
		if(Protect != true)
			Error(ErrorProtect,"");
			
        if (strlen(In_Hash) != 0) {
            int cont = 0;
            find     = FindHashNode;
            CheckDuplicate(root, In_Hash, find, &cont);
            if (cont > 1)
                Error(ErrorDuplicate, "");
            else {
                root = RemoveNode(root, In_Hash);
            }
        } else if (strlen(In_Tag) != 0) {
            int cont = 0;
            find     = FindTagNode;
            CheckDuplicate(root, In_Tag, find, &cont);
            if (cont > 1) {
                Alert("ambiguous tag\n", "do you want to specify a hash?");
                PrintFindNode(root, In_Tag, find);
                printf("Enter hash ->");
                scanf("%40s", In_Hash);
                cont = 0;
                find = FindHashNode;
                CheckDuplicate(root, In_Hash, find, &cont);
                if (cont > 1)
                    Error(ErrorDuplicate, "");
                else {
                    root = RemoveNode(root, In_Hash);
                }
            } else {
                TreeNode *nodeToRemove = FindNode(root, In_Tag, find);
                root = RemoveNode(root, nodeToRemove->data.hash);
            }
        } else
            Error(ErrorSintax, "");
        Save(NULL,NULL);
        SaveToFile(root);
    }

	else if (Organize == true) {

		if(Protect != true)
			Error(ErrorProtect,"");

		if(In_Hash[0]=='.')
			Error("the root cannot be moved ","");	
			
		int contD = 0,contS =0;
        find     = FindHashNode;
        
        CheckDuplicate(root, Parent_Hash, find, &contD);      
        if (contD > 1)
			Error(ErrorDuplicate, "destination");	 
			                 		
		CheckDuplicate(root, In_Hash, find, &contS);
        if (contS > 1){
        	Error(ErrorDuplicate, "source");
        }	
		
		find = FindHashNode;
		root = MoveNode(root, Parent_Hash, In_Hash,find);

		Save(NULL,NULL);
		SaveToFile(root);                 		
}

    else if (Show == true){
        PrintTree(root, 0);}

    else {
        if (strlen(In_Tag) != 0) {
            int size = strlen(In_Tag) - 1;
            find     = FindTagNode;
            if (File == true || FilePath == true) {
                int cont = 0;
                CheckDuplicate(root, In_Tag, find, &cont);
                if (cont > 1) {
                    Alert("ambiguous tag\n", "do you want to specify a hash?");
                    PrintFindNode(root, In_Tag, find);
                    printf("Enter hash ->");
                    scanf("%40s", In_Hash);
                    cont = 0;
                    find = FindHashNode;
                    CheckDuplicate(root, In_Hash, find, &cont);
                    if (cont > 1)
                        Error(ErrorDuplicate, "");
                    else
                        NDatPrintFind(root, In_Hash, find);
                } else
                    NDatPrintFind(root, In_Tag, find);
            } else {
                if (In_Tag[size] == '+') {
                    In_Tag[size]         = '\0';
                    TreeNode *parentNode = FindNode(root, In_Tag, find);
                    PrintChildren(parentNode);
                }
                else if (In_Tag[size] == '-') {
                    In_Tag[size]         = '\0';
                    TreeNode *parentNode = FindNode(root, In_Tag, find);
                    PrintSibling(parentNode);
                } else {
                    NDatPrintFind(root, In_Tag, find);
                }
            }
        } else if (strlen(In_Hash) != 0) {
            int size = strlen(In_Hash) - 1;
            find     = FindHashNode;
            if (In_Hash[size] == '+') {
                In_Hash[size]        = '\0';
                TreeNode *parentNode = FindNode(root, In_Hash, find);
                PrintChildren(parentNode);
            } 
            else if (In_Hash[size] == '-') {
                In_Hash[size]        = '\0';
                TreeNode *parentNode = FindNode(root, In_Hash, find);
                PrintSibling(parentNode);
            }else {
                NDatPrintFind(root, In_Hash, find);
            }
        } else if (strlen(In_Date) != 0) {
            ProcessData(root);
        } else
            NDatPrintAll(root, 0);
    }

}
