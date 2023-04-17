#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include "fram.h"
#include "excel.h"
#include "leakage.h"

/**************************************************************/ 
/* Copyright (c) 2020, longsys */ 
/* All rights reserved. */ 
/* Project Name: Leakage_Test*/ 
/* Author: gaozhe*/ 
/* Date: 2020.03.26*/ 
/* Version:v1.0 */ 
/* Abstract：Leakage的提取和处理主函数，实现各模块接口调用 */ 
/*************************************************************/


int mode_num=0; //芯片模式标识符    LPDDR4 1CS(1)  LPDDR4 2CS(2)  LPDDR3 1CS(3)  LPDDR3 2CS(4)
int pin_num=66; //初始化默认 66 pins  


int main()
{
	int i;
	int j;
	int k;
	
	char *filename_buf;
	char dirname_buf[50]={0};
	struct Fileinfo dirinfo; 
	
	FILE *fp_log=NULL;
	
	dirinfo=scan_file();  //扫描文件夹目录，记录文件夹目录信息
	for(i=0;i<dirinfo.dir_sum;i++)
	{
		printf("\n   已识别文件夹 %s ！ \n",dirinfo.dir_name[i]);
	}

	for(i=0;i<dirinfo.dir_sum;i++) 
	{ 	
		for(j=1;j<=8;j++)  //采集8个测试log文件 ,生成leakage二维结构体数组 
		{
			strcpy(dirname_buf,dirinfo.dir_name[i]);
			filename_buf=select_file(j);  //选择log文本1~8
			
			strcat(dirname_buf,"/");
			strcat(dirname_buf,filename_buf);
			
			fp_log=fopen(dirname_buf,"r");  //打开log文本
			if(fp_log==NULL)
			{
				continue;
			}
	
			get_leakage_struct(fp_log,leakage[j-1]); //获取leakage数据信息
			
			fclose(fp_log);

			memset(dirname_buf,0,50);
		
		}
			
		for(j=0;j<8;j++)  //获取排序结构体二维数组
		{
			for(k=0;k<=leakage[0][0].sample_num;k++)
			{
				leakage_sort[j][k]=leakage[j][k];
			}
		}		
		
		get_leakage_sort(leakage_sort); //将leakage_sort结构体数组进行排序  
		
		write_to_excel(leakage,leakage_sort,dirinfo.dir_name[i],dirinfo.dir_num[i]); 	 //将采集leakage数据 和 排序后leakage数据写到excel表格 

		for(j=0;j<8;j++)  //清空排序结构体二维数组
		{
			for(k=0;k<=leakage[0][0].sample_num;k++)
			{
				memset(&leakage_sort[j][k],0,sizeof(leakage_sort));
			}
		} 
		
	} 
	
	
	system("pause"); 
	
	return 0;
}




