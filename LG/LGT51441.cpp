#include<cstdio>
#include<iostream>
#include<string>
#define re register

int n,m,ans;
std::string s;

int main(){
    scanf("%d%d",&n,&m);
    std::cin>>s;
    s=s+s+s;
    for(re int i=n+1;i<=(n<<1);++i){
        int palin=1;
        for(re int j=1;j<=(m>>1)&&palin;++j)
            if(s[i+j-1]!=s[i-j-1])
                palin=0;
        ans+=palin;
    }
    printf("%d",ans);
    return 0;
}
