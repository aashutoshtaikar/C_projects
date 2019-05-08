#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node 
{ 
	int data; 
	struct node *left; 
	struct node *right; 
}node_t; 

node_t* createNode(int data){
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}



void newNode(node_t* node,int data) {
    if (node->left == NULL && node->right == NULL){
        node = createNode(data);
    }
    else if(data < node->data){
        node->left = createNode(data);
    }
    else if(data > node->data){
        node->right = createNode(data);
    }
} 

node_t* findNode(node_t* leaf,int data){
    if (leaf != NULL) {
        if (data == leaf->data) {
            return leaf;
        }
        else if(data < leaf->data){
            findNode(leaf->left,data);
        }
        else if (data > leaf->data){
            findNode(leaf->right,data);
        }
    }
}

void deleteNode(node_t* leaf, int data){
    node_t* foundNode = findNode(leaf, data);
    //no child
    if(foundNode->left == NULL && foundNode->right == NULL){
        free(foundNode);
        foundNode = NULL;
    }
    else if(foundNode->left!=NULL && foundNode->right == NULL){
        foundNode = foundNode->left;
        free(foundNode->left);
        foundNode->left = NULL;
    }
    else if (foundNode->right!=NULL && foundNode->right == NULL) {
        foundNode = foundNode->right;
        free(foundNode->right);
        foundNode->right = NULL;
    }
    else{
        foundNode = foundNode->left;
        free(foundNode->left);
        foundNode->left = NULL;
    }
}



int main() 
{ 
    node_t* n = NULL;
    newNode(n,4);
    newNode(n,2);
    newNode(n,1);
    newNode(n,3);

    //deleteNode(n, 2);
    printf("%d",n->left->data);

    getchar(); 
    return 0; 
}
