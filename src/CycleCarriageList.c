#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "CycleCarriageList.h"

#define	PREV link.prev
#define NEXT link.next

typedef struct tag_HCCL
{
  ListNode *pList;
  DWORD dwDataSize;
  DWORD dwMode;
  CCL_NodeDataProcCallback funFree;
  //CCL_IsNodeDataSameCallback funIsSame;
}_HCCL;

//����������
HCCL CCL_StartUp(DWORD dwDataSize, DWORD dwMode, CCL_NodeDataProcCallback funFreeData)
{
  _HCCL *pstHCCL;

  if ((pstHCCL=(_HCCL*)malloc(sizeof(_HCCL))) == NULL)
  {
    return (HCCL)NULL;
  }
  memset(pstHCCL, 0, sizeof(_HCCL));

  pstHCCL->dwDataSize=dwDataSize;
  pstHCCL->dwMode=dwMode;
  pstHCCL->funFree=funFreeData;
  //pstHCCL->funIsSame=funIsDataSame;

  return (HCCL)pstHCCL;
ERR_L:
  free(pstHCCL);
  return (HCCL)NULL;
}

int _FreeListNodeDataProc(void *pDataPtr)
{
  ListNode *pstListNode=(ListNode*)((BYTE*)pDataPtr-offsetof(ListNode, data));
  
  memset(pstListNode, 0, sizeof(ListNode));
  free(pstListNode);
  return 0;
}

#define pstHCCL ((_HCCL*)hCCL)
//�ͷ�������Դ
int CCL_CleanUp(HCCL hCCL)
{
  if (pstHCCL->funFree != NULL)
  {
    CCL_Travel(hCCL, pstHCCL->funFree);
  }
  CCL_Travel(hCCL, _FreeListNodeDataProc);

  pstHCCL->pList=NULL;
    
  free(pstHCCL);
  return 0;
}

//�½����
ListNode* CCL_CreateNode(HCCL hCCL)
{
  ListNode * p_new;

	p_new = (ListNode *)malloc(sizeof(Link)+pstHCCL->dwDataSize);
	if(p_new == NULL)
	{
		return NULL;
	}
  
  if ((pstHCCL->dwMode&CCL_MODE_TwoWay) != 0)
  {
    p_new->PREV = &p_new->link;
	  p_new->NEXT = &p_new->link;
  }
  else
  {
    p_new->NEXT = &p_new->link;
  }

	return p_new;
}

//�ͷ�һ�����
int CCL_FreeNode(HCCL hCCL, ListNode *pstNode)
{
  if (pstHCCL->funFree!=NULL)
  {
    pstHCCL->funFree(CCL_GetDataPtr(void, pstNode));
  }
  memset(pstNode,0,sizeof(ListNode));
  free(pstNode);
  return 0;
}

//��ָ��������ӽ��
int CCL_AddNode(HCCL hCCL, ListNode *pstNode, ListNode *pstNewNode)
{
	if(pstNewNode == NULL)
	{
		return -1;
	}

  if(pstNode == NULL)
  {
    if (pstHCCL->pList == NULL)
    {//������
      pstHCCL->pList=pstNewNode;
      pstNewNode->NEXT=&pstNewNode->link;
      pstNewNode->PREV=&pstNewNode->link;
      return 0;
    }
    else
    {
      pstNode=CCL_GetPrevNode(hCCL, pstHCCL->pList);
      pstHCCL->pList=pstNewNode;
    }
  }
	
  if ((pstHCCL->dwMode&CCL_MODE_TwoWay) != 0)
  {
    pstNode->NEXT->prev = &(pstNewNode->link);
	  pstNewNode->PREV	= &(pstNode->link);
  }
	pstNewNode->NEXT	= pstNode->NEXT;	
	pstNode->NEXT		= &(pstNewNode->link);
	return 0;
}

//��ӽ�㵽������ǰ��
int CCL_AddNode2Front(HCCL hCCL, ListNode *pstNewNode)
{
  return CCL_AddNode(hCCL, NULL, pstNewNode);
}
//��ӽ�㵽������β��
int CCL_AddNode2Tail(HCCL hCCL, ListNode *pstNewNode)
{
	if(pstHCCL == NULL || pstNewNode == NULL)
	{
		return -1;
	}
	
  if (pstHCCL->pList==NULL)
  {
	  return CCL_AddNode(hCCL, NULL, pstNewNode);
  }

	return CCL_AddNode(hCCL, CCL_GetPrevNode(hCCL, pstHCCL->pList), pstNewNode);
}

