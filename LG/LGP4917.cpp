#include<cstdio>
#define re register
#define maxn 1000000
#define mod 19260817

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

int t,n;
int f[maxn+1],g[maxn+1],phi[maxn+1]={-1,1},fac[maxn+1]={1,1},inv[maxn+1]={1,1};

int cltpow(int x,int y){
    if(y==1)
        return x;
    int res=cltpow(x,y>>1);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

int main(){
    for(re int i=2;i<=maxn;++i){
        fac[i]=1LL*fac[i-1]*i%mod;
        inv[i]=(-1LL*mod/i*inv[mod%i]%mod+mod)%mod;
        if(!f[i]){
            g[++g[0]]=i;
            phi[i]=i-1;
        }
        for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                phi[i*g[j]]=phi[i]*phi[g[j]];
            else{
                phi[i*g[j]]=phi[i]*g[j];
                break;
            }
        }
    }
    for(re int i=1;i<=maxn;++i){
        phi[i]=(1LL*phi[i-1]+2LL*phi[i])%(mod-1);
        inv[i]=1LL*inv[i-1]*inv[i]%mod;
    }
    cltstream::read(t);
    for(re int i=1;i<=t;++i){
        cltstream::read(n);
        int ans=1;
        for(re int l=1,r;l<=n;l=r+1){
            r=n/(n/l);
            ans=1LL*ans*cltpow(1LL*fac[r]*inv[l-1]%mod,phi[n/l]+mod-1)%mod;
        }
        cltstream::write(1LL*cltpow(fac[n],n<<1)*cltpow(ans,(mod<<1)-4)%mod);
        putchar(10);
    }
    return 0;
}
