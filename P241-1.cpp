// 实验八 内部排序.cpp: 定义控制台应用程序的入口点。
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 50000
typedef int STATUS;
typedef int ElemType;
typedef struct {//定义顺序表数据结构
    ElemType data[MAXSIZE + 1];
    int length;
}SqList;

//初始化顺序表
STATUS InitSqList(SqList* L)
{
    int i;
    for (i = 0; i < MAXSIZE; i++)
    {
        L->data[i] = -MAXSIZE;
    }
    return OK;
}

//生成length个随机数装进顺序表中
STATUS CreateRandomSqList(SqList* L, int length)
{
    int i;
    srand(time(NULL));
    for (i = 1; i <= length; i++)
    {
        L->data[i] = rand() % 1000;
    }
    L->length = length;
    return OK;
}

//打印顺序表
STATUS PrintSqList(SqList L)
{
    int i;
    for (i = 1; i <= L.length; i++)
    {
        printf("%d ", L.data[i]);
    }
    printf("\n");
    return OK;
}

//直接插入排序
STATUS InsertSort(SqList* L, int* compareTime, int* MobileTime)
{
    int i, j;
    for (i = 2; i <= L->length; i++)
    {
        (*compareTime)++;
        if (L->data[i] < L->data[i - 1])
        {
            L->data[0] = L->data[i];
            L->data[i] = L->data[i - 1];
            for (j = i - 2; j > 0 && L->data[0] < L->data[j]; j--)
            {
                (*MobileTime)++;
                L->data[j + 1] = L->data[j];
            }
            (*MobileTime)++;
            L->data[j + 1] = L->data[0];

        }
    }
    return OK;
}

//希尔排序，以步长为di
void ShellInsert(SqList* L, int di, int* compareTime, int* MobileTime)
{
    int i, j;
    for (i = di + 1; i <= L->length; i++)
    {
        (*compareTime)++;
        if (L->data[i] < L->data[i - di])
        {
            L->data[0] = L->data[i];//0号单元临时存放i号元素
            L->data[i] = L->data[i - di];
            for (j = i - di; j > 0 && L->data[0] < L->data[j]; j = j - di)//比0号元素大的都以步长di向后移
            {
                (*MobileTime)++;
                L->data[j + di] = L->data[j];
            }
            (*MobileTime)++;
            L->data[j + di] = L->data[0];//插入0号元素	
        }
    }
}

//希尔排序
STATUS ShellInsert(SqList* L, int* compareTime, int* MobileTime)
{
    int i, di;
    di = L->length / 2;//最大步长定为顺序表长度的一半，逐次降2
    for (i = di; i >= 1; i -= 2)
    {
        ShellInsert(L, i, compareTime, MobileTime);
    }
    ShellInsert(L, 1, compareTime, MobileTime);//最后还需要以步长为1做一次希尔排序
    return OK;
}

//快速排序之划分函数,会返回分割点下标
STATUS Partition(SqList* L, int low, int high, int* compareTime, int* MobileTime)
{
    L->data[0] = L->data[low];//0号位置存放一开始的low号位置元素，这个元素是要作为分割点的
    while (low < high)
    {
        (*compareTime)++;
        if (low < high && L->data[high] >= L->data[0])
        {
            high--;
        }
        (*MobileTime)++;
        L->data[low] = L->data[high];
        (*compareTime)++;
        if (low < high && L->data[low] <= L->data[0])
        {
            low++;
        }
        (*MobileTime)++;
        L->data[high] = L->data[low];
    }
    (*MobileTime)++;
    L->data[low] = L->data[0];
    return low;
}

//快速排序,多次递归调用，不断划分
STATUS FastSort(SqList* L, int low, int high, int* compareTime, int* MobileTime)
{
    int local;
    if (low < high)
    {
        local = Partition(L, low, high, compareTime, MobileTime);//local为分割点下标
        FastSort(L, low, local - 1, compareTime, MobileTime);//左半部分递归调用
        FastSort(L, local + 1, high, compareTime, MobileTime);//右半部分递归调用
    }
    return OK;
}

//冒泡排序
STATUS BubbleSort(SqList* L, int* compareTime, int* MobileTime)
{
    int i, j;
    ElemType temp;
    for (i = 1; i <= L->length; i++)
    {
        for (j = 1; j <= L->length - i; j++)
        {
            (*compareTime)++;
            if (L->data[j] > L->data[j + 1])
            {
                (*MobileTime)++;
                temp = L->data[j];
                L->data[j] = L->data[j + 1];
                L->data[j + 1] = temp;
            }
        }
    }
    return OK;
}

