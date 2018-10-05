#include<cstdio>
#define re register
#define maxn 1000000
#define mod 998244353

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

int t,a,b;
int f[maxn+1],g[maxn+1],d[maxn+1]={0,1},las[maxn+1],inv[maxn+1]={0,1},ans[maxn+1];

int main(){
    for(re int i=2;i<=maxn;++i){
        if(!f[i]){
            g[++g[0]]=i;
            d[i]=las[i]=2;
        }
        for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
            f[i*g[j]]=1;
            if(i%g[j]){
                d[i*g[j]]=d[i]*d[g[j]];
                las[i*g[j]]=las[g[j]];
            }
            else{
                d[i*g[j]]=d[i]*(las[i]+1)/las[i];
                las[i*g[j]]=las[i]+1;
                break;
            }
        }
    }
    for(re int i=2;i<=maxn;++i)
        inv[i]=(-1LL*(mod/i)*inv[mod%i]%mod+mod)%mod;
    for(re int i=1;i<=maxn;++i)
        inv[i]=(inv[i]+inv[i-1])%mod;
    for(re int i=1;i<=maxn;++i)
        ans[i]=(1LL*ans[i-1]+inv[maxn]-d[i]+mod)%mod;
    for(re int i=1;i<=maxn;++i)
        ans[i]=(-1LL*i*(inv[maxn]-inv[i])%mod+ans[i]+ans[i-1]+mod)%mod;
    cltstream::read(t);
    for(re int i=1;i<=t;++i){
        cltstream::read(a);
        cltstream::read(b);
        cltstream::write((ans[b]-ans[a-1]+mod)%mod);
        putchar(10);
    }
    return 0;
}
