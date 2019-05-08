#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node* next;
} node;

typedef struct NodeHeader{
    node* head;
    node* tail;
} nodeHeader;

void addNode(nodeHeader* header, int val){
    if(header->head == NULL){
        header->head = (node*)malloc(sizeof(node));
        header->head->value = val;
        header->head->next = NULL;
        header->tail = header->head;
    }
    else{
        node* current = header->head;
        while(current->next != NULL){
            current = current->next;
        }
        header->tail = (node*)malloc(sizeof(node));
        header->tail->value = val;
        header->tail->next = NULL;
        current->next = header->tail;
    }
}

void printNode(nodeHeader* header){
    node* current = header->head; 
  
    while(current != NULL){
        printf("%d, ",current->value);
        current = current->next;    
    }
    printf("\n");
}

void reverseNodes(nodeHeader* header){
    node* prev = NULL;
    node* curr = header->head;
    node* Next = NULL;
    
    header->tail = header->head;
   
   while(curr != NULL){
       Next = curr->next;
       curr->next = prev;
       prev = curr;
       curr = Next;
   }
   header->head = prev;
   
}

int main(){
    nodeHeader* nh = (nodeHeader*)malloc(sizeof(nodeHeader));
    nh->head = NULL;
    nh->tail = NULL;
    addNode(nh,1);
    addNode(nh,2);
    addNode(nh,3);
    
    printNode(nh);
    
    reverseNodes(nh);
    
    printNode(nh);
}
