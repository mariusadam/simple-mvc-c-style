/*
* controller.h
*
*  Created on: 2 mar. 2016
*      Author: marius
*/

#ifndef CONTROLLER_CONTROLLER_H_
#define CONTROLLER_CONTROLLER_H_

#include "../Repository/repository.h"
#include "../Utils/Vector/vector.h"
#include "../Utils/Vector/iterator.h"
#include "../Utils/Stack/stack.h"
#include "../Utils/Operation/operation.h"
#include "../Domain/validator.h"

typedef struct {
	Repository* repo;
	Validator* valid;
	Stack* st;
}Controller;

/*Public*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* @input  : repo - pointer to object of type Repository
*			valid- pointer to object of type Validator
* @output : returns a pointer to a newly created Controller object
*/
Controller* controller_init(Repository* repo, Validator* valid);

/*
* @input  : this - pointer to object of type Controller
* @output : frees the memory occupied by the Controller
*/
void controller_destroy(Controller* this);

/*
* @input  : this  - pointer to object of type Controller
*			ch_ptr- pointer to object of type Cheltuiala
* @output : adds an a new object to Repository
*/
void controller_add_item(Controller* this, Cheltuiala* ch_ptr);

/*
* @input  : this  - pointer to object of type Controller
*			ch_ptr- pointer to object of type Cheltuiala
* @output : if exists, deletes an object from repository
*/
void controller_delete_item(Controller* this, Cheltuiala* ch_ptr);

/*
* @input  : this        - pointer to object of type Controller
*			old_item_ptr- pointer to object of type Cheltuiala
*			new_tip		- string
* @output : if exists, modifies the tip attribute of object old_item_ptr
*/
void controller_modify_item_tip(Controller* this, Cheltuiala* old_item_ptr, char* new_tip);

/*
* @input  : this        - pointer to object of type Controller
*			old_item_ptr- pointer to object of type Cheltuiala
*			new_sum		- double positive and no more the 5 digits at integer part
* @output : if exists, modifies the suma attribute of object old_item_ptr
*/
void controller_modify_item_sum(Controller* this, Cheltuiala* old_item_ptr, double new_sum);

/*
* @input  : this  - pointer to object of type Controller
* @output : returns a pointer to a dynamic array (see Utils/Vector),
*	        containing all objects from repository
*/
Vector* controller_get_all(Controller* this);

/*
* @input  : this  - pointer to object of type Controller
*			nr_ap - int
* @output : returns a pointer to a dynamic array (see Utils/Vector),
*				containing all objects that have the nr_ap
*			returns an empty vector if no objects have been found
*/
Vector* controller_get_filtered_by_nr_ap(Controller* this, int nr_ap);

/*
* @input  : this  - pointer to object of type Controller
*			nr_ap - int
* @output : returns a pointer to a dynamic array (see Utils/Vector),
*				containing all objects that have the suma
*			returns an empty vector if no objects have been found
*/
Vector* controller_get_filtered_by_sum(Controller* this, double suma);

/*
* @input  : this  - pointer to object of type Controller
*					tip - string
* @output : returns a pointer to a dynamic array (see Utils/Vector),
*				containing all objects that have the tip
*			returns an empty vector if no objects have been found
*/
Vector* controller_get_filtered_by_tip(Controller* this, char* tip);

/*
* @input  : this    - pointer to object of type Controller
*			reversed- int from {0, 1}
* @output : if reversed = 1 , returns a new vector of pointer Cheltuiala sorted ascending by sum
*			if reversed = 0 , returns a new vector of pointer Cheltuiala  sorted descending by sum
*/
Vector* controller_get_sorted_by_sum(Controller* this, int reversed);

/*
* @input  : this    - pointer to object of type Controller
*			reversed- int from {0, 1}
* @output : if reversed = 1 , returns a new vector of pointer Cheltuiala sorted alfabetically ascending by tip
*			if reversed = 0 , returns a new vector of pointer Cheltuiala sorted alfabetically descending by tip
*/
Vector* controller_get_sorted_by_tip(Controller* this, int reversed);

/*
* @input  : this - pointer to object of type Cotnroller
*			op	 - pointer to object of type Operation
* @output : returns 1, if the last add operation had been restored
*			returns 0, if there are no more operations to be restored,
*					   or the last operation could not be restored,
*					   or the last operation was not add
*/
int controller_restore_add(Controller* this, Operation* op);

/*
* @input  : this - pointer to object of type Cotnroller
*			op	 - pointer to object of type Operation
* @output : returns 1, if the last update operation had been restored
*			returns 0, if there are no more operations to be restored,
*					   or the last operation could not be restored,
*					   or the last operation was not update
*/
int controller_restore_update(Controller* this, Operation* op);

/*
* @input  : this - pointer to object of type Cotnroller
*			op	 - pointer to object of type Operation
* @output : returns 1, if the last delete operation had been restored
*			returns 0, if there are no more operations to be restored,
*						or the last operation could not be restored,
*						or the last operation was not delete
*/
int controller_restore_delete(Controller* this, Operation* op);

/*
* @input  : this - pointer to object of type Cotnroller
* @output : returns 1, if the last operation had been restored
*			returns 0, if there are no more operations to be restored,
*						or the last operation could not be restored
*/
int controller_restore_cheltuiala(Controller* this);

/*
* @input  : this - pointer to object of type Controller
*			ch   - pointer to object of type Cheltuiala
* @output : returns 1, if ch object exists in the Repository
*			returns 0, otherwise
*/
int controller_find_item(Controller* this, Cheltuiala* ch);

/*
* @input  : this    - pointer to object of type Controller
*			cmd_str - string
* @output : returns 1, if cmd_str represents a valid menu comand
*			returns 0, otherwise
*/
int controller_validate_cmd(Controller* this, char* cmd_str);

/*
* @input  : this	  - pointer to object of type Controller
*			nr_ap_str - string
*			suma_str  - string
*			tip		  - string
* @output : returns 1, if strings passed as args represents some valid
*					   attributes of an pointer to object of type Cheltuiala
*			returns 0, otherwise
*/
int controller_validate_cheltuiala(Controller* this, char* nr_ap_str, char* suma_str, char* tip);

/*
* @input  : this	  - pointer to object of type Controller
*			nr_ap_str - string
* @output : returns 1, if string passed as arg represents a valid
*					   attribute for number of apartament of an object of type Cheltuiala
*			returns 0, otherwise
*/
int controller_validate_nr_ap(Controller* this, char* nr_ap_str);

/*
* @input  : this     - pointer to object of type Controller
*			suma_str - string
* @output : returns 1, if suma_str represents a valid sum of an
*					   pointer to object of type Cheltuiala
*			returns 0, otherwise
*/
int controller_validate_suma(Controller* this, char* suma_str);

/*
* @input  : this- pointer to object of type Controller
*			tip - string
* @output : returns 1, if tip represents a valid tip of an
*					   pointer to object of type Cheltuiala
*			returns 0, otherwise
*/
int controller_validate_tip(Controller* this, char* tip);

/*
* @input  : this      - pointer to object of type Controller
*			nr_ap_str - string containng an valid integer
* @output : returns the convertion to int of suma_str
*/
int controller_str_to_int(Controller* this, char* nr_ap_str);

/*
* @input  : this     - pointer to object of type Controller
*			suma_str - string containing a valid double number
* @output : returns the convertion to double of suma_str
*/
double controller_str_to_double(Controller* this, char* suma_str);
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#endif /* CONTROLLER_CONTROLLER_H_ */
