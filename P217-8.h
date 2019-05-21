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
        printf("队满\n");
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
        printf("队空");
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
        printf("队空\n");
        return 0;
    }
    else
    {
        *x = Q->data[(Q->front + 1) % MAXSIZE];
        return 1;
    }
}
//删除队列
void Distroy_SeqQueue(PSeqQueue * Q)
{
    if (*Q)
        free(*Q);
    *Q = NULL;
}
//在求解迷宫问题中，首先是用栈的来实现操作，一步步入栈出栈，最后找到出路，
//虽然找到的路劲不是最佳路径，但是这是一种人工智能的算法，符合人的思维方式，
//是现实生活中人解决迷宫问题的方式；
//而用队列实现迷宫问题的求解时，依次探索路径放入队列中，并对每个元素设置好前驱标志，
//这样一直遍历到终点时，按照前驱进行探索，输出整个迷宫的倒序，并对这些坐标进行编码，
//再一次遍历迷宫输出路径，即队列实现迷宫的方法；实际操作中，我已开始设置了错误的结构，
//导致好了一天的时间都没有写完这个迷宫，我开始认为多分叉的树型结构可以很好地解决这个问题，
//但是在最后探索路劲并返回结果时出现了瓶颈，最后推翻了整个结构，正如老师所说，
//数据结构的精髓是设计好能更好解决问题的结构，是解决问题的关键所在。
//https://www.cnblogs.com/a1982467767/p/8889625.html