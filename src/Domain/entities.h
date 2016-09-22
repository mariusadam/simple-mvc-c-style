/*
* entities.h
*
*  Created on: 2 mar. 2016
*      Author: marius
*/

#ifndef DOMAIN_ENTITIES_H_
#define DOMAIN_ENTITIES_H_

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*Interface of entity Cheltuiala*/
typedef struct {
	int numar_apartament;
	double suma;
	char *tip;
}Cheltuiala;


/*
* @input  : numar_apartament - positive integer
*			suma			 - positive floating point number
*			tip				 - string (apa/ gaz/ canal/ incalzire)
* @output : returns a pointer to a newly created Cheltuiala object, on the heap
*/
Cheltuiala* cheltuiala_init(int numarApartament, double suma, char *tip);

/*
* @input  : this - pointer to object of type Cheltuiala
* @output : returns a newly created object of type Cheltuiala,
*			with the same attributes as this
*/
Cheltuiala* cheltuiala_copy(Cheltuiala* this);

/*
* @input  : this - pointer to object of type Cheltuiala
* @output : free the memory on the heap occupied by an Cheltuiala object
*/
void cheltuiala_destroy(Cheltuiala* this);

/*
* @input  : this   - pointer to object of type Cheltuiala
*			 new_tip- string, representing the new type for this
* @output : modifies the current type of this to new_tip
*/
void cheltuiala_set_tip(Cheltuiala *this, char *newTip);

/*
* @input  : this - pointer to object of type Cheltuiala
*			 suma - double, representing the new sum of this
* @output : modifies the current sum of this to the value of suma
*/
void cheltuiala_set_suma(Cheltuiala *this, double suma);

/*
* @input  : chelt1 - pointer to object of type Cheltuiala
*			 chelt2 - pointer to object of type Cheltuiala
* @output : returns 1, if the two objects have the same atributes,
*			 returns 0, otherwise
*/
int cheltuiala_equal(void* first, void* second);

/*
* @input  : first  - pointer to object of type Cheltuiala
*			second - pointer to object of type Cheltuiala
* @output : compares alfabetically the tip of two objects of type Cheltuiala
*/
int cheltuiala_compare_tip(void* first, void* second);

/*
* @input  : first  - pointer to object of type Cheltuiala
*			second - pointer to object of type Cheltuiala
* @output : compares the sum of two objects of type Cheltuiala
*/
int cheltuiala_compare_sum(void* first, void* second);

/*
* @input  : this - pointer to object of type Cheltuiala
* @output : returns the number of the apartment of this
*/
int cheltuiala_get_numar_apartament(Cheltuiala* this);

/*
* @input  : this - pointer to object of type Cheltuiala
* @output : returns the sum of this
*/
double cheltuiala_get_sum(Cheltuiala* this);

/*
* @input  : this - pointer to object of type Cheltuiala
* @output : returns the type of this
*/
char *cheltuiala_get_tip(Cheltuiala* this);

/*
* @input  : nr1, nr2 - 2 floating point number
* @output : returns the absolute difference between the two number
*/
double double_abs(double nr1, double nr2);
#endif /* DOMAIN_ENTITIES_H_ */