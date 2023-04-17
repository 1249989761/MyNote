#ifndef __EXCEL_H
#define __EXCEL_H

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
/* Abstract��Excel���ݴ�ӡ�������� */ 
/*************************************************************/

extern void showtitle_1_mode1(SheetHandle sheet,int *num);  //��ӡ ģʽ1/2 �������� 1
extern void showtitle_2_mode1(SheetHandle sheet,int *num);  //��ӡ ģʽ1/2 �������� 2
extern void showtitle_1_mode3(SheetHandle sheet,int *num);   //��ӡ ģʽ 3 �������� 1
extern void showtitle_2_mode3(SheetHandle sheet,int *num);   //��ӡ ģʽ 3 �������� 2
extern void write_to_excel(struct Leakage leakage[][150],struct Leakage leakage_sort[][150],char *dirname_buf,int *dir_num); //����Excel������� 


#endif

