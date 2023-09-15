#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
//other
char vowel[] = "aeiouAEIOU";

bool isVowel(char ch) {
    for (int i = 0; vowel[i]; i++) {
        if (vowel[i] == ch) {
            return true;
        }
    }
    return false;
};

char* reverseVowels(char* s) {
    int n = strlen(s);
    int i = 0, j = n - 1;
    while (i < j) {
        while (i < n && !isVowel(s[i])) {
            ++i;
        }
        while (j > 0 && !isVowel(s[j])) {
            --j;
        }
        if (i < j) {
            char* tmp = s[i];
            s[i] = s[j], s[j] = tmp;
            ++i;
            --j;
        }
    }
    return s;
}*/
/*
作者：力扣官方题解
链接：https://leetcode.cn/problems/reverse-vowels-of-a-string/solutions/944385/fan-zhuan-zi-fu-chuan-zhong-de-yuan-yin-2bmos/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/


//Saving
char * reverseVowels(char * s){
    int slen=strlen(s),i,j,k=0;
    int add[300000];
    char a;
    for(i=0;i<slen;i++){
        switch(s[i]){
            case 'a':
                add[k]=i;
                k++;
                break;
            case 'e':
                add[k]=i;
                k++;
                break;
            case 'i':
                add[k]=i;
                k++;
                break;
            case 'o':
                add[k]=i;
                k++;
                break;
            case 'u':
                add[k]=i;
                k++;
                break;
            case 'A':
                add[k]=i;
                k++;
                break;
            case 'E':
                add[k]=i;
                k++;
                break;
            case 'I':
                add[k]=i;
                k++;
                break;
            case 'O':
                add[k]=i;
                k++;
                break;
            case 'U':
                add[k]=i;
                k++;
                break;
            default:
                break;
        }
    }
    for(j=0;j<k/2;j++){
        a=s[add[j]];
        s[add[j]]=s[add[k-j-1]];
        s[add[k-j-1]]=a;
    }
    return s;
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
    scanf("%s", str1);
    printf("%s\n", reverseVowels(str1));
//    printf("%d %d\n",strlen(str1),strlen(str2+2));

    exit(0);
}