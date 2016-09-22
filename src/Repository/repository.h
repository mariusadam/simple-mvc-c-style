/*
* repository.h
*
*  Created on: 2 mar. 2016
*      Author: marius
*/

#ifndef REPOSITORY_REPOSITORY_H_
#define REPOSITORY_REPOSITORY_H_

#include "../Utils/Vector/vector.h"
#include "../Utils/Vector/iterator.h"
#include "../Domain/entities.h"
#include <stdio.h>
#include <string.h>

typedef struct {
	Vector* items;
	char* file_name;
}Repository;

/*Public*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*
* @input  : file_name - path to a file containg objects of type Cheltuiala
* @output : loads object from file_name and returns a pointer to an Repository object
*/
Repository* repository_init(char* file_name);

/**
 * @param this
 */
void repository_destroy(Repository* this);

/*
* @input  : this - pointer to object of type Repository
* @output : destroys the objects from the Repository
*/
void repository_destroy_items(Repository* this);

/*
* @input  : this - pointer to object of type Repository
* @output : loads pointer to object of type Cheltuiala from file and
*			signals eventual errors that will occur
*/
void repository_load_from_file(Repository* this);

/*
* @input  : this - pointer to object of type Repository
* @output : saves the objects from memory into file
*/
void repository_save_to_file(Repository* this);

/*
* @input  : this - pointer to object of type Repository
*			ch	 - pointer to object of type Cheltuiala
* @output : adds a new object to Repository
*/
void repository_add_item(Repository* this, Cheltuiala* ch);

/*
* @input  : this - pointer to object of type Repository
*			ch	 - pointer to object of type Cheltuiala
* @output : if exists, deletes the object from Repository,
*			and saves changes to file
*/
void repository_delete_item(Repository* this, Cheltuiala* ch);

/*
* @input  : this - pointer to object of type Repository
* @output : deletes all objects from repository
*/
void repository_delete_all(Repository* this);

/*
* @input  : this - pointer to object of type Repository
* @output : returns a pointer to a dinamic array (see Utils/Vector),
*			containing the ojects from Rspository
*/
Vector* repository_get_all(Repository* this);

/*
* @input  : this - pointer to object of type Repository
* @output : returns the size of the Repository
*/
int repository_get_size(Repository* this);
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#endif /* REPOSITORY_REPOSITORY_H_ */
