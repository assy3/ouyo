#include <stdio.h>
#include <windows.h>
#include <string.h>
#define STR_LEN (30)

static BOOL ret;
static unsigned short g_count = 0;
static unsigned short g_packed_kouzoutai;

FILE *g_fp;         // �o�̓X�g���[��

// �ۑ�3
// �o�C�g���E4�o�C�g
typedef struct tagPersonalData
{
    unsigned short usID;
    char cName[20];
    char cPhoneNo[15];
} PersonalData;

// Step1�֐�
BOOL SetPersonalData(PersonalData * data, unsigned short id, char * name, char * phoneNo);
BOOL WritePersonalDataArray(PersonalData * dataArray, unsigned short num, char * fileName);


// Step2�֐�
BOOL OpenPersonalData(char * fileName, unsigned short * numRecords);
BOOL ReadPersonalData(unsigned short pos, PersonalData * data);
BOOL ClosePersonalData(void);
BOOL GetPersonalData(PersonalData * data, unsigned short * id, char * name, char * phoneNo);

// Step3�֐�
BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data);
BOOL SearchPersonalDataByName(char * name, PersonalData * data);


// Step1-1�֐� �f�[�^�̍쐬
SetPersonalData(PersonalData * data, unsigned short id, char * name, char * phoneNo){
    if (data == NULL || name == NULL || phoneNo == NULL){
        goto l_Error;
    }
    else if (id == 0){
        goto l_Error;
    }
    else{
        ret = TRUE;
    }

    // 0����
    memset(data, 0, sizeof(PersonalData));
    data->usID = id;
    strcpy(data->cName, name);
    strcpy(data->cPhoneNo, phoneNo);
    printf("%d %s %s\n", data->usID, data->cName, data->cPhoneNo);
    g_count++;

l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
}

// Step1-2�֐��@�t�@�C���o��
WritePersonalDataArray(PersonalData * dataArray, unsigned short num, char * fileName){
    if (fileName == NULL) {
        //printf("cannot open\n");
        goto l_Error;
    }
    else if (num == 0 || dataArray == NULL){
        goto l_Error;
    }

    FILE * outputfile;
    outputfile = fopen(fileName, "wb");  // �t�@�C�����������ݗp�ɃI�[�v��(�J��)
    if (outputfile == NULL){
        fclose(outputfile);          // �t�@�C�����N���[�Y(����)
        goto l_Error;
    }

    int i, j;
    // �d������id�̏���
    for (i = 0; i < num; i++){
        for (j = 0; j < num; j++){
            //printf("%d, %d \n", dataArray[i].usID, dataArray[j].usID);
            if (i != j){
                if (dataArray[i].usID == dataArray[j].usID){
                    goto l_Error;
                }
            }
        }
    }

    fwrite(&g_count, sizeof(g_count), 1, outputfile);
		/*
		// �f�[�^�������݂��������Ȃ�
    if (write_size != g_packed_kouzoutai){
        goto l_Error;
    }
		*/
    for (i = 0; i<num; i++){
      	fwrite(dataArray, g_packed_kouzoutai, 1, outputfile);

        //fwrite(dataArray, sizeof(dataArray->usID), 1, outputfile);
        //fwrite(dataArray, sizeof(dataArray->cName), 1, outputfile);
        //fwrite(dataArray, sizeof(dataArray->cPhoneNo), 1, outputfile);
        //printf("%d\n", dataArray);
        dataArray++;
    }
    fclose(outputfile);          // �t�@�C�����N���[�Y(����)
    ret = TRUE;

l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;

}

OpenPersonalData(char * fileName, unsigned short * numRecords){
    if (fileName == NULL || numRecords == NULL){
        goto l_Error;
    }
    g_fp = fopen(fileName, "rb");
    if (g_fp == NULL) {          // �ǂݍ��݂Ɏ��s�����ꍇ
        goto l_Error;
    }
      //else if (temp = openfile){ //���Ƀt�@�C�����I�[�v������Ă���ꍇ
    //  goto l_Error;
    //}

  	fread(numRecords, sizeof(*numRecords), 1, g_fp);
    // close�͂��Ȃ�
    // �f�[�^�ǂݍ��݂��������Ȃ�

    //printf("numRecords = %u\n", *numRecords);
    //printf("numRecords = %u\n", numRecords);

l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
}

ReadPersonalData(unsigned short pos, PersonalData * data){
    if (g_fp == NULL || data == NULL) {
        goto l_Error;
    }
    else if (pos < 0 || pos > g_count){
        goto l_Error;
    }
      /*
    int k;
    for (k = 0; k < pos; k++){
        fread(data + pos, sizeof(*data)-1, 1, g_fp);
    }
    */

    /*
    int check;
    check = fseek(g_fp, 3, SEEK_SET);   if (check != 0){
        printf("���Ȃ���\n");
    }
    */
    //fseek(g_fp, 3, SEEK_CUR);
    //  sizeof(*data)-1 37�o�C�g
		printf("before %d %s %s \n", data->usID, data->cName, data->cPhoneNo);
		// pos�Ԗڂ̃f�[�^��data�̃A�h���X�Ɋi�[
		fseek(g_fp, 2 + ((pos - 1) * g_packed_kouzoutai), SEEK_SET);
    fread(data, g_packed_kouzoutai, 1, g_fp);
		printf("after %d %s %s \n", data->usID, data->cName, data->cPhoneNo);
    // �f�[�^�ǂݍ��݂��������Ȃ�

    //fread(data, sizeof(data->usID), 1, g_fp);
    //fread(data, sizeof(data->cName), 1, g_fp);
    //fread(data, sizeof(data->cPhoneNo), 1, g_fp);

l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
}

