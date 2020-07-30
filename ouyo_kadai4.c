#define _CRT_SECURE_NO_WARNINGS
#define  MEMBER (30)
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#define malloc_usable_size(a) _msize(a)
#include "PersonalData_func.h"
#include "OneWayList_func.h"

/*応用課題4*/
int main(void){
	PersonalData *store_data[MEMBER]; //格納用
	PersonalData *rem_obj; // 解放するObjectのアドレスを格納するポインタ
	PersonalData * p;
	OneWayListNode *list_p, *temp;
	OneWayList list;
	unsigned short id = 1;
	int flag = 0;
	int select = 0;
	int store_num = 0;
	int remove_num = 0;
	int input_num;
	char command;
	char input[20];
	char name[20];
	char phoneNo[15];
	BOOL check;

	OWLInitList(&list);
	//初期化
	while (flag != 1) {
		printf("A: リストにノードを追加します\n");
		printf("S: ノードが指すオブジェクトを格納します\n");
		printf("D: リスト内の任意のノードを削除します\n");
		printf("N: ループから抜ける\n");
		
		scanf("%s", input);
		command = toupper(input[0]);

		switch (command)
		{
		case 'A':
			p = (PersonalData *)malloc(sizeof(PersonalData)); //構造体のメモリを確保
			size_t size;
			size = malloc_usable_size(p);
			printf("%d", size);
			if (p == NULL) {
				printf("メモリ割り当て失敗\n");
			}
			// データセット作成
			printf("nameを入力してください。");
			scanf("%s", name);
			printf("phoneNoを入力してください。");
			scanf("%s", phoneNo);
			// データセット関数呼び出し
			check = SetPersonalData(p, id, name, phoneNo);
			if (check == FALSE) {
				printf("データセットに失敗しました\n");
			}
			
			printf("A: リストのどの位置にノードを追加しますか?\n");
			printf("1: リストの先頭 \n");
			printf("2: リストの最後 \n");
			printf("3: リストの現在位置の前 \n");
			scanf("%d", &input_num);
			if (input_num == 1) {
				OWLInsertObjToFirst(&list, p);
				PrintAllNode(&list);
			}
			else if (input_num == 2)
			{
				OWLAddObjToLast(&list, p);
				PrintAllNode(&list);
			}
			else if (input_num == 3)
			{
				OWLInsertObjBeforeCurrent(&list, p);
				PrintAllNode(&list);
			}
			else {
				printf("無効なコマンドです\n");
			}
			id++;
			break;

		case 'S':
			if (store_num > MEMBER) {
				printf("これ以上格納できません\n");
			}
			printf("S: リストのどの位置のデータを取り出しますか?\n");
			printf("1: リストの先頭データ \n");
			printf("2: 最後に参照した次のデータ \n");
			printf("3: リストの最後のデータ \n");
			scanf("%d", &input_num);
			if (input_num == 1) {
				OWLGetFirstObj(&list, &store_data[store_num]);
				printf("格納された値\n");
				printf("%s \n", store_data[store_num]->cName);
				printf("%s \n", store_data[store_num]->cPhoneNo);
				printf("%x \n", store_data[store_num]->usID);
				store_num++;
				PrintAllNode(&list);
			}
			else if (input_num == 2)
			{
				OWLGetNextObj(&list, &store_data[store_num]);
				printf("格納された値\n");
				if (store_data[store_num] != NULL) {
					printf("%s \n", store_data[store_num]->cName);
					printf("%s \n", store_data[store_num]->cPhoneNo);
					printf("%x \n", store_data[store_num]->usID);
					store_num++;
				}
				else {
					printf("格納するデータがありません\n");
				}
				PrintAllNode(&list);
			}
			else if (input_num == 3)
			{
				OWLGetLastObj(&list, &store_data[store_num]);
				printf("格納された値\n");
				printf("%s \n", store_data[store_num]->cName);
				printf("%s \n", store_data[store_num]->cPhoneNo);
				printf("%x \n", store_data[store_num]->usID);
				store_num++;
				PrintAllNode(&list);
			}
			else {
				printf("無効なコマンドです\n");
			}
			break;

		case 'D':
			if (list.FirstNodePtr == NULL && list.LastNodePtr == NULL) {
				printf("リストが空です");
				break;
			}
			printf("D: リストのどのノードを解放しますか?\n");
			printf("1: 全てのノード \n");
			printf("2: リストの先頭ノード \n");
			printf("3: リストの最後のノード \n");
			printf("4: 現在位置のノード \n");
			scanf("%d", &input_num);
			if (input_num == 1) {
				/*
				remove_num = 0;
				OWLGetFirstObj(&list, &remove_object[remove_num]);
				while(remove_object[remove_num] != NULL){
					remove_num++;
					OWLGetNextObj(&list, &remove_object[remove_num]);
				}

				remove_num = 0;
				while(remove_object[remove_num] != NULL){
					free(remove_object[remove_num]);
						remove_num++;
				}
				OWLReleaseAllNode(&list);
				*/
				OWLGetFirstObj(&list, &rem_obj);
				size_t size;
				size = malloc_usable_size(rem_obj);
				printf("%d", size);
				free(rem_obj);
				while (list.CurrentNodePtr != list.LastNodePtr) {
					OWLGetNextObj(&list, &rem_obj);
					size = malloc_usable_size(rem_obj);
					printf("%d", size);
					free(rem_obj);
				}
				OWLReleaseAllNode(&list);


				/*
				list_p = list.FirstNodePtr;
				while (list_p != NULL) {
					temp = list_p->NextNodePtr; //次のデータの参照を取っておく
					size_t size;
					size = malloc_usable_size(list_p->ObjNodePtr);
					printf("%d", size);
					free(list_p->ObjNodePtr);
					list_p = temp;       //tempを次の処理対象に
				}
				OWLReleaseAllNode(&list);
				*/
				PrintAllNode(&list);
			}
			else if (input_num == 2)
			{
				OWLGetFirstObj(&list, &rem_obj);
				size_t size;
				size = malloc_usable_size(rem_obj);
				printf("%d", size);
				free(rem_obj);
				OWLReleaseFirstNode(&list);
				
				//free((list.FirstNodePtr)->ObjNodePtr);
				//OWLReleaseFirstNode(&list);
				//PrintAllNode(&list);
			}
			else if (input_num == 3)
			{	
				OWLGetLastObj(&list, &rem_obj);
				printf("%d\n\n", sizeof(rem_obj));
				size_t size;
				size = malloc_usable_size(rem_obj);
				printf("%d", size);
				free(rem_obj);
				OWLReleaseLastNode(&list);

				//free((list.LastNodePtr)->ObjNodePtr);
				//OWLReleaseLastNode(&list);
				//PrintAllNode(&list);
			}
			else if (input_num == 4)
			{	
				
				temp = list.CurrentNodePtr;
				OWLGetFirstObj(&list, &rem_obj);
				while (list.CurrentNodePtr != list.LastNodePtr) {
					OWLGetNextObj(&list, &rem_obj);
					size = malloc_usable_size(rem_obj);
					printf("%d", size);
					if(list.CurrentNodePtr == temp){
						free(rem_obj);
						OWLReleaseCurrentNode(&list);
						break;
					}
				}
				//free((list.CurrentNodePtr)->ObjNodePtr);
				//OWLReleaseCurrentNode(&list);
				//PrintAllNode(&list);
			}
			else {
				printf("無効なコマンドです\n");
			}
			break;

		case 'N':
			flag = 1;
			break;

		default:
			printf("無効なコマンドです\n");
			break;
		}
	}

	getchar();
	getchar();
	return 0;

}