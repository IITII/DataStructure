#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 1000  //非零元个数最大值
#define MAXROW 1000    //最大行数

typedef int Status;
typedef int ElemType;
typedef struct {
  int i, j;  //行列下标
  ElemType e;
} Triple;
typedef struct {
  Triple data[MAXSIZE + 1];
  int mu, nu, tu;
} TSMatrix;

Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T);   //快速转置三元组
Status Destroy(int ***, int, int);                      //销毁二维矩阵
Status creat(int ***, int, int);                        //创建二维矩阵
Status Transform(int **A, int m, int n, TSMatrix *T);   //转换成三元组
Status ReTransform(int ***, int m, int n, TSMatrix T);  //三元组转回矩阵
Status AddTSMatrix(TSMatrix *Tc, TSMatrix Ta, TSMatrix Tb);  //两个三元组相加
Status displayMatrix(int **, int m, int n);                  //打印矩阵
Status displayTriple(TSMatrix T);                            //打印三元组

int main() {
  int i, n, m, **A, **B, **C;
  TSMatrix Ta, Tb, Tc;
  srand(time(NULL));

  //	freopen("input1.txt","r",stdin);
  printf("请输入矩阵行列(用空格隔开)：\n");
  scanf("%d%d", &m, &n);

  creat(&A, m, n);  //生成矩阵A
  creat(&B, m, n);  //生成矩阵B

  Transform(A, m, n, &Ta);  //转换三元组
  Transform(B, m, n, &Tb);

  printf("A矩阵\n");
  displayMatrix(A, m, n);  //打印矩阵以及转换后的三元组
  displayTriple(Ta);

  printf("B矩阵\n");
  displayMatrix(B, m, n);  //打印矩阵以及转换后的三元组
  displayTriple(Tb);

  AddTSMatrix(&Tc, Ta, Tb);
  creat(&C, m, n);
  //创建空间存放三元组转矩阵
  ReTransform(&C, m, n, Tc);  //转矩阵
  printf("A+B矩阵\n");
  displayMatrix(C, m, n);  //打印矩阵以及转换后的三元组
  displayTriple(Tc);

  FastTransposeSMatrix(Ta, &Ta);  //快速转置三元组
  //因为动态分配的问题，原来的数组A是m*n的，我们需要一个n行m列的
  Destroy(&A, m, n);
  creat(&A, n, m);
  //重新创建
  ReTransform(&A, n, m, Ta);  //三元组转矩阵
  printf("转置的A矩阵\n");
  displayMatrix(A, n, m);  //打印矩阵以及转换后的三元组 ,转置后交换m,n
  displayTriple(Ta);

  Destroy(&A, n, m);  //此时A数组是n*m
  Destroy(&B, m, n);  //销毁数组B

  return 0;
}

Status displayMatrix(int **A, int m, int n) {
  int i, j;
  printf("该矩阵为：\n");
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) printf("%d ", A[i][j]);
    printf("\n");
  }
  printf("\n");
  return OK;
}

Status displayTriple(TSMatrix T) {
  int i;
  printf("该矩阵三元组为:\n");
  for (i = 1; i <= T.tu; i++)
    printf("第%d行，第%d列，值=%d\n", T.data[i].i, T.data[i].j, T.data[i].e);

  printf("\n");
  return OK;
}

