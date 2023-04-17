#include <stdio.h> 
#include <string.h>
#include <conio.h>
#include "include_c/libxl.h"
#include "excel.h"
#include "fram.h"

/**************************************************************/ 
/* Copyright (c) 2020, longsys */ 
/* All rights reserved. */ 
/* Project Name: Leakage_Test*/ 
/* Author: gaozhe*/ 
/* Date: 2020.03.26*/ 
/* Version:v1.0 */ 
/* Abstract：Excel数据打印函数定义 */ 
/*************************************************************/

extern int mode_num;  //模式标识符在外部文件中定义 


/*打印 模式1/2 表格标题栏 1*/ 
void showtitle_1_mode1(SheetHandle sheet,int *num)
{	
	int i;
	char buf[10]="样品#"; 
	char buf_name[10]={0};
    char buf_num[10]={0};
    
	xlSheetWriteStrA(sheet, 1, 1, "通道a", NULL);
	xlSheetWriteStrA(sheet, 1, 7, "通道b", NULL);
	xlSheetWriteStrA(sheet, 2, 0, "引脚", NULL);
	xlSheetWriteStrA(sheet, 2, 1, "类型", NULL);
	xlSheetWriteStrA(sheet, 2, 7, "类型", NULL);
	
	for(i=0;i<4;i++)
	{
		strcpy(buf_name,buf);
        sprintf(buf_num,"%d",num[i]);
        strcat(buf_name,buf_num);
		xlSheetWriteStrA(sheet, 2, i+2, buf_name, NULL);
		xlSheetWriteStrA(sheet, 2, i+8, buf_name, NULL);
		memset(buf_name,0,strlen(buf_name));
	}
}



/*打印 模式1/2 表格标题栏 2*/ 
void showtitle_2_mode1(SheetHandle sheet,int *num)
{
	int i;
	char buf[10]="样品#"; 
	char buf_name[10]={0};
    char buf_num[10]={0};
    
    for(i=0;i<4;i++)
    {
    	xlSheetWriteStrA(sheet, 0, 1+7*i, "通道a", NULL);
		xlSheetWriteStrA(sheet, 0, 3+7*i, "通道b", NULL);
		xlSheetWriteStrA(sheet, 1, 0+7*i, "引脚", NULL);
		xlSheetWriteStrA(sheet, 1, 1+7*i, "类型", NULL);
		xlSheetWriteStrA(sheet, 1, 2+7*i, "Leakage", NULL);
		xlSheetWriteStrA(sheet, 1, 3+7*i, "引脚", NULL);
		xlSheetWriteStrA(sheet, 1, 4+7*i, "类型", NULL);
		xlSheetWriteStrA(sheet, 1, 5+7*i, "Leakage", NULL);
	}
	
	for(i=0;i<4;i++)
	{
		strcpy(buf_name,buf);
        sprintf(buf_num,"%d",num[i]);
        strcat(buf_name,buf_num);
		xlSheetWriteStrA(sheet, 0, 0+7*i, buf_name, NULL);
		memset(buf_name,0,strlen(buf_name));
	}
}



/*打印 模式3 表格标题栏 1*/
void showtitle_1_mode3(SheetHandle sheet,int *num)
{
	
	int i;
	char buf[10]="样品#"; 
	char buf_name[10]={0};
    char buf_num[10]={0};
    
	xlSheetWriteStrA(sheet, 1, 0, "引脚", NULL);
	xlSheetWriteStrA(sheet, 1, 1, "类型", NULL);
	
	for(i=0;i<4;i++)
	{
		strcpy(buf_name,buf);
        sprintf(buf_num,"%d",num[i]);
        strcat(buf_name,buf_num);
		xlSheetWriteStrA(sheet, 1, i+2, buf_name, NULL);
		memset(buf_name,0,strlen(buf_name));
	}
} 



/*打印 模式3 表格标题栏 2*/
void showtitle_2_mode3(SheetHandle sheet,int *num)
{
	int i;
	char buf[10]="样品#"; 
	char buf_name[10]={0};
    char buf_num[10]={0};
    
    for(i=0;i<4;i++)
    {
    	xlSheetWriteStrA(sheet, 1, 0+4*i, "引脚", NULL);
		xlSheetWriteStrA(sheet, 1, 1+4*i, "类型", NULL);
		xlSheetWriteStrA(sheet, 1, 2+4*i, "Leakage", NULL);
	}
	
	for(i=0;i<4;i++)
	{
		strcpy(buf_name,buf);
        sprintf(buf_num,"%d",num[i]);
        strcat(buf_name,buf_num);
		xlSheetWriteStrA(sheet, 0, 0+4*i, buf_name, NULL);
		memset(buf_name,0,strlen(buf_name));
	}
}




