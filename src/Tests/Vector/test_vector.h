/*
 * test_vector.h
 *
 *  Created on: 2 mar. 2016
 *      Author: marius
 */

#ifndef TESTS_VECTOR_TEST_VECTOR_H_
#define TESTS_VECTOR_TEST_VECTOR_H_

#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../Utils/Vector/vector.h"
//Tests:
void test_vector_init_destroy();
void test_vector_push_back();
void test_vector_remove_at();
void test_vector_size();
void test_vector_resize();
void test_vector_element_at();
void test_vector_element_index();
void test_vector_sort();

//Main function - Calls other functions to be executed
void test_vector();

#endif /* TESTS_VECTOR_TEST_VECTOR_H_ */
