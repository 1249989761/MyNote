#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//other
char * gcdOfStrings1(char * str1, char * str2){
    int len1=strlen(str1);
    int len2=strlen(str2);
    int len=len2;
    //第一遍匹配，验证是否属于循环相等
    for(int i=0;i<len1;i++)
    {
        if(str1[i]!=str2[i%len2]) return "";
    }
    //如果长度不能整除，只有循环串如ABAB才有可能有子串能整除。先找出子串长度
    if(len1%len2!=0)
    {
        while(len1%len!=0 || len2%len!=0) len--;
    }
    //再次验证以避免非循环子串
    for(int i=0;i<len1;i++)
    {
        if(str1[i]!=str2[i%len]) return "";
    }
    str2[len]='\0';
    return str2;
}
/*
作者：tUW5Nnaqqw
链接：https://leetcode.cn/problems/greatest-common-divisor-of-strings/solutions/2368692/xun-huan-pi-pei-yan-zheng-chun-c-su-du-0-iqe3/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/


//Saving
char * gcdOfStrings(char * str1, char * str2){
    int strlen1=strlen(str1),strlen2=strlen(str2),i,j,k,flag=0;
    if(strlen1>strlen2){
        k=strlen1/2;
    }
    else{
        if(strlen1==strlen2){
           if(!strcmp(str1,str2)) return str1; 
        }
        k=strlen2/2;
        flag=1;
    }
    char *str=(char *)malloc((k+1)*sizeof(char));
    if(flag==0){
        char *str3=(char *)malloc((strlen1+1)*sizeof(char));
        for(i=k;i>0;i--){
            str3[0]='\0';
            //str4[0]='\0';
            for(j=i-1;j>-1;j--) str[j]=str1[j];
            str[i]='\0';
            while(strlen(str3)!=strlen(str1) && strlen(str3)<strlen(str1)) strcat(str3,str);
            if(strcmp(str1,str3)) continue;
            else{
                str3[0]='\0';
                while(strlen(str3)!=strlen(str2) && strlen(str3)<strlen(str2)) strcat(str3,str);
                if(strcmp(str2,str3)) continue;
                else return str;
            }
        }
        str[0]='\0';
        return str;
    }
    else{
        char *str4=(char *)malloc((strlen2+1)*sizeof(char));
        for(i=k;i>0;i--){
            //str3[0]='\0';
            str4[0]='\0';
            for(j=i-1;j>-1;j--) str[j]=str2[j];
            
            str[i]='\0';
            while(strlen(str4)!=strlen(str1) && strlen(str4)<strlen(str1)) strcat(str4,str);
            if(strcmp(str1,str4)) continue;
            else{
                str4[0]='\0';
                while(strlen(str4)!=strlen(str2) && strlen(str4)<strlen(str2)) strcat(str4,str);
                if(strcmp(str2,str4)) continue;
                else return str;
            }
        }
        str[0]='\0';
        return str;
    }
}
int main(int argc, char *argv[]){

    char str1[1000],str2[1000];

/*    printf("请输入一个整数:\n");
    scanf("%d", &a);
    printf("你输入的整数为: %d\n", a);

    printf("请输入一个浮点数:\n");
    scanf("%f", &b);
    printf("你输入的浮点数为: %f\n", b);

    printf("请输入一个字符串:\n");
    // scanf("%s", str);
*/
    scanf("%s %s", str1,str2);
    printf("%s\n", gcdOfStrings(str1,str2));
    printf("%d %d\n",strlen(str1),strlen(str2+2));

    exit(0);
}