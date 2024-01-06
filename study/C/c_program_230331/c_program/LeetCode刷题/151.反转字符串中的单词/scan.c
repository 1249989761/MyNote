#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//other



//Saving


char * reverseWords(char * s){
//  char str1[]="the sky is blue";
  int len=strlen(s),i;
  char *str=(char *)malloc(10000*sizeof(char));
  int a=len-1;
  while(s[a]==' ' && a>0) a--;
  if(a<len-1) s[a+1]='\0';
  printf("len:%d,a:%d\n", len,a);
  for(i=len-a;i<len+1;){
    while(s[a]!=' ' && i<len+1 && a>-1){
       a--;
       i++;
       printf("1\n");
    }
    strcat(str,s+a+1);
    printf("str:%s,i:%d,a:%d\n", str,i,a);
    if(i<len+1) str[i-1]=' ';
    while(s[a]==' ' && i<len+1 && a>-1){
       a--;
       i++;
    }
    printf("str:%s,i:%d,a:%d\n", str,i,a);
    s[a+1]='\0';
  }
  return str;
}


int main(int argc, char *argv[]){

    char str1[10000],str2[10000];

/*    printf("请输入一个整数:\n");
    scanf("%d", &a);
    printf("你输入的整数为: %d\n", a);

    printf("请输入一个浮点数:\n");
    scanf("%f", &b);
    printf("你输入的浮点数为: %f\n", b);

    printf("请输入一个字符串:\n");
    // scanf("%s", str);
*/
    int a=2018,b=2017;
    printf("%d\n", (a/b));

    typedef union scan
    {
        int a;
        char b[4];
        /* data */
    }X;
    X test;
    test.a=0x11223344;
    printf("%d\n", test.b[1]);

    char* p="tozed";
    printf("%c %c\n", *(p+3),p[3]);
//    gets(str1);
//    printf("%s\n", strcat(str2,str1+2));
    printf("%s\n", reverseWords(str1));
//    printf("%d %d\n",strlen(str1),strlen(str2+2));
	char at[] = "HelloWorld";
	char *p1 = at;
	int *p2= (int *)at;
	printf("%c, %c", *(++p1), *(++p2));
   

    exit(0);
}