/*Excel写函数，生成表格数据*/
void write_to_excel(struct Leakage leakage[][150],struct Leakage leakage_sort[][150],char *dirname_buf,int *dir_num)
{
	int i;
	
	BookHandle book = xlCreateBook();
	xlBookSetKey(book,"hello","windows-21202e0009c9e10465be636ca9k1lchd");
	
	if(book) 
    {	
        SheetHandle sheet1;	
		SheetHandle sheet2;	
	
        sheet1 = xlBookAddSheet(book, "leakage info", 0);
        if(sheet1) 
        {
			if(mode_num==1||mode_num==2)
			{
				if(mode_num==1)
				{
					xlSheetWriteStrA(sheet1, 0, 0, "LPDDR4", NULL);  //表格开头打印芯片信息 
					xlSheetWriteStrA(sheet1, 0, 1, "1 CS", NULL);
				}
				else
				{
					xlSheetWriteStrA(sheet1, 0, 0, "LPDDR4", NULL);
					xlSheetWriteStrA(sheet1, 0, 1, "2 CS", NULL);
				}
				
				showtitle_1_mode1(sheet1,dir_num);  //LP4型号表格1标题栏     
		
				for(i=1;i<=leakage[0][0].sample_num;i++) 
				{
					if(i%2==1) //打印 out类型数据信息 
					{
						xlSheetWriteStrA(sheet1, (i+5)/2, 0, leakage[0][i].pin_name, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 1, leakage[0][i].type, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 2, leakage[1][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 3, leakage[3][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 4, leakage[5][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 5, leakage[7][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 7, leakage[0][i].type, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 8, leakage[0][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 9, leakage[2][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 10, leakage[4][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 11, leakage[6][i].value, NULL);	
					}									
				}
				
				for(i=1;i<=leakage[0][0].sample_num;i++) 
				{
					if(i%2==0)  //打印 in类型数据信息 
					{
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 0, leakage[0][i].pin_name, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 1, leakage[0][i].type, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 2, leakage[1][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 3, leakage[3][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 4, leakage[5][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 5, leakage[7][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 7, leakage[0][i].type, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 8, leakage[0][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 9, leakage[2][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 10, leakage[4][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 11, leakage[6][i].value, NULL);
					} 					
				}	
			}
			else if(mode_num==3||mode_num==4)
			{
				if(mode_num==3)
				{
					xlSheetWriteStrA(sheet1, 0, 0, "LPDDR3", NULL);
					xlSheetWriteStrA(sheet1, 0, 1, "1 CS", NULL);
				}
				else
				{
					xlSheetWriteStrA(sheet1, 0, 0, "LPDDR3", NULL);
					xlSheetWriteStrA(sheet1, 0, 1, "2 CS", NULL);
				}
				
				showtitle_1_mode3(sheet1,dir_num);  //LP3型号表格1标题栏 
				
				for(i=1;i<=leakage[0][0].sample_num;i++) 
				{
					if(i%2==1)  //打印 out类型数据信息 
					{	
						xlSheetWriteStrA(sheet1, (i+5)/2, 0, leakage[0][i].pin_name, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 1, leakage[0][i].type, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 2, leakage[0][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 3, leakage[2][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 4, leakage[4][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+5)/2, 5, leakage[6][i].value, NULL);
					} 
					
				}
				for(i=1;i<=leakage[0][0].sample_num;i++) 
				{
					if(i%2==0)  //打印 in类型数据信息 
					{
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 0, leakage[0][i].pin_name, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 1, leakage[0][i].type, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 2, leakage[0][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 3, leakage[2][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 4, leakage[4][i].value, NULL);
						xlSheetWriteStrA(sheet1, (i+leakage[0][0].sample_num+4)/2, 5, leakage[6][i].value, NULL);
					} 	
				}
			}
			else
				;  
        }
        
        
        sheet2 = xlBookAddSheet(book,"leakage sort",0);
        if(sheet2)
        {
			if(mode_num==1||mode_num==2)
			{								
				showtitle_2_mode1(sheet2,dir_num);  //LP4型号表格2标题栏  
				
				for(i=1;i<=leakage[0][0].sample_num;i++) //打印已排序leakage数据信息 
				{
					xlSheetWriteStrA(sheet2, i+1, 0, leakage_sort[1][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 1, leakage_sort[1][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 2, leakage_sort[1][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 3, leakage_sort[0][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 4, leakage_sort[0][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 5, leakage_sort[0][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 7, leakage_sort[3][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 8, leakage_sort[3][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 9, leakage_sort[3][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 10, leakage_sort[2][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 11, leakage_sort[2][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 12, leakage_sort[2][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 14, leakage_sort[5][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 15, leakage_sort[5][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 16, leakage_sort[5][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 17, leakage_sort[4][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 18, leakage_sort[4][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 19, leakage_sort[4][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 21, leakage_sort[7][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 22, leakage_sort[7][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 23, leakage_sort[7][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 24, leakage_sort[6][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 25, leakage_sort[6][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 26, leakage_sort[6][i].value, NULL);
				}
			}
			else if(mode_num==3||mode_num==4)
			{
								
				showtitle_2_mode3(sheet2,dir_num);   //LP3型号表格2标题栏 
				
				for(i=1;i<=leakage[0][0].sample_num;i++)  //打印已排序leakage数据信息 
				{
					xlSheetWriteStrA(sheet2, i+1, 0, leakage_sort[0][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 1, leakage_sort[0][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 2, leakage_sort[0][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 4, leakage_sort[2][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 5, leakage_sort[2][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 6, leakage_sort[2][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 8, leakage_sort[4][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 9, leakage_sort[4][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 10, leakage_sort[4][i].value, NULL);
					xlSheetWriteStrA(sheet2, i+1, 12, leakage_sort[6][i].pin_name, NULL);
					xlSheetWriteStrA(sheet2, i+1, 13, leakage_sort[6][i].type, NULL);
					xlSheetWriteStrA(sheet2, i+1, 14, leakage_sort[6][i].value, NULL);
				}				
			}
			else
			 ;			
		}

		strcat(dirname_buf,"/Leakage_Test.xls");
		
        if(xlBookSave(book,dirname_buf)) 
			printf("\n   已创建Excel表格 %s \n",dirname_buf);
        xlBookRelease(book);
    }
	
} 

 



