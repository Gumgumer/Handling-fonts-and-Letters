/************************************************
Unicode to UTF-8
Input : Unicode like 4E9C
Output : UTF-8 like 0xe4 0xba 0x9c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	unsigned short b1, b2, b3, b4; /* 1st, 2nd, 3rd and 4th byte for UTF8 */
	unsigned short work1, work2, work3, work4;
	unsigned long workl1, workl2, workl3, workl4;
	unsigned long unicode=0;
	unsigned short seq_code;

	printf("input Unicode in hex(from U+0 to U+10FFFF) : U+");
	scanf("%x",&unicode);
	if(unicode<=0x0000007f){
		b1=unicode;
		printf("UTF-8 = 0x%x\n",b1);
	}
	else if(unicode<=0x00000800){
		work1 = unicode >> 6; /* Get 1st 5bit */
		work2 = unicode & 0x003F; /* Get 2nd 6bit */
		b1 = 0xc0 + work1;
		b2 = 0x80 + work2;
		printf("UTF-8 = 0x%x 0x%x\n",b1,b2);
	}
	else if(unicode<=0x0000ffff){
		work1 = unicode >> 12; /* Get 1st 4bit */
		work2 = unicode & 0x0FFF; /* Get 2nd 6bit */
		work2 = work2 >> 6;
		work3 = unicode & 0x003F; /* Get 3rd 6bit */
		b1 = 0xe0 + work1;
		b2 = 0x80 + work2;
		b3 = 0x80 + work3;
		printf("UTF-8 = 0x%x 0x%x 0x%x\n",b1,b2,b3);
	}
	else if(unicode<=0x0010ffff){
		work1 = unicode >> 18; /* Get 1st 3bit */
		workl2 = unicode & 0x0003ffff; /* Get 2nd 6bit */
		work2 = workl2 >> 12;
		workl3 = unicode & 0x00000FFF; /* Get 3rd 6bit */
		work3 = workl3 >> 6;
		work4 = unicode & 0x0000003F; /* Get 4th 6bit */
		b1 = 0xf0 + work1;
		b2 = 0x80 + work2;
		b3 = 0x80 + work3;
		b4 = 0x80 + work4;
		printf("UTF-8 = 0x%x 0x%x 0x%x 0x%x\n",b1,b2,b3,b4);
	}
	else{
		printf("Error. unicode:U+%x\n",unicode);
	}

  return 0;
}
