#include <stdio.h>
#include <windows.h>
#include <string.h>
#define STR_LEN (30)
static BOOL ret;
static unsigned short g_count = 0;
static unsigned short g_packed_kouzoutai;

FILE *g_fp;   // 出力ストリーム

// 課題3
// バイト境界4バイト
typedef struct tagPersonalData
{
    unsigned short usID;
    char cName[20];
    char cPhoneNo[15];
} PersonalData;

// Step1関数
BOOL SetPersonalData(PersonalData * data, unsigned short id, char * name, char * phoneNo);
BOOL WritePersonalDataArray(PersonalData * dataArray, unsigned short num, char * fileName);


// Step2関数
BOOL OpenPersonalData(char * fileName, unsigned short * numRecords);
BOOL ReadPersonalData(unsigned short pos, PersonalData * data);
BOOL ClosePersonalData(void);
BOOL GetPersonalData(PersonalData * data, unsigned short * id, char * name, char * phoneNo);

// Step3関数
BOOL SearchPersonalDataByID(unsigned short id, PersonalData * data);
BOOL SearchPersonalDataByName(char * name, PersonalData * data);


// Step1-1関数 データの作成
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

    // 0埋め
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

// Step1-2関数　ファイル出力
WritePersonalDataArray(PersonalData * dataArray, unsigned short num, char * fileName){
    if (fileName == NULL) {
        //printf("cannot open\n");
        goto l_Error;
    }
    else if (num == 0 || dataArray == NULL){
        goto l_Error;
    }

    FILE * outputfile;
    outputfile = fopen(fileName, "wb");  // ファイルを書き込み用にオープン(開く)
    if (outputfile == NULL){
        fclose(outputfile);          // ファイルをクローズ(閉じる)
        goto l_Error;
    }

    int i, j;
    // 重複するidの処理
    for (i = 0; i < num; i++){
        for (j = 0; j < num; j++){
            if (i != j){
                if (dataArray[i].usID == dataArray[j].usID){
                    goto l_Error;
                }
            }
        }
    }
		//データ数2バイト
    fwrite(&g_count, sizeof(g_count), 1, outputfile);
		// 37バイト分の構造体データを書き込む
    for (i = 0; i<num; i++){
      	fwrite(dataArray, g_packed_kouzoutai, 1, outputfile);
        dataArray++;
    }
    fclose(outputfile);          // ファイルをクローズ(閉じる)
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
    if (g_fp == NULL) {          // 読み込みに失敗した場合
        goto l_Error;
    }
  	fread(numRecords, sizeof(*numRecords), 1, g_fp);
    // closeはしない
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
		// pos番目のデータをdataのアドレスに格納
		// 2はファイルの先頭にあるデータ数2バイトのこと
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
    if (g_fp == NULL) {    // オープンされていない
        goto l_Error;
    }
    int close;
    close = fclose(g_fp);
    // 0はclose成功
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
    strcpy(name, data->cName);     /* 文字型配列に文字型配列をコピー */
    strcpy(phoneNo, data->cPhoneNo);     /* 文字型配列に文字型配列をコピー */

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
		// pos番目のデータをdataのアドレスに格納
		//openの時にポインタが2進からなくてもいい
		fseek(g_fp, 2 , SEEK_SET);

		for(i = 0; i < g_count; i++){
			fread(&c_id, 2, 1, g_fp);
			if(c_id == id){
				data->usID = c_id;
				fread(data->cName, 20, 1, g_fp);
				fread(data->cPhoneNo, 15, 1, g_fp);
			}
			else{
				// cNameとcPhoneの35バイトすすめる　
				fseek(g_fp,(g_packed_kouzoutai - 2), SEEK_CUR);
				check_id++;
			}
		}
		// 条件位一致するデータが無い場合
		if(check_id != g_count){
			printf("条件に一致するデータはありません\n");
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
	//ファイルOpen時に2バイト進んでいる
	fseek(g_fp, 2 , SEEK_CUR);

	for(i = 0; i < g_count; i++){
		fread(sreach_name, 20, 1, g_fp);

		if(strcmp(name, sreach_name) == 0){
			printf("同じ文字みつかった\n");
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
// 条件位一致するデータが無い場合
if(check_name_num != g_count){
	printf("条件に一致するデータはありません\n");
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
        printf("nameを入力してください。");
        scanf("%s", name);
        printf("phoneNoを入力してください。");
        scanf("%s", phoneNo);
        // データセット関数呼び出し
        check = SetPersonalData((data + m), id, name, phoneNo);
				if(check == FALSE){
					printf("データセットに失敗しました\n");
				}

        printf("データセットを続けない 1 続ける else \n");
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
    // ファイル出力関数呼び出し
    check = WritePersonalDataArray(data, num, fileName);
		if(check == FALSE){
			printf("ファイル出力に失敗しました\n");
		}

    unsigned short numRecords;
    unsigned short position;
    // ファイルオープン関数呼び出し
    check = OpenPersonalData(fileName, &numRecords);
		if(check == FALSE){
			printf("ファイルオープンに失敗しました\n");
		}
		printf("何番目のデータを格納しますか？ (position)\n");
		scanf("%u", &position);
    //ファイルの読み込みを行なう関数
    check = ReadPersonalData(position, data);
		if(check == FALSE){
			printf("ファイル読み込みに失敗しました\n");
		}
		printf("格納しました\n");
    //ファイルを閉じる関数
    check = ClosePersonalData();
		if(check == FALSE){
			printf("ファイルクローズに失敗しました\n");
		}

    for (i = 0; i < g_count; i++){
        //データの解釈を行なう関数
        check = GetPersonalData(data + i, &id, name, phoneNo);
				if(check == FALSE){
					printf("データ解釈に失敗しました\n");
				}
        printf("id  %d  name  %s  phoneNo  %s\n",id, name, phoneNo);
        printf("---------------\n");
    }

		printf("IDを検索する:0 名前を検索する:1\n");
		scanf("%d", &select);
		if(select == 0){
				OpenPersonalData(fileName, &numRecords);
				printf("何番目のidのデータを検索しますか？ (id)\n");
				scanf("%u", &id);
				// id検索
				SearchPersonalDataByID(id, data);
				//ファイルを閉じる関数
				ClosePersonalData();
		}
		else if(select == 1){
				OpenPersonalData(fileName, &numRecords);
				printf("検索するnameを入力してください(name)\n");
				scanf("%s", name);
				SearchPersonalDataByName(name, data);
				//ファイルを閉じる関数
				ClosePersonalData();
		}
		else{
			printf("正しい数字を入力してください\n");
		}

    getchar();
    getchar();
    return 0;
}
