# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <windows.h>
# include <string.h>
# include "PersonalData_func.h"
# include "OneWayList_func.h"

// STEP1-1 OneWayListNode ������������֐�
BOOL OWLInitList(OneWayList * list){
	BOOL ret;
	if (list == NULL){
		goto l_Error;
	}
	
	// �e�����o��NULL���Z�b�g
	list->FirstNodePtr = NULL;
	list->CurrentNodePtr = NULL;
	list->LastNodePtr = NULL;
	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP1-2 �f�[�^�����X�g�̐擪�ɑ}������֐�
BOOL OWLInsertObjToFirst(OneWayList * list, void * obj){
	BOOL ret;
	OneWayListNode * newNodePos;
	OneWayListNode * TempNodePos;
	if (list == NULL || obj == NULL){
		goto l_Error;
	}
	//8�o�C�g���̗̈�m��
	newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));
	TempNodePos = list->FirstNodePtr;

	if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL))
	{
		list->FirstNodePtr = newNodePos;
		list->CurrentNodePtr = newNodePos;
		list->LastNodePtr = newNodePos;

		newNodePos->ObjNodePtr = obj;
		newNodePos->NextNodePtr = NULL;
	}
	else{
		list->FirstNodePtr = newNodePos;
		list->CurrentNodePtr = newNodePos;

		newNodePos->ObjNodePtr = obj;
		newNodePos->NextNodePtr = TempNodePos;

	}

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP1-3 �f�[�^�����X�g�̍Ō�ɒǉ�����֐�
BOOL OWLAddObjToLast(OneWayList * list, void * obj){
	BOOL ret;
	OneWayListNode * newNodePos;
	OneWayListNode * TempNodePos;
	if (list == NULL || obj == NULL){
		goto l_Error;
	}
	//8�o�C�g
	newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));
	TempNodePos = list->LastNodePtr;
	if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL))
	{
		list->FirstNodePtr = newNodePos;
		list->CurrentNodePtr = newNodePos;
		list->LastNodePtr = newNodePos;

		newNodePos->ObjNodePtr = obj;
		newNodePos->NextNodePtr = NULL;
	}
	else{
		list->CurrentNodePtr = newNodePos;
		list->LastNodePtr = newNodePos;

		newNodePos->ObjNodePtr = obj;
		newNodePos->NextNodePtr = NULL;
		TempNodePos->NextNodePtr = newNodePos;
	}

	ret = TRUE;

