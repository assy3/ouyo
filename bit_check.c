#include <stdio.h>
#include <windows.h>
#define STR_LEN (30)
#define ONE_BYTE (8)
/* 関数宣言 */
BOOL GetBit(BYTE num, int bit, BOOL * onFlg);
BOOL SetBit(BYTE * num, int bit, BOOL onFlg);

/* 関数定義 */
BOOL GetBit(BYTE num, int bit, BOOL *onFlg){
	//変数の定義
	DWORD sorce_num, str_len;
	int bin_part;
	char str_f[STR_LEN] = { '\0' };
	sorce_num = num;
	str_len = ONE_BYTE;
	if(bit < 0 || bit > 7){
		printf("bitが0～7の範囲外の場合(Ret = FALSE)\n");
		return FALSE;
	}
	// numを2進数の文字列に変換
	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		bin_part = sorce_num % 2;
		if (sorce_num != 0) {
			*(str_f + str_len) = bin_part + 48;
			sorce_num /= 2;
		}
		// 残りの桁を0埋め
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
		printf("0か1以外の数字が入ってます");
	}

	if(onFlg == NULL){
		printf("onFlgがNULLの場合(Ret = FALSE)\n");
		return FALSE;
	}
}

/* 関数定義 */
BOOL SetBit(BYTE * num, int bit, BOOL onFlg){
	//変数の定義
	DWORD sorce_num, str_len;
	int bin_part;
	char str_f[STR_LEN] = { '\0' };
	sorce_num = *num;
	str_len = ONE_BYTE;
	if(bit < 0 || bit > 7){
		printf("bitが0～7の範囲外の場合(Ret = FALSE)\n");
		return FALSE;
	}
	// numを2進数の文字列に変換
	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		bin_part = sorce_num % 2;
		if (sorce_num != 0) {
				*(str_f + str_len) = bin_part + 48;
				sorce_num /= 2;
		}
		// 残りの桁を0埋め
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
		printf("numがNULLの場合(Ret = FALSE)\n");
		return FALSE;
	}
}

void main() {
	BYTE num = 255;
	BOOL onFlg1;
	BOOL onFlg2;
	// bitの数字は0~7
	int bit = 3;
	// 引数で与えたbit番目の文字が1ならonFlg1 = TRUE
	// 引数で与えたbit番目の文字が1ならonFlg1 = FALSE
	GetBit(num, bit, &onFlg1);
	onFlg2 = FALSE;
	// onFlg2 = TRUE の時は、引数で与えたbit番目の文字が1になる
	// onFlg2 = FALSE の時は、引数で与えたbit番目の文字が0になる
	SetBit(&num, bit, onFlg2);
}
