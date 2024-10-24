/************************************************
AsciiToBinary.c
This C program converts ascii.txt which has ascii letters to binary.txt which has binary code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE_NAME[] = "ascii.txt";
const char OUTPUT_FILE_NAME[] = "binary.txt";

int main(){
	FILE *i_fp, *o_fp;
	int cnt,cnt2,cnt3,ret;
	unsigned char tmp_char_high, tmp_char_low;
	char buf[0x10FFFF];
	char tmp_str[4],*tmp_str2;
	unsigned int value_i;
	unsigned char value_c;

	memset(buf,0,sizeof(buf));

	i_fp = fopen(INPUT_FILE_NAME,"rb");
	o_fp = fopen(OUTPUT_FILE_NAME,"wb");
	if( i_fp == NULL || o_fp == NULL ){
		printf("File cannot be open.\n");
		return(2);
	}

/* input file<hF@ */
	cnt = 0;
	while(1){
		buf[cnt] = fgetc(i_fp);
		if(buf[cnt] == EOF){
			buf[cnt] = 0;
			break;
		}
		if(buf[cnt] < '0' || buf[cnt] > '9'){
			if(buf[cnt] < 'a' || buf[cnt] > 'f'){
				printf("0 kara f igai no moji ga aruyo!\n");
				return(2);
			}
		}
		cnt++;
	}
	
	if(0 != cnt%2){
		printf("moji no kazu ga kisuu dayo!\n");
		return(2);
	}

/* output file=PNO */
	cnt = 0;
	while(1){
		if(buf[cnt] == 0){
			break;
		}
		tmp_char_high = buf[cnt];
		tmp_char_low  = buf[cnt+1];
		
		memset(tmp_str,0,4);
		tmp_str[0] = tmp_char_high;
		tmp_str[1] = tmp_char_low;
		
		value_i = strtol( tmp_str, &tmp_str2, 16 );
		value_c = (char)value_i;
		fputc(value_c, o_fp);
		
		cnt = cnt + 2;
	}
	
	fclose(i_fp);
	fclose(o_fp);

	return 0;
}
