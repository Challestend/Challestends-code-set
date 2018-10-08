#include<cstdio>
#define re register
#define maxn 80000

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

int n,m,mod,min,max,fin;
int a[maxn+1],sum[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(mod);
    cltstream::read(min);
    cltstream::read(max);
    for(re int i=1;i<=m;++i){
        char opt=getchar();
        for(;opt!='A'&&opt!='Q';opt=getchar());
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        if(opt=='A'){
            cltstream::read(z);
            a[x]=(1LL*a[x]+z)%mod;
            a[y+1]=(1LL*a[y+1]-z)%mod;
        }
        else{
            int cnt=0;
            for(re int j=1,k=0;j<=n;++j){
                k=(1LL*k+a[j])%mod;
                cnt+=(j>=x&&j<=y&&1LL*j*k%mod>=min&&1LL*j*k%mod<=max);
            }
            cltstream::write(cnt);
            putchar(10);
        }
    }
    for(re int i=1,k=0;i<=n;++i){
        k=(1LL*k+a[i])%mod;
        sum[i]=sum[i-1]+(1LL*i*k%mod>=min&&1LL*i*k%mod<=max);
    }
    cltstream::read(fin);
    for(re int i=1;i<=fin;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::write(sum[y]-sum[x-1]);
        putchar(10);
    }
    return 0;
}
