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

// Step3�֐��
BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data);
BOOL SearchPersonalDataByName(char * name, PersonalData * data);


static int count = 0;

int main(void){
	// PersonalData data = {15, "adfa", "dfadafdd"};
	PersonalData data[10];
	//PersonalData *data_point;
	unsigned short id = 1;

}