//��������ɾ�����ͷŽ��
int CCL_DelNode(HCCL hCCL, ListNode *pstNode, BOOL bFree)
{
  ListNode *pstNext, *pstPrev;

  if(pstNode == NULL)
  {
    return -1;
  }	
  
  pstNext=CCL_GetNextNode(hCCL, pstNode);
  if (pstNode == pstNext)
  {//last node
    if (bFree)
    {
      CCL_FreeNode(hCCL, pstNode);
    }
    pstHCCL->pList=NULL;
    return 0;
  }

  pstPrev=CCL_GetPrevNode(hCCL, pstNode);

  if ((pstHCCL->dwMode&CCL_MODE_TwoWay) != 0)
  {
    pstNext->PREV=&pstPrev->link;
  }
  pstPrev->NEXT=&pstNext->link;
  if (pstNode==pstHCCL->pList)
  {
    pstHCCL->pList=pstNext;
  }
  if (bFree)
  {
    CCL_FreeNode(hCCL, pstNode);
  }
  return 0;
}

//�ƶ�����������е�λ��
int CCL_MoveNode(HCCL hCCL, ListNode *pstDest, ListNode *pstSrc)
{
  if (pstHCCL==NULL || pstSrc==NULL)
  {
    return -1;
  }

  if (pstDest == pstSrc)
  {
    return 0;
  }
  /*if (pstDest==NULL)
  {
    pstDest=NULL;
  }*/

  CCL_DelNode(hCCL, pstSrc, FALSE);
  CCL_AddNode(hCCL, pstDest, pstSrc);
  return 0;
}
//��������������е�λ��
int CCL_ExchangeNode(HCCL hCCL, ListNode *pstNode1, ListNode *pstNode2)
{
  ListNode *pPrev;
  if (pstHCCL==NULL || pstNode2==NULL)
  {
    return -1;
  }
  if (pstNode1==NULL)
  {
    pstNode1=pstHCCL->pList;
  }
  if (pstNode2==pstNode1)
  {
    return 0;
  }

  pPrev=CCL_GetPrevNode(hCCL, pstNode2);
  if (pPrev==pstNode1)
  {
    CCL_DelNode(hCCL, pstNode1, FALSE);
    CCL_AddNode(hCCL, pstNode2, pstNode1);
    goto END_L;
  }
  CCL_DelNode(hCCL, pstNode2, FALSE);
  CCL_AddNode(hCCL, pstNode1, pstNode2);

  if (pPrev->NEXT != &pstNode1->link)
  {
    CCL_DelNode(hCCL, pstNode1, FALSE);
    CCL_AddNode(hCCL, pPrev, pstNode1);
  }

END_L:
  if (pstHCCL->pList==pstNode1)
  {
    pstHCCL->pList=pstNode2;
  }
  else if (pstHCCL->pList==pstNode2)
  {
    pstHCCL->pList=pstNode1;
  }
  return 0;
}

//��ȡǰһ�����
ListNode*	CCL_GetPrevNode(HCCL hCCL, ListNode *pstNode)
{
  Link *p;

	if(pstHCCL == NULL)
	{
		return NULL;
	}

  if (pstNode == NULL)
  {//ȡ�׽���ǰһ��(ȡβ���)
    if (pstHCCL->pList == NULL)
    {
      return NULL;
    }
    pstNode=pstHCCL->pList;
  }
  
  
  if ((pstHCCL->dwMode&CCL_MODE_TwoWay) != 0)
  {
    return (ListNode*)pstNode->PREV;
  }

  p=&pstNode->link;
	while(p->next != &pstNode->link)
	{
		p	= p->next;
	}

	return (ListNode*)p;
}

//��ȡ��һ�����
ListNode*	CCL_GetNextNode(HCCL hCCL, ListNode *pstNode)
{
  if (pstNode==NULL)
  {//ȡ��һ��
    return pstHCCL->pList;
  }
  return (ListNode*)pstNode->NEXT;
}

//��������Ѱ�ҽ��
ListNode * CCL_FindNode(HCCL hCCL, void *pDataPtr, CCL_IsNodeDataSameCallback funIsDataSame)
{
  Link *p;
	if(pstHCCL->pList == NULL || pDataPtr == NULL || funIsDataSame == NULL)
	{
		return NULL;
	}
	
  p=&pstHCCL->pList->link;
  do
	{
		if(funIsDataSame(CCL_GetDataPtr(void*, (ListNode *)p), pDataPtr) >= 0)
		{
      return (ListNode *)p;
		}
		
		p = p->next;
	}while(p != &pstHCCL->pList->link);
	return NULL;
}

//��������
int CCL_Travel(HCCL hCCL, CCL_NodeDataProcCallback funVisit)
{
  Link *p,*next;

	if(pstHCCL->pList == NULL || funVisit == NULL)
	{
		return -1;
	}

	p	= &(pstHCCL->pList->link);
	do
  {
    next=p->next;
    if(funVisit(CCL_GetDataPtr(void*,(ListNode *)p))<0)
    {
      break;
    }
		p	= next;
	}while(p != &pstHCCL->pList->link);
	return 0;
}
#undef pstHCCL