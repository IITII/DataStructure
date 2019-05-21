//maze_queue.cpp
#include<stdio.h>
#include<stdlib.h>
//#include<cctype>
#include"P217-8.h"

#define MAX_ROW  12
#define MAX_COL  14

int maze[12][14] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1,
    1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void print_line(void)
{
    int i, j;
    printf("迷宫如下‘■’代表墙,数字 或者‘☆’表示路径\n");
    for (i = 0; i < MAX_ROW; i++) {
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1)       printf("■");
            else if (maze[i][j] >= 3) {
                printf("%2d", maze[i][j] - 2);
                /*if (i == MAX_ROW-2 && j == MAX_COL-2)  printf("★");
                else                   printf("☆");*/
            }
            else  printf("  ");
        printf("\n");
    }
    printf("已找到出路...\n");
    printf("可见，用队列求解迷宫问题，可以找出一条最短路径\n");
}

void visit(int row, int col, PSeqQueue S)
{
    struct point visit_point = { row, col, S->front };
    maze[row][col] = 2;
    In_SeqQueue(S, visit_point);
}

int main()
{
    struct point p = { 1, 1, -1 };//第一个点前驱设为-1，以便后面打印迷宫
    maze[p.row][p.col] = 2;//遍历过的点设置为2
    PSeqQueue S = Init_SeqQueue();
    In_SeqQueue(S, p);
    while (!Empty_SeqQueue(S))
    {
        Out_SeqQueue(S, &p);
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)
            break;
        if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0)
            visit(p.row, p.col + 1, S);
        if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0)
            visit(p.row + 1, p.col, S);
        if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0)
            visit(p.row, p.col - 1, S);
        if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0)
            visit(p.row - 1, p.col, S); //以上是对迷宫的四个方向进行操作
    }
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//是否为出口
    {
        int count = 3;
        struct point q = { p.row, p.col, p.pre };
        while (q.pre != -1)//按照前驱进行查找
        {
            q = S->data[q.pre];
            count++;
        }
        printf("成功找到最短路径，路径倒序输出：\n");
        printf("(%d,%d)\n", p.row, p.col);
        maze[p.row][p.col] = count;
        while (p.pre != -1)//按照前驱进行查找
        {
            count--;
            p = S->data[p.pre];
            maze[p.row][p.col] = count;
            printf("(%d,%d)\n", p.row, p.col);
        }
        //printf("三秒后打印路径......\n");
        //Sleep(3000);
        print_line();
    }

    else {
        printf("没有出路\n");
    }

    system("pause");
    return 0;
}
//end maze_queue.cpp