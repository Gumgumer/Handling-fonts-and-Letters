/* This program to know JIS code from SJIS code. */
/* Example.
input 1st byte by hex : 82
input 2nd byte by hex : a0
SJIS 0x82 0xa0
JIS  0x24 0x22
Therefore, SJIS 0x82a0 is JIS 0x2422(4ku2ten).
*/
/* This program is not for Shift JIS but Shift_JIS-2004. */
/* So, it can handle also 2 men of JIS(4th level Kanji). */

#include <stdio.h>


int main(){

  int c1=0, c2=0, sjis1=0, sjis2=0;


  printf("input 1st byte by hex : ");
  scanf("%x",&sjis1);
  printf("input 2nd byte by hex : ");
  scanf("%x",&sjis2);

  c1=sjis1;
  c2=sjis2;
if (c1 >= 0xe0) { c1 = c1 - 0x40; }
if (c2 >= 0x80) { c2 = c2 - 1; }
if (c2 >= 0x9e) {
    c1 = (c1 - 0x70) * 2;
    c2 = c2 - 0x7d;
} else {
    c1 = ((c1 - 0x70) * 2) - 1;
    c2 = c2 - 0x1f;
}
  printf("SJIS 0x%x 0x%x\n",sjis1,sjis2);
  printf("JIS  0x%x 0x%x\n",c1,c2);
}
