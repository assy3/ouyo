# define STR_SIZE (30)
# include <stdio.h>

/* �֐��錾 */
long GetTotal(long * dataArray, unsigned long dataCount);

/* �֐���` */
long GetTotal(long * dataArray, unsigned long dataCount){
	int i;
	int total = 0; // ��z��ł�total������������Ă���Ύ��s�ł���
	// int total;
	int avg;
	for (i = 0; i < dataCount; i++){
		total += dataArray[i];
	}
	return total;
}


/* main(�����n�܂�̊֐�) */
int main(void)
{
	int result;
	long data_array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	unsigned long number;
	// number = sizeof(data_array) / sizeof(long);
	number = 0;
	result = GetTotal(data_array, number);

	printf("result%d \n", result);

	getchar();
	getchar();

	return 0;
}