#include <stdio.h>
#include <windows.h>
#include<string.h>
#define STR_LEN (30)
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
BOOL GetPersonalData(PersonalData * data, unsigned short * id,
char * name, char * phoneNo);

// Step3�֐��
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
		printf("name����͂��Ă��������B");
	  scanf("%s", name);
		printf("phoneNo����͂��Ă��������B");
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
		// Step1-1�֐��
		j = SetPersonalData(data, id, name, phoneNo);
		if(j == 1){
			printf("%True\n");
		}
		else{
			printf("False\n");
		}
		printf("�f�[�^�Z�b�g�𑱂��Ȃ� 1 ������ else \n");
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
	// Step1-2�֐��
	j = WritePersonalDataArray(data, num, fileName);
	if(j == 1){
		printf("%True\n");
	}
	else{
		printf("False\n");
	}
	return 0;
}

// Step1-1�֐��
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
// Step1-2�֐��
WritePersonalDataArray(PersonalData * dataArray, unsigned short num,char * fileName){
	FILE *outputfile;         // �o�̓X�g���[��
  outputfile = fopen(fileName, "w");  // �t�@�C�����������ݗp�ɃI�[�v��(�J��)
	int i;
  if (outputfile == NULL) {          // �I�[�v���Ɏ��s�����ꍇ
    printf("cannot open\n");         // �G���[���b�Z�[�W���o����
    exit(1);                         // �ُ�I��
		return FALSE;
  }
	for(i=0; i<num; i++){
			fprintf(outputfile,"%d, %s, %s\n", dataArray[i].usID, dataArray[i].cName, dataArray[i].cPhoneNo);
			printf("%d, %s, %s\n", dataArray[i].usID, dataArray[i].cName, dataArray[i].cPhoneNo);
	}
  fclose(outputfile);          // �t�@�C�����N���[�Y(����)
  return TRUE;
}
