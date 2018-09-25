#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 50
#define maxm 50
#define mod 2008

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

int n,m,ans=1;
std::string s;
long long base[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        std::cin>>s;
        long long x=0;
        for(re int j=0;j<n;++j)
            if(s[j]=='O')
                x|=1LL<<j;
        for(re int j=n-1;j>=0;--j)
            if(!base[j]){
                base[j]=x;
                ans=1*ans%mod;
                break;
            }
            else
                x^=base[j];
    }
    cltstream::write(ans);
    return 0;
}
