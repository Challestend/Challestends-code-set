#include<cstdio>
#define re register
#define maxn 200000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))

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
long long s,ans=4e18;
int w[maxn+1],v[maxn+1],maxw=-2e9,minw=2e9,a[maxn+1][2];
int f[maxn+1];
long long g[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(s);
    for(re int i=1;i<=n;++i){
        cltstream::read(w[i]);
        maxw=max(maxw,w[i]);
        minw=min(minw,w[i]);
        cltstream::read(v[i]);
    }
    for(re int i=1;i<=m;++i){
        cltstream::read(a[i][0]);
        cltstream::read(a[i][1]);
    }
    for(re int L=minw,R=maxw;L<=R;){
        int mid=(L+R)>>1;
        for(re int i=1;i<=n;++i){
            f[i]=f[i-1]+(w[i]>=mid);
            g[i]=g[i-1]+(w[i]>=mid)*v[i];
        }
        long long res=0;
        for(re int i=1;i<=m;++i)
            res+=(g[a[i][1]]-g[a[i][0]-1])*(f[a[i][1]]-f[a[i][0]-1]);
        ans=min(ans,abs(res-s));
        if(res==s)
            break;
        if(res>s)
            L=mid+1;
        else
            R=mid-1;
    }
    cltstream::write(ans);
    return 0;
}
