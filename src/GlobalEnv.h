#ifndef __GLOBAL_ENV_H__
#define __GLOBAL_ENV_H__

#include <WINDOWS.H>
#include <MALLOC.H>
extern "C"
{
#include "Log.h"
#include "CycleCarriageList.h"
};

#define S4T_WT_Undefined  (0)//δ֪
#define S4T_WT_KeyWord    (1)//�ؼ���
#define S4T_WT_Ident      (2)//��ʶ��
#define S4T_WT_Const      (3)//����
//#define S4T_WT_Ignore     (4)//ָʾ�õ��ʲ��ô���,����.���ڸ���'-',�ʷ�������,����������ֺϲ�Ϊ����,���Բ�����Ҫ���'-'
//����
typedef struct tagWord
{
  DWORD dwType;//��������
  DWORD wPos;//�ڽű���������λ��
  WORD wLen;//���ʳ���(�ֽ�)
  WORD wRow;//��
  WORD wCol;//��

  union{
    struct  
    {
      DWORD dwKeyWordType;
    };
    struct  
    {
      WORD wConstType;
      WORD wConstValPos;
    };
  };
}Word;
#define S4T_MAX_SCRIPT_SIZE (1024*100-1)
extern char g_szScript[S4T_MAX_SCRIPT_SIZE+1];
extern DWORD g_dwScriptSize;
#define S4T_MAX_WORD_NUM  (1024*100)
extern Word g_staAllWord[S4T_MAX_WORD_NUM];
extern DWORD g_dwWordCnt;
#define S4T_CONST_VAR_BUFF_SIZE (65535)
extern BYTE g_byaConstValBuff[S4T_CONST_VAR_BUFF_SIZE];
extern WORD g_wCurConstValBuffPos;

#define S4T_CT_Undefined (0)
#define S4T_CT_u32     (1)//ʮ���Ƴ���(�޷���)
#define S4T_CT_s32     (2)//ʮ���Ƴ���(�з���)
#define S4T_CT_hex     (3)//ʮ�����Ƴ���
#define S4T_CT_str     (4)//�ַ�������
#define S4T_CT_arr     (5)//�ֽ����鳣��

/*#define S4T_KWT_byte   (0x00000000)
#define S4T_KWT_word   (0x00000001)
#define S4T_KWT_dword  (0x00000002)
#define S4T_KWT_char   (0x00000003)
#define S4T_KWT_short  (0x00000004)
#define S4T_KWT_int    (0x00000005)*/
#define S4T_KWT_Undefined (0)
#define S4T_KWT_u32    (0x00000001)
#define S4T_KWT_s32    (0x00000002)
#define S4T_KWT_buffer (0x00000006)

#define S4T_KWT_var    (0x01000000)
#define S4T_KWT_src    (0x01000001)
#define S4T_KWT_call   (0x01000002)
#define S4T_KWT_function    (0x01000003)

#define S4T_KWT_if     (0x02000000)
#define S4T_KWT_else   (0x02000001)
#define S4T_KWT_while  (0x02000002)
#define S4T_KWT_exit   (0x02000003)

#define S4T_KWT_eval   (0x07000000)//=

#define S4T_KWT_add    (0x03000000)//+
#define S4T_KWT_sub    (0x03000001)//-
#define S4T_KWT_multi  (0x03000002)//*
#define S4T_KWT_div    (0x03000003)// /
#define S4T_KWT_mod    (0x03000004)//%

#define S4T_KWT_eq     (0x04000000)//==
#define S4T_KWT_neq    (0x04000001)//!=
#define S4T_KWT_gt     (0x04000002)//>
#define S4T_KWT_lt     (0x04000003)//<
#define S4T_KWT_ge     (0x04000004)//>=
#define S4T_KWT_le     (0x04000005)//<=

#define S4T_KWT_semi   (0x05000000)//;
#define S4T_KWT_comma  (0x05000001)//,
#define S4T_KWT_lpar   (0x05000002)//(
#define S4T_KWT_rpar   (0x05000003)//)
#define S4T_KWT_lbrace (0x05000004)//{
#define S4T_KWT_rbrace (0x05000005)//}
#define S4T_KWT_lbrack (0x05000006)//[
#define S4T_KWT_rbrack (0x05000007)//]

