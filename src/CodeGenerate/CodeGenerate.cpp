#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "../GlobalEnv.h"

//Word:KeyWord,Ident,Const
//Content:[Word],[Content]
#define SDGNT_undefined      (0)
#define SDGNT_word           (1)
#define SDGNT_content        (2)
/*/�﷨ͼ���
typedef struct tagSyntaxDescGraphNode
{
  BYTE type;
  union
  {
    struct  
    {
      DWORD dwWordType;
      DWORD dwSubType;
    };
    struct  
    {
      char *szContentName;
      DWORD dwReserve;
    };
  };
}SyntaxDescGraphNode;

//�﷨ͼ������
typedef struct tagSyntaxDescGraphLink
{
  SyntaxDescGraphNode *self;
  DWORD dwNextCnt;
  tagSyntaxDescGraphLink *pNextList;
}SyntaxDescGraphLink;
*/
//�﷨ͼ
char *g_szSyntaxDescGraph_Express[]=
{
  "[Item]>>> ",
  "^      v  ",
  "^<(+)<<v  ",
  "^      v  ",
  "^<(-)<<<  ",
};

char *g_szSyntaxDescGraph_Item[]=
{
  "[Factor]>>>> ",
  "^        v   ",
  "^<(*)<<<<v   ",
  "^        v   ",
  "^<(/)<<<<v   ",
  "^        v   ",
  "^<(%)<<<<<   ",
};

char *g_szSyntaxDescGraph_Factor[]=
{
  ">>(*ident)>>         ",
  "v                    ",
  "v>>(#num)>>          ",
  "v                    ",
  ">(()>[Express]>())>> ",
};

char *g_szSyntaxDescGraph_Condition[]=
{  
  "[Express]>>>>>>>>>>>>>>>>>>>>>>>>>>>>v                   ",
  "         v     v     v    v    v     v                   ",
  "         (!=)v (==)v (>)v (<)v (>=)v (<=)v               ",
  "             v     v    v    v     v     v               ",
  "             >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>[Express]>>   ",
};

char *g_szSyntaxDescGraph_Statement[]=
{
  "v>(*ident)>(=)>[Express]>>>>                             ",
  "v                                                        ",
  "v                     v<<<<<(,)<<<<                      ",
  "v                     v           ^                      ",
  "v>(call)>(*ident)>(()>[Express]>>>>>())>                 ",
  "v                    v              ^                    ",
  "v                    >>>>>>>>>>>>>>>^                    ",
  "v                                                        ",
  "v                            v<<<<<<<<<<<<<<<<<<<<<<<<<  ",
  "v                            v                        ^  ",
  "v>(if)>>>(()>[Condition]>())>({)>>[Statement]>(;)>>(})>> ",
  "v                            ^  v ^              v ^     ",
  "v                            ^  v ^<<<<<<<<<<<<<<< ^     ",
  "v                            ^  v                  ^     ",
  "v                            ^  >>>>>>>>>>>>>>>>>>>^     ",
  "v>(while)>(()>[Condition]>())^                           ",
  "v                                                        ",
  ">>(exit)>                                                ",
};

char *g_szSyntaxDescGraph_Function[]=
{
  "v                          >>>>>>>>>>>>>>>>v      >>>>>>>>>>>>>>>>>v     ",
  "v                          ^               v      ^                v     ",
  "(function)>(*ident)>(()>()>>(*ident)>>>>v  ())>({)>[Statement]>(;)>(})>> ",
  "                        ^  v            v  ^       ^              v      ",
  "                        ^  v>(#num)>>>>>()>>>v     ^<<<<<<<<<<<<<<<      ",
  "                        ^  v            ^    v                           ",
  "                        ^  >>(#string)>>^    v                           ",
  "                        ^                    v                           ",
  "                        ^<<<<<<<<<(,)<<<<<<<<<                           ",
};

char *g_szSyntaxDescGraph_CodeBlock[]=
{
  "v       >>(;)>>                    ",
  "v       ^                          ",
  "(src:)>>>>>>>>>>[Statement]>(;)>>> ",
  "      v         ^              v   ",
  "      v         ^<<<<<<<<<<<<<<<   ",
  "      v         ^                  ",
  "      [Function]>v                 ",
  "      ^          v                 ",
  "      ^<<<<<<<<<<<                 ",
};

