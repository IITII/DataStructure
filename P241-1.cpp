#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define MAXSIZE 5000
typedef struct {
    int key;
    int otherinfo;
}RedType;
typedef struct {
    RedType* r;
    int length;
}SqList;
int InitSqList(SqList* L) {
    L->r = (RedType*)malloc((MAXSIZE + 1) * sizeof(RedType));
    if (!L->r)
        exit(-1);
    L->length = 0;
    return 1;
}

int ShellInsert(SqList *L,int dk){
    int i, j;
    for (i = dk + 1; i < L->length; i++) {
        if (L->r[i].key < L->r[i - dk].key) {
            L->r[0] = L->r[i];
            for ( j = i-dk;j>0&&(L->r[0].key<L->r[j].key); j-=dk)
            {
                L->r[j + dk] = L->r[j];
            }
            L->r[j + dk] = L->r[0];
        }
    }
    return 1;
}
int ShellSort(SqList* L, int dlta[], int t) {
    int k;
    if (!L->length) {
        printf("SqList Empty!\n");
        return 0;
    }
    for (k = 0; k < t; k++)
        ShellInsert(L, dlta[k]);
    return 1;
}

int InsertSort(SqList* L) {
    int i, j;
    if (!L->length) {
        printf("The SqList is empty!\n");
        return 0;
    }
    for (i=2;i<=L->length;i++)
    {
        if (L->r[i].key<L->r[i-1].key)
        {
            L->r[0] = L->r[i];
            for ( j =i- 2;L->r[0].key<L->r[j].key; j--)
            {
                L->r[j + 1] = L->r[j];
            }
            L->r[j + 1] = L->r[0];
        }
    }
    return 1;
}
int Part(SqList* L, int low, int high) {
    int pk;
    L->r[0] = L->r[low];
    pk = L->r[low].key;
    while (low<high)
    {
        while (low < high && L->r[high].key >= pk) {
            high--;
        }
        L->r[low] = L->r[high];
        while (low<high&&L->r[high].key<=pk)
        {
            low++;
        }
        L->r[high] = L->r[low];
    }
    L->r[low] = L->r[0];
    return low;
}
int QSort(SqList* L, int low, int high) {
    int pk;
    if (low < high) {
        pk = Part(L, low, high);
        QSort(L, low, pk - 1);
        QSort(L, pk + 1, high);
    }
}
int QuickSort(SqList *L){
    if (!L->length) {
        printf("The SqList is empty!\n");
        return 0;
    }
    QSort(L, 1, L->length);
    return 1;
}

int HeapAdjust(SqList* H, int s, int m) {
    int j;
    H->r[0] = H->r[s];
    for (j=2*s; j <= m;j*=2)
    {
        if (j < m && H->r[j].key < H->r[j + 1].key)
            j++;
        if (H->r[0].key > H->r[j].key)
            break;
        H->r[s] = H->r[j];
        s = j;
    }
    H->r[s] = H->r[0];
    return 1;
}
int HeapSort(SqList* H) {
    int i;
    if(!H->length) {
        printf("The SqList is empty!\n");
        return 0;
    }
    for (i = H->length / 2; i > 0; i--)
        HeapAdjust(H, i, H->length);
    for(i = H->length; i > 1; i--)
    {

    }
}

int  main() {

}