#ifndef __LEAKAGE_H
#define __LEAKAGE_H

#include "fram.h"

/**************************************************************/ 
/* Copyright (c) 2020, longsys */ 
/* All rights reserved. */ 
/* Project Name: Leakage_Test*/ 
/* Author: gaozhe*/ 
/* Date: 2020.03.26*/ 
/* Version:v1.0 */ 
/* Abstract��ʵ��Leakage��ģʽʶ��������ȡ�Լ��������� */ 
/*************************************************************/


#define LINE 1024  //�ı�һ���ֽ��� 
#define LINE_COUNT_MAX 500  //����ȡ�ı����� 

extern char* select_file(int num);  //ѡ�� log�ļ� 
extern struct Fileinfo scan_file();  //ɨ���ļ���Ŀ¼������Ŀ¼��Ϣ�ṹ�� 

extern void get_leakage_struct(FILE* fp,struct Leakage* leakage);  //ʵ��Leakageģʽʶ�𣬻�ȡleakage������Ϣ 

extern void get_leakage_sort(struct Leakage leakage_sort[][150]);  //��ȡleakage_sort����������Ϣ


 

#endif

 
