#include<cstdio>
#include<cmath>
#define re register
#define maxp 10000
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

long long n,ans=1e18;
int p;
int f[maxp+1],g[maxp+1];

int main(){
    cltstream::read(n);
    cltstream::read(p);
    for(re int i=2;i<=p;++i){
        if(!f[i])
            g[++g[0]]=i;
        for(re int j=1;j<=g[0]&&i*g[j]<=p;++j){
            f[i*g[j]]=1;
            if(i%g[j]==0)
                break;
        }
    }
    for(re int i=1;i<=g[0];++i)
        if(p%g[i]==0){
            int cnt=0;
            for(;p%g[i]==0;p/=g[i],++cnt);
            long long lg=floor(log(n)/log(g[i])),res=0;
            for(re long long j=1,k=g[i];j<=lg;++j,k*=g[i])
                res+=n/k;
            ans=min(ans,res/cnt);
        }
    cltstream::write(ans);
    return 0;
}
