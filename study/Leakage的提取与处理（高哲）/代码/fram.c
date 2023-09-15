#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "leakage.h"
#include "fram.h"

/**************************************************************/ 
/* Copyright (c) 2020, longsys */ 
/* All rights reserved. */ 
/* Project Name: Leakage_Test*/ 
/* Author: gaozhe*/ 
/* Date: 2020.03.26*/ 
/* Version:v1.0 */ 
/* Abstract：定义Leakage数据类型结构体和结构体赋值函数 */ 
/*************************************************************/

struct Leakage leakage[8][150]; //定义Leakage结构体二维数组 
struct Leakage leakage_sort[8][150]; //定义Leakage排序结构体二维数组  

struct Leakage someprocess_1(char *buf,char *pin_name_buf,char *channel_name_buf)   //LPDDR4 1/2 CS 结构体赋值 
{
    struct Leakage info;
    memset(&info,0,sizeof(info));
    memcpy(&info.pin_name,pin_name_buf,8);
    memcpy(&info.channel,channel_name_buf,2);
    memcpy(&info.type,buf+35,3);
    memcpy(&info.value,buf+55,7);
    
    return info;
}


struct Leakage someprocess_2(char *buf,char *pin_name_buf)  //LPDDR3 1/2 CS 结构体赋值 
{
    struct Leakage info;
    memset(&info,0,sizeof(info));
    memcpy(&info.pin_name,pin_name_buf,8);
    memcpy(&info.type,buf+35,3);
    memcpy(&info.value,buf+55,7);
    
    return info;
}
