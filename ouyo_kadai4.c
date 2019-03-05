#include <stdio.h>
#include <windows.h>
#include <string.h>

// 課題4
typedef struct tagPersonalData
{
    unsigned short usID;
    char cName[20];
    char cPhoneNo[15];
} PersonalData;

typedef struct tagOneWayListNode
{
	struct tagOneWayListNode * NextNodePtr;
	void * ObjNodePtr;
} OneWayListNode;

typedef struct tagOneWayList
{
	OneWayListNode * FirstNodePtr;
	OneWayListNode * CurrentNodePtr;
	OneWayListNode * LastNodePtr;
} OneWayList;

//グローバルで定義
OneWayListNode *g_NodePos;

// 関数宣言
// Step1
BOOL OWLInitList(OneWayList * list);
BOOL OWLInsertObjToFirst(OneWayList * list, void * obj);
BOOL OWLAddObjToLast(OneWayList * list, void * obj);
// Step2
BOOL OWLGetFirstObj(OneWayList * list, void ** obj);
BOOL OWLGetNextObj(OneWayList * list, void ** obj);
BOOL OWLGetLastObj(OneWayList * list, void ** obj);
// Step3
BOOL OWLReleaseAllNode(OneWayList * list);
BOOL OWLReleaseFirstNode(OneWayList * list);
BOOL OWLReleaseLastNode(OneWayList * list);
// Step4
BOOL OWLInsertObjBeforeCurrent(OneWayList * list, void * obj);
BOOL OWLReleaseCurrentNode(OneWayList * list);


BOOL PrintALL(OneWayList * list, void ** obj);


OWLInitList(OneWayList * list){
	//OneWayListNode *newNodePos;
	//newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));
	printf("------------------------\n");

	// 各メンバにNULLをセット
	list->FirstNodePtr = NULL;
	list->CurrentNodePtr = NULL;
	list->LastNodePtr = NULL;
	return TRUE;
}

OWLInsertObjToFirst(OneWayList * list, void * obj){

	// 先頭から表示するので、現在の位置をCurrentNodePtrにセット。
	  g_NodePos = list->FirstNodePtr;
		printf("-------------------------------------\n");
		OneWayListNode *newNodePos;
		//8バイト
		newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));

		if ((list->FirstNodePtr == NULL)&&(list->LastNodePtr))
		{
				// 表示するものがない場合は何もせずにreturn。
				printf("リストは空です。\n");
				list->FirstNodePtr = newNodePos;
				list->CurrentNodePtr = newNodePos;
				list->LastNodePtr = newNodePos;
		}

		//キャスト
		PersonalData *pobj = (PersonalData *)obj;
		printf("%d\n", pobj->usID);
		printf("%s\n", pobj->cName);
		printf("%s\n", pobj->cPhoneNo);

		list->FirstNodePtr = newNodePos;
		list->CurrentNodePtr = newNodePos;

		//list->FirstNodePtr = pobj;
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
		//ポインタ型4バイト
		newNodePos->ObjNodePtr = pobj;
		// 挿入前に先頭だったノードのアドレス
		newNodePos->NextNodePtr = g_NodePos;
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
		//newNodePos->ObjNodePtr = pobj;
		printf("list->FirstNodePtr %d\n", list->FirstNodePtr);
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);

		return TRUE;
}

OWLAddObjToLast(OneWayList * list, void * obj){
	printf("-------------------------------------\n");
	OneWayListNode *newNodePos;
	//8バイト
	newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));

	if ((list->FirstNodePtr == NULL)&&(list->LastNodePtr))
	{
			// 表示するものがない場合は何もせずにreturn。
			printf("リストは空です。\n");
			list->FirstNodePtr = newNodePos;
			list->CurrentNodePtr = newNodePos;
			list->LastNodePtr = newNodePos;
	}

	//キャスト
	PersonalData *pobj = (PersonalData *)obj;
	printf("%d\n", pobj->usID);
	printf("%s\n", pobj->cName);
	printf("%s\n", pobj->cPhoneNo);
	//malloc大事
	list->LastNodePtr = malloc(sizeof(list->LastNodePtr));
	printf("list->LastNodうんこePtr->NextNodePtr %d\n", list->LastNodePtr->NextNodePtr);
	list->LastNodePtr->NextNodePtr = newNodePos;
	printf("list->LastNodePtr->NextNodePtr %d\n", list->LastNodePtr->NextNodePtr);
	list->LastNodePtr = newNodePos;
	//g_NodePos->NextNodePtr = newNodePos;

	//list->FirstNodePtr = pobj;
	printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
	//ポインタ型4バイト
	newNodePos->ObjNodePtr = pobj;
	newNodePos->NextNodePtr = NULL;
	printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
	//newNodePos->ObjNodePtr = pobj;
	printf("list->FirstNodePtr %d\n", list->FirstNodePtr);
	printf("list->LastNodePtr %d\n", list->LastNodePtr);
	printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);

	return TRUE;
}


//STEP2
OWLGetFirstObj(OneWayList * list, void ** obj){
	printf("STEP2\n");
	//キャスト
	PersonalData **ppobj = (PersonalData **)obj;
	ppobj = list->FirstNodePtr->ObjNodePtr;
	PersonalData *robj = ppobj;
	printf("%d\n", robj->usID);
	printf("%s\n", robj->cName);
	printf("%s\n", robj->cPhoneNo);
	list->CurrentNodePtr = list->FirstNodePtr;

	return TRUE;
}

