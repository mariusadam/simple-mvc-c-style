/*
* tests.c
*
*  Created on: 2 mar. 2016
*      Author: marius
*/
#include "tests.h"

//Private
void test_add_all(Test* this) {
	//All functions that will be tested shoule be added here
	test_add(this, &test_vector);
	test_add(this, &test_iterator);
	test_add(this, &test_repository);
	test_add(this, &test_validator);
}

//Public
Test* test_init() {
	Test *test = (Test*)malloc(sizeof(Test));
	test->tests = vector_init(1);
	return test;
}

void test_destroy(Test* this) {
	vector_destroy(this->tests);
	free(this);
}

void test_add(Test* this, Function fn) {
	vector_push_back(this->tests, fn);
}

void test_runner(Test* this) {
	test_add_all(this);
	Iterator* it = iterator_init(this->tests);
	for (; iterator_valid(it); iterator_next(it))
		((Function)iterator_element(it))();
	iterator_destroy(it);
}