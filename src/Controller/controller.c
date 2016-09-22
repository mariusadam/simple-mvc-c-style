/*
* controller.c
*
*  Created on: 3 mar. 2016
*      Author: marius
*/
#include "controller.h"
#include <string.h>

Controller* controller_init(Repository* repo, Validator* valid) {
	/*
	* @input  : repo - pointer to object of type Repository
	*			valid- pointer to object of type Validator
	* @output : returns a pointer to a newly created Controller object
	*/
	Controller* ctr = (Controller*)malloc(sizeof(Controller));
	ctr->repo = repo;
	ctr->valid = valid;
	ctr->st = stack_init();
	return ctr;
}

int controller_restore_add(Controller* this, Operation* op) {
	/*
	* @input  : this - pointer to object of type Cotnroller
	*			op	 - pointer to object of type Operation
	* @output : returns 1, if the last add operation had been restored
	*			returns 0, if there are no more operations to be restored,
	*					   or the last operation could not be restored,
	*					   or the last operation was not add
	*/
	if (operation_get_type(op) != add)
		return 0;
	Cheltuiala* ch_in_stack = operation_get_item(op);
	repository_delete_item(this->repo, ch_in_stack);
	operation_destroy(op);
	return 1;
}

int controller_restore_update(Controller* this, Operation* op) {
	/*
	* @input  : this - pointer to object of type Cotnroller
	*			op	 - pointer to object of type Operation
	* @output : returns 1, if the last update operation had been restored
	*			returns 0, if there are no more operations to be restored,
	*					   or the last operation could not be restored,
	*					   or the last operation was not update
	*/
	if (operation_get_type(op) != update)
		return 0;
	Vector* alls = controller_get_all(this);
	int pos = operation_get_pos(op);
	Cheltuiala* ch_in_repo = vector_element_at(alls, pos);
	Cheltuiala* ch_in_stack = operation_get_item(op);
	double old_sum = cheltuiala_get_sum(ch_in_stack);
	char* old_tip = cheltuiala_get_tip(ch_in_stack);
	cheltuiala_set_suma(ch_in_repo, old_sum);
	cheltuiala_set_tip(ch_in_repo, old_tip);
	repository_save_to_file(this->repo);
	cheltuiala_destroy(ch_in_stack);
	operation_destroy(op);
	return 1;
}

int controller_restore_delete(Controller* this, Operation* op) {
	/*
	* @input  : this - pointer to object of type Cotnroller
	*			op	 - pointer to object of type Operation
	* @output : returns 1, if the last delete operation had been restored
	*			returns 0, if there are no more operations to be restored,
	*						or the last operation could not be restored, 
	*						or the last operation was not delete
	*/
	if (operation_get_type(op) != del)
		return 0;
	Cheltuiala* ch_in_stack = operation_get_item(op);
	Vector* alls = controller_get_all(this);
	int pos = operation_get_pos(op);
	vector_insert_at(alls, ch_in_stack, pos);
	repository_save_to_file(this->repo);
	operation_destroy(op);
	return 1;
}

int controller_restore_cheltuiala(Controller* this) {
	/*
	* @input  : this - pointer to object of type Cotnroller
	* @output : returns 1, if the last operation had been restored
	*			returns 0, if there are no more operations to be restored, 
	*						or the last operation could not be restored
	*/
	if (stack_empty(this->st))
		return 0;
	Operation* op = stack_top_element(this->st);
	stack_pop(this->st);
	op_type type = operation_get_type(op);
	if (type == add)
		return controller_restore_add(this, op);
	else
		if (type == update)
			return controller_restore_update(this, op);
		else
			if (type == del)
				return controller_restore_delete(this, op);
			else
				return 0;
}

void controller_destroy(Controller* this) {
	/*
	* @input  : this - pointer to object of type Controller
	* @output : frees the memory occupied by the Controller
	*/
	node* tmp = this->st->top;
	for (; tmp != NULL; tmp = tmp->next) {
		Operation* op = tmp->info;
		cheltuiala_destroy(op->item_ptr);
		operation_destroy(op);
	}
	stack_destroy(this->st);
	free(this);
}

void controller_add_item(Controller* this, Cheltuiala* ch_ptr) {
	/*
	* @input  : this  - pointer to object of type Controller
	*			ch_ptr- pointer to object of type Cheltuiala
	* @output : adds an a new object to Repository
	*/
	int pos = repository_get_size(this->repo);
	Cheltuiala* ch_copy = cheltuiala_copy(ch_ptr);
	Operation* op = operation_init(add, ch_copy, pos);
	stack_push(this->st, op);
	repository_add_item(this->repo, ch_ptr);
}