char *g_szSyntaxDescGraph_Var[]=
{
  "v        v<<<(,)<<<<<<<<<<<<<<<<<<<                ",
  "v        v                        ^                ",
  "v>(u32)>>(*ident)>>>>>>>>>>>>>>>()>>>>             ",
  "v      ^         v             ^                   ",
  "v>(s32)^         >(=)>[Express]^                   ",
  "v                                                  ",
  "v                         v(,)<<<<<<<<<<           ",
  "v                         v            ^           ",
  "v                         v       >>>()>>>>>>>>>>  ",
  "v                         v       ^  ^             ",
  "v                         v       ^  ^<<<<<<<<<<<< ",
  "v                         v       ^              ^ ",
  ">>(buffer)>([)>(#num)>(])>(*ident)>>(=)>(#string)^ ",  
};
char *g_szSyntaxDescGraph_VarDefBlock[]=
{
  "(var:)>(;)>        ",
  "      v            ",
  "      >>[Var]>(;)>>",
  "        ^        v ",
  "        ^<<<<<<<<< ",
};

char *g_szSyntaxDescGraph_Script[]=
{
  "[VarDefBlock]>[CodeBlock]> ",
};

typedef struct tagGraphNameMap 
{
  char *szName;
  char **pGraph;
  DWORD dwRowCnt;
}GraphNameMap;
GraphNameMap g_staGraphNameMap[]=
{
  {"Script"       ,g_szSyntaxDescGraph_Script     ,sizeof(g_szSyntaxDescGraph_Script     )/sizeof(char*)},
  {"Express"      ,g_szSyntaxDescGraph_Express    ,sizeof(g_szSyntaxDescGraph_Express    )/sizeof(char*)},
  {"Item"         ,g_szSyntaxDescGraph_Item       ,sizeof(g_szSyntaxDescGraph_Item       )/sizeof(char*)},
  {"Factor"       ,g_szSyntaxDescGraph_Factor     ,sizeof(g_szSyntaxDescGraph_Factor     )/sizeof(char*)},
  {"Condition"    ,g_szSyntaxDescGraph_Condition  ,sizeof(g_szSyntaxDescGraph_Condition  )/sizeof(char*)},
  {"Statement"    ,g_szSyntaxDescGraph_Statement  ,sizeof(g_szSyntaxDescGraph_Statement  )/sizeof(char*)},
  {"Function"     ,g_szSyntaxDescGraph_Function   ,sizeof(g_szSyntaxDescGraph_Function   )/sizeof(char*)},
  {"CodeBlock"    ,g_szSyntaxDescGraph_CodeBlock  ,sizeof(g_szSyntaxDescGraph_CodeBlock  )/sizeof(char*)},
  {"Var"          ,g_szSyntaxDescGraph_Var        ,sizeof(g_szSyntaxDescGraph_Var        )/sizeof(char*)},
  {"VarDefBlock"  ,g_szSyntaxDescGraph_VarDefBlock,sizeof(g_szSyntaxDescGraph_VarDefBlock)/sizeof(char*)},
};
char** GetGraph(char *szName)
{
  int i;
  for (i=0; i<sizeof(g_staGraphNameMap)/sizeof(GraphNameMap); ++i)
  {
    if (strcmp(szName, g_staGraphNameMap[i].szName) == 0)
    {
      return g_staGraphNameMap[i].pGraph;
    }
  }
  return NULL;
}


//��¼�����ߵ�·��,���ѭ����·
typedef struct tagPoint
{
  int x,y;
}Point;
Point g_staWalkedPathSet[1024];
int g_nWalkedPathCnt=0;
void _StartWalk(){g_nWalkedPathCnt=0;}
void _Add2Walked(int x, int y)
{
  g_staWalkedPathSet[g_nWalkedPathCnt].x=x;
  g_staWalkedPathSet[g_nWalkedPathCnt].y=y;
  ++g_nWalkedPathCnt;
}
BOOL _IsWalked(int x, int y)
{
  for (int i=0; i<g_nWalkedPathCnt; ++i)
  {
    if (g_staWalkedPathSet[i].x==x && g_staWalkedPathSet[i].y==y)
    {
      return TRUE;
    }
  }
  return FALSE;
}

char *g_szOutPath="..\\SyntaxAnalysis.cpp";
char g_szCode[1024*1024]={0};
DWORD g_dwPos=0;

#define Print g_dwPos+=sprintf
#define Code g_szCode+g_dwPos

char g_szCurContentName[128]={0};
void _InsertCode(DWORD dwSDGNT, char *szName, int lx, int ly, int rx, int ry, int nLevel)
{
  Print(Code, "    if(_Recursion_%s(pCurTNode, pdwCurWordPos, %d,%d)>=0) return 0;\n", g_szCurContentName,lx,ly);
  Print(Code, "    else *pdwCurWordPos=dwSaveWordPos;//��ԭλ��\n");
  
  return ;
}


