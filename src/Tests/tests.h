/*
* tests.h
*
*  Created on: 2 mar. 2016
*      Author: marius
*/

#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_

#include "../Utils/Vector/vector.h"
#include "../Utils/Vector/iterator.h"
#include "Vector/test_vector.h"
#include "Vector/test_iterator.h"
#include "Repository/test_repository.h"
#include "Domain/test_validator.h"
#include <malloc.h>

typedef struct {
	Vector* tests;
}Test;

//Private
void test_add_all(Test* this);

//Builder for tests vector
Test* test_init();

//Destroyer for the tests vector
void test_destroy(Test* this);

//Add a new function to verify
void test_add(Test* this, Function fn);

//Add all test to test and verify them
void test_runner(Test* test);
#endif /* TESTS_TESTS_H_ */
