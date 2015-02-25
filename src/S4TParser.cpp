// AssistScriptParser.cpp : Defines the entry point for the console application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <MATH.H>
#include "GlobalEnv.h"



#define DREWBUFF_ROW  (6)
#define DREWBUFF_COL  (1024*2)
char _szaDrewBuff[DREWBUFF_ROW][DREWBUFF_COL];DWORD _dwDrewPos=0;
DWORD _dwChildCnt=10, _dwChildWidth=4, _dwSumLevel=4;
void _DrewSAT(SyntaxNode *pNode, DWORD dwLevel, DWORD dwLeftSpan)//广度
{
  int i;
  ListNode *pstCurNode;
  int nPos;
  if(pNode->byChildCnt <= 0) return;
  if (dwLevel>_dwSumLevel-1) return ;
  
  //drew child
  pstCurNode=CCL_GetNextNode(pNode->hChildList, NULL);
  for(i=0; i<pNode->byChildCnt; ++i)
  {
    //(Deman^(Sum-Level)-1)*(P-1+0.5)*width
    nPos=(pow(_dwChildCnt,(_dwSumLevel-dwLevel) - 1))*((double)(dwLeftSpan+i)-1+0.5)*_dwChildWidth;
    switch(CCL_GetDataPtr(SyntaxNode, pstCurNode)->byType)
    {
    case S4T_ST_Word:
      {
        Word *pstWord=((Word*)(CCL_GetDataPtr(SyntaxNode, pstCurNode)->hChildList));
        memcpy(_szaDrewBuff[dwLevel-1]+nPos, g_szScript+pstWord->wPos, (pstWord->wLen >_dwChildWidth)?_dwChildWidth:pstWord->wLen);
      }
      break;
    case S4T_ST_Script:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Script", 4);
      break;
    case S4T_ST_Express:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Express", 4);
      break;
    case S4T_ST_Item:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Item", 4);
      break;
    case S4T_ST_Factor:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Factor", 4);
      break;
    case S4T_ST_Condition:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Confition", 4);
      break;
    case S4T_ST_Statement:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Sta3tment", 4);
      break;
    case S4T_ST_Function:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Function", 4);
      break;
    case S4T_ST_CodeBlock:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "CodeBlock", 4);
      break;
    case S4T_ST_Var:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "Var", 3);
      break;
    case S4T_ST_VarDefBlock:
      memcpy(_szaDrewBuff[dwLevel-1]+nPos, "VarBlock", 4);
      break;
    }
    
    pstCurNode=CCL_GetNextNode(pNode->hChildList, pstCurNode);
  }
  //travel child
  pstCurNode=CCL_GetNextNode(pNode->hChildList, NULL);
  for(i=0; i<pNode->byChildCnt; ++i)
  {
    _DrewSAT(CCL_GetDataPtr(SyntaxNode, pstCurNode), dwLevel+1, (dwLeftSpan+i-1)*_dwChildCnt+1);
    pstCurNode=CCL_GetNextNode(pNode->hChildList, pstCurNode);
  }
}

void S4T_DrewSAT()
{
  int i,j;
  for (i=0;i<DREWBUFF_ROW;++i)
  {
    for (j=0;j<DREWBUFF_COL-1;++j)
    {
      _szaDrewBuff[i][j]=' ';
    }
    _szaDrewBuff[i][j]=0;
  }
  _DrewSAT(&g_stSyntaxTreeRoot, 1, 1);
  for (i=0; i<DREWBUFF_ROW; ++i)
  {
    printf("%s\n",_szaDrewBuff[i]);
  }
}


int main(int argc, char* argv[])
{
  char szScriptPath[MAX_PATH]="c:\\test.as";
  int nRet;
  FILE *pFile;
  int nPos;

  LOG_Init("LogFile\\S4T", REC_ALL, FALSE);

  if((pFile=fopen(szScriptPath, "r")) == NULL)
  {
    printf("打开脚本文件[%s]失败\n", szScriptPath);
    return 1;
  }

  nPos=0;
  while (!feof(pFile))
  {
    if((nRet=fread(g_szScript+nPos, 1, 1024, pFile)) <= 0)
    {
      return 2;
    }
    nPos+=nRet;
  }
  g_dwScriptSize=nPos;

  nRet=S4T_PickWord();
  printf("PickWord:%d\n", nRet);
  if (nRet<0)
  {
    if (g_dwErrPos>=0)
    {
      printf("error src:row[%d],col[%d],src[%.*s]", g_wErrRow+1, g_wErrCol+1, 20, g_szScript+g_dwErrPos);
    }
  }

  nRet=S4T_SyntaxAnalysis();
  if (nRet<0)
  {
    if (g_dwErrPos>=0)
    {
      printf("error src:row[%d],col[%d],src[%.*s]", g_wErrRow+1, g_wErrCol+1, 20, g_szScript+g_dwErrPos);
    }
  }
  else
  {
    S4T_DrewSAT();
  }

  LOG_Uninit();
  return 0;
}

