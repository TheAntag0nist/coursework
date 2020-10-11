#include <stdlib.h>
//-------------------------------------------------------------------------
//______________________________LIST_ZONE__________________________________
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
void push(byte_node* elem,byte_node* head, char begin_end){
    byte_node* current = head;

    if(head == NULL){
        elem = elem;
        return;
    }

    if(begin_end == 'b'){
        head -> previous = elem;
        elem -> next = head;
        elem -> previous = NULL;
    }
    else if(begin_end == 'e'){
        while(current -> next != NULL)
            current = current -> next;
        current -> next = elem;
        elem -> previous = current;
        elem -> next = NULL;
    }
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
byte_node* create_node(){
    byte_node* tmp =(byte_node*) malloc(sizeof(byte_node));
    if(tmp == NULL)
        exit(0);

    return tmp;
}
//-------------------------------------------------------------------------
//_____________________________TREE_ZONE___________________________________
//-------------------------------------------------------------------------