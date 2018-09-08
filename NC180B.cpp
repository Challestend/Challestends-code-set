#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100

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

int n,m;
double a[maxn+1],f[maxn+1][maxm+1];

int main(){
    cltstream::read(n),cltstream::read(m);
    for(re int i=1;i<=n;++i)
        scanf("%lf",&a[i]),a[0]+=a[i];
    printf("%0.4lf\n",a[0]);
    f[0][0]=1;
    for(re int i=1;i<=n;++i){
        f[i][0]=(1-a[i])*f[i-1][0];
        for(re int j=1;j<i&&j<=m;++j)
            f[i][j]=a[i]*f[i-1][j-1]+(1-a[i])*f[i-1][j];
        f[i][i]=a[i]*f[i-1][i-1];
    }
    printf("%0.4lf",f[n][m]);
    return 0;
}
