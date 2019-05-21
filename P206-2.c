#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* 从键盘读入用户输入创建线性表
 * @param ptr_array 指向数组首元素指针的指针
 * @return 读入元素的个数
 */
size_t create(int **ptr_array);

/* 按递增序合并顺序表
 * @param a 要合并的顺序表 A
 * @param naitems A 内元素个数
 * @param b 要合并的顺序表 B
 * @param nbitems B 内元素个数
 * @return 合并后的线性表
 */
int *merge(int *a, size_t naitems, int *b, size_t nbitems);

/* 反转顺序表
 * @param array 要反转的顺序表
 * @param nitems 顺序表内元素个数
 */
void reverse(int *array, size_t nitems);

/* 输出顺序表
 * @param array 要输出的顺序表
 * @param nitems 顺序表内元素个数
 */
void print(int *array, size_t nitems);

size_t create(int **ptr_array)
{
	size_t nitems;
	printf("请输入顺序表元素个数:\n");
	scanf("%llu", &nitems);
	int *array = (int *)malloc(sizeof(int) * nitems);
	printf("请输入顺序表的元素:\n");
	for (size_t i = 0; i < nitems; i++)
		scanf("%d", &array[i]);
	*ptr_array = array;
	return nitems;
}
int *merge(int *a, size_t naitems, int *b, size_t nbitems)
{
	int *dst = (int *)malloc(sizeof(int) * (naitems + nbitems));
	size_t curr_i = 0, curr_j = 0, curr_k = 0;
	while (curr_i < naitems && curr_j < nbitems)
	{
		dst[curr_k] = a[curr_i] > b[curr_j] ? b[curr_j] : a[curr_i];
		a[curr_i] > b[curr_j] ? curr_j++ : curr_i++;
		curr_k++;
	}
	for (size_t i = curr_i; i < naitems; i++)
	{
		dst[curr_k] = a[i];
		curr_k++;
	}
	for (size_t i = curr_j; i < nbitems; i++)
	{
		dst[curr_k] = b[i];
		curr_k++;
	}
	return dst;
}
void reverse(int *array, size_t nitems) {
	int tmp = 0;
	for (size_t i = 0; i < nitems/2; i++) {
		tmp = array[i];
		array[i] = array[nitems - i -1];
		array[nitems - i -1] = tmp;
	}
	
}
void print(int *array, size_t nitems) {
	for (size_t i = 0; i < nitems; i++)
	{
		printf(i == nitems - 1 ? "%d\n" : "%d ", array[i]);
	}

}
int main() {
	int *a, *b;
	size_t naitems = create(&a);
	size_t nbitems = create(&b);
	print(a, naitems);
	print(b, nbitems);
	int *c = merge(a, naitems, b, nbitems);
	print(c, naitems + nbitems);
	reverse(c, naitems + nbitems);
	print(c, naitems + nbitems);
	return 0;
}