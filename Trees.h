#ifndef TREES_H_INCLUDED
#define TREES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define noOfWords 3000

typedef struct Node{
    struct Node* left;
    struct Node* right;
    char* word;
    int height;
}Node;


Node* newNode(char* word); //Creates a new node
Node* insert(Node*root , char* input); //Inserts into the AVL tree which balances itself
Node *rightRotate(Node *node); //Right rotation of an unbalanced node
Node *leftRotate(Node *node); //Left rotation of an unbalanced node
int height(Node *node); // Get height of a given node , helping function
int getBalance(Node *node); //Get balance of given node , helping function , left - right
void findPredSucc(Node* root , Node* pred, Node* succ, char * input); //Finds the successor and predecessor and prints them
void color(int i);  //Changes color in command prompt
void search(Node *root , char* input); //Searches for a given word in the tree
int isBalanced(Node *root); //To check if the tree is balanced
Node* insertRecursion(char arr[][64], int start , int end);

#endif // TREES_H_INCLUDED