Status AddTSMatrix(TSMatrix *TC, TSMatrix A, TSMatrix B) {
  int ai, bi, ci, aj, bj, cj, ap, bp, cp;
  ap = bp = cp = 1;
  TC->mu = A.mu;
  TC->nu = A.nu;
  while (ap <= A.tu && bp <= B.tu) {
    ai = A.data[ap].i;
    bi = B.data[bp].i;
    if (ai > bi) {
      ci = bi;
      while (ci == B.data[bp].i) {
        TC->data[cp].i = ci;
        TC->data[cp].j = B.data[bp].j;
        TC->data[cp].e = B.data[bp].e;
        ++bp;
        ++cp;
      }
    } else if (ai < bi) {
      ci = ai;
      while (ci == A.data[ap].i) {
        TC->data[cp].i = ci;
        TC->data[cp].j = A.data[ap].j;
        TC->data[cp].e = A.data[ap].e;
        ++ap;
        ++cp;
      }
    } else if (ai == bi) {
      ci = ai;
      aj = A.data[ap].j;
      bj = B.data[bp].j;
      if (aj > bj) {
        TC->data[cp].i = ci;
        TC->data[cp].j = bj;
        TC->data[cp].e = B.data[bp].e;
        ++cp;
        ++bp;
      } else if (aj < bj) {
        TC->data[cp].i = ci;
        TC->data[cp].j = aj;
        TC->data[cp].e = A.data[ap].e;
        ++cp;
        ++ap;
      } else if (aj == bj) {
        if (A.data[ap].e + B.data[bp].e != 0) {
          TC->data[cp].i = ci;
          TC->data[cp].j = aj;
          TC->data[cp].e = A.data[ap].e + B.data[bp].e;
          ++cp;
        }
        ++ap;
        ++bp;
      }
    }
  }

  //稀疏矩阵A或B中的元素部分剩余的情况
  while (ap <= A.tu) {
    TC->data[cp].i = A.data[ap].i;
    TC->data[cp].j = A.data[ap].j;
    TC->data[cp].e = A.data[ap].e;
    ++cp;
    ++ap;
  }
  while (bp <= B.tu) {
    TC->data[cp].i = B.data[bp].i;
    TC->data[cp].j = B.data[bp].j;
    TC->data[cp].e = B.data[bp].e;
    ++cp;
    ++bp;
  }
  TC->tu = --cp;
  return OK;
}

Status ReTransform(int ***A, int m, int n, TSMatrix T) {
  int i, j;
  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++) (*A)[i][j] = 0;  //初始化
  for (i = 1; i <= T.tu; i++)
    (*A)[T.data[i].i][T.data[i].j] = T.data[i].e;  //转换
  return OK;
}

Status Transform(int **A, int m, int n, TSMatrix *T) {
  int i, j, len;
  T->mu = m;
  T->nu = n;
  T->tu = 0;

  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++)
      if (A[i][j] != 0)  //非空，转换成三元组
      {
        T->tu++;
        T->data[T->tu].e = A[i][j];
        T->data[T->tu].i = i;
        T->data[T->tu].j = j;
      }
  return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T)  //三元组转置
{
  int col, t, p, q;
  int num[MAXROW + 1], cpot[MAXROW + 1];

  T->mu = M.nu;
  T->nu = M.mu;
  T->tu = M.tu;  //初始数据

  if (T->tu) {
    for (col = 1; col <= M.nu; col++) num[col] = 0;
    for (t = 1; t <= M.tu; t++) ++num[M.data[t].j];
    cpot[1] = 1;

    for (col = 2; col <= M.nu; col++) cpot[col] = cpot[col - 1] + num[col - 1];
    for (p = 1; p <= M.tu; p++) {
      col = M.data[p].j;
      q = cpot[col];
      T->data[q].i = M.data[p].j;
      T->data[q].j = M.data[p].i;
      T->data[q].e = M.data[p].e;
      ++cpot[col];
    }
  }
  return OK;
}

Status Destroy(int ***MAZE, int m, int n)  //销毁
{
  int i;
  for (i = 0; i <= m + 1; i++) free(*((*MAZE) + i));
  return OK;
}

Status creat(int ***MAZE, int m, int n)  //构造矩阵 m行，n列
{
  int i, j, t;

  *MAZE = (int **)malloc((m + 2) * sizeof(int *));
  for (i = 0; i <= m + 1; i++)
    (*MAZE)[i] = (int *)malloc((n + 2) * sizeof(int));

  for (i = 0; i <= m + 1; i++)
    for (j = 0; j <= n + 1; j++) (*MAZE)[i][j] = 0;
  /*
  for (i=1;i<=m;i++)
  {
          for (j=1;j<=n;j++)
          {
                  t=rand()%1000; //随机生成 if (t>700)
                  (*MAZE)[i][j]=t;
          }
  }*/

  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      scanf("%d", &t);
      (*MAZE)[i][j] = t;
    }
  }
  return OK;
}
