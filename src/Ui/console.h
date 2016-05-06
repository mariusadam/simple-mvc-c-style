/*
 * console.h
 *
 *  Created on: 5 mar. 2016
 *      Author: marius
 */

#ifndef UI_CONSOLE_H_
#define UI_CONSOLE_H_

#include "../leak.h"
#include "../Controller/controller.h"
#include "../Utils/Vector/iterator.h"
#include <stdio.h>
#include <string.h>

typedef struct{
	Controller* ctr;
}Console;

/*Public*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* @input  : ctr - pointer to object of type Controller
* @output : returns a pointer to a newly created Console object
*/
Console* console_init(Controller* ctr);

/*
* @input  : this - pointer to object of type Console
* @output : frees the memory occupied by the Console object this
*/
void console_destroy(Console* this);

/*
* @input  : this - pointer to object of type Console
* @output : realizes the user's interface in the main menu
*/
void console_run(Console* this);
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*Private*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* @input  : this - pointer to object of type Console
* @output : reads the attributes of an object of type Cheltuiala
*			returns NULL if the introduced dates are invalid
*			returns the pointer to newly created object, otherwise
*/
Cheltuiala* console_read_cheltuiala(Console* this);

/*
* @input  : true
* @output : returns a pointer string read from stdin
*/
char* console_read_main_menu_cmd();

/*
* @input  : this - pointer to object of type Console
* @output : reads a command from stdin an retuns a pointer to a string
*/
char* console_read_modify_menu_cmd(Cheltuiala* ch_ptr);

/*
* @input  : true
* @output : returns a pointer string read from stdin
*/
char* console_read_filter_menu_cmd();

/*
* @input  : true
* @output : returns a pointer string read from stdin
*/
char* console_read_ordered_menu_cmd();

/*
* @input  : true
* @output : returns a pointer string read from stdin
*/
char* console_read_sort_menu_cmd();

/*
* @input  : true
* @output : returns a pointer string read from stdin
*/
char* console_read_tip();

/*
* @input  : true
* @output : returns a pointer string read from stdin
*/
char* console_read_suma();

/*
* @input  : true
* @output : returns a pointer string read from stdin, allocated on the heap
*/
char* console_read_nr_ap();

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface when ordering by sum
*/
void console_order_by_sum(Console* this, int spaces);

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface when ordering by tip
*/
void console_order_by_tip(Console* this, int spaces);

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface on the order menu
*/
void console_order_menu(Console* this, int spaces);

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface in the filter menu
*/
void console_filter_menu(Console* this, int spaces);

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface when filtering by tip
*/
void console_filter_by_tip(Console* this, int spaces);

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface when filtering by sum
*/
void console_filter_by_sum(Console* this, int spaces);

/*
* @input  : this  - Console object
*			spaces- int
* @output : realises user interface when filtering by number of apartment
*/
void console_filter_by_nr_ap(Console* this, int spaces);

/*
* @input  : this - pointer to object of type Console
*			ch	 - pointer to object of type Cheltuiala
* @output : realizes the user's interface in the modify option
*/
void console_modify_menu(Console* this, Cheltuiala* ch);

/*
* @input  : this - pointer to object of type Console
*			ch	 - pointer to object of type Cheltuiala
* @output : realizes the user's interface in the modify sum option
*/
void console_modify_cheltuiala(Console* this);

/*
* @input  : this - pointer to object of type Console
*			ch	 - pointer to object of type Cheltuiala
* @output : realizes the user's interface in the modify tip option
*/
void console_modify_tip(Console* this, Cheltuiala* ch, int* nr_op);

/*
* @input  : this - pointer to object of type Console
*			ch	 - pointer to object of type Cheltuiala
* @output : realizes the user's interface in the modify sum option
*/
void console_modify_suma(Console* this, Cheltuiala* ch, int* nr_op);

/*
* @input  : this - pointer to object of type Console
* @output : reads the attributes of an pointer to object of type Cheltuiala,
*			and adds it to repository, signalling eventual errors
*/
void console_add_cheltuiala(Console* this);

/*
* @input  : this - pointer to object of type Console
* @output : realizes the user's interface in the del option
*/
void console_delete_cheltuiala(Console* this);

/*
* @input  : this - pointer to object of type Console
* @output : all the objects from repository on stdout
*/
void console_print_all(Console* this, int spaces);

/*
* @input  : this  - pointer to object of type Console
*			items - pointer to a dynamic array
*			spaces- integer representing the indent of the output
* @output : prints the items on the screen using an
*			iterator (see Utils/Vector)
*/
void console_print_cheltuieli(Console* this, Vector* items, int spaces);

/*
*	@input  : number_of_spaces - integer
*	@output : printf on the screen "space" character, number_spaces times
*/
void console_print_spaces(int spaces);
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif /* UI_CONSOLE_H_ */
