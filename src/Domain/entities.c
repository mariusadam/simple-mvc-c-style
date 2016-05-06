/*
* entities.c
*
*  Created on: 2 mar. 2016
*      Author: marius
*/

#include "entities.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>

Cheltuiala* cheltuiala_init(int numar_apartament, double suma, char* tip) {
	/*
	 * @input  : numar_apartament - positive integer	
	 *			 suma			  - positive floating point number
	 *			 tip			  - string (apa/ gaz/ canal/ incalzire)
	 * @output : returns a pointer to a newly created Cheltuiala object, on the heap
	 */
	Cheltuiala* this = (Cheltuiala*)malloc(sizeof(Cheltuiala));
	this->numar_apartament = numar_apartament;
	this->suma = suma;
	this->tip = (char*)malloc(sizeof(char) * strlen(tip) + 1);
	strcpy(this->tip, tip);
	return this;
}

void cheltuiala_destroy(Cheltuiala* this) {
	/*
	 * @input  : this - pointer to object of type Cheltuiala
	 * @output : free the memory on the heap occupied by an Cheltuiala object
	 */
	free(this->tip);
	free(this);
}

int cheltuiala_get_numar_apartament(Cheltuiala *this) {
	/*
	 * @input  : this - pointer to object of type Cheltuiala
	 * @output : returns the number of the apartment of this
	 */
	return this->numar_apartament;
}

double cheltuiala_get_sum(Cheltuiala *this) {
	/*
	 * @input  : this - pointer to object of type Cheltuiala
	 * @output : returns the sum of this
	 */
	return this->suma;
}

char *cheltuiala_get_tip(Cheltuiala *this) {
	/*
	 * @input  : this - pointer to object of type Cheltuiala
	 * @output : returns the type of this
	 */
	return this->tip;
}

void cheltuiala_set_tip(Cheltuiala *this, char *new_tip) {
	/*
	 * @input  : this   - pointer to object of type Cheltuiala
	 *			 new_tip- string, representing the new type for this
	 * @output : modifies the current type of this to new_tip
	 */
	if (strlen(this->tip) < strlen(new_tip)) {
		char* new_ptr = (char*)malloc(sizeof(char) * strlen(new_tip) + 1);
		free(this->tip);
		this->tip = new_ptr;
	}
	strcpy(this->tip, new_tip);
}

void cheltuiala_set_suma(Cheltuiala* this, double suma) {
	/*
	 * @input  : this - pointer to object of type Cheltuiala
	 *			 suma - double, representing the new sum of this
	 * @output : modifies the current sum of this to the value of suma
	 */
	this->suma = suma;
}

double double_abs(double nr1, double nr2) {
	/*
	* @input  : nr1, nr2 - 2 floating point number
	* @output : returns the absolute difference between the two number
	*/
	if (nr1 > nr2)
		return nr1 - nr2;
	return nr2 - nr1;
}

int cheltuiala_equal(void* chelt1, void* chelt2) {
	/*
	 * @input  : chelt1 - pointer to object of type Cheltuiala
	 *			 chelt2 - pointer to object of type Cheltuiala
	 * @output : returns 1, if the two objects have the same atributes,
	 *			 returns 0, otherwise
	 */
	Cheltuiala* first = chelt1;
	Cheltuiala* second = chelt2;
	int equal;
	if (strcmp(first->tip, second->tip) == 0)
		equal = 1;
	else
		equal = 0;
	if (first->numar_apartament == second->numar_apartament && double_abs(first->suma, second->suma) <= 0.001 && equal == 1)
		return 1;
	return 0;
}

Cheltuiala* cheltuiala_copy(Cheltuiala* this) {
	/*
	* @input  : this - pointer to object of type Cheltuiala
	* @output : returns a newly created object of type Cheltuiala, 
	*			with the same attributes as this
	*/
	int nr_ap = cheltuiala_get_numar_apartament(this);
	double suma = cheltuiala_get_sum(this);
	char* tip = NULL;
	tip = cheltuiala_get_tip(this);
	if (tip != NULL)
		return cheltuiala_init(nr_ap, suma, tip);
	fprintf(stderr, "Eroare in entities, in cheltuiala_copy!");
	return NULL;
}

int cheltuiala_compare_tip(void* first, void* second) {
	/*
	* @input  : first  - pointer to object of type Cheltuiala
	*			second - pointer to object of type Cheltuiala
	* @output : compares alfabetically the tip of two objects of type Cheltuiala
	*/
	int min_len, i;
	Cheltuiala* first_ch = first;
	Cheltuiala* second_ch = second;
	char* str1 = cheltuiala_get_tip(first_ch);
	char* str2 = cheltuiala_get_tip(second_ch);
	if (strlen(str1) < strlen(str2))
		min_len = strlen(str1);
	else
		min_len = strlen(str2);
	for (i = 0; i < min_len; i++)
		if (str1[i] <= str2[i])
			return 1;
		else
			return 0;
	return strlen(str1) <= strlen(str2);
}

int cheltuiala_compare_sum(void* first, void* second) {
	/*
	* @input  : first  - pointer to object of type Cheltuiala
	*			second - pointer to object of type Cheltuiala
	* @output : compares the sum of two objects of type Cheltuiala
	*/
	Cheltuiala* f = first;
	Cheltuiala* s = second;
	return cheltuiala_get_sum(f) <= cheltuiala_get_sum(s);
}