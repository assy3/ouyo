//#include "stdafx.h"
#include "stdio.h"
#include "string.h"
// ���ȎQ�ƍ\���̂́uSTUDENT�^�v���`�I
typedef struct student
{
    char name[20];         // ���O
    int id;                // �w�Дԍ�
    struct student *next;  // ���̃f�[�^������ꏊ
} STUDENT;
STUDENT createStudent(char *studentName, int studentId);
int main(void)
{
    // STUDENT�^�̃|�C���^�B���݂́u�ꏊ�v��\����B
    STUDENT *current;
    // 4���̃m�[�h�𐶐��B(1)
    // ���̎��_�ł́A�܂����X�g�\���ɂȂ��Ă��܂���B
    STUDENT student1 = createStudent("���c�^��\0", 1);
    STUDENT student2 = createStudent("���q����\0", 2);
    STUDENT student3 = createStudent("��c����\0", 3);
    STUDENT student4 = createStudent("�������̂�\0", 4);
    // �e�m�[�h�ɂ��āA�u���̏ꏊ�v���Z�b�g�B
    // �����Ń��X�g�\���ɂȂ�܂��B(2)
    student1.next = &student2;
    student2.next = &student3;
    student3.next = &student4;
    student4.next = NULL;
    // while���[�v���g���āA���X�g���̑S�f�[�^��\�������B(3)
    // �u���݂̏ꏊ�v�ɁA���X�g�擪�́ustudent1�v�̏ꏊ���Z�b�g�I
    current = &student1;
    while (1)
    {
        printf("�w�Дԍ� : %d\n", current->id);
        printf("���O     : %s\n", current->name);
        printf("���g�̃m�[�h�̏ꏊ : %d\n", current);
        printf("���̃m�[�h�̏ꏊ   : %d\n", current->next);
        printf("------------------------------------------------------\n");
        if (current->next != NULL)
        {
            // ���̏ꏊ��NULL�ł͂Ȃ��A�܂莟�̃f�[�^������B
            // �u���݂̏ꏊ�v�����̏ꏊ�Ɉړ����܂��B
            current = current->next;
        }
        else
        {
            // ���̏ꏊ��NULL�Ȃ�A���݂̏ꏊ�̓��X�g�̖����B
            // �������̃f�[�^�͂Ȃ��̂ŁAbreak�Ń��[�v�I���B
            printf("�Ō�܂ŕ\��������I\n");
            break;
        }
    }
    return 0;
}
// �V�����m�[�h�𐶐�����֐��B
STUDENT createStudent(char *studentName, int studentId)
{
    STUDENT newStudent;
    // �V����STUDENT�^�ϐ��ɁAname��id���Z�b�g���ĕԂ��B
    strcpy(newStudent.name, studentName);
    newStudent.id = studentId;
    return newStudent;
}
