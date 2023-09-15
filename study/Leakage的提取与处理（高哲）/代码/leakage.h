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
/* Abstract：实现Leakage的模式识别及数据提取以及数据排序 */ 
/*************************************************************/


#define LINE 1024  //文本一行字节数 
#define LINE_COUNT_MAX 500  //最大读取文本行数 

extern char* select_file(int num);  //选择 log文件 
extern struct Fileinfo scan_file();  //扫描文件夹目录，返回目录信息结构体 

extern void get_leakage_struct(FILE* fp,struct Leakage* leakage);  //实现Leakage模式识别，获取leakage数据信息 

extern void get_leakage_sort(struct Leakage leakage_sort[][150]);  //获取leakage_sort排序数据信息


 

#endif

 