l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP2-1 ���X�g�̐擪�̃f�[�^�����o���֐�
BOOL OWLGetFirstObj(OneWayList * list, void ** obj){
	BOOL ret;
	if (list == NULL || obj == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		*obj = NULL;
		ret = TRUE;
		goto l_EXIT;
	}
	else {
		// nop
	}
	*obj = list->FirstNodePtr->ObjNodePtr;
	list->CurrentNodePtr = list->FirstNodePtr;

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP2-2 �Ō�ɎQ�Ƃ����f�[�^�̎��̃f�[�^�����o���֐�
BOOL OWLGetNextObj(OneWayList * list, void ** obj){
	BOOL ret;
	if (list == NULL || obj == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		*obj = NULL;
	}
	// �m�[�h��1�����Ȃ��ꍇ
	else if (list->FirstNodePtr == list->LastNodePtr) {
		*obj = NULL;
	}
	else if (list->CurrentNodePtr->NextNodePtr == NULL) {
		*obj = NULL;
	}
	else {
		*obj = list->CurrentNodePtr->NextNodePtr->ObjNodePtr;
		list->CurrentNodePtr = list->CurrentNodePtr->NextNodePtr;
	}
	
	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP2-3 ���X�g�̍Ō�̃f�[�^�����o���֐�
BOOL OWLGetLastObj(OneWayList * list, void ** obj){
	BOOL ret;
	if (list == NULL || obj == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		*obj = NULL;
		ret = TRUE;
		goto l_EXIT;
	}
	else {
		// nop
	}
	
	*obj = list->LastNodePtr->ObjNodePtr;
	list->CurrentNodePtr = list->LastNodePtr;
	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP3-1 ���X�g�̑S�Ẵm�[�h���������֐�
BOOL OWLReleaseAllNode(OneWayList * list){
	BOOL ret;
	OneWayListNode *p, *temp;
	if (list == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		ret = TRUE;
		goto l_EXIT;
	}
	else
	{
		// nop
	}

	p = list->FirstNodePtr;
	while (p != NULL) {
		temp = p->NextNodePtr; //���̃f�[�^�̎Q�Ƃ�����Ă���
		free(p);
		p = temp;       //temp�����̏����Ώۂ�
	}
	OWLInitList(list);
	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP3-2 ���X�g�̐擪�̃m�[�h���������֐�
BOOL OWLReleaseFirstNode(OneWayList * list){
	BOOL ret;
	OneWayListNode *p = list->FirstNodePtr;
	OneWayListNode * l_tmp = list->LastNodePtr;
	if (list == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		ret = TRUE;
		goto l_EXIT;
	}
	else
	{
		// nop
	}
	// �m�[�h��1�����Ȃ��ꍇ
	if (list->FirstNodePtr == list->LastNodePtr) {
		OWLInitList(list);
		free(l_tmp);
	}
	else{
		list->CurrentNodePtr = p->NextNodePtr;
		list->FirstNodePtr = p->NextNodePtr;
		free(p);
	}
	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP3-3 ���X�g�̍Ō�̃m�[�h���������֐�
BOOL OWLReleaseLastNode(OneWayList * list){
	BOOL ret;
	OneWayListNode *p = list->FirstNodePtr; //���X�g�̐擪���w���悤��
	OneWayListNode * c_tmp = list->CurrentNodePtr;
	OneWayListNode * l_tmp = list->LastNodePtr;
	if (list == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		ret = TRUE;
		goto l_EXIT;
	}
	else
	{
		// nop
	}

	while (1) {
		// �m�[�h��1�����Ȃ��ꍇ
		if (list->FirstNodePtr == list->LastNodePtr) {
			free(l_tmp);
			OWLInitList(list);
			break;
		}
		// �m�[�h��2�ȏ�̏ꍇ
		else if (p->NextNodePtr == list->LastNodePtr){
			p->NextNodePtr = NULL;
			free(l_tmp);
			list->CurrentNodePtr = p;
			list->LastNodePtr = p;
			break;
		}
		else {
			// nop
		}
		p = p->NextNodePtr;
	}

	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}


// STEP4-1 �f�[�^�����݈ʒu�̑O�ɑ}������֐�
BOOL OWLInsertObjBeforeCurrent(OneWayList * list, void * obj){
	BOOL ret;
	OneWayListNode * newNodePos;
	OneWayListNode *p;
	if (list == NULL || obj == NULL) {
		goto l_Error;
	}
	//p = list->FirstNodePtr;
	//8�o�C�g
	newNodePos = (OneWayListNode *)malloc(sizeof(OneWayListNode));
	p = list->FirstNodePtr;
	
	while (1) {
		if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL))
		{
			list->FirstNodePtr = newNodePos;
			list->CurrentNodePtr = newNodePos;
			list->LastNodePtr = newNodePos;

			newNodePos->ObjNodePtr = obj;
			newNodePos->NextNodePtr = NULL;
			break;
		}
		else if(p->NextNodePtr == list->CurrentNodePtr){
			p->NextNodePtr = newNodePos;
			newNodePos->ObjNodePtr = obj;
			newNodePos->NextNodePtr = list->CurrentNodePtr;
			break;
		}
		else{
			// nop
		}

		if (list->FirstNodePtr == list->CurrentNodePtr){
			newNodePos->ObjNodePtr = obj;
			newNodePos->NextNodePtr = list->CurrentNodePtr;
			list->FirstNodePtr = newNodePos;
			list->CurrentNodePtr = newNodePos;
			break;
		}
		p = p->NextNodePtr;
	}
	list->CurrentNodePtr = newNodePos;
	
	ret = TRUE;
l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}

// STEP4-2 ���݈ʒu�̃m�[�h���������֐�
BOOL OWLReleaseCurrentNode(OneWayList * list){
	BOOL ret;
	OneWayListNode *p = list->FirstNodePtr;
	OneWayListNode * c_tmp = list->CurrentNodePtr;
	OneWayListNode * next_node = list->CurrentNodePtr->NextNodePtr;
	if (list == NULL) {
		goto l_Error;
	}
	else if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)) {
		ret = TRUE;
		goto l_EXIT;
	}
	else
	{
		// nop
	}

	while (1) {
		// �m�[�h��1�����Ȃ��ꍇ
		if (list->FirstNodePtr == list->LastNodePtr) {
			free(c_tmp);
			OWLInitList(&list);
			break;
		}

		if(list->CurrentNodePtr == list->FirstNodePtr){
			list->FirstNodePtr = next_node;
		}
		else if (list->CurrentNodePtr == list->LastNodePtr) {
			list->LastNodePtr = p;
		}
		// Cureent���
		else if (p->NextNodePtr == list->CurrentNodePtr){
			p->NextNodePtr = next_node;
			list->CurrentNodePtr = p;
			free(c_tmp);
			break;
		}
		else {
			// nop
		}
		p = p->NextNodePtr;
	}
	ret = TRUE;

l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}


// �f�o�b�N�p
BOOL PrintAllNode(OneWayList * list){
	BOOL ret = TRUE;
	int count = 1;
	OneWayListNode *current;
	current = list->FirstNodePtr;
	PersonalData * robj;
	if ((list->FirstNodePtr == NULL) && (list->LastNodePtr == NULL)){
		printf("���X�g�͋�ł�\n");
		goto l_EXIT;
	}
	while (1)
	{
		printf("node%d--------------------------------------------\n", count);
		//�L���X�g
		robj = (PersonalData *)(current->ObjNodePtr);
		printf("%d\n", robj->usID);
		printf("%s\n", robj->cName);
		printf("%s\n", robj->cPhoneNo);
		printf("--------------------------------------------node%d\n\n", count);
		if (current->NextNodePtr != NULL){
			current = (OneWayListNode *)(current->NextNodePtr);
			count++;
		}
		else{
			printf("�o�͊���\n");
			break;
		}
	}
	ret = TRUE;

l_EXIT:
	return ret;
l_Error:
	ret = FALSE;
	goto l_EXIT;
}