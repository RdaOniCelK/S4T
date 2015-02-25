#ifndef __GLOBAL_ENV_H__
#define __GLOBAL_ENV_H__

#include <WINDOWS.H>
#include <MALLOC.H>
extern "C"
{
#include "Log.h"
#include "CycleCarriageList.h"
};

#define S4T_WT_Undefined  (0)//未知
#define S4T_WT_KeyWord    (1)//关键字
#define S4T_WT_Ident      (2)//标识名
#define S4T_WT_Const      (3)//常量
//#define S4T_WT_Ignore     (4)//指示该单词不用处理,忽略.用于负号'-',词法分析后,跟后面的数字合并为负数,所以不再需要理会'-'
//单词
typedef struct tagWord
{
  DWORD dwType;//单词类型
  DWORD wPos;//在脚本缓冲区的位置
  WORD wLen;//单词长度(字节)
  WORD wRow;//行
  WORD wCol;//列

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
#define S4T_CT_u32     (1)//十进制常量(无符号)
#define S4T_CT_s32     (2)//十进制常量(有符号)
#define S4T_CT_hex     (3)//十六进制常量
#define S4T_CT_str     (4)//字符串常量
#define S4T_CT_arr     (5)//字节数组常量

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
  const char *szStr;//关键字符号
  DWORD dwId;//关键字ID S4T_KWT_*
}KeyWord;
extern KeyWord g_staKeyWord[];//关键字列表
const char* _GetKeyWordStr(DWORD dwKWT);
DWORD _GetKeyWordDefine(const char *szKeyWord);
DWORD _IsKeyWord(char *pWordStart, WORD *pwKeyWordLen);

#define S4T_EC_Interal          (-100)//内部错误

extern int g_nEC;
extern WORD g_wErrRow,g_wErrCol;extern DWORD g_dwErrPos;
void _SetErrSrc(WORD wRow, WORD wCol, DWORD dwPos);

//词法分析
#define S4T_EC_NumFormat        (-1000)//错误的数字格式
#define S4T_EC_StringFormat     (-1001)//错误的字符串格式
#define S4T_EC_WordUnrecognized (-1002)//无法识别的单词


int S4T_PickWord();

//语法分析
#define S4T_EC_SAProcNULL       (-2000)//语法分析子过程为空
#define S4T_EC_SAProcNotMapped  (-2001)//找不到对应的语法分析子过程
#define S4T_EC_SAVarNotFound    (-2002)//应以"var:"开头
#define S4T_EC_SAScriptLost     (-2003)//脚本缺失,语法未结束,但文件已经结束

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
typedef struct tagSyntaxNode{
  BYTE byType;
  BYTE byChildCnt;
  HCCL hChildList;
}SyntaxNode;
extern SyntaxNode g_stSyntaxTreeRoot;
//语法分析:检查语法,生成语法树,识别最终数据类型,生成真实数据和映射表格
int S4T_SyntaxAnalysis();
void _SA_SetErrSrc(DWORD dwWordPos);
void S4T_DrewSAT();
/*
#define S4T_ST_Script         (1)//脚本
#define S4T_ST_VarDefBlock    (2)//变量定义块
#define S4T_ST_CodeBlock      (3)//代码块
#define S4T_ST_Var            (4)//变量
#define S4T_ST_Statement      (5)//语句
#define S4T_ST_Condition      (6)//条件
#define S4T_ST_FuncDef        (7)//函数定义
#define S4T_ST_Express        (8)//表达式
#define S4T_ST_Item           (9)//项
#define S4T_ST_Factor         (10)//因子
#define S4T_ST_Word           (11)//单词,叶子结点
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
    {//是分号
    }
    else
    {//是变量
      
    }
  }
  return 0;
}
int _SyntaxAnalysis_Var(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)
{
  return 0;
}
#undef pstCurWord
//语法分析:检查语法,生成语法树,识别最终数据类型,生成真实数据和映射表格
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