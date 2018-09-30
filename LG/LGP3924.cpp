#include<cstdio>
#include<cmath>
#define re register
#define maxn 1000000
#define maxm 1000000

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

int n,m,p;
long double ans;
long double c[maxn+2];

void segment_tree(int l,int r,long double x){
    c[l]+=x;
    c[r+1]-=x;
    if(l<r){
        int mid=(l+r)>>1;
        segment_tree(l,mid,x/2);
        segment_tree(mid+1,r,x/2);
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(p);
    segment_tree(1,n,1.0);
    for(re int i=1;i<=n;++i){
        c[i]+=c[i-1];
        int x;
        cltstream::read(x);
        ans+=c[i]*x;
    }
    for(re int i=1;i<=n;++i)
        c[i]+=c[i-1];
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        ans+=(c[y]-c[x-1])*z;
        cltstream::write<long long>(ans*p);
        putchar(10);
    }
    return 0;
}
