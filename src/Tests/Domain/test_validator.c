/*
 * test_validator.c
 *
 *  Created on: 5 mar. 2016
 *      Author: marius
 */
#include "test_validator.h"

void test_validate_cmd(){
	Validator* valid = validator_init();

	assert(validator_validate_cmd(valid, "1") == 1);
	assert(validator_validate_cmd(valid, "-1") == 0);
	assert(validator_validate_cmd(valid, "112") == 0);
	assert(validator_validate_cmd(valid, "") == 0);

	validator_destroy(valid);
}

void test_validate_nr_ap(){
	Validator* valid = validator_init();

	assert(validator_validate_cmd(valid, "1") == 1);
	assert(validator_validate_cmd(valid, "-112") == 0);
	assert(validator_validate_cmd(valid, "112") == 0);
	assert(validator_validate_cmd(valid, "") == 0);
	assert(validator_validate_cmd(valid, "asf") == 0);
	assert(validator_validate_cmd(valid, "123") == 0);
	assert(validator_validate_cmd(valid, "1234142") == 0);
	assert(validator_validate_cmd(valid, "12") == 1);

	validator_destroy(valid);
}

void test_validate_suma(){
	Validator* valid = validator_init();

	assert(validator_validate_suma(valid, "1.321") == 1);
	assert(validator_validate_suma(valid, "-112.3") == 0);
	assert(validator_validate_suma(valid, "112.132") == 1);
	assert(validator_validate_suma(valid, "") == 0);
	assert(validator_validate_suma(valid, "asf") == 0);
	assert(validator_validate_suma(valid, "123.43") == 1);
	assert(validator_validate_suma(valid, "1234142") == 0);
	assert(validator_validate_suma(valid, "12.") == 1);

	validator_destroy(valid);
}

void test_validate_tip(){
	Validator* valid = validator_init();

	assert(validator_validate_tip(valid, "apa") == 1);
	assert(validator_validate_tip(valid, "gaz") == 1);
	assert(validator_validate_tip(valid, "incalzire") == 1);
	assert(validator_validate_tip(valid, "canal") == 1);
	assert(validator_validate_tip(valid, "asf") == 0);
	assert(validator_validate_tip(valid, "123") == 0);
	assert(validator_validate_tip(valid, "") == 0);
	assert(validator_validate_tip(valid, "-") == 0);

	validator_destroy(valid);
}

void test_validate_cheltuiala(){
	Validator* valid = validator_init();

	assert(validator_validate_cheltuiala(valid, "1", "432.0543","apa") == 1);
	assert(validator_validate_cheltuiala(valid, "", "432.0543","apa") == 0);
	assert(validator_validate_cheltuiala(valid, "1", "432.wer","apa") == 0);
	assert(validator_validate_cheltuiala(valid, "12rwe", "432.0543","") == 0);
	assert(validator_validate_cheltuiala(valid, "1", "432.0543","aepa") == 0);
	assert(validator_validate_cheltuiala(valid, "1e", "","apa") == 0);
	assert(validator_validate_cheltuiala(valid, "1231123", "432.0543","apa") == 0);
	assert(validator_validate_cheltuiala(valid, "d1", "432.0543","apasf") == 0);
	assert(validator_validate_cheltuiala(valid, "1", "432.0543","" )== 0);
	assert(validator_validate_cheltuiala(valid, "1", "-432.0543","camal") == 0);
	assert(validator_validate_cheltuiala(valid, "", "","") == 0);

	validator_destroy(valid);
}

void test_is_digit(){
	assert(validator_is_digit( '0') == 1);
	assert(validator_is_digit( '1') == 1);
	assert(validator_is_digit( '2') == 1);
	assert(validator_is_digit( '3') == 1);
	assert(validator_is_digit( '4') == 1);
	assert(validator_is_digit( '5') == 1);
	assert(validator_is_digit( '6') == 1);
	assert(validator_is_digit( '7') == 1);
	assert(validator_is_digit( '8') == 1);
	assert(validator_is_digit( '9') == 1);
	assert(validator_is_digit( '/') == 0);
	assert(validator_is_digit( 'q') == 0);
	assert(validator_is_digit( '.') == 0);
	assert(validator_is_digit( ' ') == 0);
	assert(validator_is_digit( '@') == 0);
	assert(validator_is_digit( 'd') == 0);
}

void test_validator(){
	printf("\n-------------------------------------------\n");
	printf("Testing Domain Validator...\n");
	test_validate_cmd();
	test_validate_nr_ap();
	test_validate_suma();
	test_validate_tip();
	test_validate_cheltuiala();
	test_is_digit();
	printf("Domain Validator tested succesfully!\n");
	printf("-------------------------------------------\n");
}
