#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "CarriageList.h"

#ifdef	DE_LIST
#define	PREV link.prev
#endif
#define NEXT link.next

//static unsigned int DATA_SIZE = 0;

ListNode * _LST_CreateNode(unsigned int data_size)
{
  ListNode * p_new;

	if(data_size == 0)
	{
		return NULL;
	}
	//DATA_SIZE	= data_size;
	p_new = (ListNode *)malloc(sizeof(Link)+data_size);
	if(p_new == NULL)
	{
		return NULL;
	}
	//memset(p_new, 0, sizeof(sizeof(Link)+data_size));
#ifdef DE_LIST
	p_new->PREV = NULL;
#endif
	p_new->NEXT = NULL;
	return p_new;
}

int LST_FreeNode(ListNode *pstNode)
{
  memset(pstNode,0,sizeof(ListNode));
  free(pstNode);
  return 0;
}

int LST_AddNode(ListNode * node,ListNode * new_node)
{
	if(node == NULL || new_node == NULL)
	{
		return -1;
	}
	
	#ifdef DE_LIST
	if(node->NEXT != NULL)
		node->NEXT->prev = &(new_node->link);
	new_node->PREV	= &(node->link);
	#endif
	new_node->NEXT	= node->NEXT;	
	node->NEXT		= &(new_node->link);
	return 0;
}

#ifdef WITH_HEAD_NODE
int LST_AddNode2Front(ListNode * list_ptr,ListNode * new_node)
{
	if(list_ptr == NULL || new_node == NULL)
	{
		return -1;
	}
	
	return LST_AddNode(list_ptr, new_node);
}
#else
int LST_AddNode2Front(ListNode ** list_pptr, ListNode * new_node)
{
	if(list_pptr == NULL || *list_pptr == NULL || new_node == NULL)
	{
		return -1;
	}
	
	#ifdef DE_LIST
	((ListNode*)(*list_pptr))->PREV	= &(new_node->link);
	#endif
	new_node->NEXT	= &((*list_pptr)->link);
	*list_pptr	= new_node;
	return 0;
}
#endif

int LST_AddNode2Tail(ListNode * list_ptr,ListNode * new_node)
{
  LinkPtr	p;
	if(list_ptr == NULL || new_node == NULL)
	{
		return -1;
	}
	
	p	= &(list_ptr->link);
	while(p->next != NULL)
	{
		p	= p->next;
	}
	return LST_AddNode((ListNode *)p,new_node);
}

#ifndef DE_LIST
ListNode * LST_FindPrevNode(ListNode * list_ptr,ListNode * p_node)
{
	if(list_ptr == NULL || p_node == NULL)
	{
		return NULL;
	}
	
#ifdef WITH_HEAD_NODE
	LinkPtr	p	= list_ptr->NEXT;
#else
	LinkPtr	p = &(list_ptr->link);
#endif
	while(p != NULL && p->NEXT != p_node)
	{
		p	= p->next;
	}
	return p;
}
#endif

ListNode * LST_FindNode(ListNode * list_ptr, void *pDataPtr, IsListNodeSameProc is_same)
{
  LinkPtr	p;
	if(list_ptr == NULL || pDataPtr == NULL || is_same == NULL)
	{
		return NULL;
	}
	
	#ifdef WITH_HEAD_NODE
	p = list_ptr->link.next;
	#else
	p = &(list_ptr->link);
	#endif
	while(p != NULL)
	{
		if(is_same(LST_GetDataPtr(void*, (ListNode *)p), pDataPtr) >= 0)
		{
			break;
		}
		
		p = p->next;
	}
	return (ListNode *)p;
}

#ifdef WITH_HEAD_NODE
int LST_DelNode(ListNode * list_ptr,ListNode * p_node,ListNodeDataProc free_node)
{
	if(p_node == NULL || list_ptr == NULL)
	{
		return -1;
	}	
	
	if(p_node == list_ptr)//is first node
	{
		//perror("can not delete head-node!!!");
		return -2;//is head node
	}

	#ifdef DE_LIST
	if(p_node->NEXT != NULL)//is not last node
	{
		p_node->NEXT->prev	= p_node->PREV;
	}
	p_node->PREV->next	= p_node->NEXT;
  if (free_node != NULL)
  {
	  free_node(LST_GetDataPtr(void*,p_node));
  }
  LST_FreeNode(p_node);
	return 0;
	#else
	//....find out prev node
  if (free_node != NULL)
  {
    free_node(LST_GetDataPtr(void*,p_node));
  }
  LST_FreeNode(p_node);
	return 0;
	#endif
}
#else
int LST_DelNode(ListNode * * list_pptr, ListNode * p_node, ListNodeDataProc free_node)
{
	if(p_node == NULL || list_pptr == NULL || *list_pptr == NULL)
	{
		return -1;
	}	
	
	if(p_node == *list_pptr)//is first node
	{	
		*list_pptr	= (ListNode*)p_node->NEXT;
	#ifdef DE_LIST
		(*list_pptr)->PREV	= NULL;
	#endif
    if (free_node != NULL)
    {
      free_node(LST_GetDataPtr(void*,p_node));
    }
    LST_FreeNode(p_node);
		return 0;
	}

	#ifdef DE_LIST
	if(p_node->NEXT != NULL)//is not last node
	{
		p_node->NEXT->prev	= p_node->PREV;
	}
	p_node->PREV->next	= p_node->NEXT;
  if (free_node != NULL)
  {
    free_node(LST_GetDataPtr(void*,p_node));
  }
  LST_FreeNode(p_node);
	return 0;
	#else
	//....find out prev node
	free_node(p_node);
	return 0;
	#endif
}
#endif

int LST_Travel(ListNode * list_ptr,ListNodeDataProc fun/*call back funcation*/)
{
  LinkPtr	p,next;

	if(list_ptr == NULL || fun == NULL)
	{
		return -1;
	}
	#ifdef WITH_HEAD_NODE
	p = list_ptr->link.next;
	#else
	p	= &(list_ptr->link);
	#endif
	while(p != NULL)
  {
    next=p->next;
    if(fun(LST_GetDataPtr(void*,(ListNode *)p))<0) break;
		p	= next;
	}
	return 0;
}

int _FreeListNodeDataProc(void *pDataPtr)
{
  ListNode *pstListNode=(ListNode*)((BYTE*)pDataPtr-offsetof(ListNode, data));

  memset(pstListNode, 0, sizeof(ListNode));
  free(pstListNode);
  return 0;
}

int LST_CleanUp(ListNode **ppList,ListNodeDataProc funFree)
{
  if (funFree!=NULL)
  {
    LST_Travel(*ppList, funFree);
  }
  LST_Travel(*ppList, _FreeListNodeDataProc);
  
#ifdef WITH_HEAD_NODE
  memset(*ppList, 0, sizeof(ListNode));
  free(*ppList);
#endif

  *ppList=NULL;
  return 0;
}