//堆排序,调整首尾结点
void HeapAdjust(SqList* L, int i, int length, int* compareTime, int* MobileTime)
{
    int temp = L->data[i];
    int k;
    for (k = 2 * i; k <= length; k = 2 * k)//为什么是k=2*k,因为k取2,4,8,16... 
    {
        (*compareTime)++;
        if (k + 1 <= length && L->data[k] < L->data[k + 1])
        {
            k++;
        }
        (*compareTime)++;
        if (L->data[k] > temp)// 如果发现子节点更大，则进行值的交换
        {
            (*MobileTime)++;
            L->data[i] = L->data[k];
            L->data[k] = temp;
        }
        else //如果没有比它大的子节点，直接结束循环
        {
            break;
        }
    }
}

//堆排序
STATUS HeapSort(SqList* L, int* compareTime, int* MobileTime)
{
    int i, j;
    ElemType temp;
    for (i = L->length / 2; i >= 1; i--) //for循环走完了大顶堆也已建成
    {
        HeapAdjust(L, i, L->length, compareTime, MobileTime);
    }
    for (j = L->length; j >= 1; j--)
    {
        //最大值1号元素与末尾元素对换
        (*MobileTime)++;
        temp = L->data[1];
        L->data[1] = L->data[j];
        L->data[j] = temp;
        //对换以后需要再次调整大顶堆，这次不再需要for循环来调整了，因为这次是从1开始的
        HeapAdjust(L, 1, j - 1, compareTime, MobileTime);
    }
    return OK;
}

//选择排序
STATUS SelectSort(SqList* L, int* compareTime, int* MobileTime)
{
    int min, i, j;
    ElemType temp;
    for (i = 1; i <= L->length; i++)
    {
        min = i;
        for (j = i + 1; j <= L->length; j++)
        {
            (*compareTime)++;
            if (L->data[j] < L->data[min])
            {
                min = j;
            }
        }
        (*MobileTime)++;
        temp = L->data[i];
        L->data[i] = L->data[min];
        L->data[min] = temp;
    }
    return OK;
}

//折半插入排序
STATUS HalfInsertSort(SqList* L, int* compareTime, int* MobileTime)
{
    int i, j, low, mid, high;
    for (i = 2; i <= L->length; i++)
    {
        low = 1;
        high = i - 1;
        L->data[0] = L->data[i];
        while (low < high)
        {
            mid = (low + high) / 2;
            (*compareTime)++;
            if (L->data[mid] > L->data[i])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (j = i - 1; j > low; j--)
        {
            (*MobileTime)++;
            L->data[j + 1] = L->data[j];
        }
        (*MobileTime)++;
        L->data[low] = L->data[0];
    }
    return OK;
}

void Merge(SqList* L, int begin, int mid, int end, int* compareTime, int* MobileTime)
{
    ElemType data1[MAXSIZE], data2[MAXSIZE];
    int i, j, k = begin;
    for (i = 1; i <= mid - begin + 1; i++)
    {
        data1[i] = L->data[begin + i - 1];//这里的begin + i - 1很容易写错
    }
    for (j = 1; j <= end - mid; j++)
    {
        data2[j] = L->data[mid + j];//这里的mid + i很容易写错
    }
    i = 1, j = 1;
    while (i <= mid - begin + 1 && j <= end - mid)
    {
        (*compareTime)++;
        if (data1[i] < data2[j])
        {
            (*MobileTime)++;
            L->data[k] = data1[i];
            k++, i++;
        }
        else
        {
            (*MobileTime)++;
            L->data[k] = data2[j];
            k++, j++;
        }
    }
    while (i <= mid - begin + 1)
    {
        (*MobileTime)++;
        L->data[k] = data1[i];
        k++, i++;
    }
    while (j <= end - mid)
    {
        (*MobileTime)++;
        L->data[k] = data2[j];
        k++, j++;
    }
}

void MSort(SqList* L, int begin, int end, int* compareTime, int* MobileTime)
{
    int mid;
    (*compareTime)++;
    if (begin < end)
    {
        mid = begin + (end - begin) / 2;//这里不能写成(end - begin) / 2,否则出错
        MSort(L, begin, mid, compareTime, MobileTime);
        MSort(L, mid + 1, end, compareTime, MobileTime);
        Merge(L, begin, mid, end, compareTime, MobileTime);
    }
}

//归并排序
STATUS MergeSort(SqList * L, int* compareTime, int* MobileTime)
{
    MSort(L, 1, L->length, compareTime, MobileTime);
    return OK;
}

int main()
{
    SqList L;
    int length, compareTime, MobileTime;
    double totalTime, start, end;
    InitSqList(&L);//初始化顺序表
    printf("请输入要创建的顺序表的长度：");
    scanf("%d", &length);
    printf("排序算法\t花费时间\t比较次数\t移动次数\n");

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    InsertSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("直接插入排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    ShellInsert(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("希尔排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    FastSort(&L, 1, L.length, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("快速排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    BubbleSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("冒泡排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    HeapSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("堆排序\t\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    SelectSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("选择排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    HalfInsertSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("折半插入排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    MergeSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("归并排序\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    return 0;
}

