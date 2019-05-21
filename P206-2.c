#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* �Ӽ��̶����û����봴�����Ա�
 * @param ptr_array ָ��������Ԫ��ָ���ָ��
 * @return ����Ԫ�صĸ���
 */
size_t create(int **ptr_array);

/* ��������ϲ�˳���
 * @param a Ҫ�ϲ���˳��� A
 * @param naitems A ��Ԫ�ظ���
 * @param b Ҫ�ϲ���˳��� B
 * @param nbitems B ��Ԫ�ظ���
 * @return �ϲ�������Ա�
 */
int *merge(int *a, size_t naitems, int *b, size_t nbitems);

/* ��ת˳���
 * @param array Ҫ��ת��˳���
 * @param nitems ˳�����Ԫ�ظ���
 */
void reverse(int *array, size_t nitems);

/* ���˳���
 * @param array Ҫ�����˳���
 * @param nitems ˳�����Ԫ�ظ���
 */
void print(int *array, size_t nitems);

size_t create(int **ptr_array)
{
	size_t nitems;
	printf("������˳���Ԫ�ظ���:\n");
	scanf("%llu", &nitems);
	int *array = (int *)malloc(sizeof(int) * nitems);
	printf("������˳����Ԫ��:\n");
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