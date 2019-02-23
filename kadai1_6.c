# define STR_SIZE (30)
# include <stdio.h>

/* 関数宣言 */
void SortData(long * dataArray, unsigned long dataCount);

/* 関数定義 */
void SortData(long * dataArray, unsigned long dataCount){
    int i; 
    int j;
    int temp;
    // バブルソート前
    for(i = 0; i < dataCount; i++)
    {
        printf("%ld ",dataArray[i]);

    }

    // バブルソートアルゴリズム
    for(i = 0; i < dataCount; i++)
    {
        for(j = dataCount - 1; j > i; j--){
            if(dataArray[j] < dataArray[j-1]) {
                temp = dataArray[j];
                dataArray[j] = dataArray[j-1];
                dataArray[j-1] = temp;
            }
        }
    }

    // バブルソート後
    for(i = 0; i < dataCount; i++)
    {
        printf("%ld ",dataArray[i]);

    }
}


/* main(処理始まりの関数) */
int main(void)
{
    long data_array[] = {21,32,43,4,55,64,47,28,19};
    unsigned long number;
    number = sizeof(data_array) / sizeof(long);    
    SortData(data_array, number);

    return 0;
}