ClosePersonalData(void){
    if (g_fp == NULL) {    // �I�[�v������Ă��Ȃ�
        goto l_Error;
    }
    int close;
    close = fclose(g_fp);
    // 0��close����
    if (close != 0){
        goto l_Error;
    }

l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
}

GetPersonalData(PersonalData * data, unsigned short * id, char * name, char * phoneNo){
    *id = data->usID;

    name[sizeof(*name)] = '\0';
    phoneNo[sizeof(*phoneNo)] = '\0';
    strcpy(name, data->cName);     /* �����^�z��ɕ����^�z����R�s�[ */
    strcpy(phoneNo, data->cPhoneNo);     /* �����^�z��ɕ����^�z����R�s�[ */

		ret = TRUE;
l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
    //printf("*id-----------------%d\n", *id);
    //printf("name-----------------%s\n", name);
    //printf("phoneNo-----------------%s\n", phoneNo);
}


SearchPersonalDataByID(unsigned short id, PersonalData * data){
		unsigned short c_id;
		int y;

		printf("before %d %s %s \n", data->usID, data->cName, data->cPhoneNo);
		// pos�Ԗڂ̃f�[�^��data�̃A�h���X�Ɋi�[
		fseek(g_fp, 2 , SEEK_SET);

		for(y = 0; y < g_count; y++){
			fread(&c_id, 2, 1, g_fp);
			if(c_id == id){
				data->usID = c_id;
				printf("data->usID %d \n", data->usID);
				fread(data->cName, 20, 1, g_fp);
				printf("data->cName %s \n", data->cName);
				fread(data->cPhoneNo, 15, 1, g_fp);
				printf("data->cPhoneNo %s \n", data->cPhoneNo);
			}

			printf("c_id %d \n", c_id);
			fseek(g_fp,(g_packed_kouzoutai - 2), SEEK_CUR);
		}

		printf("after %d %s %s \n", data->usID, data->cName, data->cPhoneNo);

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}



SearchPersonalDataByName(char * name, PersonalData * data){
	printf("before %d %s %s \n", data->usID, data->cName, data->cPhoneNo);
	printf("name %d\n", name);
	char sreach_name[20];
	int y;
	int i = 0;
	int flag = 0;
	fseek(g_fp, 2 , SEEK_SET);

	for(y = 0; y < g_count; y++){
		fread(sreach_name, 20, 1, g_fp);
		printf("sreach_name %d\n", sreach_name);
		while(name[i]!='\0' && sreach_name[i]!='\0'){
				if(name[i]!=sreach_name[i]){
					flag=1;
					break;
				}
				i++;
		}
		if(flag == 0){
			printf("���������݂�����\n");
			strcpy(data->cName, sreach_name);
			printf("data->cName %s \n", data->cName);
		}
			fseek(g_fp, 17 , SEEK_CUR);
}





	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}


int main(void){
    PersonalData data[10];
    unsigned short id = 1;
    int i;
    int m = 0;
    int flag = 0;
    char name[20];
    char phoneNo[15];
    BOOL j;

    g_packed_kouzoutai = sizeof(data->usID) + sizeof(data->cName) + sizeof(data->cPhoneNo);

    while (m < 10) {
        printf("name����͂��Ă��������B");
        //memset(name, 0, sizeof(name));
        //printf("name %s", name);
        scanf("%s", name);

        printf("phoneNo����͂��Ă��������B");
        //memset(phoneNo, 0, sizeof(phoneNo));
        scanf("%s", phoneNo);

        // �f�[�^�Z�b�g�֐��Ăяo��
        SetPersonalData((data + m), id, name, phoneNo);

        printf("�f�[�^�Z�b�g�𑱂��Ȃ� 1 ������ else \n");
        scanf("%d", &flag);
        if (flag == 1){
            break;
        }
        else{
            m++;
            id++;
        }
    }

    unsigned short num = g_count;
    char fileName[20] = "data.dat";
		//char fileName[20] = "data.txt";
    // �t�@�C���o�͊֐��Ăԏo��
    WritePersonalDataArray(data, num, fileName);

    unsigned short numRecords;
    unsigned short position;
    // �t�@�C���I�[�v���֐��Ăяo��
    OpenPersonalData(fileName, &numRecords);

		printf("���Ԗڂ̃f�[�^���i�[���܂����H (position)\n");
		scanf("%u", &position);
    //�t�@�C���̓ǂݍ��݂��s�Ȃ��֐�
    ReadPersonalData(position, data);

    //�t�@�C�������֐�
    ClosePersonalData();

    int p = 0;
    for (i = 0; i < g_count; i++){
        //�f�[�^�̉��߂��s�Ȃ��֐�
        GetPersonalData(data + i, &id, name, phoneNo);

        while (name[p] == '\0'){
            p++;
        }
        printf("id  %d  name  %s  phoneNo  %s\n",id, name, phoneNo);
        printf("---------------\n");
    }

		OpenPersonalData(fileName, &numRecords);
		printf("���Ԗڂ�id�̃f�[�^���������܂����H (id)\n");
		scanf("%u", &id);
		// id����
		SearchPersonalDataByID(id, data);
		//�t�@�C�������֐�
		ClosePersonalData();

		OpenPersonalData(fileName, &numRecords);
		printf("��������name����͂��Ă�������(name)\n");
		scanf("%s", name);
		SearchPersonalDataByName(name, data);


    getchar();
    getchar();
    return 0;
}
