/*
10 12 13 15 18 19 20 25 28 29
10
29
18
17
9
30
*/
#include "stdio.h"    
#include "stdlib.h"   
 
#define HASHSIZE 10 // ����ɢ�б��� 
#define NULLKEY -32768 
 
typedef struct
{
	int *elem; // ����Ԫ�ش洢��ַ����̬�������� 
	int count; //  ��ǰ����Ԫ�ظ��� 
}HashTable;
 
int m = 0; 
		  
int Init(HashTable *H)
{
	int i;
 
	m = HASHSIZE;
	H->elem = (int *)malloc(m * sizeof(int)); //�����ڴ�
	H->count = m;
	for (i = 0; i<m; i++)
	{
		H->elem[i] = NULLKEY;
	}
	return 1;
}
 
 
int Hash(int k)
{
	return k % m;//����������
}
 
 
void Insert(HashTable *H, int k)
{
	int addr = Hash(k); 					 
	while (H->elem[addr] != NULLKEY)
	{
		addr = (addr+1) % m;//���Ŷ�ַ��
	}
	H->elem[addr] = k;
}
 
int Search(HashTable *H, int k)
{
	int addr = Hash(k); //���ϣ��ַ
 
							
	while (H->elem[addr] != k)//���Ŷ�ַ�������ͻ
	{
		addr = (addr+1) % m;
 
		if (H->elem[addr] == NULLKEY || addr == Hash(k))
			return -1;
	}
	return addr;
}
 
void Result(HashTable *H)//ɢ�б�Ԫ����ʾ
{
	int i;
	for (i = 0; i<H->count; i++)
	{
		printf("%d ", H->elem[i]);
	}
	printf("\n");
}
 
void main()
{
	int i, j, addr;
	HashTable H;
	int arr[HASHSIZE] = { NULL };
 
	Init(&H);
 
	printf("����ؼ��ּ���:\n");
	for (i = 0; i<HASHSIZE; i++)
	{
		scanf_s("%d", &arr[i]);
		Insert(&H, arr[i]);
	}
	Result(&H);
 
	printf("������Ҫ���ҵ�Ԫ�أ�\n");
	scanf_s("%d", &j);
	addr = Search(&H, j);
	if (addr == -1)
		printf("Ԫ�ز�����\n");
	else
		printf("\"%d\"Ԫ���ڱ��е�λ����:%d\n", j,addr);
 
}