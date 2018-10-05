#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define min(a,b) ((a)<=(b)?(a):(b))

int n,cnt;
std::string s;

int main(){
    scanf("%d",&n);
    std::cin>>s;
    for(re int i=1;i<=n;++i)
        cnt+=(s[i-1]=='8');
    printf("%d",min(n/11,cnt));
    return 0;
}
