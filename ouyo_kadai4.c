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
		printf("-------------------------------------\n");
		OneWayListNode *newNodePos;
		//8バイト
		newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));
		//キャスト
		PersonalData *pobj = (PersonalData *)obj;
		printf("%d\n", pobj->usID);
		printf("%s\n", pobj->cName);
		printf("%s\n", pobj->cPhoneNo);

		list->FirstNodePtr = newNodePos;


		//list->FirstNodePtr = pobj;
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
		//ポインタ型4バイト
		newNodePos->ObjNodePtr = pobj;
		newNodePos->NextNodePtr = NULL;
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
	//キャスト
	PersonalData *pobj = (PersonalData *)obj;
	printf("%d\n", pobj->usID);
	printf("%s\n", pobj->cName);
	printf("%s\n", pobj->cPhoneNo);

	list->LastNodePtr = newNodePos;


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
	(data + 1)-> usID = 2;
	strcpy((data + 1)->cName, "tanaka");
	strcpy((data + 1)->cPhoneNo, "999999999999999");
	OWLAddObjToLast(&list, (data + 1));





  return 0;
}
