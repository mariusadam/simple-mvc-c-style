/*
============================================================================
Name        : Lab24.c
Author      : marius
Version     : 1.0 Beta
Copyright   : Do not try to copy this!
Description : Application for managing the expenses of some apartments in C
============================================================================
*/
#include <stdio.h>
#include "Tests/tests.h"
#include "Repository/repository.h"
#include "Ui/console.h"

void run_tests() {
	Test *tests = test_init();
	test_runner(tests);
	test_destroy(tests);
}

void run_app() {
	/*  
	 * Builder for the application
	 */
	Repository* repo = repository_init("Files/cheltuieli.txt");
	Validator* valid = validator_init();
	Controller* ctr = controller_init(repo, valid);
	Console* cons = console_init(ctr);
	
	console_run(cons);

	console_destroy(cons);
	controller_destroy(ctr);
	validator_destroy(valid);
	repository_destroy(repo);
}

int main() {

	run_tests();
	run_app();
	getchar();

	return 0;
}