#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* 関数宣言 */
unsigned long GetStringLength(char * str);

/* 関数定義 */
unsigned long GetStringLength(char * str){
	int i;
	/* 
	比較演算子で真(1)が返ってきて条件を満たす
	strの最後のnull文字の比較で偽(0)が返ってきて0 != '\0'は真なので終了する
	for (i = 0; i < str[i] != '\0'; i++){
	printf("%c", str[i]);
	}
	*/

	for (i = 0; str[i] != '\0'; i++){
		printf("%c", str[i]);
	}
	printf("\n");
	printf("count = %d\n", i);
	return i;
}

/* 全角文字は1バイトではなく、2バイト以上であるためprintf("%c", str[i]);では正しく出力されない。 */

int main(void) 
{
	char str[30];
	int result;
	printf("文字列を入力してください。\n");
	scanf("%s", str);
	result = GetStringLength(str);
	// printf("%d\n",sizeof(str));
	printf("%d\n", result);

	getchar();
	getchar();
	
	return 0;
}