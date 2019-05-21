/*��������
A: 4 5
B: 4 5
4 5
5 5
4 4
*/
#include "bits/stdc++.h"
#define MAXSIZE 100
#define MAX_ROW_NUM 50
#define MAXRC 50
typedef int ElemType;
typedef struct
{
    int i = 0;        
    int j = 0;        
    ElemType d = 0;     

} Triple; 
typedef struct
{
    int mu = 0, nu = 0, tu = 0;
    Triple data[MAXSIZE + 1];

} TSMatrix;

//�������У�����ϡ�����,���������Ԫ��洢
int createMatrix(int row,int column,TSMatrix &M){
    int d[100];
    int A[10][10];
    srand(time(NULL));
    int n = 100;
    for (int i = 0; i < n; i++)
        d[i] = i;
    for (int i = n; i > 0; i--)
    {
        int a = i - 1;
        int b = rand() % i;
        if (a != b)
        {
            int t = d[a];
            d[a] = d[b];
            d[b] = t;
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            A[i][j] = (d[i * 10 + j] >= 50) ? 1 : 0;
            //printf("%d ", A[i][j]);
            if (A[i][j] != 0)
            {
                ++M.tu;
                M.data[M.tu].i = i+1;
                M.data[M.tu].j = j+1;
                M.data[M.tu].d = A[i][j];
            }
        }
        //printf("\n");
    }
    M.mu = row;
    M.nu = column;
    return 0;
}
//print the Triad
void printTriad(TSMatrix &M) {
        int i;
        if (M.tu <= 0)
        {
            return;
        }
        printf("����:%d ����:%d Ԫ�ظ���:%d\n", M.mu, M.nu, M.tu);
        printf("i\tj\td\n");
        for (i = 1; i <= M.tu; i++)
        {
            printf("%d\t%d\t%d\n", M.data[i].i, M.data[i].j, M.data[i].d);
        }
}
//fastzz
int TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    T.mu = M.nu; T.nu = M.mu; T.tu = M.tu;
    int num[25], cpot[25],col,q;
    if (T.tu) {
        //��ʼ��
        for (col = 1; col <= M.tu; col++)
            num[col] = 0;
        //�����Ԫ����
        for (int t = 0; t <= M.tu; t++)
            ++num[M.data[t].j];
        //���һ������Ԫ�����
        cpot[1] = 1;
        for (col = 2; col <= M.tu; ++col)
            cpot[col] = cpot[col - 1] + num[col - 1];
        //ת��
        for (int p = 1; p <= M.tu; ++p)
        {
            col = M.data[p].j;
            q = cpot[col];
            T.data[q].i = M.data[p].j;
            T.data[q].j = M.data[p].i;
            T.data[q].d = M.data[p].d;
            ++cpot[col];
        }
    }
        //int p, q = 1, v;/*qΪM.data���±�*/
        //T.mu = M.nu; T.nu =M.mu; T.tu= M.tu;
        //if (M.tu != 0)
        //{
        //    for (v = 1; v <= M.nu; v++)/*T.data[q]�еļ�¼��c��Ĵ�������*/
        //        for (p = 1; p <= M.tu; p++)/*pΪM.data���±�*/
        //            if (M.data[p].j == v)
        //            {
        //                T.data[q].i = M.data[p].j;
        //                T.data[q].j = M.data[p].i;
        //                T.data[q].d = M.data[p].d;
        //                q++;
        //            }
        //}
    return 0;
    
}
//��ӡһ��ϡ�����
void Print(TSMatrix *M){
         
    {
        int i, j;
        int t = 1;
        for (i = 1; i <= M->mu; i++)
        {
            for (j = 1; j <= M->nu; j++)
            {
                if (M->data[t].i == i && M->data[t].j == j)
                {
                    printf("%d ", M->data[t].d);
                    t++;
                }
                else printf("0 ");
            }
            printf("\n");
        }
    }
  
}
//void getMatrix(TSMatrix M, int** &A) {
//    int t = 1;
//    for (int i = 1; i <= M.mu; i++)
//    {
//        for (int j = 1; j <= M.nu; j++) {
//            if (M.data[t].i == i && M.data[t].j==j)
//            {
//                (A)[i][j] = M.data[t].d;
//            }
//            else
//                (A)[i][j] = 0;
//        }
//    }
//   
//}
////����ϡ��������
//int MultMatrix(TSMatrix M,TSMatrix N, TSMatrix &T){
//    int **A,**B,**Q;
//    
//
//    getMatrix(M, A);
//    getMatrix(N, B);
//    if (M.mu = N.nu)
//    {
//        for (int i = 1; i < M.mu; i++)
//        {
//            for (int j = 0; j < N.nu; j++)
//            {
//                for (int k = 1; k <= M.nu; ++k) {
//                    Q[i][j] += A[i][k] * B[k][j];
//                }
//            }
//        }
//    }
//    else
//        return 1;
//    for (int i = 1; i <= M.mu; i++)
//    {
//        for (int j = 1; j <= N.nu; j++)
//        {
//            
//            if (Q[i][j] != 0)
//            {
//                ++T.tu;
//                T.data[T.tu].i = i + 1;
//                T.data[T.tu].j = j + 1;
//                T.data[T.tu].d = Q[i][j];
//            }
//        }
//    }
//    T.mu = M.mu;
//    T.nu = N.nu;
//    return 0;
//}
//�����������
int AddTSMatrix(TSMatrix* TC, TSMatrix A, TSMatrix B) {
    if (!(A.mu == B.mu && A.nu == B.nu))
    {
        printf("������Ӿ�������в���ȣ��������û�����壡\n");
        exit(1);
    }
    //�ȱȽ��У���һ��ֱ�Ӹ�ֵ��һ���Ƚ��У��в�һ��ֱ�Ӹ�ֵ��һ������ӡ��������Ԫ�ؾ�ֱ�Ӹ�ֵ
    //ai, bi, ci, aj, bj, cj, ap, bp, cpΪA��B��TC���У��� �� ��ЧԪ�� ����
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
                TC->data[cp].d = B.data[bp].d;
                ++bp;
                ++cp;
            }
        }
        else if (ai < bi) {
            ci = ai;
            while (ci == A.data[ap].i) {
                TC->data[cp].i = ci;
                TC->data[cp].j = A.data[ap].j;
                TC->data[cp].d = A.data[ap].d;
                ++ap;
                ++cp;
            }
        }
        else if (ai == bi) {
            ci = ai;
            aj = A.data[ap].j;
            bj = B.data[bp].j;
            if (aj > bj) {
                TC->data[cp].i = ci;
                TC->data[cp].j = bj;
                TC->data[cp].d = B.data[bp].d;
                ++cp;
                ++bp;
            }
            else if (aj < bj) {
                TC->data[cp].i = ci;
                TC->data[cp].j = aj;
                TC->data[cp].d = A.data[ap].d;
                ++cp;
                ++ap;
            }
            else if (aj == bj) {
                if (A.data[ap].d + B.data[bp].d != 0) {
                    TC->data[cp].i = ci;
                    TC->data[cp].j = aj;
                    TC->data[cp].d = A.data[ap].d + B.data[bp].d;
                    ++cp;
                }
                ++ap;
                ++bp;
            }
        }
    }

    //ϡ�����A��B�е�Ԫ�ز���ʣ������
    while (ap <= A.tu) {
        TC->data[cp].i = A.data[ap].i;
        TC->data[cp].j = A.data[ap].j;
        TC->data[cp].d = A.data[ap].d;
        ++cp;
        ++ap;
    }
    while (bp <= B.tu) {
        TC->data[cp].i = B.data[bp].i;
        TC->data[cp].j = B.data[bp].j;
        TC->data[cp].d = B.data[bp].d;
        ++cp;
        ++bp;
    }
    TC->tu = --cp;
    return 0;
}
void TSMatrix_add(TSMatrix n, TSMatrix m, TSMatrix* z) {
    int flag[25][25];
    memset(flag, 0, sizeof(flag));
    if (!(m.mu == n.mu && m.nu==n.nu))
    {
        printf("������Ӿ�������в���ȣ��������û�����壡\n");
        exit(1);
    }
    z->mu = n.mu;
    z->nu = n.nu;
    //z->tu = n.tu;
    for (int i = 0; i < n.tu; i++) {
        z->data[i].i = n.data[i].i;
        z->data[i].j = n.data[i].j;
        z->data[i].d = n.data[i].d;
        flag[n.data[i].i][n.data[i].j] = 1;
    }
    int t = n.tu,count=0;
    for (int i = 0; i < m.tu; i++) {
        if (flag[m.data[i].i][m.data[i].j] == 0) {
            z->data[t].i = m.data[i].i;
            z->data[t].j = m.data[i].j;
            z->data[t].d = m.data[i].d;
            t++;
        }
        else {
            for (int j = 0; j < t; j++) {
                if (z->data[j].i == m.data[i].i && z->data[j].j == m.data[i].j) {
                    z->data[j].d += m.data[i].d;
                    count++;
                    break;
                }
            }
        }
    }
    //z->tu =n.tu+m.tu-count;
    z->tu = t;
    return;
}

int main()
{
    int i=0, j=0,m=0,n=0;
    TSMatrix A, B,Q,I;
    printf("�������A�����У�\n");
    scanf("%d %d", &i, &j);
    createMatrix(i, j, A);
    printf("�������B�����У�\n");
    scanf("%d %d", &m, &n);
    createMatrix(m, n, B);
    printf("A:\n");
    printTriad(A);
    Print(&A);
    printf("B:\n");
    printTriad(B);
    Print(&B);
    printf("A��ת�þ������Ԫ��\n");
    TransposeSMatrix(A, I);
    printTriad(I);
    Print(&I);
    printf("A+B�Ľ����\n");
    //TSMatrix_add(A, B,&Q);
    AddTSMatrix(&Q, A, B);
    //TSMatrix_add(A, B, &I);
   // MultMatrix(A, B, I);
    printTriad(Q);
    Print(&Q);
    //printTriad(I);
    //Print(&I);
    /*createMatrix(7, 8,B);
    printTriad(B);*/
    return 0;
}