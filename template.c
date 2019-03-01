#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct iro{
	int number;
	int koudo;
	char *namae;
};

int main(void){

	int num,i;
	FILE *fp;
	struct iro data[100];
	printf("F‚Ì”Ô†‚ğw’è‚µ‚Ä‚­‚¾‚³‚¢B");
	scanf("%d",&num);

	if ((fp = fopen("text.txt", "r")) == NULL){
		printf("not open file \n");
		exit(EXIT_SUCCESS);
	}

		fscanf(fp, "%d,%d,%s", data);

			printf("%d", data);

		fclose(fp);
	return 0;
}
