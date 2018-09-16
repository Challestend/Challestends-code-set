#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 100

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=10*x+(c^48),c=getchar());
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

int n,l,m;
std::string s[maxn+1];
int a[8]={0,7,13,18,22,25,27,28},f[maxn+1][maxn+1];

inline void binprint(int x,int y){
    long long z=f[x][y];
    int digit[30],cnt=0;
    for(re int i=0;i<30;++i)
        digit[i]=0;
    for(;z;digit[++digit[0]]=z&1,z>>=1)
        if(z&1)
            ++cnt;{
        cltstream::write(x);
        putchar(32);
        cltstream::write(y);
        putchar(32);
        for(re int i=1;i<=28;++i)
            putchar(digit[i]^48);
        putchar(10);
    }
}

int main(){
    cltstream::read(n),cltstream::read(l),cltstream::read(m);
    for(re int i=1;i<=n;++i){
        std::cin>>s[i];
        for(re int j=0;j<l;++j)
            s[i][j]-='a';
    }
    for(re int i=1;i<=n;++i)
        for(re int j=i+1;j<=n;++j)
            for(re int k=0;k<l;++k)
                if(s[i][k]<s[j][k])
                    f[i][j]|=1LL<<(a[s[i][k]]+s[j][k]-s[i][k]-1);
                else
                    if(s[i][k]>s[j][k])
                        f[i][j]|=1LL<<(a[s[j][k]]+s[i][k]-s[j][k]-1);
    for(re int i=1;i<=n;++i)
        for(re int j=i+1;j<=n;++j)
            binprint(i,j);
    return 0;
}
