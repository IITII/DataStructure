#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
//链表结构体
typedef struct node
{
    int data;
    struct node *next;
} LNODE, *LinkList;
/**
 * 创建链表头节点
 * 初始化链表
 * @parma L 需要被初始化的链表
*/
void InitList(LinkList *L)
{
    (*L) = (LinkList)malloc(sizeof(LNODE));
    (*L)->next = NULL;
}
/**
 * 将数据填入链表中
 * @parma L 需要填入数据的链表
 * @parma items 填入数据的总个数
*/
void Insert(LinkList L)
{
    size_t i, items;
    printf("请输入您想插入的数据的个数:\n");
    scanf("%llu", &items);
    printf("请输入您想插入的数据:\n");
    for (i = 0; i < items; i++)
    {
        LinkList p = (LinkList)malloc(sizeof(LNODE));
        if (p == NULL)
            printf("malloc()函数调用失败，可能已无可用内存空间！");
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
 * 打印链表
 * @param L 需要打印的链表
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
 * 链表去重
 * @parma L 需要进行去重操作的链表
 * @return 0 非递增有序 （3，2，2，1）
 * @return 1 非递减有序（1， 2，2，3）
*/
int DupRm(LinkList L)
{
    LinkList p = L->next;
    //判断链表顺序
    while (p != NULL && p->next != NULL)
    {
        if (p->data < p->next->data)
            return 1;
        p = p->next;
    }
    //去重
    //指针归位
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
 * 反转链表
 * @parma L 需要进行反转的链表
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
        printf("该链表不是非递增有序链表。\n");
    return 0;
}