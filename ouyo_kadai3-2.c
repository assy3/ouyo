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

// �O���[�o���ϐ�
char buf[BUF_SIZE];
FILE *fp;
PersonalData data[10];
// �ۑ�3

// Step2�֐��
BOOL OpenPersonalData(char * fileName, unsigned short * numRecords);
BOOL ReadPersonalData(unsigned short pos, PersonalData * data);
BOOL ClosePersonalData(void);
BOOL GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo);

int main(void){
	// �t�@�C����
	char fileName[20] = "data.txt";
	// �f�[�^��
	unsigned short numRecords;
	unsigned short position = 2;
	BOOL j;
	j = OpenPersonalData(fileName, &numRecords);
	ReadPersonalData(position, data);

	return 0;
}
// �t�@�C�����I�[�v�����čs���擾
// Step2-1�֐��
	OpenPersonalData(char * fileName, unsigned short * numRecords){
	/* �t�@�C���̃I�[�v�� */
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

// Step2-2�֐��
ReadPersonalData(unsigned short pos, PersonalData * data){
	int i;
	while (fgets(buf, BUF_SIZE, fp) != NULL) {
		printf("%s\n", buf);
	}

}
// Step2-3�֐��
ClosePersonalData(void){
	fclose(fp);
}

// Step2-4�֐��
GetPersonalData(PersonalData * data, unsigned short * id,char * name, char * phoneNo){

}
