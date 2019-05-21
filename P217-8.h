//seqqueue.h
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
struct point {
    int row, col, pre;
};
typedef struct point DataType;
typedef struct {
    DataType data[MAXSIZE];
    int front, rear;
}SeqQueue, * PSeqQueue;

PSeqQueue Init_SeqQueue()
{
    PSeqQueue Q;
    Q = (PSeqQueue)malloc(sizeof(SeqQueue));
    if (Q)
    {
        Q->front = 0;
        Q->rear = 0;
    }
    return Q;
}

int Empty_SeqQueue(PSeqQueue Q)
{
    if (Q && Q->front == Q->rear)
        return 1;
    else
        return 0;
}

int In_SeqQueue(PSeqQueue Q, DataType x)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)
    {
        printf("����\n");
        return 0;
    }
    else
    {
        Q->rear = (Q->rear + 1) % MAXSIZE;
        Q->data[Q->rear] = x;
        return 1;
    }
}

int Out_SeqQueue(PSeqQueue Q, DataType * x)
{
    if (Empty_SeqQueue(Q))
    {
        printf("�ӿ�");
        return 0;
    }
    else
    {
        Q->front = (Q->front + 1) % MAXSIZE;
        *x = Q->data[Q->front];
        return 1;
    }
}

int Front_SeqQueue(PSeqQueue Q, DataType * x)
{
    if (Q->front == Q->rear)
    {
        printf("�ӿ�\n");
        return 0;
    }
    else
    {
        *x = Q->data[(Q->front + 1) % MAXSIZE];
        return 1;
    }
}
//ɾ������
void Distroy_SeqQueue(PSeqQueue * Q)
{
    if (*Q)
        free(*Q);
    *Q = NULL;
}
//������Թ������У���������ջ����ʵ�ֲ�����һ������ջ��ջ������ҵ���·��
//��Ȼ�ҵ���·���������·������������һ���˹����ܵ��㷨�������˵�˼ά��ʽ��
//����ʵ�������˽���Թ�����ķ�ʽ��
//���ö���ʵ���Թ���������ʱ������̽��·����������У�����ÿ��Ԫ�����ú�ǰ����־��
//����һֱ�������յ�ʱ������ǰ������̽������������Թ��ĵ��򣬲�����Щ������б��룬
//��һ�α����Թ����·����������ʵ���Թ��ķ�����ʵ�ʲ����У����ѿ�ʼ�����˴���Ľṹ��
//���º���һ���ʱ�䶼û��д������Թ����ҿ�ʼ��Ϊ��ֲ�����ͽṹ���Ժܺõؽ��������⣬
//���������̽��·�������ؽ��ʱ������ƿ��������Ʒ��������ṹ��������ʦ��˵��
//���ݽṹ�ľ�������ƺ��ܸ��ý������Ľṹ���ǽ������Ĺؼ����ڡ�
//https://www.cnblogs.com/a1982467767/p/8889625.html