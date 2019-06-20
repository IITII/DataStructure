#include<stdio.h>
#include<stdlib.h>
typedef struct hasche
{
    int* elem;
    int n;
}HashTable;
#define TRUE 1
#define FALSE 0
void insert_hasche(HashTable* has, int Case);
void hascode_1(int* code, int p, int b, int i);
void hascode_2(int* code, int p, int b, int i);
void search_hasche(HashTable has, int Case);
int main()
{
    printf("ѡ�����ϣ��ķ�ʽ\n1.һ��̽��������.\n2.����̽��������\n:");
    int Case;
    scanf("%d", &Case);
    HashTable has;
    insert_hasche(&has, Case);
    search_hasche(has, Case);
    return 0;
}
void insert_hasche(HashTable* has, int Case)
{
    int n;
    printf("�����ϣ��ĳ���:");
    scanf("%d", &n);
    has->n = n;
    has->elem = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        has->elem[i] = -1;
    }
    //printf("%d %d %d %d\n", has->elem[0], has->elem[1], has->elem[2], has->elem[3]);
    printf("����%d����ϣ���Ԫ��", n);
    int i, b;
    if (Case == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &b);
            int t = 0, * index;
            index = (int*)malloc(sizeof(int));
            hascode_1(index, n, b, t);
            while (has->elem[*index] != -1)
            {
                t++;
                hascode_1(index, n, b, t);
            }
            has->elem[*index] = b;
            //printf("%d\n", has->elem[*index]);
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &b);
            int t = 0, * index;
            index = (int*)malloc(sizeof(int));
            hascode_2(index, n, b, t);
            while (has->elem[*index] != -1)
            {
                t++;
                hascode_2(index, n, b, t);
            }
            has->elem[*index] = b;
        }
    }
}
void search_hasche(HashTable has, int Case)
{
    printf("������Ҫ��ѯ������(����0����):");
    int n;
    if (Case == 1)
    {
        while (scanf("%d", &n))
        {
            if (n == 0)
                break;
            int t = 0, *index;
            index = (int*)malloc(sizeof(int));
            hascode_1(index, has.n, n, t);
            while (has.elem[*index] != n)
            {
                t++;
                hascode_1(index, has.n, n, t);
            }
            printf("%d��%dλ��\n", n, *index);
        }
    }
    else
    {
        while (scanf("%d", &n))
        {
            if (n == 0)
                break;
            int t = 0, *index;
            index = (int*)malloc(sizeof(int));
            hascode_2(index, has.n, n, t);
            while (has.elem[*index] != n)
            {
                t++;
                hascode_2(index, has.n, n, t);
            }
            printf("%d��%dλ��\n", n, *index);
        }
    }
}
void hascode_1(int* code, int p, int b, int i)
{
    *code = (b + i) % p;
}
void hascode_2(int* code, int p, int b, int i)
{
    if (i == 0)
        * code = (b + i) % p;
    else if (i % 2 == 0)
    {
        i /= 2;
        *code = (b - (i * i)) % p;
    }
    else
    {
        i = (i + 1) / 2;
        *code = (b + (i * i)) % p;
    }
}
/*14 1 68 27 55 19 20 84 79 23 11 10 13*/