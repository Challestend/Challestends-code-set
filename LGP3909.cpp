#include<cstdio>
#define re register
#define mod 1000000007

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

int n,x,a,b,ans;

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        cltstream::read(x),a=(1LL*a+1LL*x)%mod,b=(1LL*b+1LL*x*x%mod)%mod;
    printf("%d %d\n",a,b);
    ans=1LL*a*a%mod;
    printf("%d\n",ans);
    ans=1LL*ans*a%mod;
    printf("%d\n",ans);
    ans=1LL*ans-3LL*a*b%mod;
    printf("%d\n",ans);
    cltstream::write((1LL*ans+1LL*mod)%mod);
    return 0;
}
