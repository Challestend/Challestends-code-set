#include<cstdio>
#define re register
#define maxn 18
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m,k;
int a[maxn+1],cnt[1<<maxn];
long long b[maxn+1][maxn+1],f[1<<maxn][maxn+1],ans;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        f[1<<(i-1)][i]+=a[i];
    }
    for(re int i=1;i<=k;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        b[x][y]+=z;
    }
    for(re int i=1;i<(1<<n);++i){
        cnt[i]=cnt[i>>1]+(i&1);
        for(re int j=1;j<=n;++j)
            if((i>>(j-1))&1)
                for(re int k=1;k<=n;++k)
                    if(((i>>(k-1))&1)^1)
                        f[i|(1<<(k-1))][k]=max(f[i|(1<<(k-1))][k],f[i][j]+b[j][k]+a[k]);
        if(cnt[i]==m)
            for(re int j=1;j<=n;++j)
                if((i>>(j-1))&1)
                    ans=max(ans,f[i][j]);
    }
    cltstream::write(ans);
    return 0;
}
