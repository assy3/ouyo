#include <stdio.h>
#include <windows.h>
#include<string.h>
#define STR_LEN (30)
#define BUF_SIZE (256)

typedef struct tagPersonalData
{
	unsigned short usID;
	char cName[20];
	char cPhoneNo[15];
} PersonalData;

// グローバル変数
char buf[BUF_SIZE];
FILE *fp;
PersonalData data[10];
// 課題3

// Step2関数ｰ
BOOL OpenPersonalData(char * fileName, unsigned short * numRecords);
BOOL ReadPersonalData(unsigned short pos, PersonalData * data);
BOOL ClosePersonalData(void);
BOOL GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo);

int main(void){
	// ファイル名
	char fileName[20] = "data.txt";
	// データ数
	unsigned short numRecords;
	unsigned short position = 2;
	BOOL j;
	j = OpenPersonalData(fileName, &numRecords);
	ReadPersonalData(position, data);

	return 0;
}
// ファイルをオープンして行数取得
// Step2-1関数ｰ
	OpenPersonalData(char * fileName, unsigned short * numRecords){
	/* ファイルのオープン */
		int line = 0;
	  if ((fp = fopen(fileName, "r")) == NULL) {
	    return FALSE;
	  }

	  while (fgets(buf, BUF_SIZE, fp) != NULL) {
	    line++;
			printf("%s\n", buf);
	  }
		*numRecords = line;
		printf("line = %d\n", *numRecords);
		return TRUE;
}

// Step2-2関数ｰ
ReadPersonalData(unsigned short pos, PersonalData * data){
	int i;
	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		printf("%s\n", buf);
	}

}
// Step2-3関数ｰ
ClosePersonalData(void){
	fclose(fp);
}

// Step2-4関数ｰ
GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo){

}
