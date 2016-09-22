/**
 * repository.c
 *
 *  Created on: 2 mar. 2016
 *      Author: marius
 */

#include "repository.h"

Repository* repository_init(char* file_name) {
	/*
	* @input  : file_name - path to a file containg objects of type Cheltuiala
	* @output : loads object from file_name and returns a pointer to an Repository object
	*/
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	repo->file_name = (char*)malloc(sizeof(char) * strlen(file_name) + 1);
	strcpy(repo->file_name, file_name);
	repo->items = vector_init(1);
	repository_load_from_file(repo);
	return repo;
}

void repository_load_from_file(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : loads pointer to object of type Cheltuiala from file and 
	*			signals eventual errors that will occur
	*/
	FILE* fp = fopen(this->file_name, "r");
	if (fp == NULL) {
		char msg[255] = "Could not open the file : ";
		strcat(msg, this->file_name);
		perror(msg);
		return;
	}
	int nr_ap, read_bytes;
	double suma;
	char buff[255];
	for (; 1; ) {
		read_bytes = 0;
		read_bytes += fscanf(fp, "%s", buff);
		nr_ap = atoi(buff);
		read_bytes += fscanf(fp, "%s", buff);
		suma = atof(buff);
		read_bytes += fscanf(fp, "%s", buff);
		if (read_bytes > 0) {
			Cheltuiala* ch = cheltuiala_init(nr_ap, suma, buff);
			vector_push_back(this->items, ch);
		}
		else
			break;
	}
	fclose(fp);
}

void repository_destroy_items(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : destroys the objects from the Repository
	*/
	Iterator* it = iterator_init(this->items);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		cheltuiala_destroy(ch_ptr);
	}
	iterator_destroy(it);
}

void repository_destroy(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : destroys the Repository object
	*/
	repository_destroy_items(this);
	vector_destroy(this->items);
	free(this->file_name);
	free(this);
}

Vector* repository_get_all(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : returns a pointer to a dinamic array (see Utils/Vector),
	*			containing the ojects from Rspository
	*/
	return this->items;
}

void repository_delete_all(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : deletes all objects from repository
	*/
	while (repository_get_size(this) != 0) {
		Cheltuiala* ch_ptr = vector_element_at(this->items, 0);
		vector_remove_at(this->items, 0);
		cheltuiala_destroy(ch_ptr);
	}
	repository_save_to_file(this);
}

void repository_save_to_file(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : saves the objects from memory into file
	*/
	FILE* fp = fopen(this->file_name, "w");
	if (fp == NULL) {
		char msg[255] = "Could not open the file : ";
		strcat(msg, this->file_name);
		perror(msg);
		return;
	}
	Iterator* it = iterator_init(this->items);
	for (; iterator_valid(it); iterator_next(it)) {
		Cheltuiala* ch_ptr = iterator_element(it);
		int nr_ap = cheltuiala_get_numar_apartament(ch_ptr);
		double suma = cheltuiala_get_sum(ch_ptr);
		char* tip = cheltuiala_get_tip(ch_ptr);
		fprintf(fp, "%d %f %s\n", nr_ap, suma, tip);
	}
	iterator_destroy(it);
	fclose(fp);

}

void repository_add_item(Repository* this, Cheltuiala* ch) {
	/*
	* @input  : this - pointer to object of type Repository
	*			ch	 - pointer to object of type Cheltuiala
	* @output : adds a new object to Repository
	*/
	vector_push_back(this->items, ch);
	repository_save_to_file(this);
}

int repository_get_size(Repository* this) {
	/*
	* @input  : this - pointer to object of type Repository
	* @output : returns the size of the Repository
	*/
	return vector_size(this->items);
}

void repository_delete_item(Repository* this, Cheltuiala* ch_ptr) {
	/*
	* @input  : this - pointer to object of type Repository
	*			ch	 - pointer to object of type Cheltuiala
	* @output : if exists, deletes the object from Repository, 
	*			and saves changes to file
	*/
	int pos = vector_element_index(this->items, ch_ptr, &cheltuiala_equal);
	if (pos != -1) {
		Cheltuiala* ch_in_repo = vector_element_at(this->items, pos);
		vector_remove_at(this->items, pos);
		if (ch_ptr != ch_in_repo)
			cheltuiala_destroy(ch_in_repo);
		cheltuiala_destroy(ch_ptr);
	}
	repository_save_to_file(this);
}
