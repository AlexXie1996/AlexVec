#ifndef _FUNNYVEC_H
#define _FUNNYVEC_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char BYTE;
typedef struct _funnyvec funnyvec;

struct _funnyvec {
	size_t _elem_size;
	size_t _maxsize;
	BYTE* _ptr;
	size_t _head;
	size_t _tail;
	int empty;
};

#define funnyvec_init(vec, T)																	\
{																								\
	vec._elem_size = sizeof(T) / sizeof(BYTE);													\
	vec._maxsize = 1;																			\
																								\
	vec._ptr = (BYTE*)malloc(vec._elem_size);													\
	if(NULL == vec._ptr) {																		\
			printf("内存分配失败 .\n");															\
			exit(1);																			\
	}																							\
																								\
	vec._head = 0;																				\
	vec._tail = 0;																				\
	vec.empty = 1;																			\
}

#define funnyvec_push_back(vec, elem)															\
{																								\
	if(NULL == vec._ptr){																		\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	if (sizeof(elem) != vec._elem_size*sizeof(BYTE)) {											\
			printf("类型不匹配 .\n");															\
			exit(1);																			\
	}																							\
																								\
	if (vec.empty) {																			\
		vec.empty = 0;																		\
	}																							\
	else if (vec._head == vec._tail) {															\
		vec._ptr = (BYTE*)realloc((void*)vec._ptr,												\
			(size_t)(sizeof(BYTE)*(vec._elem_size * 2 * vec._maxsize)));						\
		if (vec._ptr == NULL) {																	\
				printf("内存分配失败 .\n");														\
				exit(1);																		\
		}																						\
																								\
		memcpy((void*)((BYTE*)vec._ptr + (vec._maxsize*vec._elem_size)),						\
			(const void*)vec._ptr, vec._elem_size * sizeof(BYTE)*vec._tail);					\
		vec._tail += vec._maxsize;																\
		vec._maxsize *= 2;																		\
	}																							\
																								\
	memcpy((void*)((BYTE*)vec._ptr + (vec._tail*vec._elem_size)),								\
		(const void*)&elem, vec._elem_size * sizeof(BYTE));										\
	vec._tail = (vec._tail+1)%vec._maxsize;														\
}

#define funnyvec_pop_back(vec, elem)															\
{																								\
	if(NULL == vec._ptr){																		\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	if (sizeof(elem) != vec._elem_size*sizeof(BYTE)) {											\
			printf("类型不匹配 .\n");															\
			exit(1);																			\
	}																							\
	if (vec.empty) {																			\
		printf("vec已空.\n");																	\
		exit(1);																				\
	}																							\
	vec._tail = (vec._tail + vec._maxsize - 1) % vec._maxsize;									\
	memcpy((void*)&elem,																		\
		(const void*)((BYTE*)vec._ptr + (vec._tail*vec._elem_size)),							\
		vec._elem_size * sizeof(BYTE));															\
	if (vec._tail == vec._head) {																\
		vec.empty = 1;																		\
	}																							\
}

#define funnyvec_push_front(vec, elem)															\
{																								\
	if(NULL == vec._ptr){																		\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	if (sizeof(elem) != vec._elem_size * sizeof(BYTE)) {										\
		printf("类型不匹配 .\n");																\
		exit(1);																				\
	}																							\
	if (vec.empty) {																			\
		vec.empty = 0;																		\
	}																							\
	else if (vec._head == vec._tail) {															\
		vec._ptr = (BYTE*)realloc((void*)vec._ptr,												\
		(size_t)(sizeof(BYTE)*(vec._elem_size * 2 * vec._maxsize)));							\
		if (vec._ptr == NULL) {																	\
				printf("内存分配失败 .\n");														\
				exit(1);																		\
		}																						\
		memcpy((void*)((BYTE*)vec._ptr + (vec._maxsize*vec._elem_size)),						\
		(const void*)vec._ptr, vec._elem_size * sizeof(BYTE)*vec._tail);						\
		vec._tail += vec._maxsize;																\
		vec._maxsize *= 2;																		\
	}																							\
																								\
	vec._head = (vec._head + vec._maxsize - 1) % vec._maxsize;									\
	memcpy((void*)((BYTE*)vec._ptr + (vec._head*vec._elem_size)),								\
		(const void*)&elem, vec._elem_size * sizeof(BYTE));										\
}

#define funnyvec_pop_front(vec, elem)															\
{																								\
	if(NULL == vec._ptr){																		\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	if (sizeof(elem) != vec._elem_size*sizeof(BYTE)) {											\
			printf("类型不匹配 .\n");															\
			exit(1);																			\
	}																							\
	if (vec.empty) {																			\
		printf("vec已空.\n");																	\
		exit(1);																				\
	}																							\
	memcpy((void*)&elem,																		\
		(const void*)((BYTE*)vec._ptr + (vec._head*vec._elem_size)),							\
		vec._elem_size * sizeof(BYTE));															\
	vec._head = (vec._head + 1) % vec._maxsize;													\
	if (vec._tail == vec._head) {																\
		vec.empty = 1;																		\
	}																							\
}

#define _funnyvec_size(vec, size)																\
{																								\
	if(NULL == vec._ptr){																		\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	if(vec._tail > vec._head){																	\
		size = vec._tail - vec._head;															\
	}else if(vec.empty){																		\
		size = 0;																				\
	}else if(vec._tail < vec._head){															\
		size = vec._tail + vec._maxsize - vec._head;											\
	}else{																						\
		size = vec._maxsize;																	\
	}																							\
}

#define funnyvec_get_elem(vec, i, elem)															\
{																								\
	if (NULL == vec._ptr) {																		\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	if (sizeof(elem) != vec._elem_size * sizeof(BYTE)) {										\
		printf("类型不匹配 .\n");																\
		exit(1);																				\
	}																							\
	if ((vec._head + i) % vec._maxsize >= vec._tail) {											\
		printf("索引越界 .\n");																	\
		exit(1);																				\
	}																							\
	memcpy((void*)&elem,																		\
		(const void*)((BYTE*)vec._ptr + ((vec._head+i)%vec._maxsize*vec._elem_size)),			\
		vec._elem_size * sizeof(BYTE));															\
}	

#define funnyvec_destroy(vec)																	\
{																								\
	vec._elem_size = 0;																			\
	vec._maxsize = 0;																			\
	if (NULL != vec._ptr) {																		\
		free(vec._ptr);																			\
		vec._ptr = NULL;																		\
	}																							\
	vec._head = 0;																				\
	vec._tail = 0;																				\
	vec.empty = 1;																			\
}

size_t funnyvec_size(funnyvec vec) {
	if (NULL == vec._ptr) {
			printf("vec未经过初始化 .\n");															
			exit(1);																				
	}																							
	size_t size = 0;
	_funnyvec_size(vec, size);
	return size;
}

size_t funnyvec_maxsize(funnyvec vec) {
	return vec._maxsize;
}

#endif
