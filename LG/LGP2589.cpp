#include<cstdio>
#define re register
#define maxn 9
#define maxsize 512
#define max(a,b) ((a)>=(b)?(a):(b))
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

int n,size;
int h[maxn+1],r1[maxn+1],r2[maxn+1];
double f[maxsize+1][maxn+1];

int main(){
    cltstream::read(n);
    size=1<<n;
    for(re int i=0;i<size;++i)
        for(re int j=0;j<=n;++j)
            f[i][j]=4e18;
    for(re int i=1;i<=n;++i){
        cltstream::read(h[i]);
        cltstream::read(r1[i]);
        cltstream::read(r2[i]);
        f[1<<(i-1)][i]=h[i];
    }
    for(re int i=1;i<size;++i)
        for(re int j=1;j<=n;++j)
            if((i>>(j-1))&1)
                for(re int k=1;k<=n;++k)
                    if(((i>>(k-1))&1)^1)
                        f[i|(1<<(k-1))][k]=min(f[i|(1<<(k-1))][k],f[i][j]+max(max(1.0*h[j]*(r1[k]-r1[j])/(r2[j]-r1[j]),1.0*h[k]*(r2[k]-r2[j])/(r2[k]-r1[k])),0));
    for(re int i=1;i<size;++i)
        for(re int j=1;j<=n;++j)
            if((i>>(j-1))&1)
                printf("f[%d][%d]=%lf\n",i,j,f[i][j]);
    for(re int i=1;i<=n;++i)
        f[size-1][0]=min(f[size-1][0],f[size-1][i]);
    printf("%0.0lf",f[size-1][0]);
    return 0;
}
