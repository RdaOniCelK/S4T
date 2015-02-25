/*******************************************
--------------------------------------------
|ģ���� | ����ģ�� CycleCarriageList(CCL)
|-------------------------------------------
|�ְ汾 | V2.0
|-------------------------------------------
|��  �� | ѭ������,�����κ�����������Ϊ�������
|-------------------------------------------
|��  �� | 
|-------------------------------------------
|��  �� | 
|-------------------------------------------
|               �޸���ʷ
|-------------------------------------------
|�汾�� | �������� | ������ |  ��־
|-------------------------------------------
|V1.0   |2010.04.23|������  | ����
|-------------------------------------------
|V2.0   |2013.04.12|������  | �򻯽ӿڶ���;�̶�Ϊѭ������ʽ;���Ƹ�ΪCycleCarriageList(CCL)ѭ����������
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
//����������
HCCL CCL_StartUp(DWORD dwDataSize, DWORD dwMode, CCL_NodeDataProcCallback funFreeData);
//�ͷ�������Դ
int CCL_CleanUp(HCCL hCCL);

//�½����
ListNode* CCL_CreateNode(HCCL hCCL);
//��ȡ����ڵ��û����ݵ�ָ��
#define CCL_GetDataPtr(data_type, node_ptr) ((data_type*)((node_ptr)->data))
//���ý���ڵ��û�����
#define CCL_SetData(node_ptr, data_type, data) (*CCL_GetDataPtr(data_type, node_ptr)=data)
//���û�����ָ��,ȡ���ڵĽ��ָ��
#define CCL_GetListNodePtrByDataPtr(data_ptr) ( (ListNode*)( ((BYTE*)data_ptr) - (offsetof(ListNode, data)) ) )
//�ͷ�һ�����
int CCL_FreeNode(HCCL hCCL, ListNode *pstNode);

//��ָ��������ӽ��
//pstNewNode����ӵ�pstNode��,���pstNode==NULL,��pstNewNode����ӵ���ǰ
int CCL_AddNode(HCCL hCCL, ListNode *pstNode, ListNode *pstNewNode);
//��ӽ�㵽������ǰ��
int CCL_AddNode2Front(HCCL hCCL, ListNode *pstNewNode);
//��ӽ�㵽������β��
int CCL_AddNode2Tail(HCCL hCCL, ListNode *pstNewNode);
//��������ɾ�����ͷŽ��
//bFree=FALSE:ֻ�������������Ƴ�;bFree==TRUE:�Ƴ����ͷŽ���ڴ�
int CCL_DelNode(HCCL hCCL, ListNode *pstNode, BOOL bFree);

//�ƶ�����������е�λ��
//pstSrc����ӵ�pstDest��,���pstDest==NULL,��pstSrc���ƶ�����ǰ
int CCL_MoveNode(HCCL hCCL, ListNode *pstDest, ListNode *pstSrc);
//��������������е�λ��
//���pstNode1==NULL,��pstNode2�����һ����㽻��
int CCL_ExchangeNode(HCCL hCCL, ListNode *pstNode1, ListNode *pstNode2);

//��ȡǰһ�����
ListNode*	CCL_GetPrevNode(HCCL hCCL, ListNode *pstNode);
//��ȡ��һ�����
ListNode*	CCL_GetNextNode(HCCL hCCL, ListNode *pstNode);
//��������Ѱ�ҽ��
ListNode * CCL_FindNode(HCCL hCCL, void *pDataPtr, CCL_IsNodeDataSameCallback funIsDataSame);
//��������
int CCL_Travel(HCCL hCCL, CCL_NodeDataProcCallback funVisit);

#endif
