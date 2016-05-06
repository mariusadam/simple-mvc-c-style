#include "operation.h"
#include "malloc.h"

Operation* operation_init(op_type type, Item item_ptr, int pos) {
	/*
	 * @input  : type    - enumaration data type (can be add, update or del)
	 *			 item_ptr- object of type Item (a generic datatype/pointer to void)
	 *			 int	 - the index of item_ptr in the initial list
	 * @output : returns a newly created object of type Operation, allocated on the heap
	 */
	Operation* op = (Operation*)malloc(sizeof(Operation));
	op->type = type;
	op->pos = pos;
	op->item_ptr = item_ptr;
	return op;
}

void operation_destroy(Operation* this) {
	/*
	 * @input  : this - object of type Operation
	 * @output : frees the memory occupied by this
	 */
	free(this);
}

op_type operation_get_type(Operation* this) {
	/*
	 * @input  : this - object of type Operation
	 * @output : returns the type of this
     */
	return this->type;
}

int operation_get_pos(Operation* this) {
	/*
	 * @input  : this - object of type Operation
	 * @output : returns the position of the item_ptr from this
	 */
	return this->pos;
}

Item operation_get_item(Operation* this) {
	/*
	 * @input  : this - object of type Operation
     * @output : returns the the pointer of the object memorized in this
	 */
	return this->item_ptr;
}