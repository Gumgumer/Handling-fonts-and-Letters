/************************************************
Input  : input.txt(utf8 text)
Output : output.txt(Unicode, like U+3042)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE_NAME[] = "input.txt";
const char OUTPUT_FILE_NAME[] = "output.txt";



int main(){
	FILE *in_fp, *out_fp;
	unsigned char buf[32];
	unsigned char work_c, work_c2, work_c3, work_c4;
	unsigned char uni_1st_byte, uni_2nd_byte, uni_3rd_byte;
	int char_cnt=0;
	
	in_fp = fopen(INPUT_FILE_NAME,"rb");
	if( in_fp == NULL ){
		printf("Can't open %s\n", INPUT_FILE_NAME);
		return(2);
	}
	
	out_fp = fopen(OUTPUT_FILE_NAME,"wb");
	if( out_fp == NULL ){
		printf("Can't open %s\n", OUTPUT_FILE_NAME);
		return(2);
	}
	
	while(1){
		char_cnt++;
		memset(buf, 0, sizeof(buf));
		
		work_c = fgetc(in_fp);
		if( work_c == (unsigned char)EOF ){
			printf("Done!\n");
			return 0;
		}
		
		/* 1byte utf8 : 1st byte is 0xxx xxxx */
		if( (work_c & 0x80) == 0 ){
			sprintf(buf, "U+%x\n" ,work_c);
			fprintf(out_fp, "%s", buf);
		}
		/* 2byte utf8 : 1st byte is 110x xxxx */
		else if( (work_c & 0xE0) == 0xC0 ){
			work_c2 = fgetc(in_fp);
			if( ( work_c2 == (unsigned char)EOF ) || ( (work_c2 & 0xC0) != 0x80 ) ){
				printf("Error!\n");
				return 0;
			}
			uni_1st_byte = work_c & 0x1C;
			uni_1st_byte = uni_1st_byte >> 2;
			uni_2nd_byte = (work_c & 0x03) << 6;
			uni_2nd_byte = uni_2nd_byte + (work_c2 & 0x3F);
			if( uni_2nd_byte > 0x0F ){
				sprintf(buf, "U+%x%2x\n" ,uni_1st_byte, uni_2nd_byte);
			}
			else{
				sprintf(buf, "U+%x0%x\n" ,uni_1st_byte, uni_2nd_byte);
			}
			fprintf(out_fp, "%s", buf);
		}
		/* 3byte utf8 : 1st byte is 1110 xxxx */
		else if( (work_c & 0xF0) == 0xE0 ){
			work_c2 = fgetc(in_fp);
			work_c3 = fgetc(in_fp);
			if( ( work_c2 == (unsigned char)EOF ) || ( work_c3 == (unsigned char)EOF ) || ( (work_c2 & 0xC0) != 0x80 ) || ( (work_c3 & 0xC0) != 0x80 ) ){
				printf("Error!\n");
				return 0;
			}
			uni_1st_byte = work_c & 0x0F;
			uni_1st_byte = uni_1st_byte << 4;
			uni_1st_byte = uni_1st_byte + ((work_c2 & 0x3C) >>2);
			uni_2nd_byte = (work_c2 & 0x03) << 6;
			uni_2nd_byte = uni_2nd_byte + (work_c3 & 0x3F);
			if( uni_2nd_byte > 0x0F ){
				sprintf(buf, "U+%x%2x\n" ,uni_1st_byte, uni_2nd_byte);
			}
			else{
				sprintf(buf, "U+%x0%x\n" ,uni_1st_byte, uni_2nd_byte);
			}
			fprintf(out_fp, "%s", buf);
		}
		/* 4byte utf8 : 1st byte is 1111 0xxx */
		else if( (work_c & 0xF8) == 0xF0 ){
			work_c2 = fgetc(in_fp);
			work_c3 = fgetc(in_fp);
			work_c4 = fgetc(in_fp);
			if( ( work_c2 == (unsigned char)EOF ) || ( work_c3 == (unsigned char)EOF ) || ( work_c4 == (unsigned char)EOF ) || ( (work_c2 & 0xC0) != 0x80 ) || ( (work_c3 & 0xC0) != 0x80 ) || ( (work_c4 & 0xC0) != 0x80 ) ){
				printf("Error!\n");
				return 0;
			}
			uni_1st_byte = (work_c & 0x07) << 2;
			uni_1st_byte = uni_1st_byte + ((work_c2 & 0x30) >> 4);
			uni_2nd_byte = (work_c2 & 0x0F) << 4;
			uni_2nd_byte = uni_2nd_byte + ((work_c3 & 0x3C) >> 2);
			uni_3rd_byte = (work_c3 & 0x03) << 6;
			uni_3rd_byte = uni_3rd_byte + (work_c4 & 0x3F);
			if( uni_2nd_byte > 0x0F ){
				if( uni_3rd_byte > 0x0F ){
					sprintf(buf, "U+%x%x%x\n" ,uni_1st_byte, uni_2nd_byte, uni_3rd_byte);
				}
				else{
					sprintf(buf, "U+%x%x0%x\n" ,uni_1st_byte, uni_2nd_byte, uni_3rd_byte);
				}
			}
			else{
				if( uni_3rd_byte > 0x0F ){
					sprintf(buf, "U+%x0%x%x\n" ,uni_1st_byte, uni_2nd_byte, uni_3rd_byte);
				}
				else{
					sprintf(buf, "U+%x0%x0%x\n" ,uni_1st_byte, uni_2nd_byte, uni_3rd_byte);
				}
			}
			fprintf(out_fp, "%s", buf);
		}
		else{
			printf("error : not 1byte, 2byte, 3byte or 4byte.\n");
			return 0;
		}
	}
	
	fclose(in_fp);
	fclose(out_fp);
	
	return 0;
}
