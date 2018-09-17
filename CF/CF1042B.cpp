#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 1000
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n;
int a[maxn+1];
std::string s;
int c[maxn+1],f[7];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        std::cin>>s;
        if(s.find('A')!=-1)
            c[i]|=1;
        if(s.find('B')!=-1)
            c[i]|=2;
        if(s.find('C')!=-1)
            c[i]|=4;
    }
    for(re int i=1;i<8;++i)
        f[i]=2e9;
    f[0]=0;
    for(re int i=1;i<=n;++i)
        for(re int j=0;j<8;++j)
            f[j|c[i]]=min(f[j|c[i]],f[j]+a[i]);
    cltstream::write(f[7]<2e9?f[7]:-1);
    return 0;
}
