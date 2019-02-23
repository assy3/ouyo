#include <stdio.h>
#include <windows.h>
# define STR_LEN (30)

/* 関数宣言 */
BOOL MakeIntString(DWORD num, char * str, DWORD len);
BOOL MakeHexString(DWORD num, char * str);
BOOL MakeBinString(BYTE num, char * str);
BOOL GetBit(BYTE num, int bit, BOOL * onFlg);
BOOL SetBit(BYTE * num, int bit, BOOL onFlg);

/* 関数定義 問題1*/
BOOL MakeIntString(DWORD num, char * str, DWORD len) {
	//変数の定義
	//入力エラー処理
	DWORD raw_num, str_len;
	if(str == NULL || len == 0){
		printf("strがNULLもしくはlenが0(Ret = FALSE)\n");
		return FALSE;
	}
	raw_num = num;
	str_len = len;

	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		if (raw_num != 0) {
			// 数字から文字に変換 +48で整数が文字に変わる
			*(str + str_len) = (raw_num % 10) + 48; //配列の一番右から順に一桁目の文字を入れていく
			raw_num /= 10;
		}
		// 残りの桁を0埋め
		else {
			*(str + str_len) = '0';
		}
	}
	*(str + len) = '\0';

	//出力
	printf("MakeIntString(%d, str, %d) → ", num, len);
	if (raw_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		return FALSE;
	}
}


/* 関数定義 問題2*/
BOOL MakeHexString(DWORD num, char * str) {
	//変数の定義
	DWORD raw_num, str_len;
	int i = 0;
	int hex_part;
	raw_num = num;
	str_len = 8;
	if(str == NULL){
		printf("strがNULL(Ret = FALSE)\n");
		goto label;
	}

	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		hex_part = raw_num % 16;
		if (raw_num != 0) {
				if (hex_part >= 0 && hex_part <= 9){
					*(str + str_len) = hex_part + 48;
				}
				// 数字から文字に変換 +55で整数(1~9)が文字に変わる
				else if(hex_part >= 10 && hex_part <= 15 ){
					*(str + str_len) = hex_part + 55;
				}
			  // 配列の一番右から順に一桁目の文字を入れていく
				raw_num /= 16;
		}
		// 残りの桁を0埋め
		else {
			*(str + str_len) = '0';
		}
	}

	*(str + 8) = '\0';
	//出力
	printf("MakeHexString(%d, str) → ", num);
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


/* 関数定義 問題3*/
BOOL MakeBinString(BYTE num, char * str){
	//変数の定義
	DWORD raw_num, str_len;
	int bin_part;
	raw_num = num;
	str_len = 8;
	if(str == NULL){
		printf("strがNULL(Ret = FALSE)\n");
		goto label;
	}

	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		bin_part = raw_num % 2;
		if (raw_num != 0) {
				if (bin_part >= 0 && bin_part <= 9){
					*(str + str_len) = bin_part + 48;
				}
				// 数字から文字に変換 +55で整数(1~9)が文字に変わる
				else if(bin_part >= 10 && bin_part <= 15 ){
					*(str + str_len) = bin_part + 55;
				}
			  // 配列の一番右から順に一桁目の文字を入れていく
				raw_num /= 2;
		}
		// 残りの桁を0埋め
		else {
			*(str + str_len) = '0';
		}
	}

	*(str + 8) = '\0';
	//出力
	printf("MakeBinString(%d, str) → ", num);
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


/* 関数定義 問題4 */
BOOL GetBit(BYTE num, int bit, BOOL *onFlg){
	//変数の定義
	DWORD raw_num, str_len;
	int bin_part;
	char str_f[STR_LEN] = { '\0' };
	raw_num = num;
	str_len = 8;
	if(bit < 0 || bit > 8){
		printf("bitが0～7の範囲外の場合(Ret = FALSE)\n");
		return FALSE;
	}

	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		bin_part = raw_num % 2;
		if (raw_num != 0) {
				if (bin_part >= 0 && bin_part <= 9){
					*(str_f + str_len) = bin_part + 48;
				}
				// 数字から文字に変換 +55で整数(1~9)が文字に変わる
				else if(bin_part >= 10 && bin_part <= 15 ){
					*(str_f + str_len) = bin_part + 55;
				}
			  // 配列の一番右から順に一桁目の文字を入れていく
				raw_num /= 2;
		}
		// 残りの桁を0埋め
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
		printf("0か1以外の数字が入ってます");
	}

	if(onFlg == NULL){
		printf("onFlgがNULLの場合(Ret = FALSE)\n");
		return FALSE;
	}
}


/* 関数定義 問題5 */
BOOL SetBit(BYTE * num, int bit, BOOL onFlg){
		//変数の定義
		DWORD raw_num, str_len;
		int bin_part;
		char str_f[STR_LEN] = { '\0' };
		raw_num = *num;
		str_len = 8;
		if(bit < 0 || bit > 8){
			printf("bitが0～7の範囲外の場合(Ret = FALSE)\n");
			return FALSE;
		}

		// 変換した文字をstrに格納
		while(str_len > 0) {
			str_len--;
			bin_part = raw_num % 2;
			if (raw_num != 0) {
					if (bin_part >= 0 && bin_part <= 9){
						*(str_f + str_len) = bin_part + 48;
					}
					// 数字から文字に変換 +55で整数(1~9)が文字に変わる
					else if(bin_part >= 10 && bin_part <= 15 ){
						*(str_f + str_len) = bin_part + 55;
					}
				  // 配列の一番右から順に一桁目の文字を入れていく
					raw_num /= 2;
			}
			// 残りの桁を0埋め
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
			printf("numがNULLの場合(Ret = FALSE)\n");
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
	// 問題1 関数呼び出し
	MakeIntString(i, str, len);
	// 問題2 関数呼び出し
	MakeHexString(255, str1);
	// 問題3 関数呼び出し
	MakeBinString(5, str2);
  // 問題4 関数呼び出し
	GetBit(num, bit, &onFlg);
  // 問題5 関数呼び出し
	onFlg2 = FALSE;
	SetBit(&num, bit, onFlg2);

	}
