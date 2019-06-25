// ʵ��� �ڲ�����.cpp: �������̨Ӧ�ó������ڵ㡣
//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 50000
typedef int STATUS;
typedef int ElemType;
typedef struct {//����˳������ݽṹ
    ElemType data[MAXSIZE + 1];
    int length;
}SqList;

//��ʼ��˳���
STATUS InitSqList(SqList* L)
{
    int i;
    for (i = 0; i < MAXSIZE; i++)
    {
        L->data[i] = -MAXSIZE;
    }
    return OK;
}

//����length�������װ��˳�����
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

//��ӡ˳���
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

//ֱ�Ӳ�������
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

//ϣ�������Բ���Ϊdi
void ShellInsert(SqList* L, int di, int* compareTime, int* MobileTime)
{
    int i, j;
    for (i = di + 1; i <= L->length; i++)
    {
        (*compareTime)++;
        if (L->data[i] < L->data[i - di])
        {
            L->data[0] = L->data[i];//0�ŵ�Ԫ��ʱ���i��Ԫ��
            L->data[i] = L->data[i - di];
            for (j = i - di; j > 0 && L->data[0] < L->data[j]; j = j - di)//��0��Ԫ�ش�Ķ��Բ���di�����
            {
                (*MobileTime)++;
                L->data[j + di] = L->data[j];
            }
            (*MobileTime)++;
            L->data[j + di] = L->data[0];//����0��Ԫ��	
        }
    }
}

//ϣ������
STATUS ShellInsert(SqList* L, int* compareTime, int* MobileTime)
{
    int i, di;
    di = L->length / 2;//��󲽳���Ϊ˳����ȵ�һ�룬��ν�2
    for (i = di; i >= 1; i -= 2)
    {
        ShellInsert(L, i, compareTime, MobileTime);
    }
    ShellInsert(L, 1, compareTime, MobileTime);//�����Ҫ�Բ���Ϊ1��һ��ϣ������
    return OK;
}

//��������֮���ֺ���,�᷵�طָ���±�
STATUS Partition(SqList* L, int low, int high, int* compareTime, int* MobileTime)
{
    L->data[0] = L->data[low];//0��λ�ô��һ��ʼ��low��λ��Ԫ�أ����Ԫ����Ҫ��Ϊ�ָ���
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

//��������,��εݹ���ã����ϻ���
STATUS FastSort(SqList* L, int low, int high, int* compareTime, int* MobileTime)
{
    int local;
    if (low < high)
    {
        local = Partition(L, low, high, compareTime, MobileTime);//localΪ�ָ���±�
        FastSort(L, low, local - 1, compareTime, MobileTime);//��벿�ֵݹ����
        FastSort(L, local + 1, high, compareTime, MobileTime);//�Ұ벿�ֵݹ����
    }
    return OK;
}

//ð������
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

//������,������β���
void HeapAdjust(SqList* L, int i, int length, int* compareTime, int* MobileTime)
{
    int temp = L->data[i];
    int k;
    for (k = 2 * i; k <= length; k = 2 * k)//Ϊʲô��k=2*k,��Ϊkȡ2,4,8,16... 
    {
        (*compareTime)++;
        if (k + 1 <= length && L->data[k] < L->data[k + 1])
        {
            k++;
        }
        (*compareTime)++;
        if (L->data[k] > temp)// ��������ӽڵ���������ֵ�Ľ���
        {
            (*MobileTime)++;
            L->data[i] = L->data[k];
            L->data[k] = temp;
        }
        else //���û�б�������ӽڵ㣬ֱ�ӽ���ѭ��
        {
            break;
        }
    }
}

//������
STATUS HeapSort(SqList* L, int* compareTime, int* MobileTime)
{
    int i, j;
    ElemType temp;
    for (i = L->length / 2; i >= 1; i--) //forѭ�������˴󶥶�Ҳ�ѽ���
    {
        HeapAdjust(L, i, L->length, compareTime, MobileTime);
    }
    for (j = L->length; j >= 1; j--)
    {
        //���ֵ1��Ԫ����ĩβԪ�ضԻ�
        (*MobileTime)++;
        temp = L->data[1];
        L->data[1] = L->data[j];
        L->data[j] = temp;
        //�Ի��Ժ���Ҫ�ٴε����󶥶ѣ���β�����Ҫforѭ���������ˣ���Ϊ����Ǵ�1��ʼ��
        HeapAdjust(L, 1, j - 1, compareTime, MobileTime);
    }
    return OK;
}

//ѡ������
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

//�۰��������
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
        data1[i] = L->data[begin + i - 1];//�����begin + i - 1������д��
    }
    for (j = 1; j <= end - mid; j++)
    {
        data2[j] = L->data[mid + j];//�����mid + i������д��
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
        mid = begin + (end - begin) / 2;//���ﲻ��д��(end - begin) / 2,�������
        MSort(L, begin, mid, compareTime, MobileTime);
        MSort(L, mid + 1, end, compareTime, MobileTime);
        Merge(L, begin, mid, end, compareTime, MobileTime);
    }
}

//�鲢����
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
    InitSqList(&L);//��ʼ��˳���
    printf("������Ҫ������˳���ĳ��ȣ�");
    scanf("%d", &length);
    printf("�����㷨\t����ʱ��\t�Ƚϴ���\t�ƶ�����\n");

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    InsertSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("ֱ�Ӳ�������\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    ShellInsert(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("ϣ������\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    FastSort(&L, 1, L.length, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("��������\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    BubbleSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("ð������\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    HeapSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("������\t\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    SelectSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("ѡ������\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    HalfInsertSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("�۰��������\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    CreateRandomSqList(&L, length);
    //PrintSqList(L);
    start = clock();
    compareTime = 0, MobileTime = 0;
    MergeSort(&L, &compareTime, &MobileTime);
    end = clock();
    totalTime = (double)(end - start) / CLK_TCK;
    //PrintSqList(L);
    printf("�鲢����\t%lf\t%d\t\t%d\n", totalTime, compareTime, MobileTime);

    return 0;
}