void controller_delete_item(Controller* this, Cheltuiala* ch_ptr) {
	/*
	* @input  : this  - pointer to object of type Controller
	*			ch_ptr- pointer to object of type Cheltuiala
	* @output : if exists, deletes an object from repository
	*/
	Cheltuiala* ch_copy = cheltuiala_copy(ch_ptr);
	Vector* alls = controller_get_all(this);
	int pos = vector_element_index(alls, ch_ptr, &cheltuiala_equal);
	Operation* op = operation_init(del, ch_copy, pos);
	stack_push(this->st, op);
	repository_delete_item(this->repo, ch_ptr);
}

Vector* controller_get_all(Controller* this) {
	/*
	* @input  : this  - pointer to object of type Controller
	* @output : returns a pointer to a dynamic array (see Utils/Vector),
	*	        containing all objects from repository
	*/
	return repository_get_all(this->repo);
}

Vector * controller_get_filtered_by_nr_ap(Controller * this, int nr_ap) {
	/*
	* @input  : this  - pointer to object of type Controller
	*			nr_ap - int
	* @output : returns a pointer to a dynamic array (see Utils/Vector),
	*				containing all objects that have the nr_ap
	*			returns an empty vector if no objects have been found
	*/
	Vector* alls = controller_get_all(this);
	Vector* filtered = vector_init(1);
	Iterator* it = iterator_init(alls);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		if (cheltuiala_get_numar_apartament(ch_ptr) == nr_ap)
			vector_push_back(filtered, ch_ptr);
	}
	iterator_destroy(it);
	return filtered;
}

Vector * controller_get_filtered_by_sum(Controller * this, double suma) {
	/*
	* @input  : this  - pointer to object of type Controller
	*			nr_ap - int
	* @output : returns a pointer to a dynamic array (see Utils/Vector),
	*				containing all objects that have the suma
	*			returns an empty vector if no objects have been found
	*/
	Vector* alls = controller_get_all(this);
	Vector* filtered = vector_init(1);
	Iterator* it = iterator_init(alls);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		if (cheltuiala_get_sum(ch_ptr) <= suma)
			vector_push_back(filtered, ch_ptr);
	}
	iterator_destroy(it);
	return filtered;
}

Vector * controller_get_filtered_by_tip(Controller * this, char * tip) {
	/*
	* @input  : this  - pointer to object of type Controller
	*					tip - string
	* @output : returns a pointer to a dynamic array (see Utils/Vector),
	*				containing all objects that have the tip
	*			returns an empty vector if no objects have been found
	*/
	Vector* alls = controller_get_all(this);
	Vector* filtered = vector_init(1);
	Iterator* it = iterator_init(alls);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		if (strcmp(cheltuiala_get_tip(ch_ptr), tip) == 0)
			vector_push_back(filtered, ch_ptr);
	}
	iterator_destroy(it);
	return filtered;
}

Vector* controller_get_sorted_by_sum(Controller* this, int reversed) {
	/*
	* @input  : this    - pointer to object of type Controller
	*			reversed- int from {0, 1}
	* @output : if reversed = 1 , returns a new vector of pointer Cheltuiala sorted ascending by sum
	*			if reversed = 0 , returns a new vector of pointer Cheltuiala  sorted descending by sum
	*/
	Vector* alls = controller_get_all(this);
	Vector* sorted = vector_init(1);
	Iterator* it = iterator_init(alls);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		vector_push_back(sorted, ch_ptr);
	}
	iterator_destroy(it);
	vector_sort(sorted, &cheltuiala_compare_sum, reversed);
	return sorted;
}

Vector* controller_get_sorted_by_tip(Controller* this, int reversed) {
	/*
	* @input  : this    - pointer to object of type Controller
	*			reversed- int from {0, 1}
	* @output : if reversed = 1 , returns a new vector of pointer Cheltuiala sorted alfabetically ascending by tip
	*			if reversed = 0 , returns a new vector of pointer Cheltuiala sorted alfabetically descending by tip
	*/
	Vector* alls = controller_get_all(this);
	Vector* sorted = vector_init(1);
	Iterator* it = iterator_init(alls);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		vector_push_back(sorted, ch_ptr);
	}
	iterator_destroy(it);
	vector_sort(sorted, &cheltuiala_compare_tip, reversed);
	return sorted;
}

