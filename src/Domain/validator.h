/*
* validator.h
*
*  Created on: 5 mar. 2016
*      Author: marius
*/

#ifndef DOMAIN_VALIDATOR_H_
#define DOMAIN_VALIDATOR_H_

#include <string.h>
#include <malloc.h>

typedef void* Validator;

/*
* @input  : true
* @output : returns a pointer to an Validator object
*/
Validator* validator_init();

/*
* @input  : this - pointer to an Validator object
* @output : frees the memory occupied by an Validator pointer
*/
void validator_destroy(Validator* this);

/*
* @input  : this - pointer to an Validator object
* 			 cmd_string - string
* @output : returns 1 if the cmd_string is a valid valid positive integer
* 					   with max 2 digits
* 			 returns 0, otherwise
*/
int validator_validate_cmd(Validator* this, char* cmd_string);

/*
* @input  : this - pointer to an Validator object
* 			 nr_ap_str - pointer to an array of char
* @output : returns 1 if nr_ap_str represents a valid integer of max 5 digits
* 			 returns 0, otherwise
*/
int validator_validate_nr_ap(Validator* this, char* nr_ap_str);

/*
* @input  : this - pointer to an Validator object
* 			 suma_ptr - pointer to an array of char
* @output : returns 1 if suma_ptr represents a valid floating point number,
* 					   with max 5 digits at the integer part,
* 			 returns 0, otherwise
*/
int validator_validate_suma(Validator* this, char* suma_str);

/*
* @input  : this - pointer to an Validator object
* 			 tip - pointer to an array of char
* @output : returns 1 if tip represents a valid type for an pointer to object of type Cheltuiala
* 			 returns 0, otherwise
*/
int validator_validate_tip(Validator* this, char* tip);

/*
* @input  : this - pointer to an Validator object
* 			 suma_ptr - pointer to an array of char
* 			 tip - pointer to an array of char
* 			 nr_ap_str - pointer to an array of char
* @output : returns 1 suma_ptr, nr_ap_str and tip represents valid atributes for and
* 						pointer to object of type Cheltuiala,
* 			 returns 0, otherwise
*/
int validator_validate_cheltuiala(Validator* this, char* nr_ap_str, char* suma_str, char* tip);

/*
* @input  : chr - char (otherwise undefined behaviour will occur)
* @output : returns 1 if chr contains a digit,
* 			 returns 0, otherwise
*/
int validator_is_digit(char chr);

/*
* @input  : str - string
* @output : returns 1 if str represents a valid lowercase word
*			returns 0, otherwise
*/
int validator_is_valid_word(char* str_w);
#endif /* DOMAIN_VALIDATOR_H_ */
