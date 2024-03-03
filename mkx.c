
/*!
*****   Program Description: MemoKeeperX   *****

 "MemoKeeperX" alias "mkx" is a command-line Linux application
  designed to streamline the management and organization of notes and crucial information.
  It provides an intuitive interface for input, categorization, and display of notes,
  allowing users to create a hierarchical structure using personalized tags.

***   Key Features   ***
 ° Note Creation: Users can input notes containing comments, text, and file paths,
   providing a comprehensive view of the desired information.

 ° Hierarchical Organization: Leveraging the use of tags, the program allows users to organize notes into tree structures,
   enabling flexible and customized categorization.

 ° File Links: Users can associate notes with specific files,
   creating direct links for quick and efficient access to related resources.

 ° Terminal-Friendly:** The program is designed for interaction via the command line Linux,
   offering a fast and no-frills user experience.

***   Practical Applications   ***

 ° Penetration Testing: mkx is an essential tool during information research in pentesting,
   enabling operators to effectively archive discoveries and access them rapidly when needed.

 ° Personal Management: Adaptable to any field where the orderly storage of notes and texts is crucial,
   facilitating the swift retrieval of previously saved information.

**   License   **
 This program is distributed under the terms of the GNU General Public License (GPL),
 ensuring the freedom to redistribute and modify the software in accordance with open-source standards.

**   Author   **
 Catoni Mirko (IMprojtech)

 Create your personal organizational structure with "MemoKeeperX" and simplify the management of your information! */

#define _GNU_SOURCE
#include <stdio.h>
#include "Source/Global.h"

int main(int argc, char *argv[]) {

    Start_System_Check();
    printf("%s", Font);
		
    ProcessArguments(argc, argv);
    root = LoadFromFile(root);

    ProcessTree();

    if (Memo != NULL)
        free(Memo);
    FreeTree(root);
    return 0;
}
