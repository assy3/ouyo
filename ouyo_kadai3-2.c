#include <stdio.h>
#include <windows.h>
#include<string.h>
#define STR_LEN (30)
#define BUF_SIZE (256)
// �ۑ�3
typedef struct tagPersonalData
{
	unsigned short usID;
	char cName[20];
	char cPhoneNo[15];
} PersonalData;

// Step1�֐��
BOOL SetPersonalData(PersonalData * data, unsigned short id,char * name, char * phoneNo);
BOOL WritePersonalDataArray(PersonalData * dataArray, unsigned short num,char * fileName);

// Step2�֐��
BOOL OpenPersonalData(char * fileName, unsigned short * numRecords);
BOOL ReadPersonalData(unsigned short pos, PersonalData * data);
BOOL ClosePersonalData(void);
BOOL GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo);

// Step3�֐��
BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data);
BOOL SearchPersonalDataByName(char * name, PersonalData * data);

int main(void){
	PersonalData data[10];
	// �t�@�C����
	char fileName[20] = "data.txt";
	// �f�[�^��
	unsigned short numRecords;
	unsigned short position = 2;
	BOOL j;
	OpenPersonalData(fileName, &numRecords);
	ReadPersonalData(position, data);

	return 0;
}
// �t�@�C�����I�[�v�����čs���擾
// Step2-1�֐��
	FILE *fp;
	OpenPersonalData(char * fileName, unsigned short * numRecords){
		/* �t�@�C���̃I�[�v�� */
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

// Step2-2�֐��
ReadPersonalData(unsigned short pos, PersonalData * data){
	*(data + pos) =  
}
// Step2-3�֐��
ClosePersonalData(void){

}

// Step2-4�֐��
GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo){

}
