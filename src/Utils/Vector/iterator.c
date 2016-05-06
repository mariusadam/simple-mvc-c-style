/*
 * iterator.c
 *
 *  Created on: 5 mar. 2016
 *      Author: marius
 */

#include "vector.h"
#include "iterator.h"

Iterator* iterator_init(Vector* vec) {
	/*
	* @input  : vec - pointer to an dynamic array (see Utils\Vector)
	* @output : returns a pointer to a newly created Iterator object
	*/
	Iterator* it = (Iterator*)malloc(sizeof(Iterator));
	it->container = vec;
	it->curent = vec->array;
	return it;
}

void iterator_destroy(Iterator* this){
	/*
	* @input  : this - pointer to an Iterator object
	* @output : frees the memory occupied by the iterator
	*/
	free(this);
}

void iterator_begin(Iterator* this){
	/*
	* @input  : this - pointer to an Iterator object
	* @output : the iterator points to the first element of the container
	*/
	this->curent = this->container->array;
}

void iterator_end(Iterator* this) {
	/*
	* @input  : this - pointer to an Iterator object
	* @output : the iterator points to the last element of the container
	*/
	if (vector_size(this->container) == 0)
		this->curent = this->container->array;
	else
		this->curent = this->container->array + vector_size(this->container) - 1;
}

void iterator_next(Iterator* this) {
	/*
	* @input  : this - pointer to an Iterator object
	* @output : the iterator points to the next element of the container
	*/
	this->curent++;
}

void iterator_before(Iterator* this) {
	/*
	* @input  : this - pointer to an Iterator object
	* @output : the iterator points to the precedent element of the container
	*/
	this->curent--;
}

int iterator_valid(Iterator* this) {
	/*
	* @input  : this - pointer to an Iterator object
	* @output : returns 1 if the iterator is valid
	*			returns 0, otherwise
	*/
	int size = vector_size(this->container);
	int diff = this->curent - this->container->array;
	return (diff < size && diff >= 0);
}

Element iterator_element(Iterator* this) {
	/*
	* @input  : this - pointer to an Iterator object
	* @output : returns the element pointed by the iterator
	*/
	return *(this->curent);
}
