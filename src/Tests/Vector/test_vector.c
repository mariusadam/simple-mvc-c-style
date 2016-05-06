/*
 * test_vector.c
 *
 *  Created on: 2 mar. 2016
 *      Author: marius
 */
#include "test_vector.h"

void test_vector_init_destroy() {
	//Normal case
	Vector* vec = vector_init(1);

	assert(vector_size(vec)== 0);
	vector_push_back(vec, (Element)2);
	vector_push_back(vec, (Element)3);
	assert(vector_size(vec)== 2);
	vector_destroy(vec);
}

void test_vector_push_back(){
	Vector* vec = vector_init(2);

	assert(vector_size(vec)== 0);

	int e1 = 1, e2 = 2, e3 = 3, e4 = 4;

	vector_push_back(vec, &e1);
	assert(vector_size(vec)== 1);
	assert(vector_element_at(vec, 0) == &e1);

	vector_push_back(vec, &e2);
	assert(vector_size(vec)== 2);
	assert(vector_element_at(vec, 1) == &e2);

	vector_push_back(vec, &e3);
	assert(vector_size(vec)== 3);
	assert(vector_element_at(vec, 2) == &e3);

	vector_push_back(vec, &e4);
	assert(vector_size(vec)== 4);
	assert(vector_element_at(vec, 3) == &e4);

	vector_destroy(vec);
}

void test_vector_remove_at(){
	Vector* vec = vector_init(-12);

	assert(vector_size(vec) == 0);
	vector_push_back(vec, (Element)0);
	vector_push_back(vec, (Element)1);
	vector_push_back(vec, (Element)2);
	vector_push_back(vec, (Element)3);
	vector_push_back(vec, (Element)4);
	assert(vector_size(vec) == 5);

	vector_remove_at(vec, 1);
	assert(vector_element_at(vec, 0) == (Element)0);
	assert(vector_element_at(vec, 1) == (Element)2);
	assert(vector_element_at(vec, 2) == (Element)3);
	assert(vector_element_at(vec, 3) == (Element)4);

	vector_remove_at(vec, 0);
	assert(vector_element_at(vec, 0) == (Element)2);
	assert(vector_element_at(vec, 1) == (Element)3);
	assert(vector_element_at(vec, 2) == (Element)4);

	vector_remove_at(vec, 1);
	assert(vector_element_at(vec, 0) == (Element)2);
	assert(vector_element_at(vec, 1) == (Element)4);

	vector_remove_at(vec, 1);
	assert(vector_element_at(vec, 0) == (Element)2);

	vector_remove_at(vec, 0);
	assert(vector_size(vec) == 0);
	vector_destroy(vec);
}

void test_vector_size(){
	Vector* vec = vector_init(1);

	assert(vector_size(vec) == 0);

	vector_push_back(vec, (Element)(1));
	assert(vector_size(vec) == 1);

	vector_push_back(vec, (Element)(3));
	assert(vector_size(vec) == 2);

	int a = 12, b = 41;

	vector_push_back(vec, &a);
	assert(vector_size(vec) == 3);

	vector_push_back(vec, &b);
	assert(vector_size(vec) == 4);
	vector_destroy(vec);
}

void test_vector_resize(){
	Vector* vec = vector_init(1);

	assert(vector_max_size(vec) == 1);

	int a = 43;
	vector_push_back(vec, &a);
	assert(vector_max_size(vec) == 1);

	int b = 15;
	vector_push_back(vec, &b);
	assert(vector_max_size(vec) == 2);

	vector_push_back(vec, &b);
	assert(vector_max_size(vec) == 4);

	vector_destroy(vec);
}

void test_vector_element_at(){
	test_vector_push_back();
}

int equality_func(void* ff, void* ss){
	char *first = ff;
	char *second= ss;
	int len1 = strlen(first);
	int len2 = strlen(second);
	if (len1 != len2)
		return 0;
	int i;
	for(i = 0; i < len1; i++)
		if (first[i] != second[i])
			return 0;
	return 1;
}

void test_vector_element_index(){
	Vector* vec = vector_init(1);

	char *e0 = "zero";
	char *e1 = "unu";
	char *e2 = "doi";
	char *e3 = "trei";
	char *e4 = "patru";
	vector_push_back(vec, e0);
	vector_push_back(vec, e1);
	vector_push_back(vec, e2);
	vector_push_back(vec, e3);
	vector_push_back(vec, e4);

	assert(vector_element_index(vec, e0, &equality_func) == 0);
	assert(vector_element_index(vec, e1, &equality_func) == 1);
	assert(vector_element_index(vec, e2, &equality_func) == 2);
	assert(vector_element_index(vec, e3, &equality_func) == 3);
	assert(vector_element_index(vec, e4, &equality_func) == 4);

	char* e5 = "not in vector";
	assert(vector_element_index(vec, e5, &equality_func) == -1);
	vector_destroy(vec);
}

int cmp(void* a, void* b){
	int *aa = a, *bb = b;
	return *aa < *bb;
}

void test_vector_sort(){
	Vector* vec = vector_init(1);
	int e0 = 10, e1 = -2, e2 = 0, e3 = 9, e4 = -43, e5 = 1;
	vector_push_back(vec, &e0);
	vector_push_back(vec, &e1);
	vector_push_back(vec, &e2);
	vector_push_back(vec, &e3);
	vector_push_back(vec, &e4);
	vector_push_back(vec, &e5);

	vector_sort(vec, &cmp, 0);

	int *to_int = vector_element_at(vec, 0);
	assert( *to_int == -43);
	to_int = vector_element_at(vec, 1);
	assert( *to_int == -2);
	to_int = vector_element_at(vec, 2);
	assert( *to_int == 0);
	to_int = vector_element_at(vec, 3);
	assert( *to_int == 1);
	to_int = vector_element_at(vec, 4);
	assert( *to_int == 9);
	to_int = vector_element_at(vec, 5);
	assert( *to_int == 10);


	vector_sort(vec, &cmp, 1);

	to_int = vector_element_at(vec, 5);
	assert( *to_int == -43);
	to_int = vector_element_at(vec, 4);
	assert( *to_int == -2);
	to_int = vector_element_at(vec, 3);
	assert( *to_int == 0);
	to_int = vector_element_at(vec, 2);
	assert( *to_int == 1);
	to_int = vector_element_at(vec, 1);
	assert( *to_int == 9);
	to_int = vector_element_at(vec, 0);
	assert( *to_int == 10);

	vector_destroy(vec);
}

void test_vector() {
	printf("\n-------------------------------------------\n");
	printf("Testing Vector utility...\n");
	test_vector_init_destroy();
	test_vector_push_back();
	test_vector_remove_at();
	test_vector_size();
	test_vector_resize();
	test_vector_element_at();
	test_vector_element_index();
	test_vector_sort();
	printf("Vector utility tested succesfully!\n");
	printf("-------------------------------------------\n");
}
