#include <stdio.h>
#include <windows.h>
#include<string.h>
#define STR_LEN (30)
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
BOOL GetPersonalData(PersonalData * data, unsigned short * id,
char * name, char * phoneNo);

// Step3関数ｰ
BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data);
BOOL SearchPersonalDataByName(char * name, PersonalData * data);


static int count = 0;

int main(void){
	// PersonalData data = {15, "adfa", "dfadafdd"};
	PersonalData data[10];
	//PersonalData *data_point;
	unsigned short id = 1;
	int k;
	int l;
	int flag = 0;
	int m = 0;
	//char name[20] = "TAKUMI ASHIKAWA";
	//char phoneNo[15] = "08066704846";
	char name[20];
	char phoneNo[15];
	BOOL j;

	while (m < 10) {
		printf("nameを入力してください。");
	  scanf("%s", name);
		printf("phoneNoを入力してください。");
		scanf("%s", phoneNo);
		l=0;
		while (name[l] != '\0'){
			l++;
		}
	  for (k = l; k < 20; k++) {
	    name[k] = '0';
	  }
		name[19] = '\0';
		// char phoneNo[15] = "123456";
		l=0;
		while (phoneNo[l] != '\0'){
			l++;
		}
		for (k = l; k < 15; k++) {
	    phoneNo[k] = '0';
	  }
		phoneNo[14] = '\0';
		// Step1-1関数ｰ
		j = SetPersonalData(data, id, name, phoneNo);
		if(j == 1){
			printf("%True\n");
		}
		else{
			printf("False\n");
		}
		printf("データセットを続けない 1 続ける else \n");
		scanf("%d", &flag);
		if(flag == 1){
			break;
		}
		else{
			m++;
			id++;
		}
	}
	unsigned short num = 9;
	char fileName[20] = "data.txt";
	// Step1-2関数ｰ
	j = WritePersonalDataArray(data, num, fileName);
	if(j == 1){
		printf("%True\n");
	}
	else{
		printf("False\n");
	}
	return 0;
}

// Step1-1関数ｰ
SetPersonalData(PersonalData * data, unsigned short id, char * name, char * phoneNo){
    //int i;
    //for(i=0; i<10; i++){
				data[count].usID = id;
				strcpy(data[count].cName, name);
				strcpy(data[count].cPhoneNo, phoneNo);
				printf("%d %s %s\n", data[count].usID, data[count].cName, data[count].cPhoneNo);
        count++;
    //}
		if(data == NULL || name == NULL || phoneNo == NULL){
			return FALSE;
		}
		else if(id == 0){
			return FALSE;
		}
		else{
			return TRUE;
		}
}
// Step1-2関数ｰ
WritePersonalDataArray(PersonalData * dataArray, unsigned short num,char * fileName){
	FILE *outputfile;         // 出力ストリーム
  outputfile = fopen(fileName, "w");  // ファイルを書き込み用にオープン(開く)
	int i;
  if (outputfile == NULL) {          // オープンに失敗した場合
    printf("cannot open\n");         // エラーメッセージを出して
    exit(1);                         // 異常終了
		return FALSE;
  }
	for(i=0; i<num; i++){
			fprintf(outputfile,"%d, %s, %s\n", dataArray[i].usID, dataArray[i].cName, dataArray[i].cPhoneNo);
			printf("%d, %s, %s\n", dataArray[i].usID, dataArray[i].cName, dataArray[i].cPhoneNo);
	}
  fclose(outputfile);          // ファイルをクローズ(閉じる)
  return TRUE;
}
