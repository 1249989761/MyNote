#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <dirent.h>
#include <io.h>
#include <sys/types.h>
#include<stdbool.h>

#include "leakage.h"
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

extern int mode_num;
extern int pin_num;

/*ѡ��log�ļ�*/
char* select_file(int filename_num)
{
	char filename_num_buf[8];
	static char filename_buf[30]={0};
	
	sprintf(filename_num_buf,"%d",filename_num); //�ļ�����ʶ��
	strcpy(filename_buf,"TRLogDetailed_MST1_DUT0");
	strcat(filename_buf,filename_num_buf);
	strcat(filename_buf,".txt"); 
	
	return filename_buf;
}


/*ɨ���ļ���Ŀ¼*/
struct Fileinfo scan_file()
{
	int i=0;
	int j=0;
	int count=0;
	int flag=0;
	
    char path[100] = "./*";  
	char *p; 
	
	struct Fileinfo info;
    struct _finddata_t fa;  //�ļ�Ŀ¼��Ϣ�ṹ�� 

    long handle;
    
    handle=_findfirst(path,&fa);
    
    do
    {
        if(fa.attrib == _A_ARCH||_A_HIDDEN||_A_RDONLY||_A_SUBDIR||_A_SYSTEM)
        {
        	for(count=0;count<strlen(fa.name);count++)
        	{
        		if(fa.name[count]=='-')
        		{
        			flag++;
				}
        		
        		if(flag==3)
        		{
        			strcpy(info.dir_name[i],fa.name);
        			
        			p=strtok(fa.name,"-");  //��Ʒ��Ÿ�ֵ 
        			info.dir_num[i][0]=atoi(p); 
        			
        			for(j=1;j<4;j++)
        			{
        				p=strtok(NULL,"-"); 
        				info.dir_num[i][j]=atoi(p);  
					}	
					
        			i++;
					break;	
				}	
			}
        	flag=0;
		}
    }while(_findnext(handle,&fa) == 0); //�ɹ��ҵ�ʱ����0 
    
    info.dir_sum=i;  //������Ч�ļ������� 

    _findclose(handle);

    return info;
    
}




