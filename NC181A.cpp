#include<cstdio>
#include<cstring>

char s[1000010];

int main(){
    scanf("%s",s);
    int len=strlen(s);
    if(s[len-1]%2==0)
        putchar(49);
    else
        putchar(45),putchar(49);
    return 0;
}
