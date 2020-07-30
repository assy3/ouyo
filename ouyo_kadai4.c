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

/*���p�ۑ�4*/
int main(void){
	PersonalData *store_data[MEMBER]; //�i�[�p
	PersonalData *rem_obj; // �������Object�̃A�h���X���i�[����|�C���^
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
	//������
	while (flag != 1) {
		printf("A: ���X�g�Ƀm�[�h��ǉ����܂�\n");
		printf("S: �m�[�h���w���I�u�W�F�N�g���i�[���܂�\n");
		printf("D: ���X�g���̔C�ӂ̃m�[�h���폜���܂�\n");
		printf("N: ���[�v���甲����\n");
		
		scanf("%s", input);
		command = toupper(input[0]);

		switch (command)
		{
		case 'A':
			p = (PersonalData *)malloc(sizeof(PersonalData)); //�\���̂̃��������m��
			size_t size;
			size = malloc_usable_size(p);
			printf("%d", size);
			if (p == NULL) {
				printf("���������蓖�Ď��s\n");
			}
			// �f�[�^�Z�b�g�쐬
			printf("name����͂��Ă��������B");
			scanf("%s", name);
			printf("phoneNo����͂��Ă��������B");
			scanf("%s", phoneNo);
			// �f�[�^�Z�b�g�֐��Ăяo��
			check = SetPersonalData(p, id, name, phoneNo);
			if (check == FALSE) {
				printf("�f�[�^�Z�b�g�Ɏ��s���܂���\n");
			}
			
			printf("A: ���X�g�̂ǂ̈ʒu�Ƀm�[�h��ǉ����܂���?\n");
			printf("1: ���X�g�̐擪 \n");
			printf("2: ���X�g�̍Ō� \n");
			printf("3: ���X�g�̌��݈ʒu�̑O \n");
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
				printf("�����ȃR�}���h�ł�\n");
			}
			id++;
			break;

		case 'S':
			if (store_num > MEMBER) {
				printf("����ȏ�i�[�ł��܂���\n");
			}
			printf("S: ���X�g�̂ǂ̈ʒu�̃f�[�^�����o���܂���?\n");
			printf("1: ���X�g�̐擪�f�[�^ \n");
			printf("2: �Ō�ɎQ�Ƃ������̃f�[�^ \n");
			printf("3: ���X�g�̍Ō�̃f�[�^ \n");
			scanf("%d", &input_num);
			if (input_num == 1) {
				OWLGetFirstObj(&list, &store_data[store_num]);
				printf("�i�[���ꂽ�l\n");
				printf("%s \n", store_data[store_num]->cName);
				printf("%s \n", store_data[store_num]->cPhoneNo);
				printf("%x \n", store_data[store_num]->usID);
				store_num++;
				PrintAllNode(&list);
			}
			else if (input_num == 2)
			{
				OWLGetNextObj(&list, &store_data[store_num]);
				printf("�i�[���ꂽ�l\n");
				if (store_data[store_num] != NULL) {
					printf("%s \n", store_data[store_num]->cName);
					printf("%s \n", store_data[store_num]->cPhoneNo);
					printf("%x \n", store_data[store_num]->usID);
					store_num++;
				}
				else {
					printf("�i�[����f�[�^������܂���\n");
				}
				PrintAllNode(&list);
			}
			else if (input_num == 3)
			{
				OWLGetLastObj(&list, &store_data[store_num]);
				printf("�i�[���ꂽ�l\n");
				printf("%s \n", store_data[store_num]->cName);
				printf("%s \n", store_data[store_num]->cPhoneNo);
				printf("%x \n", store_data[store_num]->usID);
				store_num++;
				PrintAllNode(&list);
			}
			else {
				printf("�����ȃR�}���h�ł�\n");
			}
			break;

		case 'D':
			if (list.FirstNodePtr == NULL && list.LastNodePtr == NULL) {
				printf("���X�g����ł�");
				break;
			}
			printf("D: ���X�g�̂ǂ̃m�[�h��������܂���?\n");
			printf("1: �S�Ẵm�[�h \n");
			printf("2: ���X�g�̐擪�m�[�h \n");
			printf("3: ���X�g�̍Ō�̃m�[�h \n");
			printf("4: ���݈ʒu�̃m�[�h \n");
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
					temp = list_p->NextNodePtr; //���̃f�[�^�̎Q�Ƃ�����Ă���
					size_t size;
					size = malloc_usable_size(list_p->ObjNodePtr);
					printf("%d", size);
					free(list_p->ObjNodePtr);
					list_p = temp;       //temp�����̏����Ώۂ�
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
				printf("�����ȃR�}���h�ł�\n");
			}
			break;

		case 'N':
			flag = 1;
			break;

		default:
			printf("�����ȃR�}���h�ł�\n");
			break;
		}
	}

	getchar();
	getchar();
	return 0;

}