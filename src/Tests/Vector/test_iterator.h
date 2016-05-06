/*
 * test_iterator.h
 *
 *  Created on: 4 mar. 2016
 *      Author: marius
 */

#ifndef TESTS_VECTOR_TEST_ITERATOR_H_
#define TESTS_VECTOR_TEST_ITERATOR_H_
#include <stdio.h>
#include <assert.h>
#include "../../Utils/Vector/vector.h"
#include "../../Utils/Vector/iterator.h"

//Tests:
void test_iterator_init_destroy();
void test_iterator_begin();
void test_iterator_end();
void test_iterator_next();
void test_iterator_before();
void test_iterator_valid();
void test_iterator_element();

//Main function to test all:
void test_iterator();

#endif /* TESTS_VECTOR_TEST_ITERATOR_H_ */
