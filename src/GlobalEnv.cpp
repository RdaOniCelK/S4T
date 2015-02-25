#include "GlobalEnv.h"
#include <stdio.h>

int g_nEC=0;
WORD g_wErrRow=0,g_wErrCol=0;DWORD g_dwErrPos=-1;

char g_szScript[S4T_MAX_SCRIPT_SIZE+1]={0};
DWORD g_dwScriptSize=0;
Word g_staAllWord[S4T_MAX_WORD_NUM]={0};
DWORD g_dwWordCnt=0;
BYTE g_byaConstValBuff[S4T_CONST_VAR_BUFF_SIZE]={0};
WORD g_wCurConstValBuffPos=0;

KeyWord g_staKeyWord[]=
{
  /*
  {"byte"    ,S4T_KWT_byte    },
  {"word"    ,S4T_KWT_word    },
  {"dword"   ,S4T_KWT_dword   },
  {"char"    ,S4T_KWT_char    },
  {"short"   ,S4T_KWT_short   },
  {"int"     ,S4T_KWT_int     },*/
  {"s32"     ,S4T_KWT_u32     },
  {"u32"     ,S4T_KWT_s32     },
  {"buffer"  ,S4T_KWT_buffer  },
  {"var:"    ,S4T_KWT_var     },
  {"src:"    ,S4T_KWT_src     },
  {"call"    ,S4T_KWT_call    },
  {"function",S4T_KWT_function},
  {"if"      ,S4T_KWT_if      },
  {"else"    ,S4T_KWT_else    },
  {"while"   ,S4T_KWT_while   },
  {"exit"    ,S4T_KWT_exit    },
  {"=="      ,S4T_KWT_eq      },
  {"!="      ,S4T_KWT_neq     },
  {">"       ,S4T_KWT_gt      },
  {"<"       ,S4T_KWT_lt      },
  {">="      ,S4T_KWT_ge      },
  {"<="      ,S4T_KWT_le      },
  {"="       ,S4T_KWT_eval    },
  {"+"       ,S4T_KWT_add     },
  {"-"       ,S4T_KWT_sub     },
  {"*"       ,S4T_KWT_multi   },
  {"/"       ,S4T_KWT_div     },
  {"%"       ,S4T_KWT_mod     },
  {";"       ,S4T_KWT_semi    },
  {","       ,S4T_KWT_comma   },
  {"("       ,S4T_KWT_lpar    },
  {")"       ,S4T_KWT_rpar    },
  {"{"       ,S4T_KWT_lbrace  },
  {"}"       ,S4T_KWT_rbrace  },
  {"["       ,S4T_KWT_lbrack  },
  {"]"       ,S4T_KWT_rbrack  },
  {"H"       ,S4T_KWT_hex     },
};
const char* _GetKeyWordStr(DWORD dwKWT)
{
  int i;
  for (i=0; i<sizeof(g_staKeyWord)/sizeof(KeyWord); ++i)
  {
    if (g_staKeyWord[i].dwId == dwKWT)
    {
      return g_staKeyWord[i].szStr;
    }
  }
  return NULL;
}
DWORD _GetKeyWordDefine(const char *szKeyWord)
{
  int i;
  for (i=0; i<sizeof(g_staKeyWord)/sizeof(KeyWord); ++i)
  {
    if (strcmp(g_staKeyWord[i].szStr, szKeyWord)==0)
    {
      return g_staKeyWord[i].dwId;
    }
  }
  return S4T_KWT_Undefined;
}
DWORD _IsKeyWord(char *pWordStart, WORD *pwKeyWordLen)
{
  int i;
  for (i=0; i<sizeof(g_staKeyWord)/sizeof(KeyWord); ++i)
  {
    if (strncmp(g_staKeyWord[i].szStr, pWordStart, strlen(g_staKeyWord[i].szStr))==0)
    {
      *pwKeyWordLen=strlen(g_staKeyWord[i].szStr);
      return g_staKeyWord[i].dwId;
    }
  }
  return S4T_KWT_Undefined;
}

void _SetErrSrc(WORD wRow, WORD wCol, DWORD dwPos){g_wErrRow=wRow;g_wErrCol=wCol;g_dwErrPos=dwPos;}
void _SA_SetErrSrc(DWORD dwWordPos)
{//取分析得最多的为错误点
  if (g_staAllWord[dwWordPos].wRow>g_wErrRow)
  {
    goto RENEW_L;
  }
  else if (g_staAllWord[dwWordPos].wRow==g_wErrRow)
  {
    if (g_staAllWord[dwWordPos].wCol>g_wErrCol)
    {
      goto RENEW_L;
    }
  }

  return;
RENEW_L:
  _SetErrSrc(g_staAllWord[dwWordPos].wRow,g_staAllWord[dwWordPos].wCol,g_staAllWord[dwWordPos].wPos);
}
