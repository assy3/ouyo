#define _CRT_SECURE_NO_WARNINGS
# define STR_SIZE (30)
# include <stdio.h>

/* �֐��錾 */
void CatString(char * str1, char * str2);

/* �֐���` */
void CatString(char * str1, char * str2){
	int i;
	int j;
	for (i = 0; str1[i] != '\0'; i++){
	}
	for (j = 0; str2[j] != '\0'; j++){
		str1[i] = str2[j];
		i++;
	}
	str1[i] = '\0';
	printf("�A�����ꂽ������@%s \n", str1);
}


/* main(�����n�܂�̊֐�) */
int main(void)
{
	char str1[STR_SIZE] = "abcde";
	char str2[STR_SIZE] = "12345678";
	/*
	printf("str1 ");
	scanf("%s", str1);
	printf("str2 ");
	scanf("%s", str2);
	// */
	CatString(str1, str2);

	getchar();
	getchar();
	return 0;
}