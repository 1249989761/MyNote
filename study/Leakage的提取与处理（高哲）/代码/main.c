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
/* Abstract��Leakage����ȡ�ʹ�����������ʵ�ָ�ģ��ӿڵ��� */ 
/*************************************************************/


int mode_num=0; //оƬģʽ��ʶ��    LPDDR4 1CS(1)  LPDDR4 2CS(2)  LPDDR3 1CS(3)  LPDDR3 2CS(4)
int pin_num=66; //��ʼ��Ĭ�� 66 pins  


int main()
{
	int i;
	int j;
	int k;
	
	char *filename_buf;
	char dirname_buf[50]={0};
	struct Fileinfo dirinfo; 
	
	FILE *fp_log=NULL;
	
	dirinfo=scan_file();  //ɨ���ļ���Ŀ¼����¼�ļ���Ŀ¼��Ϣ
	for(i=0;i<dirinfo.dir_sum;i++)
	{
		printf("\n   ��ʶ���ļ��� %s �� \n",dirinfo.dir_name[i]);
	}

	for(i=0;i<dirinfo.dir_sum;i++) 
	{ 	
		for(j=1;j<=8;j++)  //�ɼ�8������log�ļ� ,����leakage��ά�ṹ������ 
		{
			strcpy(dirname_buf,dirinfo.dir_name[i]);
			filename_buf=select_file(j);  //ѡ��log�ı�1~8
			
			strcat(dirname_buf,"/");
			strcat(dirname_buf,filename_buf);
			
			fp_log=fopen(dirname_buf,"r");  //��log�ı�
			if(fp_log==NULL)
			{
				continue;
			}
	
			get_leakage_struct(fp_log,leakage[j-1]); //��ȡleakage������Ϣ
			
			fclose(fp_log);

			memset(dirname_buf,0,50);
		
		}
			
		for(j=0;j<8;j++)  //��ȡ����ṹ���ά����
		{
			for(k=0;k<=leakage[0][0].sample_num;k++)
			{
				leakage_sort[j][k]=leakage[j][k];
			}
		}		
		
		get_leakage_sort(leakage_sort); //��leakage_sort�ṹ�������������  
		
		write_to_excel(leakage,leakage_sort,dirinfo.dir_name[i],dirinfo.dir_num[i]); 	 //���ɼ�leakage���� �� �����leakage����д��excel��� 

		for(j=0;j<8;j++)  //�������ṹ���ά����
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




