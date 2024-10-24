/************************************************
AsciiToBinary2.c
This C program converts ascii.txt which has ascii letters to binary.txt which has binary code.

Before
%ABC!"123#

After
0x25,0x41,0x42,0x43,0x21,0x22,0x31,0x32,0x33,0x23,
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* input file size by my self ot FILE_SIZE */
//#define COUNT

const char INPUT_FILE_NAME[] = "ascii.txt";
const char OUTPUT_FILE_NAME[] = "binary.txt";
const int FILE_SIZE = 0x6beb35;

int main(){
	FILE *i_fp, *o_fp;
	int cnt,cnt2,cnt3,ret;
	unsigned char tmp_char_high, tmp_char_low;
	char buf[0x10FFFF];
	char tmp_str[4],*tmp_str2;
	unsigned int value_i;
	char value_c;

	memset(buf,0,sizeof(buf));

	i_fp = fopen(INPUT_FILE_NAME,"rb");
	o_fp = fopen(OUTPUT_FILE_NAME,"wb");
	if( i_fp == NULL || o_fp == NULL ){
		printf("File cannot be open.\n");
		return(2);
	}

/* input file */
	cnt = 0;
	while(1){
		value_c = fgetc(i_fp);
		
#ifndef COUNT
		if(value_c == EOF){
			break;
		}
#endif
		
		fputc('0', o_fp);
		fputc('x', o_fp);
		
		tmp_char_high = (unsigned char)value_c & 0xf0;
		tmp_char_high = tmp_char_high >> 4;
			if(tmp_char_high >= 0 && tmp_char_high <= 9){	/* Numeric */
			fputc(tmp_char_high+0x30, o_fp);
		}
		else{	/* Alphabet */
			fputc(tmp_char_high+0x57, o_fp);
		}
		
		tmp_char_low = (unsigned char)value_c & 0x0f;
			if(tmp_char_low >= 0 && tmp_char_low <= 9){	/* Numeric */
			fputc(tmp_char_low+0x30, o_fp);
		}
		else{	/* Alphabet */
			fputc(tmp_char_low+0x57, o_fp);
		}
		
		fputc(',', o_fp);
		
#ifdef COUNT
		cnt++;
		if(cnt>FILE_SIZE){
			break;
		}
#endif
	}
	
	
	fclose(i_fp);
	fclose(o_fp);

	return 0;
}
