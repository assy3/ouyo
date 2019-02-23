#include <stdio.h>
#include <windows.h>
# define STR_LEN (30)

/* �֐��錾 */
BOOL MakeIntString(DWORD num, char * str, DWORD len);
BOOL MakeHexString(DWORD num, char * str);
BOOL MakeBinString(BYTE num, char * str);
BOOL GetBit(BYTE num, int bit, BOOL * onFlg);
BOOL SetBit(BYTE * num, int bit, BOOL onFlg);

/* �֐���` ���1*/
BOOL MakeIntString(DWORD num, char * str, DWORD len) {
	//�ϐ��̒�`
	//���̓G���[����
	DWORD raw_num, str_len;
	if(str == NULL || len == 0){
		printf("str��NULL��������len��0(Ret = FALSE)\n");
		return FALSE;
	}
	raw_num = num;
	str_len = len;

	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		if (raw_num != 0) {
			// �������當���ɕϊ� +48�Ő����������ɕς��
			*(str + str_len) = (raw_num % 10) + 48; //�z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
			raw_num /= 10;
		}
		// �c��̌���0����
		else {
			*(str + str_len) = '0';
		}
	}
	*(str + len) = '\0';

	//�o��
	printf("MakeIntString(%d, str, %d) �� ", num, len);
	if (raw_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		return FALSE;
	}
}


/* �֐���` ���2*/
BOOL MakeHexString(DWORD num, char * str) {
	//�ϐ��̒�`
	DWORD raw_num, str_len;
	int i = 0;
	int hex_part;
	raw_num = num;
	str_len = 8;
	if(str == NULL){
		printf("str��NULL(Ret = FALSE)\n");
		goto label;
	}

	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		hex_part = raw_num % 16;
		if (raw_num != 0) {
				if (hex_part >= 0 && hex_part <= 9){
					*(str + str_len) = hex_part + 48;
				}
				// �������當���ɕϊ� +55�Ő���(1~9)�������ɕς��
				else if(hex_part >= 10 && hex_part <= 15 ){
					*(str + str_len) = hex_part + 55;
				}
			  // �z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
				raw_num /= 16;
		}
		// �c��̌���0����
		else {
			*(str + str_len) = '0';
		}
	}

	*(str + 8) = '\0';
	//�o��
	printf("MakeHexString(%d, str) �� ", num);
	if (raw_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		label:
		return FALSE;
	}

}


/* �֐���` ���3*/
BOOL MakeBinString(BYTE num, char * str){
	//�ϐ��̒�`
	DWORD raw_num, str_len;
	int bin_part;
	raw_num = num;
	str_len = 8;
	if(str == NULL){
		printf("str��NULL(Ret = FALSE)\n");
		goto label;
	}

	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		bin_part = raw_num % 2;
		if (raw_num != 0) {
				if (bin_part >= 0 && bin_part <= 9){
					*(str + str_len) = bin_part + 48;
				}
				// �������當���ɕϊ� +55�Ő���(1~9)�������ɕς��
				else if(bin_part >= 10 && bin_part <= 15 ){
					*(str + str_len) = bin_part + 55;
				}
			  // �z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
				raw_num /= 2;
		}
		// �c��̌���0����
		else {
			*(str + str_len) = '0';
		}
	}

	*(str + 8) = '\0';
	//�o��
	printf("MakeBinString(%d, str) �� ", num);
	if (raw_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		label:
		return FALSE;
	}

}


/* �֐���` ���4 */
BOOL GetBit(BYTE num, int bit, BOOL *onFlg){
	//�ϐ��̒�`
	DWORD raw_num, str_len;
	int bin_part;
	char str_f[STR_LEN] = { '\0' };
	raw_num = num;
	str_len = 8;
	if(bit < 0 || bit > 8){
		printf("bit��0�`7�͈̔͊O�̏ꍇ(Ret = FALSE)\n");
		return FALSE;
	}

	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		bin_part = raw_num % 2;
		if (raw_num != 0) {
				if (bin_part >= 0 && bin_part <= 9){
					*(str_f + str_len) = bin_part + 48;
				}
				// �������當���ɕϊ� +55�Ő���(1~9)�������ɕς��
				else if(bin_part >= 10 && bin_part <= 15 ){
					*(str_f + str_len) = bin_part + 55;
				}
			  // �z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
				raw_num /= 2;
		}
		// �c��̌���0����
		else {
			*(str_f + str_len) = '0';
		}
	}

	*(str_f + 8) = '\0';

	if (str_f[bit] == '1') {
		*onFlg = TRUE;
		printf("GetBit(%d %d %d) ON %s\n", num, bit, *onFlg, str_f);
		return *onFlg;
	}
	else if(str_f[bit] == '0'){
		*onFlg = FALSE;
		printf("GetBit(%d %d %d) OFF %s\n", num, bit, *onFlg, str_f);
		return *onFlg;
	}
	else{
		printf("0��1�ȊO�̐����������Ă܂�");
	}

	if(onFlg == NULL){
		printf("onFlg��NULL�̏ꍇ(Ret = FALSE)\n");
		return FALSE;
	}
}


/* �֐���` ���5 */
BOOL SetBit(BYTE * num, int bit, BOOL onFlg){
		//�ϐ��̒�`
		DWORD raw_num, str_len;
		int bin_part;
		char str_f[STR_LEN] = { '\0' };
		raw_num = *num;
		str_len = 8;
		if(bit < 0 || bit > 8){
			printf("bit��0�`7�͈̔͊O�̏ꍇ(Ret = FALSE)\n");
			return FALSE;
		}

		// �ϊ�����������str�Ɋi�[
		while(str_len > 0) {
			str_len--;
			bin_part = raw_num % 2;
			if (raw_num != 0) {
					if (bin_part >= 0 && bin_part <= 9){
						*(str_f + str_len) = bin_part + 48;
					}
					// �������當���ɕϊ� +55�Ő���(1~9)�������ɕς��
					else if(bin_part >= 10 && bin_part <= 15 ){
						*(str_f + str_len) = bin_part + 55;
					}
				  // �z��̈�ԉE���珇�Ɉꌅ�ڂ̕��������Ă���
					raw_num /= 2;
			}
			// �c��̌���0����
			else {
				*(str_f + str_len) = '0';
			}
		}

		*(str_f + 8) = '\0';

		if(onFlg == TRUE){
			str_f[7-bit] = '1';
			printf("SetBit(%d %d %d) ON %s\n", *num, bit, onFlg, str_f);
			return onFlg;
		}
		else if(onFlg == FALSE){
			str_f[7-bit] = '0';
			printf("SetBit(%d %d %d) OFF %s\n", *num, bit, onFlg, str_f);
			return onFlg;
		}

		if(num == NULL){
			printf("num��NULL�̏ꍇ(Ret = FALSE)\n");
			return FALSE;
		}
}


int main() {
	DWORD i = 123456;
	DWORD len = 10;
	BYTE num = 255;
	char str[STR_LEN] = { '\0' };
	char str1[STR_LEN] = { '\0' };
	char str2[STR_LEN] = { '\0' };
	BOOL onFlg;
	BOOL onFlg2;
	int bit = 3;
	// ���1 �֐��Ăяo��
	MakeIntString(i, str, len);
	// ���2 �֐��Ăяo��
	MakeHexString(255, str1);
	// ���3 �֐��Ăяo��
	MakeBinString(5, str2);
  // ���4 �֐��Ăяo��
	GetBit(num, bit, &onFlg);
  // ���5 �֐��Ăяo��
	onFlg2 = FALSE;
	SetBit(&num, bit, onFlg2);

	}
