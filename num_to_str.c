#include <stdio.h>
#include <windows.h>
#define STR_LEN (30)
#define STORE_SIZE (16)

/* 関数宣言 */
BOOL MakeIntString(DWORD num, char * str, DWORD len);
BOOL MakeHexString(DWORD num, char * str);
BOOL MakeBinString(BYTE num, char * str);

/* 関数定義 */
BOOL MakeIntString(DWORD num, char * str, DWORD len) {
	//変数の定義
	//入力エラー処理
	DWORD sorce_num, str_len;
	if(str == NULL || len == 0){
		printf("strがNULLもしくはlenが0(Ret = FALSE)\n");
		return FALSE;
	}
	sorce_num = num;
	str_len = len;
	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		if (sorce_num != 0) {
			// 数字から文字に変換 +48で整数が文字に変わる
			*(str + str_len) = (sorce_num % 10) + 48; //配列の一番右から順に一桁目の文字を入れていく
			sorce_num /= 10;
		}
		// 残りの桁を0埋め
		else {
			*(str + str_len) = '0';
		}
	}
	*(str + len) = '\0';
	//出力
	printf("MakeIntString(%d, str, %d) → ", num, len);
	if (sorce_num == 0) {
		printf("str = %s(Ret=TRUE)\n", str);
		return TRUE;
	}
	else {
		printf("str = %s(Ret=FALS+E)\n", str);
		return FALSE;
	}
}

/* 関数定義 */
BOOL MakeHexString(DWORD num, char * str) {
	//変数の定義
	DWORD sorce_num, str_len;
	int hex_part;
	sorce_num = num;
	str_len = STORE_SIZE;
	if(str == NULL){
		printf("strがNULL(Ret = FALSE)\n");
		goto label;
	}
	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		hex_part = sorce_num % 16;
		if (sorce_num != 0) {
				if (hex_part >= 0 && hex_part <= 9){
					*(str + str_len) = hex_part + 48;
				}
				// 数字から文字に変換 +55で整数(1~9)が文字に変わる
				else if(hex_part >= 10 && hex_part <= 15 ){
					*(str + str_len) = hex_part + 55;
				}
			  // 配列の一番右から順に一桁目の文字を入れていく
				sorce_num /= 16;
		}
		// 残りの桁を0埋め
		else {
			*(str + str_len) = '0';
		}
	}

	*(str + STORE_SIZE) = '\0';
	//出力
	printf("MakeHexString(%d, str) → ", num);
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


/* 関数定義 */
BOOL MakeBinString(BYTE num, char * str){
	//変数の定義
	DWORD sorce_num, str_len;
	int bin_part;
	sorce_num = num;
	str_len = STORE_SIZE;
	if(str == NULL){
		printf("strがNULL(Ret = FALSE)\n");
		goto label;
	}

	// 変換した文字をstrに格納
	while(str_len > 0) {
		str_len--;
		bin_part = sorce_num % 2;
		if (sorce_num != 0) {
			*(str + str_len) = bin_part + 48;
		  // 配列の一番右から順に一桁目の文字を入れていく
			sorce_num /= 2;
		}
		// 残りの桁を0埋め
		else {
			*(str + str_len) = '0';
		}
	}
	*(str + STORE_SIZE) = '\0';
	//出力
	printf("MakeBinString(%d, str) → ", num);
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
	// 変換後の文字列を格納するための配列
	char str1[STR_LEN] = { '\0' };
	char str2[STR_LEN] = { '\0' };
	char str3[STR_LEN] = { '\0' };
	// 数字を10進の文字列に変換
	MakeIntString(i, str1, len);
	// 数字を16進の文字列に変換
	MakeHexString(200, str2);
	// 数字を2進の文字列に変換
	MakeBinString(200, str3);
}
