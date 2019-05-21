/*测试用例
{{{{{{{{{{(((((((((([[[[[[[[[[]]]]]]]]]]))))))))))}}}}}}}}}}
({[]})
(([[]]}}))
(){}[]*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define INCREASE 10
/**
* 栈节点
*/
typedef struct {
	int* base;
	int* top;
	int size;
}OPTR;
/*创建栈*/
void createOPTR(OPTR &L){
	L.base = (int *)malloc(sizeof(int) * STACK_INIT_SIZE);
	if (!L.base)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	L.top = L.base;
	L.size = STACK_INIT_SIZE;
}
/*删除栈*/
void distory(OPTR& L) {
	free(L.base);
	L.top = NULL;
	L.base = NULL;
	L.size = 0;
}
/*入栈*/
void push(OPTR &L, char &i){
	if (L.top - L.base >= L.size)
	{
		L.base = (int*)realloc(L.base, (STACK_INIT_SIZE + INCREASE) * sizeof(int));
		if (!L.base)
		{
			printf("内存分配失败！\n");
			exit(1);
		}
	}
	//先自增一，再解引用进行赋值
	*L.top++ = i;
}
/*出栈*/
char pop(OPTR &L){
	if (L.top == L.base)
	{
		printf("栈为空！\n");
		exit(1);
	}
	else
		//先解引用，再减一
		return *--L.top;
}
/*检查括号匹配情况*/
void check(OPTR L,char i) {
	while (i && i != '\n')
	{
		if (i == '(' || i == '[' || i == '{')
			push(L, i);
		if (i == (char)')' || i == (char)']' || i == (char)'}') {
			char k = pop(L);
			switch (i)
			{
			case ')': if (k == '(')
				printf("Checked\"()\"\n");
					  else {
				printf("Mismatch \")\"\n");
				exit(1);
			}
                      break;
			case ']': if (k == '[')
				printf("Checked\"[]\"\n");
					  else {
				printf("Mismatch \"]\"\n");
				exit(1);
			}
					  break;
			case '}': if (k == '{')
				printf("Checked\"{}\"\n");
					  else {
				printf("Mismatch \"}\"\n");
				exit(1);
			}
					  break;
			}
		}
		scanf("%c", &i);
	}
}
int main() {
	OPTR L;
	createOPTR(L);
	printf("请输入包括\"(\" \"[\" \"{\" 的算数表达式：\n");
	char i = NULL;
	scanf("%c", &i);
	//getchar();
	check(L, i);
	return 0;
}