/*
 * vector.c
 *
 *  Created on: 2 mar. 2016
 *      Author: marius
 */
#include <malloc.h>
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

Vector* vector_init(int max_size){
	/*
	 * @input  : max_size - integer representing number of elements that will be allocated space
	 * @output : returns a pointer to a newly created Vector object
	 *			 Since we use only shallow copies of elements in our vector, 
	 *			 it's enough to keep only the pointer size
	 *			 (any pointer has the same sizeof()) -> use sizeof(void*)
	 */
	if (max_size <= 0)
		max_size = 1;
	Vector* vec = (Vector*)malloc(sizeof(Vector));
	vec->size = 0;
	vec->max_size = max_size;
	vec->array = (Element*)malloc(sizeof(Element) * max_size);
	return vec;
}


void vector_destroy(Vector* this) {
	/*
	* @input  : this - pointer to an object of type Vector
	* @output : frees the memory occupied by this
	*/
	free(this->array);
	free(this);
}


void vector_push_back(Vector* this, Element elem) {
	/*
	* @input  : this - pointer to an object of type Vector
	*			elem - pointer an Element
	* @output : insert the elem at the end of the vector, 
	*			reallocating memory if necessary
	*/
	if(vector_size(this) == vector_max_size(this))
		vector_resize(this);
	this->array[this->size++] = elem;
}

void vector_remove_at(Vector* this, int pos){
	/*
	* @input  : this - pointer to an object of type Vector
	*			int  - integer representing the positon of the pointer
	*				   element that is about to be deleted from vector
	* @output : deletes the pointer to element from positon pos
	*/
	int i;
	for(i = pos; i < vector_size(this) - 1; i++)
		this->array[i] = this->array[i + 1];
	this->size--;
}

int vector_size(Vector* this){
	/*
	* @input  : this - pointer to an object of type Vector
	* @output : returns an int, representing the number of
	*			elements in the vector
	*/
	return this->size;
}

int vector_max_size(Vector* this){
	/*
	* @input  : this - pointer to an object of type Vector
	* @output : returns an int, representing the maximum
	*			size of the vector
	*/
	return this->max_size;
}

void vector_resize(Vector* this) {
	/*
	* @input  : this - pointer to an object of type Vector
	* @output : double the maximum size of the array
	*/
	Element* newArray = (Element*)malloc(sizeof(Element) * this->max_size * 2);

	int i;
	for(i = 0; i < this->size; i++)
		newArray[i] = this->array[i];

	free(this->array);

	this->array = newArray;
	this->max_size = this->size * 2;

}

Element vector_element_at(Vector* this, int pos) {
	/*
	* @input  : this - pointer to an object of type Vector
	* @output : returns the element at index pos, from the vector
	*/
	return this->array[pos];
}

int vector_element_index(Vector* this, Element elem, int (*eq_func)(Element, Element)) {
	/*
	* @input  : this   - pointer to an object of type Vector
	*			elem   - pointer to an Element
	*			eq_func- pointer to a function that tests equality between two Elements
	* @output : returns an int, representing the index of elem, if elem in vector
	*			returns -1, if the elem couldn't be found 
	*/
	int i;
	for(i = 0; i < vector_size(this); i++)
		if(eq_func(elem, vector_element_at(this, i)))
			return i;
	return -1;
}

void vector_insert_at(Vector * this, Element elem, int pos) {
	if (vector_size(this) == vector_max_size(this))
		vector_resize(this);
	int i, size = vector_size(this);
	for (i = size; i > pos; i--)
		this->array[i] = this->array[i - 1];
	this->array[pos] = elem;
	this->size++;
}

void swap(Element *a, Element *b){
	/*
	* @input  : a, b : pointers
	* @output : swaps the addreses of a and b
	*/
	Element aux = *a;
	*a = *b;
	*b = aux;
}

void vector_sort(Vector* this, int (*cmp)(Element, Element), int reversed){
	/*
	* @input  : this    - pointer to an object of type Vector
	*			cmp     - function that compares two Elements
	*			reversed- int from set {0, 1}
	* @output : if reversed = 1, the vector is sorted descendingly,
	*		    if reversed = 0,the vector is sorted ascendingly,
	*			all this according to cmp
	*/
	int i, done, len = vector_size(this);
	done = 0;
	while(!done){
		done = 1;
		for(i = 0; i < len - 1; i++){
			Element *x = &(this->array[i]);
			Element *y = &(this->array[i + 1]);
			if((!cmp(*x, *y)) != reversed){
				swap(x, y);
				done = 0;
			}
		}
		len--;
	}
}
