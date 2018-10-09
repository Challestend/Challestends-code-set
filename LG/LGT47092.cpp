#include<cstdio>
#define re register
#define maxn 18
#define maxsize 262144
#define mod 4921057
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
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,size;
int a[maxn+1],b[maxn+1],f[maxsize+1][maxn+1];

int main(){
    cltstream::read(n);
    size=1<<n;
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        cltstream::read(b[i]);
        f[1<<(i-1)][i]=1;
    }
    for(re int i=1;i<size;++i)
        for(re int j=1;j<=n;++j)
            if((i>>(j-1))&1)
                for(re int k=max(j-b[j]-1,1);k<=min(j+b[j]+1,n);++k)
                    if((((i>>(k-1))&1)^1)&&a[j]<=a[k])
                        printf("[%d][%d]->[%d][%d]\n",i,j,i|(1<<(k-1)),k),
                        f[i|(1<<(k-1))][k]=(f[i|(1<<(k-1))][k]+f[i][j])%mod;
    // for(re int i=1;i<size;++i)
    //     for(re int j=1;j<=n;++j)
    //         if((i>>(j-1))&1)
    //             printf("%cf[%d][%d]=%d"," \n"[(1<<(j-1))==(i&(-i))?1:0],i,j,f[i][j]);
    // putchar(10);
    for(re int i=1;i<=n;++i)
        f[size-1][0]=(f[size-1][0]+f[size-1][i])%mod;
    cltstream::write(f[size-1][0],'\n');
    return 0;
}
