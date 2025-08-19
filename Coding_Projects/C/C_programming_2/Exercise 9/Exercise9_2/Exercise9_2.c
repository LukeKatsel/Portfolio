#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 30

typedef struct _listNode {
    char word[MAX_WORD_LENGTH];
    struct _listNode *pNext;
} LinkedListNode;

LinkedListNode *AddWord(LinkedListNode *list, char word[MAX_WORD_LENGTH]);
void PrintFunc(LinkedListNode *list);

int main(int argc, char *argv[]){
    
    if (argc != 2){
        printf("\nWrong number of command arguments\n\n");
        return -1;
    }
    
    FILE *file;
    char line[MAX_WORD_LENGTH];
    char word[MAX_WORD_LENGTH];
    LinkedListNode *plist = NULL;

    if((file = fopen(argv[1], "r")) != NULL){

        while (fgets(line, MAX_WORD_LENGTH, file) != NULL){
            sscanf(line, "%s", word);                           // removes whitespace from line
            plist = AddWord(plist, word);
        }
        fclose(file);

        PrintFunc(plist);
    }
    else{
        printf("\nERROR: File did not open!\n\n");
        return -2;
    }
    return 0;
}

LinkedListNode *AddWord(LinkedListNode *list, char word[MAX_WORD_LENGTH]){

    // allocate mem for first node with error checking
    LinkedListNode *pNewNode = malloc(sizeof(LinkedListNode));
    if( pNewNode == NULL){
        printf("\nError: Count not allocate memory for new node\n\n");
        exit(-3);
    }
    
    // copy date into new node
    strcpy(pNewNode->word, word);
    pNewNode->pNext = NULL;            

    // Add new node to linked list
    if (list == NULL){

        list = pNewNode;                // List is empty
    }
    else{        
        LinkedListNode *pCurNode = list;                                    // so we can assign pNewNode->pNext
        LinkedListNode *pPrevNode = NULL;

        while (pCurNode != NULL && strcasecmp(pCurNode->word, word) < 0){   // while list is not empty and have not found location for word
            
            pPrevNode = pCurNode;                                           // go through list
            pCurNode = pCurNode->pNext;
        }

        if (pPrevNode == NULL) {                                            // if list was empty
            pNewNode->pNext = list;                                         // newNode is first node
            list = pNewNode;
        }
        else {                                                          
            pPrevNode->pNext = pNewNode;
            pNewNode->pNext = pCurNode;
        }
    }
    return list;
}

void PrintFunc(LinkedListNode *list){
    LinkedListNode *pTemp;

    while (list != NULL){

        printf("%s\n", list->word);

        pTemp = list;
        list= list->pNext;
        free(pTemp);
    }
}
