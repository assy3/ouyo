#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* �֐��錾 */
unsigned long GetStringLength(char * str);

/* �֐���` */
unsigned long GetStringLength(char * str){
	int i;
	/* 
	��r���Z�q�Ő^(1)���Ԃ��Ă��ď����𖞂���
	str�̍Ō��null�����̔�r�ŋU(0)���Ԃ��Ă���0 != '\0'�͐^�Ȃ̂ŏI������
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

/* �S�p������1�o�C�g�ł͂Ȃ��A2�o�C�g�ȏ�ł��邽��printf("%c", str[i]);�ł͐������o�͂���Ȃ��B */

int main(void) 
{
	char str[30];
	int result;
	printf("���������͂��Ă��������B\n");
	scanf("%s", str);
	result = GetStringLength(str);
	// printf("%d\n",sizeof(str));
	printf("%d\n", result);

	getchar();
	getchar();
	
	return 0;
}