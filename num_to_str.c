#include <stdio.h>
#include <windows.h>
#define STR_LEN (30)
#define STORE_SIZE (16)

/* �֐��錾 */
BOOL MakeIntString(DWORD num, char * str, DWORD len);
BOOL MakeHexString(DWORD num, char * str);
BOOL MakeBinString(BYTE num, char * str);

/* �֐���` */
BOOL MakeIntString(DWORD num, char * str, DWORD len) {
	//�ϐ��̒�`
	//���̓G���[����
	DWORD sorce_num, str_len;
	if(str == NULL || len == 0){
		printf("str��NULL��������len��0(Ret = FALSE)\n");
		return FALSE;
	}
	sorce_num = num;
	str_len = len;
	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		if (sorce_num != 0) {
			// �������當���ɕϊ� +48�Ő����������ɕς��
			*(str + str_len) = (sorce_num % 10) + 48; //�z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
			sorce_num /= 10;
		}
		// �c��̌���0����
		else {
			*(str + str_len) = '0';
		}
	}
	*(str + len) = '\0';
	//�o��
	printf("MakeIntString(%d, str, %d) �� ", num, len);
	if (sorce_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		return FALSE;
	}
}

/* �֐���` */
BOOL MakeHexString(DWORD num, char * str) {
	//�ϐ��̒�`
	DWORD sorce_num, str_len;
	int hex_part;
	sorce_num = num;
	str_len = STORE_SIZE;
	if(str == NULL){
		printf("str��NULL(Ret = FALSE)\n");
		goto label;
	}
	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		hex_part = sorce_num % 16;
		if (sorce_num != 0) {
				if (hex_part >= 0 && hex_part <= 9){
					*(str + str_len) = hex_part + 48;
				}
				// �������當���ɕϊ� +55�Ő���(1~9)�������ɕς��
				else if(hex_part >= 10 && hex_part <= 15 ){
					*(str + str_len) = hex_part + 55;
				}
			  // �z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
				sorce_num /= 16;
		}
		// �c��̌���0����
		else {
			*(str + str_len) = '0';
		}
	}

	*(str + STORE_SIZE) = '\0';
	//�o��
	printf("MakeHexString(%d, str) �� ", num);
	if (sorce_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		label:
		return FALSE;
	}
}


/* �֐���` */
BOOL MakeBinString(BYTE num, char * str){
	//�ϐ��̒�`
	DWORD sorce_num, str_len;
	int bin_part;
	sorce_num = num;
	str_len = STORE_SIZE;
	if(str == NULL){
		printf("str��NULL(Ret = FALSE)\n");
		goto label;
	}

	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		bin_part = sorce_num % 2;
		if (sorce_num != 0) {
			*(str + str_len) = bin_part + 48;
		  // �z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
			sorce_num /= 2;
		}
		// �c��̌���0����
		else {
			*(str + str_len) = '0';
		}
	}
	*(str + STORE_SIZE) = '\0';
	//�o��
	printf("MakeBinString(%d, str) �� ", num);
	if (sorce_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		label:
		return FALSE;
	}
}

void main() {
	DWORD i = 123456;
	DWORD len = 10;
	// �ϊ���̕�������i�[���邽�߂̔z��
	char str1[STR_LEN] = { '\0' };
	char str2[STR_LEN] = { '\0' };
	char str3[STR_LEN] = { '\0' };
	// ������10�i�̕�����ɕϊ�
	MakeIntString(i, str1, len);
	// ������16�i�̕�����ɕϊ�
	MakeHexString(200, str2);
	// ������2�i�̕�����ɕϊ�
	MakeBinString(200, str3);
}
