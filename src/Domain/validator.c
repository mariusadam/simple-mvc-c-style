/*
* validator.c
*
*  Created on: 5 mar. 2016
*      Author: marius
*/
#include "validator.h"

Validator* validator_init() {
	/*
	* @input  : true
	* @output : returns a pointer to an Validator object
	*/
	Validator* valid = (Validator*)malloc(sizeof(Validator));
	return valid;
}

void validator_destroy(Validator* this) {
	/*
	* @input  : this - pointer to an Validator object
	* @output : frees the memory occupied by an Validator pointer
	*/
	free(this);
}

int validator_validate_cmd(Validator* this, char* cmd_string) {
	/*
	* @input  : this - pointer to an Validator object
	* 			 cmd_string - string
	* @output : returns 1 if the cmd_string is a valid valid positive integer
	* 					   with max 2 digits
	* 			 returns 0, otherwise
	*/
	if (cmd_string == NULL || strlen(cmd_string) > 2 || strlen(cmd_string) < 1)
		return 0;
	if (!validator_is_digit(cmd_string[0]) || (strlen(cmd_string) == 2 && !validator_is_digit(cmd_string[1])))
		return 0;
	return 1;
}

int validator_is_digit(char chr) {
	/*
	* @input  : chr - char (otherwise undefined behaviour will occur)
	* @output : returns 1 if chr contains a digit,
	* 			 returns 0, otherwise
	*/
	int diff = chr - '0';
	return (diff >= 0 && diff <= 9);
}

int validator_validate_nr_ap(Validator* this, char* nr_ap_str) {
	/*
	* @input  : this - pointer to an Validator object
	* 			 nr_ap_str - pointer to an array of char
	* @output : returns 1 if nr_ap_str represents a valid integer of max 5 digits
	* 			 returns 0, otherwise
	*/
	if (nr_ap_str == NULL)
		return 0;
	int len = strlen(nr_ap_str), i;
	for (i = 0; i < len; i++)
		if (!validator_is_digit(nr_ap_str[i]))
			return 0;
	if (len > 5 || len < 1)
		return 0;
	return 1;
}
int validator_validate_suma(Validator* this, char* suma_str) {
	/*
	* @input  : this - pointer to an Validator object
	* 			 suma_ptr - pointer to an array of char
	* @output : returns 1 if suma_ptr represents a valid floating point number,
	* 					   with max 5 digits at the integer part,
	* 			 returns 0, otherwise
	*/
	if (suma_str == NULL)
		return 0;
	int len = strlen(suma_str), i, nr_decimal_points, pos_decimal = -1;
	nr_decimal_points = 0;
	for (i = 0; i < len; i++)
		if (suma_str[i] == '.') {
			nr_decimal_points++;
			pos_decimal = i;
		}
		else
			if (!validator_is_digit(suma_str[i]))
				return 0;
	if (nr_decimal_points > 1 || pos_decimal > 6 || len < 1)
		return 0;
	if (nr_decimal_points == 0 && len > 5)
		return 0;
	return 1;
}

int validator_is_valid_word(char* str_w) {
	/*
	* @input  : str - string
	* @output : returns 1 if str represents a valid lowercase word
	*			returns 0, otherwise
	*/
	int i, len = strlen(str_w);
	for (i = 0; i < len; i++) {
		char ch = str_w[i];
		if (ch == ' ' || ch < 'a' || ch > 'z')
			return 0;
	}
	return 1;
}

int validator_validate_tip(Validator* this, char* tip) {
	/*
	 * @input  : this - pointer to an Validator object
	 * 			 tip - pointer to an array of char
	 * @output : returns 1 if tip represents a valid type for an pointer to object of type Cheltuiala
	 * 			 returns 0, otherwise
	 */
	if (tip == NULL || !validator_is_valid_word(tip))
		return 0;
	int ok1 = strcmp(tip, "apa");
	int ok2 = strcmp(tip, "canal");
	int ok3 = strcmp(tip, "incalzire");
	int ok4 = strcmp(tip, "gaz");
	return (!ok1 || !ok2 || !ok3 || !ok4);
}

int validator_validate_cheltuiala(Validator* this, char* nr_ap_str, char* suma_str, char* tip) {
	/*
	* @input  : this - pointer to an Validator object
	* 			 suma_ptr - pointer to an array of char
	* 			 tip - pointer to an array of char
	* 			 nr_ap_str - pointer to an array of char
	* @output : returns 1 suma_ptr, nr_ap_str and tip represents valid atributes for and
	* 						pointer to object of type Cheltuiala,
	* 			 returns 0, otherwise
	*/
	int ok1 = validator_validate_nr_ap(this, nr_ap_str);
	int ok2 = validator_validate_suma(this, suma_str);
	int ok3 = validator_validate_tip(this, tip);
	return (ok1 && ok2 && ok3);
}
