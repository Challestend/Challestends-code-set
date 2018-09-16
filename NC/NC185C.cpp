#include<cstdio>
#define re register
#define maxn 10000

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=10*x+(c^48),c=getchar());
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

int n,top;
int a[maxn+1],p[maxn+1],b[maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=n;i>=1;--i){
        for(;top&&a[p[top]]<=a[i];--top);
        b[i]=top?p[top]:0;
        p[++top]=i;
    }
    for(re int i=1;i<=n;++i)
        cltstream::write(b[i]),putchar(32);
    return 0;
}
