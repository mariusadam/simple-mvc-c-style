/*
* test_repository.c
*
*  Created on: 3 mar. 2016
*      Author: marius
*/
#include "test_repository.h"
#include "../../Domain/entities.h"
#include "../../Utils/Vector/vector.h"
#include <assert.h>
#include <stdio.h>

void test_repository_create_destroy() {
	//Normal case
	Repository* repo = repository_init("Files/test_cheltuieli.txt");
	repository_delete_all(repo);
	assert(repository_get_size(repo) == 0);

	Cheltuiala *ch, *ch1, *ch2, *ch3;
	ch = cheltuiala_init(1, 432.123, "apa");
	ch1 = cheltuiala_init(2, 21.43, "canal");
	ch2 = cheltuiala_init(3, 3.65, "incalzire");
	ch3 = cheltuiala_init(4, 65.69, "gaz");

	repository_add_item(repo, ch);
	assert(repository_get_size(repo) == 1);

	repository_add_item(repo, ch1);
	assert(repository_get_size(repo) == 2);

	repository_add_item(repo, ch2);
	assert(repository_get_size(repo) == 3);

	repository_add_item(repo, ch3);
	assert(repository_get_size(repo) == 4);

	repository_destroy(repo);
}

void test_repository_create_destroy_ptr() {
	//Normal case
	Repository* repo = repository_init("Files//test_cheltuieli.txt");
	repository_delete_all(repo);
	assert(repository_get_size(repo) == 0);

	Cheltuiala *ch, *ch1, *ch2, *ch3;
	ch = cheltuiala_init(1, 432.123, "apa");
	ch1 = cheltuiala_init(2, 21.43, "canal");
	ch2 = cheltuiala_init(3, 3.65, "incalzire");
	ch3 = cheltuiala_init(4, 65.69, "gaz");

	repository_add_item(repo, ch);
	assert(repository_get_size(repo) == 1);

	repository_add_item(repo, ch1);
	assert(repository_get_size(repo) == 2);

	repository_add_item(repo, ch2);
	assert(repository_get_size(repo) == 3);

	repository_add_item(repo, ch3);
	assert(repository_get_size(repo) == 4);

	repository_destroy(repo);
}

void test_repository_get_all() {
	Repository* repo = repository_init("Files//test_cheltuieli.txt");
	repository_delete_all(repo);
	Vector* alls = repository_get_all(repo);
	assert(vector_size(alls) == 0);

	Cheltuiala *ch, *ch1, *ch2, *ch3;
	ch = cheltuiala_init(1, 432.123, "apa");
	ch1 = cheltuiala_init(2, 21.43, "canal");
	ch2 = cheltuiala_init(3, 3.65, "incalzire");
	ch3 = cheltuiala_init(4, 65.69, "gaz");

	repository_add_item(repo, ch);
	alls = repository_get_all(repo);
	assert(vector_size(alls) == 1);

	repository_add_item(repo, ch1);
	alls = repository_get_all(repo);
	assert(vector_size(alls) == 2);

	repository_add_item(repo, ch2);
	alls = repository_get_all(repo);
	assert(vector_size(alls) == 3);

	repository_add_item(repo, ch3);
	alls = repository_get_all(repo);
	assert(vector_size(alls) == 4);

	repository_destroy(repo);
}

void test_repository_add_item() {
	//Normal case
	Repository* repo = repository_init("Files//test_cheltuieli.txt");
	repository_delete_all(repo);
	assert(repository_get_size(repo) == 0);

	Cheltuiala *ch, *ch1, *ch2, *ch3;
	ch = cheltuiala_init(1, 432.123, "apa");
	ch1 = cheltuiala_init(2, 21.43, "canal");
	ch2 = cheltuiala_init(3, 3.65, "incalzire");
	ch3 = cheltuiala_init(4, 65.69, "gaz");

	repository_add_item(repo, ch);
	assert(repository_get_size(repo) == 1);
	assert(cheltuiala_equal(vector_element_at(repo->items, 0), ch));

	repository_add_item(repo, ch1);
	assert(repository_get_size(repo) == 2);
	assert(cheltuiala_equal(vector_element_at(repo->items, 1), ch1));

	repository_add_item(repo, ch2);
	assert(repository_get_size(repo) == 3);
	assert(cheltuiala_equal(vector_element_at(repo->items, 2), ch2));

	repository_add_item(repo, ch3);
	assert(repository_get_size(repo) == 4);
	assert(cheltuiala_equal(vector_element_at(repo->items, 3), ch3));

	repository_destroy(repo);
}

void test_repository_delete_item() {
	//Normal case
	Repository* repo = repository_init("Files//test_cheltuieli.txt");
	repository_delete_all(repo);
	assert(repository_get_size(repo) == 0);

	Cheltuiala *ch, *ch1, *ch2, *ch3;
	ch = cheltuiala_init(1, 432.123, "apa");
	ch1 = cheltuiala_init(2, 21.43, "canal");
	ch2 = cheltuiala_init(3, 3.65, "incalzire");
	ch3 = cheltuiala_init(4, 65.69, "gaz");

	repository_add_item(repo, ch);
	repository_add_item(repo, ch1);
	repository_add_item(repo, ch2);
	repository_add_item(repo, ch3);

	assert(cheltuiala_equal(vector_element_at(repo->items, 0), ch));
	repository_delete_item(repo, ch);
	assert(cheltuiala_equal(vector_element_at(repo->items, 0), ch1));

	assert(cheltuiala_equal(vector_element_at(repo->items, 1), ch2));
	repository_delete_item(repo, ch2);
	assert(cheltuiala_equal(vector_element_at(repo->items, 1), ch3));

	repository_delete_item(repo, ch1);
	repository_delete_item(repo, ch3);
	assert(repository_get_size(repo) == 0);

	repository_destroy(repo);
}

void test_repository_delete_all() {
	Repository* repo = repository_init("Files//test_cheltuieli.txt");
	repository_delete_all(repo);

	assert(repository_get_size(repo) == 0);

	Cheltuiala *ch, *ch1, *ch2, *ch3;
	ch = cheltuiala_init(1, 432.123, "apa");
	ch1 = cheltuiala_init(2, 21.43, "canal");
	ch2 = cheltuiala_init(3, 3.65, "incalzire");
	ch3 = cheltuiala_init(4, 65.69, "gaz");

	repository_add_item(repo, ch);
	repository_add_item(repo, ch1);
	repository_add_item(repo, ch2);
	repository_add_item(repo, ch3);
	assert(repository_get_size(repo) == 4);

	repository_delete_all(repo);
	assert(repository_get_size(repo) == 0);

	repository_destroy(repo);
}

void test_repository() {
	printf("\n-------------------------------------------\n");
	printf("Testing Repository...\n");
	test_repository_delete_all();
	test_repository_create_destroy();
	test_repository_create_destroy_ptr();
	test_repository_add_item();
	test_repository_delete_item();
	test_repository_get_all();
	printf("Repository tested succesfully!\n");
	printf("-------------------------------------------\n");
}