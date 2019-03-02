//#include "stdafx.h"
#include "stdio.h"
#include "string.h"
// 自己参照構造体の「STUDENT型」を定義！
typedef struct student
{
    char name[20];         // 名前
    int id;                // 学籍番号
    struct student *next;  // 次のデータがある場所
} STUDENT;
STUDENT createStudent(char *studentName, int studentId);
int main(void)
{
    // STUDENT型のポインタ。現在の「場所」を表すよ。
    STUDENT *current;
    // 4件のノードを生成。(1)
    // この時点では、まだリスト構造になっていません。
    STUDENT student1 = createStudent("内田真礼\0", 1);
    STUDENT student2 = createStudent("佐倉綾音\0", 2);
    STUDENT student3 = createStudent("種田梨沙\0", 3);
    STUDENT student4 = createStudent("水瀬いのり\0", 4);
    // 各ノードについて、「次の場所」をセット。
    // ここでリスト構造になります。(2)
    student1.next = &student2;
    student2.next = &student3;
    student3.next = &student4;
    student4.next = NULL;
    // whileループを使って、リスト内の全データを表示するよ。(3)
    // 「現在の場所」に、リスト先頭の「student1」の場所をセット！
    current = &student1;
    while (1)
    {
        printf("学籍番号 : %d\n", current->id);
        printf("名前     : %s\n", current->name);
        printf("自身のノードの場所 : %d\n", current);
        printf("次のノードの場所   : %d\n", current->next);
        printf("------------------------------------------------------\n");
        if (current->next != NULL)
        {
            // 次の場所がNULLではない、つまり次のデータがある。
            // 「現在の場所」を次の場所に移動します。
            current = current->next;
        }
        else
        {
            // 次の場所がNULLなら、現在の場所はリストの末尾。
            // もう次のデータはないので、breakでループ終了。
            printf("最後まで表示したよ！\n");
            break;
        }
    }
    return 0;
}
// 新しいノードを生成する関数。
STUDENT createStudent(char *studentName, int studentId)
{
    STUDENT newStudent;
    // 新しいSTUDENT型変数に、nameとidをセットして返す。
    strcpy(newStudent.name, studentName);
    newStudent.id = studentId;
    return newStudent;
}
