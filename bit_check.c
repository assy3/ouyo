#include <stdio.h>
#include <windows.h>
#define STR_LEN (30)
#define ONE_BYTE (8)
/* �֐��錾 */
BOOL GetBit(BYTE num, int bit, BOOL * onFlg);
BOOL SetBit(BYTE * num, int bit, BOOL onFlg);

/* �֐���` */
BOOL GetBit(BYTE num, int bit, BOOL *onFlg){
	//�ϐ��̒�`
	DWORD sorce_num, str_len;
	int bin_part;
	char str_f[STR_LEN] = { '\0' };
	sorce_num = num;
	str_len = ONE_BYTE;
	if(bit < 0 || bit > 7){
		printf("bit��0�`7�͈̔͊O�̏ꍇ(Ret = FALSE)\n");
		return FALSE;
	}
	// num��2�i���̕�����ɕϊ�
	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		bin_part = sorce_num % 2;
		if (sorce_num != 0) {
			*(str_f + str_len) = bin_part + 48;
			sorce_num /= 2;
		}
		// �c��̌���0����
		else {
			*(str_f + str_len) = '0';
		}
	}

	*(str_f + ONE_BYTE) = '\0';
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

/* �֐���` */
BOOL SetBit(BYTE * num, int bit, BOOL onFlg){
	//�ϐ��̒�`
	DWORD sorce_num, str_len;
	int bin_part;
	char str_f[STR_LEN] = { '\0' };
	sorce_num = *num;
	str_len = ONE_BYTE;
	if(bit < 0 || bit > 7){
		printf("bit��0�`7�͈̔͊O�̏ꍇ(Ret = FALSE)\n");
		return FALSE;
	}
	// num��2�i���̕�����ɕϊ�
	// �ϊ�����������str�Ɋi�[
	while(str_len > 0) {
		str_len--;
		bin_part = sorce_num % 2;
		if (sorce_num != 0) {
				*(str_f + str_len) = bin_part + 48;
				sorce_num /= 2;
		}
		// �c��̌���0����
		else {
			*(str_f + str_len) = '0';
		}
	}
	*(str_f + ONE_BYTE) = '\0';

	if(onFlg == TRUE){
		str_f[ONE_BYTE-bit] = '1';
		printf("SetBit(%d %d %d) ON %s\n", *num, bit, onFlg, str_f);
		return onFlg;
	}
	else if(onFlg == FALSE){
		str_f[ONE_BYTE-bit] = '0';
		printf("SetBit(%d %d %d) OFF %s\n", *num, bit, onFlg, str_f);
		return onFlg;
	}

	if(num == NULL){
		printf("num��NULL�̏ꍇ(Ret = FALSE)\n");
		return FALSE;
	}
}

void main() {
	BYTE num = 255;
	BOOL onFlg1;
	BOOL onFlg2;
	// bit�̐�����0~7
	int bit = 3;
	// �����ŗ^����bit�Ԗڂ̕�����1�Ȃ�onFlg1 = TRUE
	// �����ŗ^����bit�Ԗڂ̕�����1�Ȃ�onFlg1 = FALSE
	GetBit(num, bit, &onFlg1);
	onFlg2 = FALSE;
	// onFlg2 = TRUE �̎��́A�����ŗ^����bit�Ԗڂ̕�����1�ɂȂ�
	// onFlg2 = FALSE �̎��́A�����ŗ^����bit�Ԗڂ̕�����0�ɂȂ�
	SetBit(&num, bit, onFlg2);
}
