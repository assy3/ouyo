#include <stdio.h>
#include <windows.h>
#include <string.h>
#define STR_LEN (30)
static BOOL ret;
static unsigned short g_count = 0;
static unsigned short g_packed_kouzoutai;

FILE *g_fp;   // �o�̓X�g���[��

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
    printf("id = %d cName = %s cPhoneNo = %s\n", data->usID, data->cName, data->cPhoneNo);
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
            if (i != j){
                if (dataArray[i].usID == dataArray[j].usID){
                    goto l_Error;
                }
            }
        }
    }
		//�f�[�^��2�o�C�g
    fwrite(&g_count, sizeof(g_count), 1, outputfile);
		// 37�o�C�g���̍\���̃f�[�^����������
    for (i = 0; i<num; i++){
      	fwrite(dataArray, g_packed_kouzoutai, 1, outputfile);
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
  	fread(numRecords, sizeof(*numRecords), 1, g_fp);
    // close�͂��Ȃ�
		ret = TRUE;

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
		// pos�Ԗڂ̃f�[�^��data�̃A�h���X�Ɋi�[
		// 2�̓t�@�C���̐擪�ɂ���f�[�^��2�o�C�g�̂���
		fseek(g_fp, 2 + ((pos - 1) * g_packed_kouzoutai), SEEK_SET);
    fread(data, g_packed_kouzoutai, 1, g_fp);
		ret = TRUE;
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
		ret = TRUE;

l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
}

GetPersonalData(PersonalData * data, unsigned short * id, char * name, char * phoneNo){
	if (data == NULL || id == NULL || name == NULL || phoneNo == NULL){
			goto l_Error;
	}
    *id = data->usID;
    //name[sizeof(*name)] = '\0';
    //phoneNo[sizeof(*phoneNo)] = '\0';
    strcpy(name, data->cName);     /* �����^�z��ɕ����^�z����R�s�[ */
    strcpy(phoneNo, data->cPhoneNo);     /* �����^�z��ɕ����^�z����R�s�[ */

		ret = TRUE;
l_EXIT:
    return ret;
l_Error:
    ret = FALSE;
    goto l_EXIT;
}


SearchPersonalDataByID(unsigned short id, PersonalData * data){
	if (data == NULL){
			goto l_Error;
	}
		unsigned short c_id;
		int i;
		int check_id = 1;

		printf("before %d %s %s \n", data->usID, data->cName, data->cPhoneNo);
		// pos�Ԗڂ̃f�[�^��data�̃A�h���X�Ɋi�[
		//open�̎��Ƀ|�C���^��2�i����Ȃ��Ă�����
		fseek(g_fp, 2 , SEEK_SET);

		for(i = 0; i < g_count; i++){
			fread(&c_id, 2, 1, g_fp);
			if(c_id == id){
				data->usID = c_id;
				fread(data->cName, 20, 1, g_fp);
				fread(data->cPhoneNo, 15, 1, g_fp);
			}
			else{
				// cName��cPhone��35�o�C�g�����߂�@
				fseek(g_fp,(g_packed_kouzoutai - 2), SEEK_CUR);
				check_id++;
			}
		}
		// �����ʈ�v����f�[�^�������ꍇ
		if(check_id != g_count){
			printf("�����Ɉ�v����f�[�^�͂���܂���\n");
			goto l_Error;
		}

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

SearchPersonalDataByName(char * name, PersonalData * data){
	if (name == NULL || data == NULL){
			goto l_Error;
	}
	//printf("before %d %s %s \n", data->usID, data->cName, data->cPhoneNo);
	//printf("name %s\n", name);
	char sreach_name[20];
	int i;
	int check_name_num = 0;
	//�t�@�C��Open����2�o�C�g�i��ł���
	fseek(g_fp, 2 , SEEK_CUR);

	for(i = 0; i < g_count; i++){
		fread(sreach_name, 20, 1, g_fp);

		if(strcmp(name, sreach_name) == 0){
			printf("���������݂�����\n");
			data->usID = i + 1;
			strcpy(data->cName, sreach_name);
			fread(data->cPhoneNo, 15, 1, g_fp);
			//printf("data->cPhoneNo %s \n", data->cPhoneNo);
			fseek(g_fp, 2 , SEEK_CUR);
			ret = TRUE;
			goto l_EXIT;
		}
		else{
			fseek(g_fp, 17 , SEEK_CUR);
			check_name_num++;
		}
}
// �����ʈ�v����f�[�^�������ꍇ
if(check_name_num != g_count){
	printf("�����Ɉ�v����f�[�^�͂���܂���\n");
	goto l_Error;
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
		int select = 0;
    char name[20];
    char phoneNo[15];
		BOOL check;
    g_packed_kouzoutai = sizeof(data->usID) + sizeof(data->cName) + sizeof(data->cPhoneNo);

    while (m < 10) {
        printf("name����͂��Ă��������B");
        scanf("%s", name);
        printf("phoneNo����͂��Ă��������B");
        scanf("%s", phoneNo);
        // �f�[�^�Z�b�g�֐��Ăяo��
        check = SetPersonalData((data + m), id, name, phoneNo);
				if(check == FALSE){
					printf("�f�[�^�Z�b�g�Ɏ��s���܂���\n");
				}

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
    // �t�@�C���o�͊֐��Ăяo��
    check = WritePersonalDataArray(data, num, fileName);
		if(check == FALSE){
			printf("�t�@�C���o�͂Ɏ��s���܂���\n");
		}

    unsigned short numRecords;
    unsigned short position;
    // �t�@�C���I�[�v���֐��Ăяo��
    check = OpenPersonalData(fileName, &numRecords);
		if(check == FALSE){
			printf("�t�@�C���I�[�v���Ɏ��s���܂���\n");
		}
		printf("���Ԗڂ̃f�[�^���i�[���܂����H (position)\n");
		scanf("%u", &position);
    //�t�@�C���̓ǂݍ��݂��s�Ȃ��֐�
    check = ReadPersonalData(position, data);
		if(check == FALSE){
			printf("�t�@�C���ǂݍ��݂Ɏ��s���܂���\n");
		}
		printf("�i�[���܂���\n");
    //�t�@�C�������֐�
    check = ClosePersonalData();
		if(check == FALSE){
			printf("�t�@�C���N���[�Y�Ɏ��s���܂���\n");
		}

    for (i = 0; i < g_count; i++){
        //�f�[�^�̉��߂��s�Ȃ��֐�
        check = GetPersonalData(data + i, &id, name, phoneNo);
				if(check == FALSE){
					printf("�f�[�^���߂Ɏ��s���܂���\n");
				}
        printf("id  %d  name  %s  phoneNo  %s\n",id, name, phoneNo);
        printf("---------------\n");
    }

		printf("ID����������:0 ���O����������:1\n");
		scanf("%d", &select);
		if(select == 0){
				OpenPersonalData(fileName, &numRecords);
				printf("���Ԗڂ�id�̃f�[�^���������܂����H (id)\n");
				scanf("%u", &id);
				// id����
				SearchPersonalDataByID(id, data);
				//�t�@�C�������֐�
				ClosePersonalData();
		}
		else if(select == 1){
				OpenPersonalData(fileName, &numRecords);
				printf("��������name����͂��Ă�������(name)\n");
				scanf("%s", name);
				SearchPersonalDataByName(name, data);
				//�t�@�C�������֐�
				ClosePersonalData();
		}
		else{
			printf("��������������͂��Ă�������\n");
		}

    getchar();
    getchar();
    return 0;
}
