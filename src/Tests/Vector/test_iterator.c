/*
 * test_iterator.c
 *
 *  Created on: 4 mar. 2016
 *      Author: marius
 */
#include "test_iterator.h"

void test_iterator_init_destroy(){
	Vector* vec = vector_init(1);
	int *a = NULL, *b = NULL, *c = NULL;

	vector_push_back(vec, a);
	vector_push_back(vec, b);
	vector_push_back(vec, c);

	Iterator* it = iterator_init(vec);
	assert(it->container == vec);
	assert(it->curent == vec->array);
	assert(*(it->curent) == a);

	iterator_destroy(it);
	vector_destroy(vec);
}

void test_iterator_begin(){
	Vector* vec = vector_init(1);
	int a = 1, b = 2, c = 3, d = 4;

	vector_push_back(vec, &a);
	vector_push_back(vec, &b);
	vector_push_back(vec, &c);
	vector_push_back(vec, &d);

	Iterator* it = iterator_init(vec);
	assert(iterator_element(it) == &a);
	iterator_next(it);
	iterator_next(it);
	iterator_next(it);
	iterator_begin(it);
	assert(iterator_element(it) == &a);

	iterator_destroy(it);
	vector_destroy(vec);
}

void test_iterator_end(){
	Vector* vec = vector_init(1);
	int a = 1, b = 2, c = 3, d = 4;

	vector_push_back(vec, &a);
	vector_push_back(vec, &b);
	vector_push_back(vec, &c);
	vector_push_back(vec, &d);

	Iterator* it = iterator_init(vec);

	assert(iterator_element(it) == &a);
	iterator_end(it);
	assert(iterator_element(it) == &d);

	iterator_destroy(it);
	vector_destroy(vec);

}

void test_iterator_next(){
	Vector* vec = vector_init(1);
	int a = 1, b = 2, c = 3, d = 4;

	vector_push_back(vec, &a);
	vector_push_back(vec, &b);
	vector_push_back(vec, &c);
	vector_push_back(vec, &d);

	Iterator* it = iterator_init(vec);
	assert(iterator_element(it) == &a);
	iterator_next(it);
	assert(iterator_element(it) == &b);
	iterator_next(it);
	assert(iterator_element(it) == &c);
	iterator_next(it);
	assert(iterator_element(it) == &d);
	iterator_begin(it);
	assert(iterator_element(it) == &a);

	iterator_destroy(it);
	vector_destroy(vec);

}

void test_iterator_before(){
	Vector* vec = vector_init(1);
	int a = 1, b = 2, c = 3, d = 4;

	vector_push_back(vec, &a);
	vector_push_back(vec, &b);
	vector_push_back(vec, &c);
	vector_push_back(vec, &d);

	Iterator* it = iterator_init(vec);

	assert(iterator_element(it) == &a);
	iterator_end(it);
	assert(iterator_element(it) == &d);
	iterator_before(it);
	assert(iterator_element(it) == &c);
	iterator_before(it);
	assert(iterator_element(it) == &b);
	iterator_before(it);
	assert(iterator_element(it) == &a);

	iterator_destroy(it);
	vector_destroy(vec);
}

void test_iterator_valid(){
	Vector* vec = vector_init(1);
	int a = 1, b = 2, c = 3, d = 4;

	vector_push_back(vec, &a);
	vector_push_back(vec, &b);
	vector_push_back(vec, &c);
	vector_push_back(vec, &d);

	Iterator* it = iterator_init(vec);
	assert(iterator_valid(it) == 1);
	iterator_before(it);
	assert(iterator_valid(it) == 0);
	iterator_end(it);
	assert(iterator_valid(it) == 1);
	iterator_next(it);
	assert(iterator_valid(it) == 0);

	iterator_destroy(it);
	vector_destroy(vec);
}

void test_iterator_element(){
	Vector* vec = vector_init(1);
	int a = 1, b = 2, c = 3, d = 4;

	vector_push_back(vec, &a);
	vector_push_back(vec, &b);
	vector_push_back(vec, &c);
	vector_push_back(vec, &d);

	Iterator* it = iterator_init(vec);
	assert(iterator_element(it) == &a);
	iterator_next(it);
	assert(iterator_element(it) == &b);
	iterator_next(it);
	assert(iterator_element(it) == &c);
	iterator_next(it);
	assert(iterator_element(it) == &d);
	iterator_next(it);

	iterator_destroy(it);
	vector_destroy(vec);
}

void test_iterator(){
	printf("\n-------------------------------------------\n");
	printf("Testing Iterator utility...\n");
	test_iterator_init_destroy();
	test_iterator_begin();
	test_iterator_end();
	test_iterator_next();
	test_iterator_before();
	test_iterator_valid();
	test_iterator_element();
	printf("Iterator utility tested succesfully!\n");
	printf("-------------------------------------------\n");
}