#define S4T_KWT_hex    (0x06000000)//H

typedef struct tagKeyWord 
{
  const char *szStr;//�ؼ��ַ���
  DWORD dwId;//�ؼ���ID S4T_KWT_*
}KeyWord;
extern KeyWord g_staKeyWord[];//�ؼ����б�
const char* _GetKeyWordStr(DWORD dwKWT);
DWORD _GetKeyWordDefine(const char *szKeyWord);
DWORD _IsKeyWord(char *pWordStart, WORD *pwKeyWordLen);

#define S4T_EC_Interal          (-100)//�ڲ�����

extern int g_nEC;
extern WORD g_wErrRow,g_wErrCol;extern DWORD g_dwErrPos;
void _SetErrSrc(WORD wRow, WORD wCol, DWORD dwPos);

//�ʷ�����
#define S4T_EC_NumFormat        (-1000)//��������ָ�ʽ
#define S4T_EC_StringFormat     (-1001)//������ַ�����ʽ
#define S4T_EC_WordUnrecognized (-1002)//�޷�ʶ��ĵ���


int S4T_PickWord();

//�﷨����
#define S4T_EC_SAProcNULL       (-2000)//�﷨�����ӹ���Ϊ��
#define S4T_EC_SAProcNotMapped  (-2001)//�Ҳ�����Ӧ���﷨�����ӹ���
#define S4T_EC_SAVarNotFound    (-2002)//Ӧ��"var:"��ͷ
#define S4T_EC_SAScriptLost     (-2003)//�ű�ȱʧ,�﷨δ����,���ļ��Ѿ�����

