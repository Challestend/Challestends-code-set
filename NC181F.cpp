#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000
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

int t,n,m;
int C[maxn+1][maxn+1],a[maxn+1];

inline int pm(int x,int y){
    if(y==0)
        return 1;
    if(y==1)
        return x;
    int res=pm(x,y>>1);
    res=1LL*res*res%mod;
    return (y&1)?1LL*res*x%mod:res;
}

int main(){
    for(re int i=0;i<=maxn;++i)
        C[i][0]=C[i][i]=1;
    for(re int i=2;i<=maxn;++i)
        for(re int j=1;j<i;++j)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%(mod-1);
    cltstream::read(t);
    for(;t;--t){
        cltstream::read(n),cltstream::read(m);
        for(int i=1;i<=n;++i)
            cltstream::read(a[i]);
        std::sort(a+1,a+n+1);
        int ans=1,x;
        for(int i=2;i<n;++i){
            x=(C[n-1][m-1]-C[i-1][m-1]-C[n-i][m-1])%(mod-1);
            ans=1LL*ans*pm(a[i],x+mod-1)%mod;
        }
        cltstream::write(ans);
        putchar(10);
    }
    return 0;
}
