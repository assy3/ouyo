# define STR_SIZE (30)
# include <stdio.h>

/* �֐��錾 */
void SortData(long * dataArray, unsigned long dataCount);

/* �֐���` */
void SortData(long * dataArray, unsigned long dataCount){
	int i;
	int j;
	int temp;
	// �o�u���\�[�g�O
	for (i = 0; i < dataCount; i++)
	{
		printf("%ld ", dataArray[i]);

	}
	// �o�u���\�[�g�A���S���Y��
	for (i = 0; i < dataCount; i++)
	{
		for (j = dataCount - 1; j > i; j--){
			if (dataArray[j] < dataArray[j - 1]) {
				temp = dataArray[j];
				dataArray[j] = dataArray[j - 1];
				dataArray[j - 1] = temp;
			}
		}
	}

	// �o�u���\�[�g��
	for (i = 0; i < dataCount; i++)
	{
		printf("%ld ", dataArray[i]);
	}
}

/* main(�����n�܂�̊֐�) */
int main(void)
{
	long data_array[] = { 21, 32, 43, 4, 55, 64, 47, 28, 19 };
	unsigned long number;
	//number = sizeof(data_array) / sizeof(long);
	number = 0;
	SortData(data_array, number);

	getchar();
	getchar();

	return 0;
}