#define S4T_ST_Word (1)//����,Ҷ�ӽ��
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
typedef struct tagSyntaxNode{
  BYTE byType;
  BYTE byChildCnt;
  HCCL hChildList;
}SyntaxNode;
extern SyntaxNode g_stSyntaxTreeRoot;
//�﷨����:����﷨,�����﷨��,ʶ��������������,������ʵ���ݺ�ӳ����
int S4T_SyntaxAnalysis();
void _SA_SetErrSrc(DWORD dwWordPos);
void S4T_DrewSAT();
/*
#define S4T_ST_Script         (1)//�ű�
#define S4T_ST_VarDefBlock    (2)//���������
#define S4T_ST_CodeBlock      (3)//�����
#define S4T_ST_Var            (4)//����
#define S4T_ST_Statement      (5)//���
#define S4T_ST_Condition      (6)//����
#define S4T_ST_FuncDef        (7)//��������
#define S4T_ST_Express        (8)//���ʽ
#define S4T_ST_Item           (9)//��
#define S4T_ST_Factor         (10)//����
#define S4T_ST_Word           (11)//����,Ҷ�ӽ��
typedef struct tagSyntaxNode
{
  BYTE byType;
  BYTE byChildCnt;
  ListNode *pChildList;
}SyntaxNode;

SyntaxNode g_stSyntaxTreeRoot={0};

typedef int (*SyntaxAnalysisProc)(SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
typedef struct tagSyntaxAnalysisMap 
{
  BYTE byST;
  SyntaxAnalysisProc funProc;
}SyntaxAnalysisMap;

int _SyntaxAnalysis_VarDefBlock(SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_CodeBlock  (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Var        (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Statement  (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Condition  (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_FuncDef    (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Express    (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Item       (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Factor     (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
int _SyntaxAnalysis_Word       (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);
SyntaxAnalysisMap g_staSyntaxAnalysisMap[]=
{
  {S4T_ST_Script     ,NULL                       },
  {S4T_ST_VarDefBlock,_SyntaxAnalysis_VarDefBlock},
  //{S4T_ST_CodeBlock  ,_SyntaxAnalysis_CodeBlock  },
//   {S4T_ST_Var        ,_SyntaxAnalysis_Var        },
//   {S4T_ST_Statement  ,_SyntaxAnalysis_Statement  },
//   {S4T_ST_Condition  ,_SyntaxAnalysis_Condition  },
//   {S4T_ST_FuncDef    ,_SyntaxAnalysis_FuncDef    },
//   {S4T_ST_Express    ,_SyntaxAnalysis_Express    },
//   {S4T_ST_Item       ,_SyntaxAnalysis_Item       },
//   {S4T_ST_Factor     ,_SyntaxAnalysis_Factor     },
  {S4T_ST_Word       ,_SyntaxAnalysis_Word       },
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
  pCurTNode->byChildCnt=0;
  pCurTNode->pChildList=(ListNode*)pstCurWord;
  ++(*pdwCurWordPos);
  return 0;
}
int _SyntaxAnalysis_VarDefBlock(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  int nRet;
  SyntaxNode *pstCurSN;
  ListNode *pstNode;

  if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != S4T_KWT_var)
  {
    return S4T_EC_SAVarNotFound;
  }

  pCurTNode->pChildList=NULL;
  pCurTNode->byChildCnt=1;
  pCurTNode->pChildList=LST_CreateNode(SyntaxNode);
  pstCurSN=LST_GetDataPtr(SyntaxNode, pCurTNode->pChildList);
  pstCurSN->byType=S4T_ST_Word;
  if ((nRet=_SyntaxAnalysisSubProc(S4T_ST_Word, pstCurSN, pdwCurWordPos)) < 0)
  {
    return nRet;
  }
  
  if(pstCurWord->dwType == S4T_WT_Undefined)
  {
    return S4T_EC_SAScriptLost; 
  }
  
  while (pstCurWord->dwType != S4T_WT_Undefined)
  {
    if (pstCurWord->dwType == S4T_WT_KeyWord && pstCurWord->dwKeyWordType==S4T_KWT_semi)
    {//�Ƿֺ�
    }
    else
    {//�Ǳ���
      
    }
  }
  return 0;
}
int _SyntaxAnalysis_Var(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  return 0;
}
#undef pstCurWord
//�﷨����:����﷨,�����﷨��,ʶ��������������,������ʵ���ݺ�ӳ����
int S4T_SyntaxAnalysis(DWORD dwWordPos)
{
#define pstCurWord ((Word*)(&g_staAllWord[dwCurWordPos]))
  int nRet;
  DWORD dwCurWordPos=0;
  SyntaxNode *pstCurSN;
  ListNode *pstNode;

  memset(&g_stSyntaxTreeRoot, 0, sizeof(SyntaxNode));

  g_stSyntaxTreeRoot.byType=S4T_ST_Script;
  if(pstCurWord->dwType == S4T_WT_Undefined)
  {
    return 0; 
  }

  g_stSyntaxTreeRoot.byChildCnt=1;
  g_stSyntaxTreeRoot.pChildList=LST_CreateNode(SyntaxNode);
  pstCurSN=LST_GetDataPtr(SyntaxNode, g_stSyntaxTreeRoot.pChildList);
  pstCurSN->byType=S4T_ST_VarDefBlock;
  if ((nRet=_SyntaxAnalysisSubProc(S4T_ST_VarDefBlock, pstCurSN, &dwCurWordPos)) < 0)
  {
    return nRet;
  }

  if(pstCurWord->dwType == S4T_WT_Undefined)
  {
    return S4T_EC_SAScriptLost; 
  }

  ++g_stSyntaxTreeRoot.byChildCnt;
  pstNode=LST_CreateNode(SyntaxNode);
  LST_AddNode2Tail(g_stSyntaxTreeRoot.pChildList, pstNode);
  pstCurSN=LST_GetDataPtr(SyntaxNode, g_stSyntaxTreeRoot.pChildList);
  pstCurSN->byType=S4T_ST_CodeBlock;
  if ((nRet=_SyntaxAnalysisSubProc(S4T_ST_CodeBlock, pstCurSN, &dwCurWordPos)) < 0)
  {
    return nRet;
  }
  return 0;
#undef pstCurWord
}
*/
#endif