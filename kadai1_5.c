# define STR_SIZE (30)
# include <stdio.h>

/* 関数宣言 */
long GetTotal(long * dataArray, unsigned long dataCount);

/* 関数定義 */
long GetTotal(long * dataArray, unsigned long dataCount){
    int i;
    int total = 0;
    int avg;
    for(i = 0; i < dataCount; i++){    
        total += dataArray[i];
    }
    avg = total / dataCount;
    
    printf("avg%d \n", avg);
    return avg;
} 


/* main(処理始まりの関数) */
int main(void)
{
    int result;
    long data_array[] = {1,2,3,4,5,6,7,8,9};
    unsigned long number;
    number = sizeof(data_array) / sizeof(long);    
    result = GetTotal(data_array, number);

    printf("result%d \n", result);

    return 0;
}

