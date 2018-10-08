#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#define re register
#define maxn 10000

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
    }
}

int n,m,ans;
std::string name[maxn+1]={"I became a brony's waifu!"};
int x[maxn+1],y[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        std::getline(std::cin,name[i]);
        cltstream::read(x[i]);
        cltstream::read(y[i]);
        ans=x[i]*y[i]<=m&&x[i]>x[ans]?i:ans;
    }
    std::cout<<name[ans];
    return 0;
}
