#include "stack.h"

Stack* stack_init() {
	/*
	 * @input  : true
	 * @output : returns a pointer to a new empty stack, allocated on the heap
	 */
	Stack* st = (Stack*)malloc(sizeof(Stack));
	st->size = 0;
	st->top = NULL;
	return st;
}

void stack_destroy(Stack* this) {
	/*
	* @input  : this - pointer to a Stack object
	* @output : frees the memory occupied by this
	*/
	while (this->top != NULL)
		stack_pop(this);
	free(this);
}

void stack_pop(Stack* this) {
	/*
	* @input  : this - pointer to a Stack object
	* @output : eliminates the last inserted Element into the Stack this
	*/
	if (this->top != NULL) {
		node* tmp = this->top;
		this->top = this->top->next;
		free(tmp);
		this->size--;
	}
	else
		this->size = 0;
}
Element stack_top_element(Stack* this) {
	/*
	* @input  : this - pointer to a Stack object
	* @output : returns the elment from the top of the Stack this
	*			(the last inserted element)
	*/
	return this->top->info;
}

void stack_push(Stack* this, Element elem) {
	/*
	* @input  : this - pointer to a Stack object
	*			elem - Element (generic datatype/pointer to void)
	* @output : inserts elem in the Stack this(on top)
	*/
	if (this->top == NULL) {
		this->top = (node*)malloc(sizeof(node));
		this->top->info = elem;
		this->top->next = NULL;
		this->size = 1;
	}
	else {
		node* new_node = (node*)malloc(sizeof(node));
		new_node->next = this->top;
		new_node->info = elem;
		this->top = new_node;
		this->size++;
	}
}

int stack_size(const Stack* this) {
	/*
	* @input  : this - pointer to a Stack object
	* @output : returns the size of the Stack this
	*/
	return this->size;
}

int stack_empty(const Stack* this) {
	/*
	* @input  : this - pointer to a Stack object
	* @output : returns 1, if the Stack this is empty
	*			returns 0, if the Stack this is not empty
	*/
	if (this->size == 0)
		return 1;
	return 0;
}