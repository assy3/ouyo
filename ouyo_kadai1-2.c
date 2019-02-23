#define _CRT_SECURE_NO_WARNINGS
#define STR_SIZE (30)
#include <stdio.h>

/* 関数宣言 */
void CopyString(char * str1, char * str2);

/* 関数定義 */
void CopyString(char * str1, char * str2){
	int i;
	printf("コピー元 \n");
	for (i = 0; i < str2[i] != '\0'; i++){
		printf("%c", str2[i]);
		str2[i] = str1[i];
	}
	str1[i] = '\0';
	printf("\n");
	printf("コピー先 \n");
	for (i = 0; i < str1[i] != '\0'; i++){
		printf("%c", str1[i]);
	}
}


int main(void)
{
	char str1[STR_SIZE] = "abcde";
	char str2[STR_SIZE] = "12345678";
#if 0
	printf("文字列を入力してください。\n");
	scanf("%s", str2);
#endif
	CopyString(str1, str2);
	
	getchar();
	getchar();

	return 0;
}