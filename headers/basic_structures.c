#include <stdlib.h>
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
typedef struct byte_node{
    struct byte_node *previous;
    char value;
    struct byte_node *next;
} byte_node;
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void cut_elem(byte_node* elem){
    byte_node* tmp;

    if((tmp = elem -> previous) != NULL)
        tmp -> next = elem -> next;

    if((tmp = elem -> next) != NULL)
        tmp -> previous = elem -> previous; 

    elem -> next = NULL;
    elem -> previous = NULL;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void push(byte_node* elem,byte_node* head){
    head -> previous = elem;
    elem -> next = head;
    elem -> previous = NULL;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------