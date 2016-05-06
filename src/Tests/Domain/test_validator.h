/*
 * test_validator.h
 *
 *  Created on: 5 mar. 2016
 *      Author: marius
 */

#ifndef TESTS_DOMAIN_TEST_VALIDATOR_H_
#define TESTS_DOMAIN_TEST_VALIDATOR_H_

#include <assert.h>
#include <stdio.h>
#include "../../Domain/validator.h"

//Tests:
void test_validate_cmd();
void test_validate_nr_ap();
void test_validate_suma();
void test_validate_tip();
void test_validate_cheltuiala();
void test_is_digit();

//Main subroutine for testing Validator
void test_validator();

#endif /* TESTS_DOMAIN_TEST_VALIDATOR_H_ */
