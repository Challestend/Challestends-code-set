#include<cstdio>
#define re register
#define maxn 23333
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

int n;
int a[maxn+1],f[maxn+1],g[maxn+1];

int main(){
    cltstream::read(n);
    a[0]=-2e9;
    for(int i=1;i<=n;++i)
        cltstream::read(a[i]);
    f[1]=g[0]=g[1]=1;
    for(int i=2;i<=n;++i)
        if(a[i]>=a[g[g[0]]])
            g[f[i]=++g[0]]=i;
        else{
            int l=0,r=g[0]-1;
            for(;l<r;){
                int mid=(l+r+1)>>1;
                if(a[i]>=a[g[mid]])
                    l=mid;
                else
                    r=mid-1;
            }
            g[f[i]=l+1]=i;
        }
    for(int i=1;i<=n;++i)
        f[0]=max(f[0],f[i]);
    cltstream::write(f[0]);
    return 0;
}
