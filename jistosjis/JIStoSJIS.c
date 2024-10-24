/* This program to know SJIS code from JIS information. */
/* Example.
input men : 1
input ku(hex-0x20) : 4
input ten(hex-0x20) : 2
JIS  0x2422 1men 4ku 2ten
SJIS 0x82a0
Therefore, JIS 1men 4ku 2ten is SJIS 0x82a0.
*/
/* This program is not for Shift JIS but Shift_JIS-2004. */
/* So, it can handle also 2 men of JIS(4th level Kanji). */

#include <stdio.h>

int main(){

  int men=0, ku=0, ten=0;    /* Men, Ku and Ten of JIS. */
  int S1=0, S2;    /* 1st byte and 2nd byte of Shif JIS. */

  printf("input men : ");
  scanf("%d",&men);
  printf("input ku : ");
  scanf("%d",&ku);
  printf("input ten : ");
  scanf("%d",&ten);
#if 0
  men=1;
  ku=1;    /* hex - 0x20(32) */
  ten=1;   /* hex - 0x20(32) */
#endif
  /* 1st byte */
  if( men==1 ){
    if(1 <= ku && ku <= 62){
      S1 = (ku + 0x101) / 2;
    }
    else if(63 <= ku && ku <= 94){
      S1 = (ku + 0x181) / 2;
    }
    else{
      printf("ku is NG.\n");
    }
  }
  else if( men==2 ){
    if(ku==1||ku==3||ku==4||ku==5||ku==8||ku==12||ku==13||ku==14||ku==15){
      S1 = (ku + 0x1df) / 2 - (ku / 8) * 3;
    }
    else if(78 <= ku <= 94){
      S1 = (ku + 0x19b) / 2;
    }
    else{
      printf("ku is NG.\n");
    }
  }
  else{
    printf("men is NG.\n");
  }
  
  /* 2nd byte */
  if(ku%2==1){
    if(1 <= ku <= 63){
      S2 = ten + 0x3f;
    }
    else if(64 <= ku <= 94){
      S2 = ten + 0x40;
    }
    else{
      printf("ku is NG.\n");
    }
  }
  else{
    S2 = ten + 0x9e;
  }
  printf("JIS  0x%x%x %dmen %dku %dten\n",ku+32,ten+32, men, ku, ten);
  printf("SJIS 0x%x%x\n",S1,S2);
}

