#ifndef __FRAM_H
#define __FRAM_H

/**************************************************************/ 
/* Copyright (c) 2020, longsys */ 
/* All rights reserved. */ 
/* Project Name: Leakage_Test*/ 
/* Author: gaozhe*/ 
/* Date: 2020.03.26*/ 
/* Version:v1.0 */ 
/* Abstract������Leakage�������ͽṹ��ͽṹ�帳ֵ���� */ 
/*************************************************************/


struct Leakage //����Leakage������Ϣ�ṹ�� 
{
	int sample_num;
	char pin_name[10];
	char channel[10];
	char type[10];
	char value[10];
};

struct Fileinfo //�����ļ�Ŀ¼��Ϣ�ṹ�� 
{
	char dir_name[50][50];  //�洢Ŀ¼��Ϣ 
	int dir_num[50][4];  //�洢��Ʒ�����Ϣ 
	int dir_sum;  //����Ŀ¼�� 
};


extern struct Leakage leakage[8][150];  //����leakage���ݲɼ���ά�ṹ������ 
extern struct Leakage leakage_sort[8][150]; //����leakage���������ά�ṹ������ 


extern struct Leakage someprocess_1(char *buf,char *pin_name_buf,char *channel_name_buf);
extern struct Leakage someprocess_2(char *buf,char *pin_name_buf);



#endif
 
