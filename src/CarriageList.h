#ifndef __DANIEL_LIST_H__
#define	__DANIEL_LIST_H__

#include <WTYPES.H>

#define DE_LIST			/*define double direction list*/
						/*else define single direction list*/
//#define WITH_HEAD_NODE	/*define list with head node*/
						/*else define list without head node*/
//......cycle_list

typedef struct _link/*double direction list*/
{
	#ifdef DE_LIST
	struct _link *prev;
	#endif
	struct _link *next;/*single direction list*/
}Link, *LinkPtr;

/*typedef struct _link
{
	struct _link *next;
}Link,*p_Link;*/

typedef struct tagListNode
{
	Link link;
	BYTE data[];
}ListNode;

typedef int  (*IsListNodeSameProc)(void *pDataPtr1, void *pDataPtr2);//return >=0 stand for is same,<0 is not same
typedef int (*ListNodeDataProc)(void *pDataPtr);//return >=0 stand for continue; return <0 stop

#define LST_GetDataPtr(data_type, node_ptr) ((data_type*)((node_ptr)->data))

#define LST_CreateNode(type) _LST_CreateNode(sizeof(type))
ListNode* _LST_CreateNode(unsigned int data_size);
int LST_FreeNode(ListNode *pstNode);
int LST_CleanUp(ListNode **ppList,ListNodeDataProc funFree);

int LST_AddNode(ListNode *pstNode, ListNode *pstNewNode);

#ifndef WITH_HEAD_NODE
int LST_AddNode2Front(ListNode **ppList, ListNode *pstNewNode);
#else
int LST_AddNode2Front(ListNode *pList, ListNode *pstNewNode);
#endif

int LST_AddNode2Tail(ListNode *pList, ListNode *pstNewNode);

#ifndef DE_LIST
ListNode*	LST_FindPrevNode(ListNode *pList, ListNode *pstNode);
#endif

ListNode * LST_FindNode(ListNode * list_ptr, void *pDataPtr, IsListNodeSameProc is_same);

#ifdef WITH_HEAD_NODE
int LST_DelNode(ListNode *pList, ListNode *pstNode, ListNodeDataProc funFree);
#else
int LST_DelNode(ListNode **ppList, ListNode *pstNode, ListNodeDataProc funFree);
#endif

int LST_Travel(ListNode *pList, ListNodeDataProc funVisit);

#endif
