#ifndef _ALEXVEC_H
#define _ALEXVEC_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char BYTE;
#define alexvec BYTE*

#define alexvec_init(ptr, T)																	\
{																								\
	size_t _elem_size = sizeof(T) / sizeof(BYTE);												\
	size_t head_size = 3 * sizeof(size_t) / sizeof(BYTE);										\
	size_t _size = 0;																			\
	size_t _maxsize =  1;																		\
	ptr = (alexvec)malloc(sizeof(BYTE)*(head_size+_elem_size));									\
	if(NULL == ptr) {																			\
			printf("内存分配失败 .\n");															\
			exit(1);																			\
	}																							\
	*(size_t*)ptr = _elem_size;																	\
	*((size_t*)ptr+1) = _size;																	\
	*((size_t*)ptr+2) = _maxsize;																\
}

#define alexvec_push_back(ptr, elem)															\
{																								\
	if(NULL == ptr){																			\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	size_t _elem_size = *(size_t*)ptr;															\
	if(sizeof(elem) != _elem_size*sizeof(BYTE)){												\
		printf("类型不匹配 .\n");																\
		exit(1);																				\
	}																							\
																								\
	size_t _size = *((size_t*)ptr+1);															\
	size_t _maxsize = *((size_t*)ptr+2);														\
	if(_size == _maxsize){																		\
			size_t head_size = 3 * sizeof(size_t) / sizeof(BYTE);								\
			ptr = (alexvec)realloc((void*)ptr,													\
				(size_t)(sizeof(BYTE)*(head_size+_elem_size*2*_maxsize)));						\
			if(ptr==NULL) {																		\
					printf("内存分配失败 .\n");													\
					exit(1);																	\
			}																					\
			*(size_t*)ptr = _elem_size;															\
			*((size_t*)ptr+2) = 2*_maxsize;														\
			*((size_t*)ptr+1) = _size;															\
	}																							\
	memcpy((void*)((BYTE*)((size_t*)ptr+3)+*((size_t*)ptr+1)*_elem_size*sizeof(BYTE)),			\
							(const void*)&elem, _elem_size*sizeof(BYTE));						\
	*((size_t*)ptr+1) = _size+1;																\
}		

#define alexvec_pop_back(ptr, elem)																\
{																								\
	if(NULL == ptr){																			\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	size_t _elem_size = *(size_t*)ptr;															\
	if(sizeof(elem) != _elem_size*sizeof(BYTE)){												\
		printf("类型不匹配 .\n");																\
		exit(1);																				\
	}																							\
																								\
	size_t _size = *((size_t*)ptr+1);															\
	if(_size == 0){																				\
		printf("vec已空.\n");																	\
		exit(1);																				\
	}																							\
																								\
	*((size_t*)ptr+1) = _size-1;																\
	memcpy((void*)&elem,																		\
		(const void*)((BYTE*)((size_t*)ptr+3)+*((size_t*)ptr+1)*_elem_size*sizeof(BYTE)),		\
		_elem_size*sizeof(BYTE));																\
}

#define alexvec_destroy(p)																		\
{																								\
	if (NULL != p) {																			\
		free(p);																				\
		p = NULL;																				\
	}																							\
}

#define _alexvec_size(ptr, size)																\
{																								\
	if(NULL == ptr){																			\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	size = *((size_t*)ptr + 1);																	\
}

#define _alexvec_maxsize(ptr, maxsize)															\
{																								\
	if(NULL == ptr){																			\
		printf("vec未经过初始化 .\n");															\
		exit(1);																				\
	}																							\
	maxsize = *((size_t*)ptr + 2);																\
}

size_t alexvec_size(alexvec p)
{
	size_t _size = 0;
	_alexvec_size(p, _size);
	return _size;
}

size_t alexvec_maxsize(alexvec p)
{
	size_t _maxsize = 0;
	_alexvec_maxsize(p, _maxsize);
	return _maxsize;
}


#endif