/*
 * test_repository.h
 *
 *  Created on: 3 mar. 2016
 *      Author: marius
 */

#ifndef TESTS_REPOSITORY_TEST_REPOSITORY_H_
#define TESTS_REPOSITORY_TEST_REPOSITORY_H_

#include "../../Repository/repository.h"

//Tests:
void test_repository_create_destroy();
void test_repository_create_destroy_ptr();
void test_repository_get_all();
void test_repository_add_item();
void test_repository_delete_item();
void test_repository_delete_all();

//Runner for all repository tests:
void test_repository();

#endif /* TESTS_REPOSITORY_TEST_REPOSITORY_H_ */
