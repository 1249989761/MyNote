#ifndef __FRAM_H
#define __FRAM_H

/**************************************************************/ 
/* Copyright (c) 2020, longsys */ 
/* All rights reserved. */ 
/* Project Name: Leakage_Test*/ 
/* Author: gaozhe*/ 
/* Date: 2020.03.26*/ 
/* Version:v1.0 */ 
/* Abstract：声明Leakage数据类型结构体和结构体赋值函数 */ 
/*************************************************************/


struct Leakage //声明Leakage引脚信息结构体 
{
	int sample_num;
	char pin_name[10];
	char channel[10];
	char type[10];
	char value[10];
};

struct Fileinfo //声明文件目录信息结构体 
{
	char dir_name[50][50];  //存储目录信息 
	int dir_num[50][4];  //存储样品标号信息 
	int dir_sum;  //计算目录数 
};


extern struct Leakage leakage[8][150];  //定义leakage数据采集二维结构体数组 
extern struct Leakage leakage_sort[8][150]; //定义leakage数据排序二维结构体数组 


extern struct Leakage someprocess_1(char *buf,char *pin_name_buf,char *channel_name_buf);
extern struct Leakage someprocess_2(char *buf,char *pin_name_buf);



#endif
 
