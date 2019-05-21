/*��������
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
* ջ�ڵ�
*/
typedef struct {
	int* base;
	int* top;
	int size;
}OPTR;
/*����ջ*/
void createOPTR(OPTR &L){
	L.base = (int *)malloc(sizeof(int) * STACK_INIT_SIZE);
	if (!L.base)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	L.top = L.base;
	L.size = STACK_INIT_SIZE;
}
/*ɾ��ջ*/
void distory(OPTR& L) {
	free(L.base);
	L.top = NULL;
	L.base = NULL;
	L.size = 0;
}
/*��ջ*/
void push(OPTR &L, char &i){
	if (L.top - L.base >= L.size)
	{
		L.base = (int*)realloc(L.base, (STACK_INIT_SIZE + INCREASE) * sizeof(int));
		if (!L.base)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			exit(1);
		}
	}
	//������һ���ٽ����ý��и�ֵ
	*L.top++ = i;
}
/*��ջ*/
char pop(OPTR &L){
	if (L.top == L.base)
	{
		printf("ջΪ�գ�\n");
		exit(1);
	}
	else
		//�Ƚ����ã��ټ�һ
		return *--L.top;
}
/*�������ƥ�����*/
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
	printf("���������\"(\" \"[\" \"{\" ���������ʽ��\n");
	char i = NULL;
	scanf("%c", &i);
	//getchar();
	check(L, i);
	return 0;
}