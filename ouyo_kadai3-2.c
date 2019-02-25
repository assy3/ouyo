#include <stdio.h>
#include <windows.h>
#include<string.h>
#define STR_LEN (30)
#define BUF_SIZE (256)
// 課題3
typedef struct tagPersonalData
{
	unsigned short usID;
	char cName[20];
	char cPhoneNo[15];
} PersonalData;

// Step1関数ｰ
BOOL SetPersonalData(PersonalData * data, unsigned short id,char * name, char * phoneNo);
BOOL WritePersonalDataArray(PersonalData * dataArray, unsigned short num,char * fileName);

// Step2関数ｰ
BOOL OpenPersonalData(char * fileName, unsigned short * numRecords);
BOOL ReadPersonalData(unsigned short pos, PersonalData * data);
BOOL ClosePersonalData(void);
BOOL GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo);

// Step3関数ｰ
BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data);
BOOL SearchPersonalDataByName(char * name, PersonalData * data);

int main(void){
	PersonalData data[10];
	// ファイル名
	char fileName[20] = "data.txt";
	// データ数
	unsigned short numRecords;
	unsigned short position = 2;
	BOOL j;
	OpenPersonalData(fileName, &numRecords);
	ReadPersonalData(position, data);

	return 0;
}
// ファイルをオープンして行数取得
// Step2-1関数ｰ
	FILE *fp;
	OpenPersonalData(char * fileName, unsigned short * numRecords){
		/* ファイルのオープン */
	int line = 0;
	char buf[BUF_SIZE];
  if ((fp = fopen(fileName, "r")) == NULL) {
    return FALSE;
  }
  while (fgets(buf, BUF_SIZE, fp) != NULL) {
    line++;
  }
	*numRecords = line;
	printf("line = %d\n", *numRecords);
	return TRUE;
}

// Step2-2関数ｰ
ReadPersonalData(unsigned short pos, PersonalData * data){
	*(data + pos) =  
}
// Step2-3関数ｰ
ClosePersonalData(void){

}

// Step2-4関数ｰ
GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo){

}
