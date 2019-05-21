#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
//����ṹ��
typedef struct node
{
    int data;
    struct node *next;
} LNODE, *LinkList;
/**
 * ��������ͷ�ڵ�
 * ��ʼ������
 * @parma L ��Ҫ����ʼ��������
*/
void InitList(LinkList *L)
{
    (*L) = (LinkList)malloc(sizeof(LNODE));
    (*L)->next = NULL;
}
/**
 * ����������������
 * @parma L ��Ҫ�������ݵ�����
 * @parma items �������ݵ��ܸ���
*/
void Insert(LinkList L)
{
    size_t i, items;
    printf("�����������������ݵĸ���:\n");
    scanf("%llu", &items);
    printf("������������������:\n");
    for (i = 0; i < items; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(LNODE));
        if (p == NULL)
            printf("malloc()��������ʧ�ܣ��������޿����ڴ�ռ䣡");
        if (L->data == NULL)
            L = p;
        else
        {
            LinkList cur = L;
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = p;
            scanf("%d", &p->data);
            p->next = NULL;
        }
    }
}
/**
 * ��ӡ����
 * @param L ��Ҫ��ӡ������
*/
void print(LinkList L)
{
    LinkList p = L->next;
    while (p)
    {
        printf(p->next == NULL ? "%d\n" : "%d ", p->data);
        p = p->next;
    }
}
/**
 * ����ȥ��
 * @parma L ��Ҫ����ȥ�ز���������
 * @return 0 �ǵ������� ��3��2��2��1��
 * @return 1 �ǵݼ�����1�� 2��2��3��
*/
int DupRm(LinkList L)
{
    LinkList p = L->next;
    //�ж�����˳��
    while (p != NULL && p->next != NULL)
    {
        if (p->data < p->next->data)
            return 1;
        p = p->next;
    }
    //ȥ��
    //ָ���λ
    p = L->next;
    while (p != NULL && p->next != NULL)
    {
        if (p->data == p->next->data)
        {
            LinkList q = p->next;
            p->next = p->next->next;
            free(q);
        }
        else
            p = p->next;
    }
    return 0;
}
/**
 * ��ת����
 * @parma L ��Ҫ���з�ת������
*/
void reverse(LinkList L)
{
    LinkList p, q, pr;
    p = L->next;
    q = NULL;
    L->next = NULL;
    while (p)
    {
        pr = p->next;
        p->next = q;
        q = p;
        p = pr;
    }
    L->next = q;
}

int main()
{
    LinkList L = NULL;
    InitList(&L);
    Insert(L);
    print(L);
    int i = DupRm(L);
    if (i != 1)
    {
        print(L);
        reverse(L);
        print(L);
    }
    else
        printf("�������Ƿǵ�����������\n");
    return 0;
}