//�ݹ�����﷨����ͼ
#define SDGDirect_up      (0)
#define SDGDirect_right   (1)
#define SDGDirect_down    (2)
#define SDGDirect_left    (3)

//�ڵ�pGraph[y][x]����ʼѰ�����ӽ��
int _FindChild(char **pGraph, int nRowCnt, int y, int x, Point *pstaChild, int *pnChildCnt)
{
  int nRet;
#define up ((y-1<0)?' ':pGraph[y-1][x])
#define down ((y+1>=nRowCnt)?' ':pGraph[y+1][x])
#define right pGraph[y][x+1]
#define left ((x-1<0)?' ':pGraph[y][x-1])
#define cur pGraph[y][x]

FORWARD_L:
  switch(cur)
  {
  case '>':
    if (up=='^')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y-1,x,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    if (down=='v')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y+1,x,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    ++x;
    goto FORWARD_L;
  case '<':
    if (up=='^')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y-1,x,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    if (down=='v')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y+1,x,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    --x;
    goto FORWARD_L;
  case '^':
    if (right=='>')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y,x+1,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    if (left=='<')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y,x-1,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    --y;
    goto FORWARD_L;
  case 'v':
    if (right=='>')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y,x+1,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    if (left=='<')
    {
      if ((nRet=_FindChild(pGraph,nRowCnt,y,x-1,pstaChild,pnChildCnt)) < 0){return nRet;}
    }
    ++y;
    goto FORWARD_L;
  case '(':
  case '[':
  case ')':
  case ']':
  case ' '://����Ҳ�����ǽ�㴦��
  case '\0':
    //mark node
    pstaChild[*pnChildCnt].x=x;pstaChild[*pnChildCnt].y=y;
    ++(*pnChildCnt);
    return 0;
  }
  printf("�����Ƿ��ַ�[%c]\n", pGraph[y][x]);
  return -1;
  
#undef cur
#undef up
#undef down
#undef left
#undef right
}
//�������ӽ��(����>����>������>����)
int _SortChildSet(char **pGraph, int nRowCnt, Point *pstaChild, int nChildCnt)
{
  int i;
  Point tmp;
  int nOrgChildCnt=nChildCnt;

  for (i=0;i<nChildCnt;++i)
  {
    switch (pGraph[pstaChild[i].y][pstaChild[i].x])
    {
    case '(':
      if(pGraph[pstaChild[i].y][pstaChild[i].x+1]==')' && pGraph[pstaChild[i].y][pstaChild[i].x+2]!=')')
      {//"()"�ŵ���,��Ϊ���ĺ��ӿ����г���
        goto EMPTY_NODE_L;
      }
      goto WORD_L;
    case ')'://move to head.�ŵ�һ
      if(pGraph[pstaChild[i].y][pstaChild[i].x-1]=='(' && pGraph[pstaChild[i].y][pstaChild[i].x-2]!='(')
      {//"()"�ŵ���,��Ϊ���ĺ��ӿ����г���
        goto EMPTY_NODE_L;
      }
WORD_L:
      tmp=pstaChild[i];
      memmove(pstaChild+1, pstaChild, sizeof(Point)*i);
      pstaChild[0]=tmp;
      break;
EMPTY_NODE_L:
      //�ŵ���
      tmp=pstaChild[i];
      memmove(pstaChild+i, pstaChild+i+1, sizeof(Point)*(nChildCnt-i-1));
      --nChildCnt;
      pstaChild[nChildCnt]=tmp;
      break;
    case '[':
    case ']'://stay,�ŵڶ�
      break;
    case ' ':
    case '\0'://move to tail,�ŵ���,���
      tmp=pstaChild[i];
      memmove(pstaChild+i, pstaChild+i+1, sizeof(Point)*(nOrgChildCnt-i-1));
      --nChildCnt;
      pstaChild[nOrgChildCnt-1]=tmp;
      break;
    default:
      return -1;
    }
  }
  return 0;
}

