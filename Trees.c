#include "Trees.h"

Node* newNode(char* word)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->word = word;
    node->height = 1;
    return node;
}

  /////////////// AVL TREE /////////////////

Node* insert(Node*root , char* input)
{
    if(root == NULL)
        return newNode(input);
    if(strcmp(root->word , input) > 0)
        root->left = insert(root->left , input);
    else if(strcmp(root->word , input) < 0)
        root->right = insert(root->right , input);
    else
        return root;
    int balance = getBalance(root);
    // Left Left Case
    if (balance > 1 && strcmp(root->left->word , input) > 0)
        return rightRotate(root);
        // Left Right Case
    if (balance > 1 && strcmp(root->left->word , input) < 0){
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && strcmp(root->right->word , input) < 0)
        return leftRotate(root);
    // Right Left Case
    if (balance < -1 && strcmp(root->right->word , input) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    root->height= 1+ max(height(root->left),height(root->right));
    return root;
}

Node* rightRotate(Node *node)
{
    Node *left = node->left;
    Node *right = left->right;
    left->right = node;
    node->left = right;
    node->height = max(height(node->left), height(node->right))+1;
    left->height = max(height(left->left), height(left->right))+1;
    return left;
}

Node* leftRotate(Node *node)
{
    Node *right = node->right;
    Node *left = right->left;
    right->left = node;
    node->right = left;
    node->height = max(height(node->left), height(node->right))+1;
    right->height = max(height(right->left), height(right->right))+1;
    return right;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int height(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int isBalanced(Node *root)
{
   int lh;
   int rh;
   if(root == NULL)
    return 1;
   /* Get the height of left and right sub trees */
   lh = height(root->left);
   rh = height(root->right);
   if( abs(lh-rh) <= 1 &&
       isBalanced(root->left) &&
       isBalanced(root->right))
     return 1;
   /* If we reach here then tree is not height-balanced */
   return 0;
}

  //////////////////////BINARY SEARCH TREE/////////////////////

Node* insertRecursion(char arr[][64], int start , int end)
{
      if (start > end) return NULL;
      int mid = (start + end)/2;
      Node* node = newNode(arr[mid]);
      node->left = insertRecursion(arr, start, mid-1);
      node->right = insertRecursion(arr, mid+1, end);
      return node;
}


void search(Node *root , char* input)
{
    char buffer[64];
    strcpy(buffer,input);
    int i;
    for(i=0;i<64;i++)
        buffer[i] = tolower(buffer[i]);
    if(root == NULL) return;
    Node * node = root;
    Node * parent = node;
    while(node)
    {
        parent = node;
        if(strcmp(node->word,buffer) == 0)
            break;
        else if(strcmp(node->word , buffer) > 0)
            node = node->left;
        else
            node = node->right;
    }
    if(node!=NULL)
        printf("%s is a correct word!   \n",parent->word);
    else
    {
        Node*pred=NULL;
        Node*succ=NULL;
        //Print parent > successor > predecessor
        printf("%s -> Incorrect , Suggestions: %s    ",input,parent->word);
        findPredSucc(root,pred,succ,parent->word);
    }
}


void findPredSucc(Node* root , Node* pred, Node* succ, char * input)
{
    //Base Case
    if(root == NULL)
        return;
    //If key exist in root
    if(strcmp(root->word , input) == 0){
        //Maximum value in the left subtree
        if(root->left!=NULL){
            Node * temp = root->left;
            while(temp->right)
                temp = temp->right;
            pred = temp;
        }
        //Minimum value in the right subtree
        if(root->right!=NULL){
            Node* temp = root->right;
            while(temp->left)
                temp = temp->left;
            succ = temp;
        }
        if(succ)
            printf("%s    ",succ->word);
        if(pred)
            printf("%s\n",pred->word);
        if(!pred)
            printf("\n");
        return;
    }
    //Input is smaller than root , go left
    if(strcmp(root->word , input) > 0){
        succ = root;
        findPredSucc(root->left , pred , succ, input);
    }
    //Input is larger that root , go right
    else{
        pred = root;
        findPredSucc(root->right , pred , succ , input);
    }
}

void color(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}
