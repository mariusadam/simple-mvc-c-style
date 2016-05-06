#ifndef UTILS_STACK_STACK_H
#define UTILS_STACK_STACK_H

#include "../../leak.h"

typedef void* Element;
typedef void(*destructor)(Element);

typedef struct node{
	Element info;
	struct node* next;
}node;

typedef struct {
	node* top;
	int size;
}Stack;


/*
* @input  : true
* @output : returns a pointer to a new empty stack, allocated on the heap
*/
Stack* stack_init();

/*
* @input  : this - pointer to a Stack object
* @output : frees the memory occupied by this
*/
void stack_destroy(Stack* this);

/*
* @input  : this - pointer to a Stack object
* @output : eliminates the last inserted Element into the Stack this
*/
void stack_pop(Stack* this);

/*
* @input  : this - pointer to a Stack object
*			elem - Element (generic datatype/pointer to void)
* @output : inserts elem in the Stack this(on top)
*/
void stack_push(Stack* this, Element elem);

/*
* @input  : this - pointer to a Stack object
* @output : returns the elment from the top of the Stack this
*			(the last inserted element)
*/
Element stack_top_element(Stack* this);

/*
* @input  : this - pointer to a Stack object
* @output : returns 1, if the Stack this is empty
*			returns 0, if the Stack this is not empty
*/
int stack_empty(const Stack* this);

/*
* @input  : this - pointer to a Stack object
* @output : returns the size of the Stack this
*/
int stack_size(const Stack* this);

#endif // !UTILS_STACK_STACK_H
