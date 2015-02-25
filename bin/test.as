var: 
u32 dw1=0;
buffer[16] buf1="12345678";
s32 n1,n2=16,n3=n2/2;

src:
function fun1(a,b,c)
{
  if(a>0)
  {
    n1=a;
    exit;
  };
  
  n1=b;
}

call fun1(n2,0,0);