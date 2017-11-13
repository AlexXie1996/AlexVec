#include<stdio.h>

#include <crtdbg.h>
#include"alexvec.h"

struct my_struct 
{
	int elem;

}test;

int main(void)
{
	//_CrtSetBreakAlloc(100);
	alexvec my_vec;		// 声明在这里

	// char
	alexvec_init(my_vec, char);		// 创建在这里
	char src = 'a';
	char des;
	size_t size = 0;
	size_t maxsize = 0;

	for (int i = 0; i < 100; i++) {
		alexvec_push_back(my_vec, src);		// 压栈在这里
		size = alexvec_size(my_vec);
		maxsize = alexvec_maxsize(my_vec);
		printf("vec size = %d, vec maxsize = %d\n", size, maxsize);
	}

	for (int i = 0; i < 100; i++) {
		alexvec_pop_back(my_vec, des);	// 出栈在这里
		size = alexvec_size(my_vec);
		printf("vec size = %d, elem = %c\n", size, des);
	}
	alexvec_destroy(my_vec);	// 销毁在这里
	printf("**************** char *********************\n\n");
	getchar();

	// double
	alexvec_init((alexvec)my_vec, double);
	double src1 = 8.88888;
	double des1 = 0;

	for (int i = 0; i < 100; i++) {
		alexvec_push_back(my_vec, src1);
		size = alexvec_size(my_vec);
		maxsize = alexvec_maxsize(my_vec);
		printf("vec size = %d, vec maxsize = %d\n", size, maxsize);
	}
	for (int i = 0; i < 100; i++) {
		alexvec_pop_back(my_vec, des1);
		size = alexvec_size(my_vec);
		printf("vec size = %d, elem = %f\n", size, des1);
	}
	alexvec_destroy(my_vec);
	printf("**************** double *********************\n\n");
	getchar();

	// struct
	alexvec_init((alexvec)my_vec, struct my_struct);
	struct my_struct src2;
	src2.elem = 4;
	struct my_struct des2;
	des2.elem = 0;

	for (int i = 0; i < 100; i++) {
		alexvec_push_back(my_vec, src2);
		size = alexvec_size(my_vec);
		maxsize = alexvec_maxsize(my_vec);
		printf("vec size = %d, vec maxsize = %d\n", size, maxsize);
	}
	for (int i = 0; i < 100; i++) {
		alexvec_pop_back(my_vec, des2);
		size = alexvec_size(my_vec);
		printf("vec size = %d, elem = %d\n", size, des2.elem);
	}
	alexvec_destroy(my_vec);
	printf("**************** struct *********************\n\n");

	getchar();
	_CrtDumpMemoryLeaks();
	return 0;
}