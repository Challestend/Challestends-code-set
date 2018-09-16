#include<cstdio>
#define re register
#define maxn 1000000
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

int n,ans;
int a[maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        a[0]=(1LL*a[0]+1LL*a[i])%mod;
    }
    ans=1LL*a[0]*a[0]%mod;
    ans=1LL*ans*a[0]%mod;
    for(re int i=1;i<=n;++i){
        int x=1LL*a[i]*a[i]%mod;
        ans=(1LL*ans-3LL*x*a[0]+2LL*x*a[i])%mod;
    }
    cltstream::write((1LL*ans+1LL*mod)%mod);
    return 0;
}
