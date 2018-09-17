#include<cstdio>
#include<map>
#define re register
#define maxn 100000
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

int n,m,x,p,q,ans;
std::map<int,int> P[30];

int main(){
    cltstream::read(n);
    cltstream::read(x);
    for(re int i=1;i<=n;++i){
        cltstream::read(x);
        ++x;
        for(re int j=0,k=1;k<=x;++j,k=k<<1|1){
            printf("%d->%d\n",x,x&k);
            ++P[j][x&k];
            ans=max(ans,P[j][x&k]);
        }
        if(n==1)
            p=x;
    }
    cltstream::read(m);
    cltstream::read(x);
    for(re int i=1;i<=m;++i){
        cltstream::read(x);
        ++x;
        for(re int j=0,k=1;(k<<1|1)<=(j?x+(1<<j):x);++j,k=k<<1|1){
            printf("%d->%d\n",x,(j?(x+(1<<j)):x)&k);
            ++P[j][(j?(x+(1<<j)):x)&k];
            ans=max(ans,P[j][(j?(x+(1<<j)):x)&k]);
        }
        if(m==1)
            q=x;
    }
    if(n==1&&m==1)
        putchar(50);
    else
        cltstream::write(ans);
    return 0;
}
