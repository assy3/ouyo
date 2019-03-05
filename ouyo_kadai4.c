#include <stdio.h>
#include <windows.h>
#include <string.h>

// �ۑ�4
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


// �֐��錾
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

	// �e�����o��NULL���Z�b�g
	list->FirstNodePtr = NULL;
	list->CurrentNodePtr = NULL;
	list->LastNodePtr = NULL;
	return TRUE;
}

OWLInsertObjToFirst(OneWayList * list, void * obj){
	// �擪����\������̂ŁA���݂̈ʒu��CurrentNodePtr�ɃZ�b�g�B
	list->CurrentNodePtr = list->FirstNodePtr;
		printf("-------------------------------------\n");
		OneWayListNode *newNodePos;
		//8�o�C�g
		newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));

		if (list->FirstNodePtr == NULL)
		{
				// �\��������̂��Ȃ��ꍇ�͉���������return�B
				printf("���X�g�͋�ł��B\n");
				list->FirstNodePtr = newNodePos;
				list->CurrentNodePtr = newNodePos;
		}


		//�L���X�g
		PersonalData *pobj = (PersonalData *)obj;
		printf("%d\n", pobj->usID);
		printf("%s\n", pobj->cName);
		printf("%s\n", pobj->cPhoneNo);

		list->CurrentNodePtr = list->FirstNodePtr;
		list->FirstNodePtr = newNodePos;


		//list->FirstNodePtr = pobj;
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
		//�|�C���^�^4�o�C�g
		newNodePos->ObjNodePtr = pobj;
		newNodePos->NextNodePtr = list->CurrentNodePtr;
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
		//newNodePos->ObjNodePtr = pobj;
		printf("list->FirstNodePtr %d\n", list->FirstNodePtr);
		printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);

		return TRUE;
}

OWLAddObjToLast(OneWayList * list, void * obj){
	printf("-------------------------------------\n");
	OneWayListNode *newNodePos;
	//8�o�C�g
	newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));
	//�L���X�g
	PersonalData *pobj = (PersonalData *)obj;
	printf("%d\n", pobj->usID);
	printf("%s\n", pobj->cName);
	printf("%s\n", pobj->cPhoneNo);

	list->LastNodePtr = newNodePos;


	//list->FirstNodePtr = pobj;
	printf("newNodePos->ObjNodePtr %d \n", newNodePos->ObjNodePtr);
	//�|�C���^�^4�o�C�g
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
	//�L���X�g
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
	//�L���X�g
	PersonalData **ppobj = (PersonalData **)obj;
	PersonalData **next = (PersonalData **)obj;
	ppobj = list->CurrentNodePtr->ObjNodePtr;
	next = list->CurrentNodePtr->NextNodePtr;
 	PersonalData *robj = ppobj;
	printf("%d\n", robj->usID);
	printf("%s\n", robj->cName);
	printf("%s\n", robj->cPhoneNo);
	list->CurrentNodePtr = next;

	return TRUE;
}






int main(void){
	OneWayList list;
	// STEP1-1�֐��Ăяo��
	OWLInitList(&list);

	PersonalData data[10];
	// �ꉞ�����l���Z�b�g
	data-> usID = 1;
	strcpy(data->cName, "ashikawa");
	strcpy(data->cPhoneNo, "0806670");
	OWLInsertObjToFirst(&list, data);
	(data + 1)-> usID = 2;
	strcpy((data + 1)->cName, "tanaka");
	strcpy((data + 1)->cPhoneNo, "999999999999999");
	OWLInsertObjToFirst(&list, (data+1));
	(data + 2)-> usID = 3;
	strcpy((data + 2)->cName, "marukusu");
	strcpy((data + 2)->cPhoneNo, "654364745");
	OWLAddObjToLast(&list, (data + 2));


	void **DataPtr;
	OWLGetFirstObj(&list, DataPtr);

	OWLGetNextObj(&list, DataPtr);





  return 0;
}
