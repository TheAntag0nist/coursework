typedef struct byte_node{
    struct byte_node *previous;
    char value;
    struct byte_node *next;
} byte_node;
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void cut_elem(byte_node* elem);
void push(byte_node* elem,byte_node* head, char begin_end);
byte_node* create_node();