/*��ȡleakage�ṹ����Ϣ*/
void get_leakage_struct(FILE* fp,struct Leakage* leakage)
{
	int i=0;
	int j=0;
	int m=0;
	int count=0;
	int pin_count=0;
	int line_count=0;
	
	char buf[1024];  //��ȡÿһ��
	char pin_name_buf[8]={0};
	char channel_name_buf[2]; 
	char temp_buf[1];
	
	char *lp4=NULL;
	char *lp3=NULL;
	char *cs2=NULL;
	char *cs1=NULL;
	
	bool flag_mode=false; //ģʽʶ���־λ 
	bool lp4_mode=false;
	bool lp3_mode=false;
	bool cs2_mode=false;
	bool cs1_mode=false;
	
	bool flag_pin=false;  //ȫ��������Ϣ�ɼ���ɱ�־λ 
	
	while(flag_pin==false&&!feof(fp)) //���ɨ�������ı������ᳬ���ı����� 
    {
        fgets(buf,LINE,fp); //��ȡÿһ������ 

        line_count++;  //��¼�Ѷ�ȡ�ı�����      
        
        if(mode_num==0)
        {        	
        	if(flag_mode==false)
	        {	        	
	        	lp4=strstr(buf,"LPDDR4");
	        	lp3=strstr(buf,"LPDDR3");
		        cs2=strstr(buf,"2 CS");
		        cs1=strstr(buf,"1 CS");
		                
		        if(lp4!=NULL)
		        {
		        	lp4_mode=true;
		        	lp4=NULL;	
				}
				if(lp3!=NULL)
				{
					lp3_mode=true;
					lp3=NULL;
				}
				if(cs2!=NULL)
				{
					cs2_mode=true;
					cs2=NULL;
				}
				if(cs1!=NULL)
				{
					cs1_mode=true;
					cs1=NULL;
				}

					
				if(lp4_mode&&cs1_mode)
				{
					flag_mode=true;                //LPDDR4  1 CS   ģʽ 1   66pins
					mode_num=1;
					pin_num=66; 
					printf("\n   ��ʶ��  LPDDR4 1 CS Mode  �� \n");
				}
				else if(lp4_mode&&cs2_mode)
				{
					flag_mode=true;                //LPDDR4  2 CS   ģʽ 2   68pins
					mode_num=2;
					pin_num=68;
					printf("\n   ��ʶ��  LPDDR4 2 CS Mode  �� \n");
				}
				else if(lp3_mode&&cs1_mode)
				{
					flag_mode=true;                //LPDDR3  1 CS   ģʽ 3   118pins
					mode_num=3;
					pin_num=118;
					printf("\n   ��ʶ��  LPDDR3 1 CS Mode  �� \n");
				}
				else if(lp3_mode&&cs2_mode)
				{
					flag_mode=true;                //LPDDR3  2 CS   ģʽ 4   122pins
					mode_num=4;
					pin_num=122;
					printf("\n   ��ʶ��  LPDDR3 2 CS Mode  �� \n");
				}
				else               				   //�Ƿ���Ʒ����   ģʽ 0 
				{
					flag_mode=false;
					mode_num=0;
				}
			}
		}
		
		 
        
		if(mode_num==1||mode_num==2)  //LPDDR4 1/2 CSģʽ����ʶ������ȡ
		{	
		
			for(i=0;i<100;i++)
			{
				if(buf[i]=='_'&&buf[i+2]==' '&&buf[30]=='L') //��Ч��Ϣ�ж����� 
		    	{
		    			
					pin_count++;
					if(pin_count==pin_num)
						flag_pin=true;
					 
		    		for(j=0;j<i;j++)
		    		{
		    			memset(temp_buf,0,1); 
		    			sprintf(temp_buf,"%c",buf[j]); //������������ 
		    			strcat(pin_name_buf,temp_buf);
		    			memset(temp_buf,0,1); 
					}	
									
					sprintf(channel_name_buf,"%c",buf[i+1]);  //����ͨ���� 
					
					struct Leakage temp_leakage = someprocess_1(buf,pin_name_buf,channel_name_buf);  
		        	memcpy(&leakage[++count],&temp_leakage,sizeof(leakage[++count]));  //Leakage�ṹ�帳ֵ    /////////////////////////������   
		        	
		        	
		        	
		
		        	if(atof(leakage[1].value)<=0.20)  //�ж��Ƿ���Ч���ݣ���Ч����սṹ�岢�˳�ѭ�� 
		        	{
		        		memset(&leakage[1].pin_name,0,10);
		        		memset(&leakage[1].channel,0,10);
		        		memset(&leakage[1].type,0,10);
		        		memset(&leakage[1].value,0,10);  
		        		goto Label1;
					}
		        	
					leakage[0].sample_num=count; //����ṹ������
		
					memset(pin_name_buf,0,10);
					memset(channel_name_buf,0,2); 

				}
			}
			
			memset(buf,0,1024);
		
		}
		else if(mode_num==3||mode_num==4)   //LPDDR3 1 CSģʽ����ʶ������ȡ 
		{		
			for(i=0;i<100;i++)
			{
				if(buf[i]!=' '&&buf[i+1]==' '&&buf[i+2]==' '&&buf[30]=='L') //��Ч��Ϣ�ж�����  
		    	{
					pin_count++;
					
					if(pin_count==pin_num)
						flag_pin=true;	
						
		    		for(j=0;j<=i;j++)
		    		{
		    			memset(temp_buf,0,1); 
		    			sprintf(temp_buf,"%c",buf[j]); //������������ 
		    			strcat(pin_name_buf,temp_buf);
		    			memset(temp_buf,0,1); 
					}
					
					struct Leakage temp_leakage = someprocess_2(buf,pin_name_buf);                
		        	memcpy(&leakage[++count],&temp_leakage,sizeof(leakage[++count]));  //Leakage�ṹ�帳ֵ  
		        	
		
		        	if(atof(leakage[1].value)<=0.20)  //�ж��Ƿ���Ч���ݣ���Ч����սṹ�岢�˳�ѭ�� 
		        	{
		        		memset(&leakage[1].pin_name,0,10);
		        		memset(&leakage[1].type,0,10);
		        		memset(&leakage[1].value,0,10);  
		        		goto Label1;
					}
		        	
					leakage[0].sample_num=count; //����ṹ������
					
					memset(pin_name_buf,0,10);
					memset(channel_name_buf,0,2);
				}
			}
			
			memset(buf,0,1024);
		}
		else
		{
			;
		}
			
    }
Label1:  //ʶ��Ϊ��Ч���ݣ�ֱ����ת�˳��ı���Ϣ�ɼ� 
	;
}



/*���������¶�ά�ṹ������*/
void get_leakage_sort(struct Leakage leakage_sort[][150])
{
	int count;
	int leakage_num;
	int i;
	int j;
	
	
	float k;
	float m;
	struct Leakage temp_leakage;
	
	leakage_num=leakage_sort[0][0].sample_num;
	

	for(count=0;count<8;count++)
	{
		for(i=1;i<leakage_num+1;i++)  //ð������  
		{
			for(j=1;j<leakage_num-i+1;j++) 
			{
				k=atof(leakage_sort[count][j].value);
				m=atof(leakage_sort[count][j+1].value);
				if(k<m)
				{ 
					temp_leakage=leakage_sort[count][j];
					leakage_sort[count][j]=leakage_sort[count][j+1];
					leakage_sort[count][j+1]=temp_leakage;
	
				}
			}
		}
	}
	
} 



