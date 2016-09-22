/*
 * vector.h
 *
 *  Created on: 2 mar. 2016
 *      Author: marius
 */

#ifndef UTILS_VECTOR_VECTOR_H_
#define UTILS_VECTOR_VECTOR_H_

#include <stdlib.h>

typedef void* Element;
typedef void* (*DestructorFn)(void* elementPtr);
typedef void  (*Function)();

typedef struct Vector{
	Element* array;
	int size, max_size;
}Vector;

/*Public*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
Vector* vector_init(int maxSize); 							//creeaza un vector si returneaza un pointer care vectorul nou creat
void vector_destroy(Vector* this);					 		//elibereaza memoria ocupata de vector
void vector_push_back(Vector* this, Element elem); 		//adauga un nou element la sfarsiutul vectorului
void vector_remove_at(Vector* this, int pos);	 	 		//elimina elementul de pe pozitia poz
int vector_size(Vector* this);					     		//returneaza dimensiunea vectorului
int vector_max_size(Vector* this);
Element vector_element_at(Vector* this, int pos);	 		//returneaza elementul de pe pozitia pos
int vector_element_index(Vector* this, Element elem, int (*equality_func)(Element , Element)); //returneaza pozitia elementului in vector, folosind equality_func ca si functie de comparare
void vector_insert_at(Vector* this, Element elem, int pos);
void vector_sort(Vector* this, int (*cmp)(Element , Element), int revesed);	//sorteaza vectorul folosind functia de comparare cmp, crescator sau descrescator
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*Private*/
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void vector_resize(Vector* this);	//dubleaza capacitatea de memorare a vectorului
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif /* UTILS_VECTOR_VECTOR_H_ */
