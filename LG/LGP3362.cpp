#include<cstdio>
#define re register
#define maxn 10000000
#define maxg 664579
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

int n,m;
long long d;
int f[maxn+1],g[maxg+1],las[maxn+1]={0,1},sigma[maxn+1]={0,1};

int cltpow(int x,long long y){
    if(y==0)
        return 1;
    if(y==1)
        return x;
    int res=cltpow(x,y>>1);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(d);
    cltstream::read(m);
    for(re int i=2;i<=n;++i){
        if(!f[i]){
            g[++g[0]]=i;
            las[i]=(cltpow(i,d)+1)%mod;
            sigma[i]=1;
        }
        for(re int j=1;j<=g[0]&&i*g[j]<=n;++j){
            f[i*g[j]]=1;
            if(i%g[j]){
                sigma[i*g[j]]=1LL*sigma[i]*las[i]%mod;
                las[i*g[j]]=las[g[j]];
            }
            else{
                sigma[i*g[j]]=sigma[i];
                las[i*g[j]]=(1LL*las[i]*(las[g[j]]-1+mod)%mod+1)%mod;
                break;
            }
        }
    }
    for(re int i=1;i<=n;++i)
        sigma[i]=(1LL*sigma[i]*las[i]%mod+sigma[i-1])%mod;
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::write((1LL*sigma[y]-sigma[x-1]+mod)%mod);
        putchar(10);
    }
    return 0;
}
