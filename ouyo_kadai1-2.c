#define _CRT_SECURE_NO_WARNINGS
#define STR_SIZE (30)
#include <stdio.h>

/* �֐��錾 */
void CopyString(char * str1, char * str2);

/* �֐���` */
void CopyString(char * str1, char * str2){
	int i;
	printf("�R�s�[�� \n");
	for (i = 0; i < str2[i] != '\0'; i++){
		printf("%c", str2[i]);
		str2[i] = str1[i];
	}
	str1[i] = '\0';
	printf("\n");
	printf("�R�s�[�� \n");
	for (i = 0; i < str1[i] != '\0'; i++){
		printf("%c", str1[i]);
	}
}


int main(void)
{
	char str1[STR_SIZE] = "abcde";
	char str2[STR_SIZE] = "12345678";
#if 0
	printf("���������͂��Ă��������B\n");
	scanf("%s", str2);
#endif
	CopyString(str1, str2);
	
	getchar();
	getchar();

	return 0;
}