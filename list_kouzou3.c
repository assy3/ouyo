#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
typedef struct student
{
    char name[20];         // 名前
    int id;                // 学籍番号
    struct student *next;  // 次のデータがある場所
} STUDENT;
STUDENT *head = NULL; // リストの先頭
STUDENT *tail = NULL; // リストの末尾
STUDENT *createNode(void);
void addNodeToList(void);
void printList(void);
void insertNodeToList(void);
int main(void)
{
    char input;
    char command;
    while (1)
    {
        printf("-------------操作方法-------------\n");
        printf("A : リストの末尾にノードを追加します。\n");
        printf("P : リスト内のノードを全て表示します。\n");
        printf("I : リスト内の任意の場所にノードを挿入します。\n");
        printf("コマンドを入力してください:");
        // 入力されたアルファベットをtoupperで大文字に変換。
        // switch文の判定にアルファベットの大文字を使うため。
        scanf("%s", &input);
        command = toupper(input);
        switch (command)
        {
            case 'A':
                addNodeToList(); // リスト末尾にノード追加。
                break;
            case 'P':
                printList(); // リストの内容を画面表示。
                break;
            case 'I':
                insertNodeToList(); // 任意の場所にノードを挿入。
                break;
            default:
                printf("無効なコマンドです。\n");
                break;
        }
        printf("\n");
    }
    return 0;
}
// ノードを生成する関数。
STUDENT *createNode(void)
{
    // 新しいノード1個分のメモリを確保し、その場所を返します。
    STUDENT *newNodePos;
    newNodePos = (STUDENT *)malloc(sizeof(STUDENT));
    return newNodePos;
}
// リストの末尾にノードを追加する関数。
void addNodeToList(void)
{
    STUDENT *newNodePos;
    int inputId;
    char inputName[20];
    // 新しいノードを作成。(1)
    newNodePos = createNode();
    printf("学籍番号を入力：");
    scanf("%d", &inputId);
    newNodePos->id = inputId;
    printf("名前を入力：");
    scanf("%s", inputName);
    strcpy(newNodePos->name, inputName);
    if ((head == NULL) && (tail == NULL))
    {
        // リストが空の場合はこちら。
        // 新しいノードが、先頭かつ末尾になる。
        head = newNodePos;
        tail = newNodePos;
    }
    else
    {
        // リストに1件以上ノードが存在する場合はこちら。
        // 末尾ノード(tail)のnextに、新しいノードの場所をセット。
        tail->next = newNodePos;
        // 追加した新しいノードをtailとする。
        tail = newNodePos;
    }
    // 次のデータは無いので、nextにはNULLをセット。
    tail ->next = NULL;
    printf("ノードを追加しました。\n");
}
// リストの内容を全て表示する関数。
void printList(void)
{
    STUDENT *current;
    if ((head == NULL) && (tail == NULL))
    {
        // 表示するものがない場合は何もせずにreturn。
        printf("リストは空です。\n");
        return;
    }
    // 先頭から表示するので、現在の位置をheadにセット。
    current = head;
    printf("----------------------------------\n");
    while (1)
    {
        printf("学籍番号 : %d\n", current->id);
        printf("名前     : %s\n", current->name);
        printf("自身のノードの場所 : %d\n", current);
        printf("次のノードの場所   : %d\n", current->next);
        printf("----------------------------------\n");
        if (current->next != NULL)
        {
            // 次の場所がNULLではない、つまり次のノードがある。
            // 現在の場所を次のノードに移動します。
            current = current->next;
        }
        else
        {
            // 次の場所がNULLなら、現在の場所はリストの末尾。
            // もう次のデータはないので、breakでループ終了。
            printf("最後まで表示しました。\n");
            break;
        }
    }
}
// リスト内の任意の場所にノードを挿入する関数。
void insertNodeToList(void)
{
    char insertTargetName[20] = "";
    STUDENT *current, *temp, *newNodePos;
    int inputId;
    char inputName[20];
    printf("挿入先のノードのnameを入力してください。\n");
    printf("入力されたnameを持つノードの後ろに、新しいノードを挿入します。\n");
    scanf("%s", insertTargetName);
    // リストの先頭から、挿入先ノードを探します。
    current = head;
    while (current != NULL)
    {
        if (strcmp(current->name, insertTargetName) == 0)
        {
            printf("ノードが見つかりました。\n");
            break;
        }
        else
        {
            current = current->next;
        }
    }
    // 挿入先ノードが見つからなかったら、何もせずreturn。
    if (current == NULL)
    {
        printf("ノードが見つかりませんでした。\n");
        return;
    }
    // 新規ノードを作成。
    newNodePos = createNode();
    printf("学籍番号を入力：");
    scanf("%d", &inputId);
    newNodePos->id = inputId;
    printf("名前を入力：");
    scanf("%s", inputName);
    strcpy(newNodePos->name, inputName);
    // tempに、挿入先ノードの「1つ後ろのノード」の場所を一時記憶。
    temp = current->next;
    // 挿入先ノードのnextに、新規ノードを追加。
    current->next = newNodePos;
    // さっき一時記憶した場所(temp)を、新規ノードの「次の場所」にする。
    newNodePos->next = temp;
    printf("ノードを挿入しました。\n");
}
