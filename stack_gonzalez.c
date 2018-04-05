#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct{
    char** data; // Array of strings representing the stack 
    int top;   // Index of the top of the stack.  top is -1 if the stack is empty.
    int size; // Number of elements that the stack can currently hold 
} Stack;
 
typedef enum { FALSE, TRUE } bool;
 
Stack create();
void deleteStack( Stack* ps );
void push( Stack* ps, char* str );
char* pop( Stack* ps );
bool empty( Stack s );
bool full( Stack s );
char nextString[30];
 
int main(int argc, char *argv[])
{
    FILE *in_file = fopen("data_a2.txt", "r");
    Stack s;
    s = create();
    printf("CS 2123 Assignment 2 written by Grecia Gonzalez.\n");
    if (in_file == NULL)
    {
        printf("File %s not found.\n", "data_a2.txt");
        return -1;
    }
   
    while(!feof(in_file))
    {
       fscanf(in_file, "%s\n", nextString);
       if (strcmp(nextString, "pop") == 0)
         if (empty(s))
            printf("Cannot pop an empty stack...\n");
         else
         {
           printf("# of elements after popping: %d, string popped: %s\n", s.top , pop(&s));
           free(s.data[s.top+1]);
         }
       else
         push(&s, nextString);
     }
   
    deleteStack(&s);
    fclose(in_file);
    return 0;
}
 
 // create returns a new empty stack
Stack create(){
    Stack s;
    s.data = (char**)malloc(10 * sizeof(char*));
    s.top= -1;
    s.size= 10;
    return s;
}

/* deleteStack: deletes the memory associated with the given stack. */ 
void deleteStack( Stack* ps )
{
    while( ps->top>=0 )
    {
        free( ps->data[ps->top] );
        ps->top--;
    }
    free( ps->data );
}
 //takes a string parameter which is the value it pushes onto the stack.
//It may also need to call realloc to expand the size of the stack before completing the push.
void push( Stack* s, char* str )
{
    ++s->top;
    if (full(*s) == TRUE)
    {
        s->size = (s->size) + 10;
        s->data = realloc(s->data, (s->size) * sizeof(char*));
        printf("Stack capacity has grown from %d elements to %d elements.\n", s->size-10, s->size);
    }
    s->data[(s->top)] = malloc(strlen(str)+1 * sizeof(char));
    strcpy(s->data[s->top], str);
}
 //returns the string that was removed from stack
char* pop( Stack* s )
{
    if(!empty(*s))
    {
        s->top--;
        return s->data[(s->top)+1];
    }
    return NULL;
}
 
 //returns true if the stacj has no elements,otherwise false
bool empty( Stack s )
{
    if (s.top == -1)
        return TRUE;
    return FALSE;
}
 
//full returns TRUE if the stack does not have any room left, otherwise false 
bool full( Stack s )
{
    if(s.top == s.size-1)
        return TRUE;
    return FALSE;
}
 

