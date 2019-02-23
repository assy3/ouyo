# define STR_SIZE (30)
# include <stdio.h>

#define D_ERROR_ZERO_DIV ( 0x80000000L )

/* 関数宣言 */
long GetTotal(long * dataArray, unsigned long dataCount);

/* 関数定義 */
long GetTotal(long * dataArray, unsigned long dataCount){
	int i;
	long total = 0;
	long avg= 0;

	for (i = 0; i < dataCount; i++){
		total += dataArray[i];
	}
	// 配列がNULLだったら0除算になりエラー
	if (dataCount == '\0'){
		printf("配列がNULLです");
		//return D_ERROR_ZERO_DIV;
		avg = D_ERROR_ZERO_DIV;
	}
	else{
		avg = total / dataCount;
		printf("avg %ld\n", avg);
	}
		return avg;
}


/* main(処理始まりの関数) */
int main(void)
{
	long result;
	long data_array[] = { 1, 3, 2, 3, 4, 5, 6, 7, 8, 9 };
	// 空配列 0 '\0'
	unsigned long number;
	// number = sizeof(data_array) / sizeof(long);
	number = 0;
	result = GetTotal(data_array, number);

	printf("result %ld\n", result);

	getchar();
	getchar();

	return 0;
}