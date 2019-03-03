//#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
typedef struct student
{
    char name[20];         // ���O
    int id;                // �w�Дԍ�
    struct student *next;  // ���̃f�[�^������ꏊ
} STUDENT;
STUDENT *head = NULL; // ���X�g�̐擪
STUDENT *tail = NULL; // ���X�g�̖���
STUDENT *createNode(void);
void addNodeToList(void);
void printList(void);
int main(void)
{
    char input;
    char command;
    while (1)
    {
        printf("-------------������@-------------\n");
        printf("A : ���X�g�̖����Ƀm�[�h��ǉ����܂��B\n");
        printf("P : ���X�g���̃m�[�h��S�ĕ\�����܂��B\n");
        printf("�R�}���h����͂��Ă�������:");
        // ���͂��ꂽ�A���t�@�x�b�g��toupper�ő啶���ɕϊ��B
        // switch���̔���ɃA���t�@�x�b�g�̑啶�����g�����߁B
        scanf("%s", &input);
        command = toupper(input);
        switch (command)
        {
            case 'A':
                addNodeToList(); // ���X�g�����Ƀm�[�h�ǉ��B
                break;
            case 'P':
                printList(); // ���X�g�̓��e����ʕ\���B
                break;
            default:
                printf("�����ȃR�}���h�ł��B\n");
                break;
        }
        printf("\n");
    }
    return 0;
}
// �m�[�h�𐶐�����֐��B
STUDENT *createNode(void)
{
    // �V�����m�[�h1���̃��������m�ۂ��A���̏ꏊ��Ԃ��܂��B
    STUDENT *newNodePos;
    newNodePos = (STUDENT *)malloc(sizeof(STUDENT));
    return newNodePos;
}
// ���X�g�̖����Ƀm�[�h��ǉ�����֐��B
void addNodeToList(void)
{
    STUDENT *newNodePos;
    int inputId;
    char inputName[20];
    // �V�����m�[�h���쐬�B(1)
    newNodePos = createNode();
    printf("�w�Дԍ�����́F");
    scanf("%d", &inputId);
    newNodePos->id = inputId;
    printf("���O����́F");
    scanf("%s", inputName);
    strcpy(newNodePos->name, inputName);
    if ((head == NULL) && (tail == NULL))
    {
        // ���X�g����̏ꍇ�͂�����B
        // �V�����m�[�h���A�擪�������ɂȂ�B
        head = newNodePos;
        tail = newNodePos;
    }
    else
    {
        // ���X�g��1���ȏ�m�[�h�����݂���ꍇ�͂�����B
        // �����m�[�h(tail)��next�ɁA�V�����m�[�h�̏ꏊ���Z�b�g�B
        tail->next = newNodePos;
        // �ǉ������V�����m�[�h��tail�Ƃ���B
        tail = newNodePos;
    }
    // ���̃f�[�^�͖����̂ŁAnext�ɂ�NULL���Z�b�g�B
    tail ->next = NULL;
    printf("�m�[�h��ǉ����܂����B\n");
}
// ���X�g�̓��e��S�ĕ\������֐��B
void printList(void)
{
    STUDENT *current;
    if ((head == NULL) && (tail == NULL))
    {
        // �\��������̂��Ȃ��ꍇ�͉���������return�B
        printf("���X�g�͋�ł��B\n");
        return;
    }
    // �擪����\������̂ŁA���݂̈ʒu��head�ɃZ�b�g�B
    current = head;
    printf("----------------------------------\n");
    while (1)
    {
        printf("�w�Дԍ� : %d\n", current->id);
        printf("���O     : %s\n", current->name);
        printf("���g�̃m�[�h�̏ꏊ : %d\n", current);
        printf("���̃m�[�h�̏ꏊ   : %d\n", current->next);
        printf("----------------------------------\n");
        if (current->next != NULL)
        {
            // ���̏ꏊ��NULL�ł͂Ȃ��A�܂莟�̃m�[�h������B
            // ���݂̏ꏊ�����̃m�[�h�Ɉړ����܂��B
            current = current->next;
        }
        else
        {
            // ���̏ꏊ��NULL�Ȃ�A���݂̏ꏊ�̓��X�g�̖����B
            // �������̃f�[�^�͂Ȃ��̂ŁAbreak�Ń��[�v�I���B
            printf("�Ō�܂ŕ\�����܂����B\n");
            break;
        }
    }
}
