#ifndef UTILS_OPERATION_OPERATION_H
#define UTILS_OPERATION_OPERATION_H

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*Interface of entity Operation*/
/*
Stores the detalis of last performed operation
op_type can be add, update or del
For each type of operation memorize the initial position
in the vector and a pointer to the added, updated or deleted object
from initial vector
*/
typedef enum operation { add, update, del } op_type;

typedef void* Item;

typedef struct {
	op_type type;
	int pos;
	Item item_ptr;
}Operation;


/*
* @input  : type    - enumaration data type (can be add, update or del)
*			 item_ptr- object of type Item (a generic datatype/pointer to void)
*			 int	 - the index of item_ptr in the initial list
* @output : returns a newly created object of type Operation, allocated on the heap
*/
Operation* operation_init(op_type type, Item item_ptr, int pos);

/*
* @input  : this - object of type Operation
* @output : frees the memory occupied by this
*/
void operation_destroy(Operation* this);

/*
* @input  : this - object of type Operation
* @output : returns the type of this
*/
op_type operation_get_type(Operation* this);

/*
* @input  : this - object of type Operation
* @output : returns the position of the item_ptr from this
*/
int operation_get_pos(Operation* this);

/*
* @input  : this - object of type Operation
* @output : returns the the pointer of the object memorized in this
*/
Item operation_get_item(Operation* this);

#endif /* UTILS_OPERATION_OPERATION_H */