# define _CRT_SECURE_NO_WARNINGS
# define ID_SIZE (2)
# define NAME_SIZE (20)
# define PNUM_SIZE (15)
# include <stdio.h>
# include <windows.h>
# include <string.h>
# include "PersonalData_func.h"


static unsigned short g_num;
static unsigned short g_packed_kouzoutai = ID_SIZE + NAME_SIZE + PNUM_SIZE;
FILE *g_fp = NULL;   // �o�̓X�g���[��


// Step1-1�֐� �f�[�^�̍쐬
BOOL SetPersonalData(PersonalData * data, unsigned short id, char * name, char * phoneNo){
	BOOL ret;
	if (data == NULL || name == NULL || phoneNo == NULL){
		goto l_Error;
	}
	else if (id == 0){
		goto l_Error;
	}
	else{

	}

	// 0����
	memset(data, 0, sizeof(PersonalData));
	data->usID = id;
	strcpy(data->cName, name);
	strcpy(data->cPhoneNo, phoneNo);
	printf("id = %d cName = %s cPhoneNo = %s\n", data->usID, data->cName, data->cPhoneNo);
	//g_count++;

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// Step1-2�֐��@�t�@�C���o��
BOOL WritePersonalDataArray(PersonalData * dataArray, unsigned short num, char * fileName){
	BOOL ret;
	if (fileName == NULL) {
		goto l_Error;
	}
	else if (num == 0 || dataArray == NULL){
		goto l_Error;
	}

	FILE * outputfile;
	outputfile = fopen(fileName, "wb");  // �t�@�C�����������ݗp�ɃI�[�v��(�J��)
	if (outputfile == NULL){
		goto l_Error;
	}

	int i, j;
	// �d������id�̏���
	for (i = 0; i < num; i++){
		for (j = 0; j < num; j++){
			if (i != j){
				if (dataArray[i].usID == dataArray[j].usID){
					fclose(outputfile);          // �t�@�C�����N���[�Y
					outputfile = NULL;
					goto l_Error;
				}
			}
		}
	}
	//�f�[�^��2�o�C�g
	fwrite(&num, sizeof(num), 1, outputfile);
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

BOOL OpenPersonalData(char * fileName, unsigned short * numRecords){
	BOOL ret;
	int read_num;
	if (fileName == NULL || numRecords == NULL){
		goto l_Error;
	}
	else if (g_fp != NULL) {   // �t�@�C�������ɃI�[�v��
		goto l_Error;
	}
	else{
		//nop
	}
	g_fp = fopen(fileName, "rb");
	if (g_fp == NULL) {          // �I�[�v���Ɏ��s�����ꍇ
		goto l_Error;
	}
	read_num = fread(numRecords, sizeof(*numRecords), 1, g_fp);
	g_num = *numRecords;
	if (read_num != 1){
		fclose(g_fp);          // �t�@�C�����N���[�Y(����)
		g_fp = NULL;
		goto l_Error;
	}
	// �ǂݍ��݂Ɏ��s�����ꍇ
	// close�͂��Ȃ�
	ret = TRUE;

l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

BOOL ReadPersonalData(unsigned short pos, PersonalData * data){
	BOOL ret;
	int read_num;

	if (g_fp == NULL || data == NULL) {
		goto l_Error;
	}
	else if (pos < 0 || pos > g_num){
		goto l_Error;
	}

	// pos�Ԗڂ̃f�[�^��data�̃A�h���X�Ɋi�[
	// 2�̓t�@�C���̐擪�ɂ���f�[�^��2�o�C�g�̂���
	fseek(g_fp, 2 + ((pos - 1) * g_packed_kouzoutai), SEEK_SET);
	read_num = fread(data, 2, 1, g_fp);
	if (read_num != 1){
		g_fp = NULL;
		goto l_Error;
	}

	read_num = fread(data, 20, 1, g_fp);
	if (read_num != 1){
		g_fp = NULL;
		goto l_Error;
	}

	read_num = fread(data, 15, 1, g_fp);
	if (read_num != 1){
		g_fp = NULL;
		goto l_Error;
	}

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

BOOL ClosePersonalData(void){
	BOOL ret;
	if (g_fp == NULL) {    // �I�[�v������Ă��Ȃ�
		goto l_Error;
	}
	int close;
	close = fclose(g_fp);
	g_fp = NULL;
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

BOOL GetPersonalData(PersonalData * data, unsigned short * id, char * name, char * phoneNo){
	BOOL ret;
	if (data == NULL || id == NULL || name == NULL || phoneNo == NULL){
		goto l_Error;
	}
	*id = data->usID;
	strcpy(name, data->cName);     /* �����^�z��ɕ����^�z����R�s�[ */
	strcpy(phoneNo, data->cPhoneNo);     /* �����^�z��ɕ����^�z����R�s�[ */

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}


BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data){
	BOOL ret;
	BOOL decision = FALSE;
	if (data == NULL){
		goto l_Error;
	}
	int i, read_num;
	unsigned short Infunc_usID;
	char Infunc_cName[20];
	char Infinc_cPhoneNo[15];

	fseek(g_fp, 2, SEEK_SET);

	for (i = 0; i < g_num; i++){
		read_num = fread(&Infunc_usID, 2, 1, g_fp);
		if (read_num != 1){
			g_fp = NULL;
			goto l_Error;
		}

		if (Infunc_usID == id){
			data->usID = Infunc_usID;
			read_num = fread(Infunc_cName, 20, 1, g_fp);
			if (read_num != 1){
				g_fp = NULL;
				goto l_Error;
			}
			read_num = fread(Infinc_cPhoneNo, 15, 1, g_fp);
			if (read_num != 1){
				g_fp = NULL;
				goto l_Error;
			}
			strcpy(data->cName, Infunc_cName);
			strcpy(data->cPhoneNo, Infinc_cPhoneNo);
			decision = TRUE;
			break;
		}
		else{
			// cName��cPhone��35�o�C�g�����߂�@
			fseek(g_fp, (g_packed_kouzoutai - 2), SEEK_CUR);
		}
	}
	// �����ʈ�v����f�[�^�������ꍇ
	if (decision == FALSE){
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

BOOL SearchPersonalDataByName(char * name, PersonalData * data){
	BOOL ret;
	BOOL decision = FALSE;
	if (name == NULL || data == NULL){
		goto l_Error;
	}

	char sreach_name[20];
	char serach_cPhoneNo[15];
	int i, ID, read_num;
	int check_name_num = 0;
	//�t�@�C��Open����2�o�C�g�i��ł���
	fseek(g_fp, 2, SEEK_SET);

	for (i = 0; i < g_num; i++){
		read_num = fread(&ID, 2, 1, g_fp);
		if (read_num != 1){
			g_fp = NULL;
			goto l_Error;
		}
		//��������0��Ԃ�
		read_num = fread(sreach_name, 20, 1, g_fp);
		if (read_num != 1){
			g_fp = NULL;
			goto l_Error;
		}
		if (strcmp(name, sreach_name) == 0){
			// printf("�����������݂�����\n");
			data->usID = ID;
			strcpy(data->cName, sreach_name);
			read_num = fread(serach_cPhoneNo, 15, 1, g_fp);
			if (read_num != 1){
				g_fp = NULL;
				goto l_Error;
			}
			strcpy(data->cPhoneNo, serach_cPhoneNo);
			decision = TRUE;
			break;
		}
		else{
			fseek(g_fp, 15, SEEK_CUR);
			check_name_num++;
		}
	}
	// �����ʈ�v����f�[�^�������ꍇ
	if (decision == FALSE){
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

