#include<cstdio>
#define re register
#define maxn 16
#define maxsize 65535
#define abs(a)  ((a)>=0?(a):(-(a)))

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

int n,m;
int a[maxn+1];
long long f[maxsize+1][maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        f[1<<(i-1)][i]=1;
    }
    for(re int i=0;i<(1<<n);++i)
        for(re int j=1;j<=n;++j)
            if(i>>(j-1)&1)
                for(re int k=1;k<=n;++k)
                    if(!(i>>(k-1)&1)&&abs(a[j]-a[k])>m)
                        f[i|(1<<(k-1))][k]+=f[i][j];
    for(re int i=1;i<=n;++i)
        f[(1<<n)-1][0]+=f[(1<<n)-1][i];
    cltstream::write(f[(1<<n)-1][0]);
    return 0;
}
