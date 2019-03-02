
#include <stdio.h>
#include <windows.h>
#include <string.h>

// 課題4
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
}OneWayList;







int main(void){
    return 0;
}
