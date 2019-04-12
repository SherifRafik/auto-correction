#include <stdio.h>
#include <stdlib.h>
#include "Trees.h"


int readFile(const char * filepath); //Read from the given file
void putWords(); //Insert words into the tree
void seachWordBST(char input[]); //Search every word entered by user
void seachWordAVL(char input[]); //Search every word entered by user
int treeHeight(Node * root); //Get Tree height
char words[noOfWords][64];  //2d - Array of words
Node *AVLroot = NULL; //ROOT
Node *BSTroot = NULL; //ROOT

int main()
{
    if(!readFile("dictionary.txt")) exit(-1);
    putWords();
    char inputBST[512] , inputAVL[512];
    color(11);
    printf("Tree height = %d.\n" , treeHeight(BSTroot));
    printf("Parent > Successor > Predecessor\n");
    printf("BST tree results may be different from the AVL tree results\ndue to balancing methods\n");
    color(15);
    fflush(stdin);
    printf("Enter your sentence:");
    fgets(inputBST,512,stdin);
    inputBST[strlen(inputBST) - 1] = '\0';
    if (inputBST[0] == '\0') {
        color(12);
        printf("Input string is NULL\n");
        color(7);
        return 0;
    }
    strcpy(inputAVL,inputBST);
    color(11); printf("\nBST\n"); color(15);
    seachWordBST(inputBST);
    color(11); printf("\nAVL\n"); color(15);
    seachWordAVL(inputAVL);
    color(7);
    return 0;
}


int readFile(const char * filepath)
{
    int i=0;
    FILE *filePointer = fopen(filepath,"r");
    if(!filePointer) return 0;
    char buffer[64];
    int counter = 0;
    while(!feof(filePointer))
    {
        fscanf(filePointer,"%s\n",buffer);
        for(counter = 0 ; counter < 64 ; counter ++)
            buffer[counter] = tolower(buffer[counter]);
        strcpy(words[i++] , buffer);
    }
    fclose(filePointer);
    return 1;
}

int treeHeight(Node * root)
{
    if(root == NULL)
        return 0;
    int leftHeight = root->left ? treeHeight(root->left) : 0;
    int rightHeight = root->right ? treeHeight(root->right) : 0;
    return 1+(leftHeight>=rightHeight?leftHeight:rightHeight);
}

void putWords()
{
    int i;
    //AVL TREE
    for(i = 0 ; i < noOfWords ; i++)
        AVLroot  = insert(AVLroot,words[i]);
    //Sorted Array to BST
    BSTroot  = insertRecursion(words,0,noOfWords-1);
}

void seachWordBST(char input[])
{
    char *split = strtok(input," ,.");
    while(split!=NULL)
    {
        search(BSTroot,split);
        split = strtok (NULL, " ,.");
    }
    return;
}

void seachWordAVL(char input[])
{
    char *split = strtok(input," ,.");
    while(split!=NULL)
    {
        search(AVLroot,split);
        split = strtok (NULL, " ,.");
    }
    return;
}