//������ȵݹ�����﷨ͼ,�����﷨ͼ��Ӧ���﷨��������
int SyntaxDescGraphWalk(char **pGraph, int nRowCnt, int y, int x, int nLevel)
{
  int nRet;
  int nPos,i;
  int nOrgX=x,nOrgY=y;
  Point staChild[64];//һ������
  int naX[64];//��һ��X����
  int nChildCnt=0;
  char szBuff[128];
  DWORD dwNodeType;
#define up ((y-1<0)?' ':pGraph[y-1][x])
#define down ((y+1>=nRowCnt)?' ':pGraph[y+1][x])
#define right pGraph[y][x+1]
#define left ((x-1<0)?' ':pGraph[y][x-1])
#define cur pGraph[y][x]

  Print(Code,"  case NODE_POS(%d,%d):\n", x,y);
  //�жϿ�ʼ���Ƿ�Ϊ���,�������(���������,ֻ������ڴ�,����һ�εݹ�ʱ�Ż��в�Ϊ�������)
  switch(pGraph[y][x])
  {
  case '('://�﷨����Ҷ�ӽ��
    nPos=x;
    ++x;
    while (cur!=')' || (right!='^' && right!='>' && right!='v' && right!='<'))
    {
      ++x;
    }
    sprintf(szBuff, "%.*s", x-nPos-1, pGraph[y]+nPos+1);
    Print(Code,"  case NODE_POS(%d,%d):\n", x,y);
    //�����ж�
    if (right=='<') x=nPos-1;
    else ++x;
    goto PRINT_CODE_WORD_L;
  case ')'://�﷨����Ҷ�ӽ��
    nPos=x;
    --x;
    while ((left!='^' && left!='>' && left!='v' && left!='<') || cur!='(')
    {
      --x;
    }
    sprintf(szBuff, "%.*s", nPos-x-1, pGraph[y]+x+1);
    Print(Code,"  case NODE_POS(%d,%d):\n", x,y);
    //�����ж�
    if (left=='>') x=nPos+1;
    else --x;

PRINT_CODE_WORD_L:
    printf("����(%s)\n", szBuff);
    dwNodeType=SDGNT_word;
    
    if (szBuff[0]=='*')//Ident
    {
      Print(Code,"    if(pstCurWord->dwType != S4T_WT_Ident){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//����(%s)\n", szBuff);
    }
    else if (szBuff[0]=='#')//Const
    {
      Print(Code,"    if(pstCurWord->dwType != S4T_WT_Const){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//����(%s)\n", szBuff);
    }
    else//KeyWord
    {
      if(strcmp(szBuff,"")!=0)
      {
        Print(Code,"    if(pstCurWord->dwType != S4T_WT_KeyWord || pstCurWord->dwKeyWordType != 0x%X){ _SA_SetErrSrc(*pdwCurWordPos);return -1;}//����(%s)\n",_GetKeyWordDefine(szBuff), szBuff);
      }
      else
      {
        Print(Code,"    //�սڵ�(�����н��)ֱ�Ӵ����ֽڵ�\n");
        break;
      }
    }
    Print(Code,"    //��ӽ��\n");
    Print(Code,"    ++pCurTNode->byChildCnt;\n");
    Print(Code,"    pCurChild=CCL_CreateNode(pCurTNode->hChildList);\n");
    Print(Code,"    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);\n");
    Print(Code,"    _SyntaxAnalysis_Word(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos);\n");
    break;
  case '['://�﷨���ķ�Ҷ�ӽ��
    nPos=x;
    ++x;
    while (cur!=']')
    {
      ++x;
    }
    sprintf(szBuff, "%.*s", x-nPos-1, pGraph[y]+nPos+1);
    Print(Code,"  case NODE_POS(%d,%d):\n", x,y);
    //�����ж�
    if (right=='<') x=nPos-1;
    else ++x;
    goto PRINT_CODE_CONTENT_L;
  case ']'://�﷨���ķ�Ҷ�ӽ��
    nPos=x;
    --x;
    while (cur!='[')
    {
      --x;
    }
    sprintf(szBuff, "%.*s", nPos-x-1, pGraph[y]+x+1);
    Print(Code,"  case NODE_POS(%d,%d):\n", x,y);
    //�����ж�
    if (left=='>') x=nPos+1;
    else --x;

PRINT_CODE_CONTENT_L:
    printf("����[%s]\n", szBuff);
    dwNodeType=SDGNT_content;
    Print(Code,"    //��ӽ��\n");
    Print(Code,"    ++pCurTNode->byChildCnt;\n");
    Print(Code,"    pCurChild=CCL_CreateNode(pCurTNode->hChildList);\n");
    Print(Code,"    CCL_AddNode2Tail(pCurTNode->hChildList, pCurChild);\n");
    Print(Code,"    if(_SyntaxAnalysis_%s(CCL_GetDataPtr(SyntaxNode, pCurChild), pdwCurWordPos)<0) goto END_%d_%d_L;//����[%s]\n", szBuff, nOrgX,nOrgY, szBuff);
    break;
  case ' ':
  case '\0':
    dwNodeType=SDGNT_undefined;
    Print(Code,"    return 0;//����\n");
    return 0;
    break;
  default:
    goto CHECK_CHILDREN_L;
  }
  if(nPos==0 && y==0)
  {//pGraph[0][0]=='(' || pGraph[0][0]=='['
    _Add2Walked(0,0);_Add2Walked(x,0);
  }

CHECK_CHILDREN_L:
  Print(Code, "    dwSaveWordPos=*pdwCurWordPos;//����λ��\n");
  //find all child.Ѱ�ұ�������ڵ����ӽ��
  if ((nRet=_FindChild(pGraph, nRowCnt, y,x, staChild, &nChildCnt)) < 0)
  {
    printf("�������ӽ�����\n");
    return nRet;
  }
  if ((nRet=_SortChildSet(pGraph, nRowCnt, staChild, nChildCnt)) < 0)
  {
    printf("�����ӽ�����\n");
    return nRet;
  }
  
  //proc children.�������ӽ��,��Щ�ӽ�㶼�Ǳ������һ������ƥ����﷨���
  for (i=0; i<nChildCnt; ++i)
  {
    x=staChild[i].x;y=staChild[i].y;
    switch(cur)
    {
    case '(':
      nPos=x;
      ++x;
      while (cur!=')' || (right!='^' && right!='>' && right!='v' && right!='<'))
      {
        ++x;
      }
      sprintf(szBuff, "%.*s", x-nPos-1, pGraph[y]+nPos+1);
      _InsertCode(SDGNT_word, szBuff, nPos,y, x,y, nLevel);
      naX[i]=nPos;//��¼(λ��
      if(_IsWalked(x,y)){continue;}
      printf("����(%.*s)\n", x-nPos-1, pGraph[y]+nPos+1);
      break;
    case '[':
      nPos=x;
      ++x;
      while (cur!=']')
      {
        ++x;
      }
      sprintf(szBuff, "%.*s", x-nPos-1, pGraph[y]+nPos+1);
      _InsertCode(SDGNT_content, szBuff, nPos,y, x,y, nLevel);
      naX[i]=nPos;//��¼[λ��
      if(_IsWalked(x,y)){continue;}
      printf("����[%.*s]\n", x-nPos-1, pGraph[y]+nPos+1);
      break;
    case ')':
      nPos=x;
      --x;
      while ((left!='^' && left!='>' && left!='v' && left!='<') || cur!='(')
      {
        --x;
      }
      sprintf(szBuff, "%.*s", nPos-x-1, pGraph[y]+x+1);
      _InsertCode(SDGNT_word, szBuff, x,y, nPos,y, nLevel);
      naX[i]=nPos;//��¼)λ��
      if(_IsWalked(x,y)){continue;}
      printf("����(%.*s)\n", nPos-x-1, pGraph[y]+x+1);
      break;
    case ']':
      nPos=x;
      --x;
      while (cur!='[')
      {
        --x;
      }
      sprintf(szBuff, "%.*s", nPos-x-1, pGraph[y]+x+1);
      _InsertCode(SDGNT_content, szBuff, x,y, nPos,y, nLevel);
      naX[i]=nPos;//��¼]λ��
      if(_IsWalked(x,y)){continue;}
      printf("����[%.*s]\n", nPos-x-1, pGraph[y]+x+1);
      break;
    case ' ':
    case '\0':
      _InsertCode(SDGNT_word, szBuff, x,y, nPos,y, nLevel);
      printf("����[x:%d, y:%d]\n", x,y);
      break;
    default:
      printf("�������ӽ�����쳣[%c]\n", cur);
      return -1;
    }
  }

  Print(Code,"    //��ԭ����(�������ӽ�㶼ƥ��ʧ��,Ϊƥ�䱾�������ֵܽ����׼��)\n");
  Print(Code,"    END_%d_%d_L:\n", nOrgX, nOrgY);
  Print(Code,"    while (pCurTNode->byChildCnt > byOrgChildCnt)\n");
  Print(Code,"    {\n");
  Print(Code,"      pCurChild=CCL_GetPrevNode(pCurTNode->hChildList, NULL);\n");//ȡβ
  Print(Code,"      CCL_DelNode(pCurTNode->hChildList, pCurChild, TRUE);\n");
  Print(Code,"      --pCurTNode->byChildCnt;\n");
  Print(Code,"    }\n");
  Print(Code,"    return -1;\n");

  //travel children.������ӽ������ȱ���
  for (i=0; i<nChildCnt; ++i)
  {
    /*if ((cVal=pGraph[staChild[i].y][staChild[i].x])==' ' || cVal=='\0')
    {//��������
      continue;
    }*/
    if(!_IsWalked(staChild[i].x,staChild[i].y)){ _Add2Walked(naX[i],staChild[i].y); _Add2Walked(staChild[i].x,staChild[i].y);}
    else{continue;}
    if ((nRet=SyntaxDescGraphWalk(pGraph, nRowCnt, staChild[i].y, staChild[i].x, 0)) < 0)
    {
      return nRet;
    }
  }
  
  return 0;
#undef cur
#undef up
#undef down
#undef left
#undef right
}
/*int SyntaxDescGraphWalk(char **pGraph, int nRowCnt, int y, int x)//������ȱ���,������....
{
  int nRet;
  int nPos;
  char szBuff[128];
#define up ((y-1<0)?' ':pGraph[y-1][x])
#define down ((y+1>=nRowCnt)?' ':pGraph[y+1][x])
#define right pGraph[y][x+1]
#define left ((x-1<0)?' ':pGraph[y][x-1])
#define cur pGraph[y][x]

  while (1)
  {
    //if(_IsWalked(x,y)) return 0;
    //_Add2Walked(x,y);
    switch(cur)
    {
    case '>':
CONTINUE_RIGHT_L:
      //look up
      if (up == '^')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y-1,x)) < 0)
        {
          return nRet;
        }
      }
      //look down
      if (down == 'v')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y+1,x)) < 0)
        {
          return nRet;
        }
      }
      //walk self way
      x+=1;//step next
      if (cur==' ' || cur=='\0')
      {//exit
        printf("����[x:%d,y:%d]\n", x, y);
        return 0;
      }
      else if (cur == '>')
      {
        goto CONTINUE_RIGHT_L;
      }
      else if (cur == '^')
      {
        goto CONTINUE_UP_L;
      }
      else if (cur == 'v')
      {
        goto CONTINUE_DOWN_L;
      }
      break;
    case 'v':
CONTINUE_DOWN_L:
      //look left
      if (left == '<')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y,x-1)) < 0)
        {
          return nRet;
        }
      }
      //look right
      if (right == '>')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y,x+1)) < 0)
        {
          return nRet;
        }
      }
      //walk self way
      ++y;//step next
      if (cur==' ' || y>=nRowCnt)
      {//exit
        printf("����[x:%d,y:%d]\n", x, y);
        return 0;
      }
      else if (cur == 'v')
      {
        goto CONTINUE_DOWN_L;
      }
      else if (cur == '<')
      {
        goto CONTINUE_LEFT_L;
      }
      else if (cur == '>')
      {
        goto CONTINUE_RIGHT_L;
      }
      break;
    case '<':
CONTINUE_LEFT_L:
      //look up
      if (up == '^')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y-1,x)) < 0)
        {
          return nRet;
        }
      }
      //look down
      if (down == 'v')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y+1,x)) < 0)
        {
          return nRet;
        }
      }
      //walk self way
      --x;//step next
      if (cur==' ' || x<0)
      {//exit
        printf("����[x:%d,y:%d]\n", x, y);
        return 0;
      }
      else if (cur == '<')
      {
        goto CONTINUE_LEFT_L;
      }
      else if (cur == '^')
      {
        goto CONTINUE_UP_L;
      }
      else if (cur == 'v')
      {
        goto CONTINUE_DOWN_L;
      }
      break;
    case '^':
CONTINUE_UP_L:
      //look left
      if (left == '<')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y,x-1)) < 0)
        {
          return nRet;
        }
      }
      //look right
      if (right == '>')
      {
        if ((nRet=SyntaxDescGraphWalk(pGraph,nRowCnt, y,x+1)) < 0)
        {
          return nRet;
        }
      }
      //walk self way
      --y;//step next
      if (cur==' ' || y<0)
      {//exit
        printf("����[x:%d,y:%d]\n", x, y);
        return 0;
      }
      else if (cur == '^')
      {
        goto CONTINUE_UP_L;
      }
      else if (cur == '<')
      {
        goto CONTINUE_LEFT_L;
      }
      else if (cur == '>')
      {
        goto CONTINUE_RIGHT_L;
      }
      break;
    default:
      
      switch(cur)
      {
      case '(':
        nPos=x;
        ++x;
        while (cur!=')' || (right!='^' && right!='>' && right!='v' && right!='<'))
        {
          ++x;
        }
        sprintf(szBuff, "%.*s", x-nPos-1, pGraph[y]+nPos+1);
        _InsertCode(SDGNT_word, szBuff, nPos,y, x,y);
        if(!_IsWalked(x,y)){ _Add2Walked(nPos,y); _Add2Walked(x,y);}
        else{return 0;}
        printf("����(%.*s)\n", x-nPos-1, pGraph[y]+nPos+1);
        ++x;
        break;
      case '[':
        nPos=x;
        ++x;
        while (cur!=']')
        {
          ++x;
        }
        sprintf(szBuff, "%.*s", x-nPos-1, pGraph[y]+nPos+1);
        _InsertCode(SDGNT_content, szBuff, nPos,y, x,y);
        if(!_IsWalked(x,y)){ _Add2Walked(nPos,y); _Add2Walked(x,y);}
        else{return 0;}
        printf("����[%.*s]\n", x-nPos-1, pGraph[y]+nPos+1);
        ++x;
        break;
      case ')':
        nPos=x;
        --x;
        while ((left!='^' && left!='>' && left!='v' && left!='<') || cur!='(')
        {
          --x;
        }
        sprintf(szBuff, "%.*s", nPos-x-1, pGraph[y]+x+1);
        _InsertCode(SDGNT_word, szBuff, x,y, nPos,y);
        if(!_IsWalked(x,y)){ _Add2Walked(nPos,y); _Add2Walked(x,y);}
        else{return 0;}
        printf("����(%.*s)\n", nPos-x-1, pGraph[y]+x+1);
        --x;
        break;
      case ']':
        nPos=x;
        --x;
        while (cur!='[')
        {
          --x;
        }
        sprintf(szBuff, "%.*s", nPos-x-1, pGraph[y]+x+1);
        _InsertCode(SDGNT_content, szBuff, x,y, nPos,y);
        if(!_IsWalked(x,y)){ _Add2Walked(nPos,y); _Add2Walked(x,y);}
        else{return 0;}
        printf("����[%.*s]\n", nPos-x-1, pGraph[y]+x+1);
        --x;
        break;
      default:
        printf("�����Ƿ��ַ�[%c]\n", cur);
        return -1;
      }
      break;
    }
    
  }

#undef cur
#undef up
#undef down
#undef left
#undef right
}*/

