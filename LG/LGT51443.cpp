#include<cstdio>
#include<iostream>
#include<string>
#define re register

int n,cnt,ans;
std::string s;

int main(){
    scanf("%d",&n);
    std::cin>>s;
    for(re int i=1;i<=n;++i)
        if((s[i-1]^48)&&cnt){
            ans+=2;
            --cnt;
        }
        else
            cnt+=s[i-1]^49;
    printf("%d",ans);
    return 0;
}