OWLGetNextObj(OneWayList * list, void ** obj){
	printf("STEP2-1\n");
	//キャスト
	PersonalData **ppobj = (PersonalData **)obj;
	OneWayListNode **next = (OneWayListNode **)obj;
	//ppobj = list->CurrentNodePtr->ObjNodePtr;
	next = list->CurrentNodePtr->NextNodePtr;
	OneWayListNode *next_obj = next;
	ppobj = next_obj->ObjNodePtr;
 	PersonalData *robj = ppobj;
	printf("%d\n", robj->usID);
	printf("%s\n", robj->cName);
	printf("%s\n", robj->cPhoneNo);
	printf("最後に参照した次のデータダヨーン\n");

	return TRUE;
}


OWLGetLastObj(OneWayList * list, void ** obj){
	printf("STEP2-2\n");
	//キャスト
	PersonalData **ppobj = (PersonalData **)obj;
	ppobj = list->LastNodePtr->ObjNodePtr;
	PersonalData *robj = ppobj;
	printf("%d\n", robj->usID);
	printf("%s\n", robj->cName);
	printf("%s\n", robj->cPhoneNo);
	list->CurrentNodePtr = list->LastNodePtr;

	return TRUE;

}

OWLReleaseAllNode(OneWayList * list){
	OneWayListNode *p, *temp;
	p = list->FirstNodePtr;
	 while( p != NULL ) {
			 temp = p->NextNodePtr; //次のデータの参照を取っておく
			 free( p );
			 printf("う\n");
			 p = temp;       //tempを次の処理対象に
	 }
	return TRUE;
}

OWLReleaseFirstNode(OneWayList * list){
	OneWayListNode *p;
	p = list->FirstNodePtr;
	list->FirstNodePtr = p->NextNodePtr;
	free( p );

	return TRUE;
}

OWLReleaseLastNode(OneWayList * list){
	OneWayListNode *p = list->FirstNodePtr; //リストの先頭を指すように
    while( (p->NextNodePtr) != NULL) {
			p = p->NextNodePtr;
    	if( p->NextNodePtr == list->LastNodePtr ){
					p->NextNodePtr = NULL;
					p = p->NextNodePtr;
					free( p );
			}
	 }
}


PrintALL(OneWayList * list, void ** obj){
	list->CurrentNodePtr = list->FirstNodePtr;

	while (1) {
		if(list->CurrentNodePtr->NextNodePtr != NULL){
			printf("---------------------------------------\n");
			PersonalData **ppobj = (PersonalData **)obj;
			ppobj = list->CurrentNodePtr->ObjNodePtr;
			PersonalData *robj = ppobj;
			printf("%d\n", robj->usID);
			printf("%s\n", robj->cName);
			printf("%s\n", robj->cPhoneNo);
			list->CurrentNodePtr = list->CurrentNodePtr->NextNodePtr;
			printf("---------------------------------------\n");
		}
		else{
			printf("最後まで示しました\n");
			//list->CurrentNodePtr = list->FirstNodePtr;
			return TRUE;
		}
	}
return TRUE;
}

BOOL OWLInsertObjBeforeCurrent(OneWayList * list, void * obj){
	return TRUE;

}
BOOL OWLReleaseCurrentNode(OneWayList * list){
	return TRUE;

}


int main(void){
	OneWayList list;
	// STEP1-1関数呼び出し
	OWLInitList(&list);

	PersonalData data[10];
	// 一応初期値をセット
	data-> usID = 1;
	strcpy(data->cName, "ashikawa");
	strcpy(data->cPhoneNo, "0806670");
	OWLInsertObjToFirst(&list, data);
	OWLInsertObjToFirst(&list, data);
	OWLInsertObjToFirst(&list, data);
	(data + 1) -> usID = 2;
	strcpy((data + 1)->cName, "tanaka");
	strcpy((data + 1)->cPhoneNo, "999999999999999");
	OWLInsertObjToFirst(&list, (data+1));
	(data + 2)-> usID = 3;
	strcpy((data + 2)->cName, "marukusu");
	strcpy((data + 2)->cPhoneNo, "654364745");
	OWLAddObjToLast(&list, (data + 2));
	OWLAddObjToLast(&list, (data + 2));
	OWLAddObjToLast(&list, (data + 2));
	OWLInsertObjToFirst(&list, data);


	void **DataPtr;

	OWLGetFirstObj(&list, DataPtr);

	PrintALL(&list, DataPtr);

	OWLGetNextObj(&list, DataPtr);

	PrintALL(&list, DataPtr);

	OWLGetNextObj(&list, DataPtr);

	PrintALL(&list, DataPtr);

	OWLGetLastObj(&list, DataPtr);

	PrintALL(&list, DataPtr);

	OWLReleaseFirstNode(&list);

	PrintALL(&list, DataPtr);

	OWLReleaseAllNode(&list);

	PrintALL(&list, DataPtr);

	OWLReleaseLastNode(&list);

	PrintALL(&list, DataPtr);

	OWLInsertObjBeforeCurrent(&list, data);
	OWLReleaseCurrentNode(&list);
  return 0;
}