int main(int argc, char * argv[])
{
  int i,nGraphCnt,nRet;
  FILE *pFile;

  nGraphCnt=sizeof(g_staGraphNameMap)/sizeof(GraphNameMap);
  
  Print(Code, "//�˴���ҳ�ɹ���<CodeGenerate>��[%s]����\n", __TIMESTAMP__);
  Print(Code, "#include <WTypes.h>\n");
  Print(Code, "#include \"GlobalEnv.h\"\n");
  Print(Code, "#define S4T_ST_Word (1)//����,Ҷ�ӽ��\n");
  for (i=0;i<nGraphCnt;++i)
  {
    Print(Code, "#define S4T_ST_%s (%d)\n", g_staGraphNameMap[i].szName, i+2);
  }

  Print(Code, "SyntaxNode g_stSyntaxTreeRoot={0};\n");

  Print(Code, "typedef int (*SyntaxAnalysisProc)(SyntaxNode *pCurNode, DWORD *pdwCurWordPos);\n");
  Print(Code, "typedef struct tagSyntaxAnalysisMap {\n");
  Print(Code, "BYTE byST;\n");
  Print(Code, "SyntaxAnalysisProc funProc;\n");
  Print(Code, "}SyntaxAnalysisMap;\n");

  Print(Code, "int _SyntaxAnalysis_Word (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);\n");
  for (i=0;i<nGraphCnt;++i)
  {
    Print(Code, "int _SyntaxAnalysis_%s (SyntaxNode *pCurNode, DWORD *pdwCurWordPos);\n", g_staGraphNameMap[i].szName);
  }

  Print(Code, "SyntaxAnalysisMap g_staSyntaxAnalysisMap[]={\n");
  Print(Code, "{S4T_ST_Script, NULL},\n");
  Print(Code, "{S4T_ST_Word, _SyntaxAnalysis_Word},\n");
  for (i=0;i<nGraphCnt;++i)
  {
    Print(Code, "{S4T_ST_%s, _SyntaxAnalysis_%s},\n", g_staGraphNameMap[i].szName, g_staGraphNameMap[i].szName);
  }
  Print(Code, "};\n");

  Print(Code, "int _SyntaxAnalysisSubProc(BYTE byST, SyntaxNode *pCurNode, DWORD *pdwCurWordPos)\n");
  Print(Code, "{\n");
  Print(Code, "  int i;\n");
  Print(Code, "  for (i=0; i<sizeof(g_staSyntaxAnalysisMap)/sizeof(SyntaxAnalysisMap); ++i)\n");
  Print(Code, "  {\n");
  Print(Code, "    if (g_staSyntaxAnalysisMap[i].byST==byST)\n");
  Print(Code, "    {\n");
  Print(Code, "      if (g_staSyntaxAnalysisMap[i].funProc != NULL)\n");
  Print(Code, "      {\n");
  Print(Code, "        return g_staSyntaxAnalysisMap[i].funProc(pCurNode, pdwCurWordPos);\n");
  Print(Code, "      }\n");
  Print(Code, "      return S4T_EC_SAProcNULL;\n");
  Print(Code, "    }\n");
  Print(Code, "  }\n");
  Print(Code, "  return S4T_EC_SAProcNotMapped;\n");
  Print(Code, "}\n");

  
  Print(Code, "#define pstCurWord ((Word*)(&g_staAllWord[*pdwCurWordPos]))\n");
  Print(Code, "int _SyntaxAnalysis_Word(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)\n");
  Print(Code, "{\n");
  Print(Code, "  pCurTNode->byType=S4T_ST_Word;\n");
  Print(Code, "  pCurTNode->byChildCnt=0;\n");
  Print(Code, "  pCurTNode->hChildList=(HCCL)pstCurWord;\n");
  Print(Code, "  ++(*pdwCurWordPos);\n");
  Print(Code, "  return 0;\n");
  Print(Code, "}\n");

  Print(Code, "#define NODE_POS(x,y) ((x<<16)|y)\n");
  for (i=0;i<nGraphCnt;++i)
  {
    Print(Code, "int _Recursion_%s(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos, int x, int y)\n", g_staGraphNameMap[i].szName);
    Print(Code, "{\n");
    Print(Code, "  BYTE byOrgChildCnt=pCurTNode->byChildCnt;\n");
    Print(Code, "  DWORD dwOrgWordPos=*pdwCurWordPos;\n");
    Print(Code, "  DWORD dwSaveWordPos=*pdwCurWordPos;\n");
    Print(Code, "  DWORD pos=(x<<16)|y;\n");
    Print(Code, "  ListNode *pCurChild=NULL;\n");
    Print(Code, "\n");
    
    printf("=%s==========================\n", g_staGraphNameMap[i].szName);
    _StartWalk();//��ֹ��·��ѭ��
    strcpy(g_szCurContentName, g_staGraphNameMap[i].szName);
    
    Print(Code, "  switch(pos)\n");
    Print(Code, "  {\n");
    if ((nRet=SyntaxDescGraphWalk(g_staGraphNameMap[i].pGraph, g_staGraphNameMap[i].dwRowCnt ,0,0, 1)) < 0)
    {
      return nRet;
    }
    Print(Code, "  }\n");
    Print(Code, "  return -2;\n");
    Print(Code, "}\n");


    Print(Code, "int _SyntaxAnalysis_%s(SyntaxNode *pCurTNode, DWORD *pdwCurWordPos)\n", g_staGraphNameMap[i].szName);
    Print(Code, "{\n");
    Print(Code, "  int nRet;\n");
    Print(Code, "  pCurTNode->byType=S4T_ST_%s;\n", g_staGraphNameMap[i].szName);
    Print(Code, "  pCurTNode->byChildCnt=0;\n");
    Print(Code, "  pCurTNode->hChildList=CCL_StartUp(sizeof(SyntaxNode), 0, NULL);\n");
    Print(Code, "\n");
    Print(Code, "  nRet=_Recursion_%s(pCurTNode, pdwCurWordPos, 0,0);\n", g_staGraphNameMap[i].szName);
    Print(Code, "  if(nRet<0)\n");
    Print(Code, "  {\n");
    Print(Code, "    CCL_CleanUp(pCurTNode->hChildList);\n");
    Print(Code, "    pCurTNode->hChildList=NULL;\n");
    Print(Code, "    pCurTNode->byChildCnt=0;\n");
    Print(Code, "  }\n");
    Print(Code, "  return nRet;\n");
    Print(Code, "}\n");
  }
  Print(Code, "int S4T_SyntaxAnalysis()\n");
  Print(Code, "{\n");
  Print(Code, "  DWORD dwWordPos=0;\n");
  Print(Code, "  return _SyntaxAnalysis_%s(&g_stSyntaxTreeRoot, &dwWordPos);\n", g_staGraphNameMap[0].szName);
  Print(Code, "}\n");

  Print(Code, "#undef pstCurWord\n");
  
  printf("%s", g_szCode);
//return 0;
  if((pFile=fopen(g_szOutPath, "w+")) != NULL)
  {
    fprintf(pFile, "%s", g_szCode);
    fclose(pFile);
  }
  return 0;
}