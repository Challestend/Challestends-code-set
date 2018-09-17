#include<cstdio>
#define re register
#define maxn 100
#define max(a,b) ((a)>=(b)?(a):(b))
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

int n,m,maxa=-1000,mina=1000;
int a[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        a[0]+=a[i];
        maxa=max(maxa,a[i]);
        mina=min(mina,a[i]);
    }
    if(a[0]+m<=n*maxa)
        cltstream::write(maxa);
    else
        cltstream::write(maxa+(a[0]+m-n*maxa)/n+((a[0]+m-n*maxa)%n>0));
    putchar(32);
    cltstream::write(maxa+m);
    return 0;
}
