//此代码页由工程<CodeGenerate>于[Fri May 10 19:13:05 2013]生成
#include <WTypes.h>
#include "GlobalEnv.h"
#define S4T_ST_Word (1)//单词,叶子结点
#define S4T_ST_Script (2)
#define S4T_ST_Express (3)
#define S4T_ST_Item (4)
#define S4T_ST_Factor (5)
#define S4T_ST_Condition (6)
#define S4T_ST_Statement (7)
#define S4T_ST_Function (8)
#define S4T_ST_CodeBlock (9)
#define S4T_ST_Var (10)
#define S4T_ST_VarDefBlock (11)
SyntaxNode g_stSyntaxTreeRoot={0};
typedef int (*SyntaxAnalysisProc)(SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
typedef struct tagSyntaxAnalysisMap {
BYTE byST;
SyntaxAnalysisProc funProc;
}SyntaxAnalysisMap;
int _SyntaxAnalysis_Word (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Script (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Express (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Item (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Factor (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Condition (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Statement (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Function (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_CodeBlock (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Var (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_VarDefBlock (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
SyntaxAnalysisMap g_staSyntaxAnalysisMap[]={
{S4T_ST_Script, NULL},
{S4T_ST_Word, _SyntaxAnalysis_Word},
{S4T_ST_Script, _SyntaxAnalysis_Script},
{S4T_ST_Express, _SyntaxAnalysis_Express},
{S4T_ST_Item, _SyntaxAnalysis_Item},
{S4T_ST_Factor, _SyntaxAnalysis_Factor},
{S4T_ST_Condition, _SyntaxAnalysis_Condition},
{S4T_ST_Statement, _SyntaxAnalysis_Statement},
{S4T_ST_Function, _SyntaxAnalysis_Function},
{S4T_ST_CodeBlock, _SyntaxAnalysis_CodeBlock},
{S4T_ST_Var, _SyntaxAnalysis_Var},
{S4T_ST_VarDefBlock, _SyntaxAnalysis_VarDefBlock},
};
int _SyntaxAnalysisSubProc(BYTE byST, SyntaxNode *pCurNode, DWORD *pdwCurWordPos)
{
  int i;
  for (i=0; i<sizeof(g_staSyntaxAnalysisMap)/sizeof(SyntaxAnalysisMap); ++i)
  {
    if (g_staSyntaxAnalysisMap[i].byST==byST)
    {
      if (g_staSyntaxAnalysisMap[i].funProc != NULL)
      {
        return g_staSyntaxAnalysisMap[i].funProc(pCurNode, pdwCurWordPos);
      }
      return S4T_EC_SAProcNULL;
    }
  }
  return S4T_EC_SAProcNotMapped;
}
#define pstCurWord ((Word*)(&g_staAllWord[*pdwCurWordPos]))
int _SyntaxAnalysis_Word(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  pCurTNode->byType=S4T_ST_Word;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=(HCCL)pstCurWord;
  ++(*pdwCurWordPos);
  return 0;
}
#define NODE_POS(x,y) ((x<<16)|y)
int _Recursion_Script(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
  case NODE_POS(12,0):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_VarDefBlock(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_0_0_L;//内容[VarDefBlock]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Script(pCurTNode, pdwCurWordPos, 14,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(14,0):
  case NODE_POS(24,0):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_CodeBlock(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_14_0_L;//内容[CodeBlock]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Script(pCurTNode, pdwCurWordPos, 26,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_14_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(26,0):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_Script(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Script;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Script(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Express(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
  case NODE_POS(5,0):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Item(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_0_0_L;//内容[Item]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Express(pCurTNode, pdwCurWordPos, 2,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Express(pCurTNode, pdwCurWordPos, 2,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Express(pCurTNode, pdwCurWordPos, 9,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(4,4):
  case NODE_POS(2,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x3000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(-)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Express(pCurTNode, pdwCurWordPos, 0,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_4_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(4,2):
  case NODE_POS(2,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x3000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(+)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Express(pCurTNode, pdwCurWordPos, 0,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_4_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(9,0):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_Express(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Express;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Express(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Item(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
  case NODE_POS(7,0):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Factor(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_0_0_L;//内容[Factor]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 2,6)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 2,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 2,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 12,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(4,6):
  case NODE_POS(2,6):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x3000004){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(%)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 0,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_4_6_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(4,4):
  case NODE_POS(2,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x3000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(/)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 0,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_4_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(4,2):
  case NODE_POS(2,2):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Item(pCurTNode, pdwCurWordPos, 0,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_4_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(12,0):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_Item(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Item;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Item(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Factor(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 2,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 1,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 3,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(2,0):
  case NODE_POS(9,0):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 12,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(12,0):
    return 0;//出口
  case NODE_POS(1,4):
  case NODE_POS(3,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(()
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 5,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_1_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(5,4):
  case NODE_POS(13,4):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Express(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_5_4_L;//内容[Express]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 15,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_5_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(15,4):
  case NODE_POS(17,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词())
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 20,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_15_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(20,4):
    return 0;//出口
  case NODE_POS(3,2):
  case NODE_POS(8,2):
    if(pstCurWord->dwType != S4T_WT_Const){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(#num)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Factor(pCurTNode, pdwCurWordPos, 11,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_3_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(11,2):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_Factor(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Factor;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Factor(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Condition(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
  case NODE_POS(8,0):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Express(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_0_0_L;//内容[Express]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 37,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 31,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 26,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 21,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 15,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 9,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(37,2):
  case NODE_POS(40,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x4000005){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(<=)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 43,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_37_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(43,4):
  case NODE_POS(51,4):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Express(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_43_4_L;//内容[Express]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 54,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_43_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(54,4):
    return 0;//出口
  case NODE_POS(31,2):
  case NODE_POS(34,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x4000004){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(>=)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 43,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_31_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(26,2):
  case NODE_POS(28,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x4000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(<)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 43,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_26_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(21,2):
  case NODE_POS(23,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x4000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(>)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 43,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_21_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(15,2):
  case NODE_POS(18,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x4000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(==)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 43,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_15_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(9,2):
  case NODE_POS(12,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x4000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(!=)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Condition(pCurTNode, pdwCurWordPos, 43,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_9_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  }
  return -2;
}
int _SyntaxAnalysis_Condition(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Condition;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Condition(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Statement(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 2,17)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 2,15)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 2,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 2,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 2,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(2,17):
  case NODE_POS(7,17):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x2000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(exit)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 9,17)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_17_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(9,17):
    return 0;//出口
  case NODE_POS(2,15):
  case NODE_POS(8,15):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x2000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(while)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 10,15)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_15_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(10,15):
  case NODE_POS(12,15):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(()
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 14,15)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_10_15_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(14,15):
  case NODE_POS(24,15):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Condition(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_14_15_L;//内容[Condition]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 26,15)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_14_15_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(26,15):
  case NODE_POS(28,15):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词())
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 29,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_26_15_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(29,10):
  case NODE_POS(31,10):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000004){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词({)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 51,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 34,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_29_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(51,10):
  case NODE_POS(53,10):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000005){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(})
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 29,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 56,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_51_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(56,10):
    return 0;//出口
  case NODE_POS(34,10):
  case NODE_POS(44,10):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Statement(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_34_10_L;//内容[Statement]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 46,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_34_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(46,10):
  case NODE_POS(48,10):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(;)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 51,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 34,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_46_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(2,10):
  case NODE_POS(5,10):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x2000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(if)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 9,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(9,10):
  case NODE_POS(11,10):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(()
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 13,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_9_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(13,10):
  case NODE_POS(23,10):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Condition(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_13_10_L;//内容[Condition]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 25,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_13_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(25,10):
  case NODE_POS(27,10):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词())
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 29,10)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_25_10_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(2,4):
  case NODE_POS(7,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x1000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(call)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 9,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(9,4):
  case NODE_POS(16,4):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 18,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_9_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(18,4):
  case NODE_POS(20,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(()
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 36,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 22,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_18_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(36,4):
  case NODE_POS(38,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词())
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 40,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_36_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(40,4):
    return 0;//出口
  case NODE_POS(22,4):
  case NODE_POS(30,4):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Express(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_22_4_L;//内容[Express]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 36,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 28,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_22_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(30,2):
  case NODE_POS(28,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(,)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 22,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_30_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(2,0):
  case NODE_POS(9,0):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 11,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(11,0):
  case NODE_POS(13,0):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x7000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(=)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 15,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_11_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(15,0):
  case NODE_POS(23,0):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Express(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_15_0_L;//内容[Express]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Statement(pCurTNode, pdwCurWordPos, 28,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_15_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(28,0):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_Statement(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Statement;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Statement(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Function(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 0,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(0,2):
  case NODE_POS(9,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x1000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(function)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 11,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(11,2):
  case NODE_POS(18,2):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 20,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_11_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(20,2):
  case NODE_POS(22,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000002){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(()
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 24,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_20_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(24,2):
  case NODE_POS(25,2):
    //空节点(方向集中结点)直接处理字节点
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 28,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 29,6)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 29,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 43,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_24_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(28,2):
  case NODE_POS(35,2):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 40,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_28_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(40,4):
  case NODE_POS(41,4):
    //空节点(方向集中结点)直接处理字节点
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 34,8)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 43,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_40_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(36,8):
  case NODE_POS(34,8):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(,)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 24,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_36_8_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(43,2):
  case NODE_POS(45,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000003){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词())
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 47,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_43_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(47,2):
  case NODE_POS(49,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000004){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词({)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 67,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 51,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_47_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(67,2):
  case NODE_POS(69,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000005){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(})
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 72,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_67_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(72,2):
    return 0;//出口
  case NODE_POS(51,2):
  case NODE_POS(61,2):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Statement(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_51_2_L;//内容[Statement]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 63,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_51_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(63,2):
  case NODE_POS(65,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(;)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 67,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 51,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_63_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(29,6):
  case NODE_POS(37,6):
    if(pstCurWord->dwType != S4T_WT_Const){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(#string)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 40,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_29_6_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(29,4):
  case NODE_POS(34,4):
    if(pstCurWord->dwType != S4T_WT_Const){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(#num)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Function(pCurTNode, pdwCurWordPos, 40,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_29_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  }
  return -2;
}
int _SyntaxAnalysis_Function(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Function;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Function(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_CodeBlock(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 0,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(0,2):
  case NODE_POS(5,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x1000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(src:)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 10,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 6,6)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 16,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(10,0):
  case NODE_POS(12,0):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(;)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 15,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_10_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(15,0):
    return 0;//出口
  case NODE_POS(6,6):
  case NODE_POS(15,6):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Function(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_6_6_L;//内容[Function]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 16,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 6,6)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_6_6_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(16,2):
  case NODE_POS(26,2):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Statement(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_16_2_L;//内容[Statement]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 28,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_16_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(28,2):
  case NODE_POS(30,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(;)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 16,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 34,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_28_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(34,2):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_CodeBlock(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_CodeBlock;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_CodeBlock(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_Var(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 2,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 2,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 2,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(2,12):
  case NODE_POS(9,12):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x6){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(buffer)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 11,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(11,12):
  case NODE_POS(13,12):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000006){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词([)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 15,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_11_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(15,12):
  case NODE_POS(20,12):
    if(pstCurWord->dwType != S4T_WT_Const){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(#num)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 22,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_15_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(22,12):
  case NODE_POS(24,12):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000007){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(])
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 26,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_22_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(26,12):
  case NODE_POS(33,12):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 36,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 37,8)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_26_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(36,12):
  case NODE_POS(38,12):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x7000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(=)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 40,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_36_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(40,12):
  case NODE_POS(48,12):
    if(pstCurWord->dwType != S4T_WT_Const){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(#string)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 37,8)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_40_12_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(37,8):
  case NODE_POS(38,8):
    //空节点(方向集中结点)直接处理字节点
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 27,6)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 49,8)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_37_8_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(29,6):
  case NODE_POS(27,6):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(,)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 26,12)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_29_6_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(49,8):
    return 0;//出口
  case NODE_POS(2,4):
  case NODE_POS(6,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x1){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(s32)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 9,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(9,2):
  case NODE_POS(16,2):
    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(*ident)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 18,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 32,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_9_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(18,4):
  case NODE_POS(20,4):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x7000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(=)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 22,4)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_18_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(22,4):
  case NODE_POS(30,4):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Express(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_22_4_L;//内容[Express]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 32,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_22_4_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(32,2):
  case NODE_POS(33,2):
    //空节点(方向集中结点)直接处理字节点
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 13,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 38,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_32_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(15,0):
  case NODE_POS(13,0):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000001){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(,)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 9,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_15_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(38,2):
    return 0;//出口
  case NODE_POS(2,2):
  case NODE_POS(6,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x2){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(u32)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_Var(pCurTNode, pdwCurWordPos, 9,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_2_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  }
  return -2;
}
int _SyntaxAnalysis_Var(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_Var;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_Var(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int _Recursion_VarDefBlock(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)
{
  BYTE byOrgChildCnt=pCurTNode->byChildCnt;
  DWORD dwOrgWordPos=*pdwCurWordPos;
  DWORD dwSaveWordPos=*pdwCurWordPos;
  DWORD pos=(x<<16)|y;
  ListNode *pCurChild=NULL;

  switch(pos)
  {
  case NODE_POS(0,0):
  case NODE_POS(5,0):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x1000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(var:)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 7,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 8,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_0_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(7,0):
  case NODE_POS(9,0):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(;)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 11,0)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_7_0_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(11,0):
    return 0;//出口
  case NODE_POS(8,2):
  case NODE_POS(12,2):
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    if(_SyntaxAnalysis_Var(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_8_2_L;//内容[Var]
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 14,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_8_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(14,2):
  case NODE_POS(16,2):
    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x5000000){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//单词(;)
    //添加结点
    ++pCurTNode->byChildCnt;
    pCurChild=CCL_CreateNode(pCurTNode->hChildList);
    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);
    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);
    dwSaveWordPos=*pdwCurWordPos;//保存位置
    if(_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 8,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    if(_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 19,2)>=0) return 0;
    else *pdwCurWordPos=dwSaveWordPos;//还原位置
    //还原所有(所有亲子结点都匹配失败,为匹配本结点的右兄弟结点做准备)
    END_14_2_L:
    while (pCurTNode->byChildCnt > byOrgChildCnt)
    {
      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);
      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);
      --pCurTNode->byChildCnt;
    }
    return -1;
  case NODE_POS(19,2):
    return 0;//出口
  }
  return -2;
}
int _SyntaxAnalysis_VarDefBlock(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  pCurTNode->byType=S4T_ST_VarDefBlock;
  pCurTNode->byChildCnt=0;
  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);

  nRet=_Recursion_VarDefBlock(pCurTNode, pdwCurWordPos, 0,0);
  if(nRet<0)
  {
    CCL_CleanUp(pCurTNode->hChildList);
    pCurTNode->hChildList=NULL;
    pCurTNode->byChildCnt=0;
  }
  return nRet;
}
int S4T_SyntaxAnalysis()
{
  DWORD dwWordPos=0;
  return _SyntaxAnalysis_Script(&g_stSyntaxTreeRoot, &dwWordPos);
}
#undef pstCurWord
