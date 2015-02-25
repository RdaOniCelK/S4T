/*******************************************
--------------------------------------------
|模块名 | 链表模块 CycleCarriageList(CCL)
|-------------------------------------------
|现版本 | V2.0
|-------------------------------------------
|功  能 | 循环链表,可用任何数据类型作为结点数据
|-------------------------------------------
|依  赖 | 
|-------------------------------------------
|改  进 | 
|-------------------------------------------
|               修改历史
|-------------------------------------------
|版本号 | 操作日期 | 操作者 |  日志
|-------------------------------------------
|V1.0   |2010.04.23|邓丽达  | 创建
|-------------------------------------------
|V2.0   |2013.04.12|邓丽达  | 简化接口定义;固定为循环链表方式;名称改为CycleCarriageList(CCL)循环运输链表
*******************************************/
#ifndef __DANIEL_LIST_H__
#define	__DANIEL_LIST_H__

#include <WTYPES.H>
#include <stddef.h>

typedef struct _link/*double direction list*/
{
	struct _link *prev;
	struct _link *next;
}Link;

typedef struct tagListNode
{
	Link link;
	BYTE data[];
}ListNode;

typedef int (*CCL_IsNodeDataSameCallback)(void *pDataPtr1, void *pDataPtr2);//return >=0 stand for is same,<0 is not same
typedef int (*CCL_NodeDataProcCallback)(void *pDataPtr);//return >=0 stand for continue; return <0 stop

#define HCCL long

#define CCL_GetFirstNode(hCCL)  (*(ListNode**)hCCL)

#define CCL_MODE_TwoWay   (1)
//申请链表句柄
HCCL CCL_StartUp(DWORD dwDataSize, DWORD dwMode, CCL_NodeDataProcCallback funFreeData);
//释放链表资源
int CCL_CleanUp(HCCL hCCL);

//新建结点
ListNode* CCL_CreateNode(HCCL hCCL);
//获取结点内的用户数据的指针
#define CCL_GetDataPtr(data_type, node_ptr) ((data_type*)((node_ptr)->data))
//设置结点内的用户数据
#define CCL_SetData(node_ptr, data_type, data) (*CCL_GetDataPtr(data_type, node_ptr)=data)
//由用户数据指针,取所在的结点指针
#define CCL_GetListNodePtrByDataPtr(data_ptr) ( (ListNode*)( ((BYTE*)data_ptr) - (offsetof(ListNode, data)) ) )
//释放一个结点
int CCL_FreeNode(HCCL hCCL, ListNode *pstNode);

//在指定结点后添加结点
//pstNewNode将添加到pstNode后,如果pstNode==NULL,则pstNewNode将添加到最前
int CCL_AddNode(HCCL hCCL, ListNode *pstNode, ListNode *pstNewNode);
//添加结点到链表最前处
int CCL_AddNode2Front(HCCL hCCL, ListNode *pstNewNode);
//添加结点到链表最尾处
int CCL_AddNode2Tail(HCCL hCCL, ListNode *pstNewNode);
//从链表中删除并释放结点
//bFree=FALSE:只将结点从链表中移出;bFree==TRUE:移出并释放结点内存
int CCL_DelNode(HCCL hCCL, ListNode *pstNode, BOOL bFree);

//移动结点在链表中的位置
//pstSrc将添加到pstDest后,如果pstDest==NULL,则pstSrc将移动到最前
int CCL_MoveNode(HCCL hCCL, ListNode *pstDest, ListNode *pstSrc);
//交换结点在链表中的位置
//如果pstNode1==NULL,则pstNode2将与第一个结点交换
int CCL_ExchangeNode(HCCL hCCL, ListNode *pstNode1, ListNode *pstNode2);

//获取前一个结点
ListNode*	CCL_GetPrevNode(HCCL hCCL, ListNode *pstNode);
//获取后一个结点
ListNode*	CCL_GetNextNode(HCCL hCCL, ListNode *pstNode);
//在链表中寻找结点
ListNode * CCL_FindNode(HCCL hCCL, void *pDataPtr, CCL_IsNodeDataSameCallback funIsDataSame);
//遍历链表
int CCL_Travel(HCCL hCCL, CCL_NodeDataProcCallback funVisit);

#endif