void controller_modify_item_tip(Controller* this, Cheltuiala* old_item_ptr, char* new_tip) {
	/*
	* @input  : this        - pointer to object of type Controller
	*			old_item_ptr- pointer to object of type Cheltuiala
	*			new_tip		- string
	* @output : if exists, modifies the tip attribute of object old_item_ptr
	*/
	Vector* alls = controller_get_all(this);
	int pos = vector_element_index(alls, old_item_ptr, &cheltuiala_equal);
	if (pos != -1) {
		Cheltuiala* ch = vector_element_at(alls, pos);
		Cheltuiala* ch_copy = cheltuiala_copy(ch);
		Operation* op = operation_init(update, ch_copy, pos);
		stack_push(this->st, op);
		cheltuiala_set_tip(ch, new_tip);
		repository_save_to_file(this->repo);
	}
}

void controller_modify_item_sum(Controller* this, Cheltuiala* old_item_ptr, double new_sum) {
	/*
	* @input  : this        - pointer to object of type Controller
	*			old_item_ptr- pointer to object of type Cheltuiala
	*			new_sum		- double positive and no more the 5 digits at integer part
	* @output : if exists, modifies the suma attribute of object old_item_ptr
	*/
	Vector* alls = controller_get_all(this);
	int pos = vector_element_index(alls, old_item_ptr, &cheltuiala_equal);
	if (pos != -1) {
		Cheltuiala* ch = vector_element_at(alls, pos);
		Cheltuiala* ch_copy = cheltuiala_copy(ch);
		Operation* op = operation_init(update, ch_copy, pos);
		stack_push(this->st, op);
		cheltuiala_set_suma(ch, new_sum);
		repository_save_to_file(this->repo);
	}
}

int controller_validate_cmd(Controller* this, char* cmd_str) {
	/*
	* @input  : this    - pointer to object of type Controller
	*			cmd_str - string
	* @output : returns 1, if cmd_str represents a valid menu comand
	*			returns 0, otherwise
	*/
	return validator_validate_cmd(this->valid, cmd_str);
}

int controller_validate_cheltuiala(Controller* this, char* nr_ap_str, char* suma_str, char* tip) {
	/*
	* @input  : this	  - pointer to object of type Controller
	*			nr_ap_str - string
	*			suma_str  - string
	*			tip		  - string
	* @output : returns 1, if strings passed as args represents some valid
	*					   attributes of an pointer to object of type Cheltuiala
	*			returns 0, otherwise
	*/
	return validator_validate_cheltuiala(this->valid, nr_ap_str, suma_str, tip);
}

int controller_validate_nr_ap(Controller * this, char * nr_ap_str) {
	/*
	* @input  : this	  - pointer to object of type Controller
	*			nr_ap_str - string
	* @output : returns 1, if string passed as arg represents a valid
	*					   attribute for number of apartament of an object of type Cheltuiala
	*			returns 0, otherwise
	*/
	return validator_validate_nr_ap(this->valid, nr_ap_str);
}

int controller_str_to_int(Controller* this, char* nr_ap_str) {
	/*
	* @input  : this      - pointer to object of type Controller
	*			nr_ap_str - string containng an valid integer
	* @output : returns the convertion to int of suma_str
	*/
	return atoi(nr_ap_str);
}

double controller_str_to_double(Controller* this, char* suma_str) {
	/*
	* @input  : this     - pointer to object of type Controller
	*			suma_str - string containing a valid double number
	* @output : returns the convertion to double of suma_str
	*/
	return atof(suma_str);
}

int controller_validate_suma(Controller* this, char* suma_str) {
	/*
	* @input  : this     - pointer to object of type Controller
	*			suma_str - string
	* @output : returns 1, if suma_str represents a valid sum of an
	*					   pointer to object of type Cheltuiala
	*			returns 0, otherwise
	*/
	return validator_validate_suma(this->valid, suma_str);
}

int controller_validate_tip(Controller* this, char* tip) {
	/*
	* @input  : this- pointer to object of type Controller
	*			tip - string
	* @output : returns 1, if tip represents a valid tip of an
	*					   pointer to object of type Cheltuiala
	*			returns 0, otherwise
	*/
	return validator_validate_tip(this->valid, tip);
}

int controller_find_item(Controller* this, Cheltuiala* ch) {
	/*
	* @input  : this - pointer to object of type Controller
	*			ch   - pointer to object of type Cheltuiala
	* @output : returns 1, if ch object exists in the Repository
	*			returns 0, otherwise
	*/
	Vector* alls = controller_get_all(this);
	if (vector_element_index(alls, ch, &cheltuiala_equal) == -1)
		return 0;
	else
		return 1;
}
