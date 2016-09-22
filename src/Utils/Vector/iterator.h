/*
 * iterator.h
 *
 *  Created on: 4 mar. 2016
 *      Author: marius
 */

#ifndef UTILS_VECTOR_ITERATOR_H_
#define UTILS_VECTOR_ITERATOR_H_

#include "vector.h"

typedef struct{
	//pointer catre container
	Vector* container;
	//pointer spre elementul curent din vector
	Element* curent;
}Iterator;

/*Public*/
/*++++++++++++++++++++++++++++++++++++++++*/
Iterator* iterator_init(Vector* vec);		//constructor, retuneaza un iterator pentru vector, plasat la primul element al vectorului
void iterator_destroy(Iterator* this);		//destructor
void iterator_begin(Iterator* this);		//seteaza iteratorul pe prima pozitie din vector
void iterator_end(Iterator* this);			//seteaza iteratorul pe ultima pozitie din vector
void iterator_next(Iterator* this);			//seteaza iteratorul la urmatorul element din vector
void iterator_before(Iterator* this);		//seteaza iteratorul la elemtul precedent din vector;
int iterator_valid(Iterator* this);			//verifica validitatea iteratorului
Element iterator_element(Iterator* this);	//returneaza elementul curent din vector
/*++++++++++++++++++++++++++++++++++++++++*/


#endif /* UTILS_VECTOR_ITERATOR_H_ */
