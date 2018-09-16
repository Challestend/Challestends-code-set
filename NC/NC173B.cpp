#include<cstdio>
#define re register
#define maxn 1000000
#define mod 1000000007
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

int n,ans;
int a[maxn+1],f[maxn+1],g[maxn+1],h[maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    switch(n){
    case 1:
        cltstream::write(a[1]);
        break;
    case 2:
        cltstream::write(a[1]*a[2]-min(a[1],a[2]));
        break;
    default:
        f[1]=h[1]=a[1];
        g[1]=min(a[1],a[n]);
        for(re int i=2;i<n;++i){
            f[i]=1LL*(a[i]-1)*f[i-1]%mod;
            g[i]=1LL*(a[i]-1)*g[i-1]%mod;
            h[i]=(1LL*f[i-1]-h[i-1]+mod)%mod;
        }
        ans=(1LL*a[n]*f[n-1]%mod-min(f[n-1],1LL*(a[n]-1)*f[n-2]%mod)-g[n-1]+h[n-1]+mod)%mod;
        cltstream::write(ans);
    }
    for(re int i=1;i<=n;++i)
        printf("\na[%d]=%d,f[%d]=%d,g[%d]=%d,h[%d]=%d",i,a[i],i,f[i],i,g[i],i,h[i]);
    return 0;
}
