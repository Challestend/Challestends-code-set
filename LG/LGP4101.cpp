#include<cstdio>
#define re register

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

int t,n,m,x,p,q;

int main(){
    cltstream::read(t);
    for(re int i=1;i<=t;++i){
        cltstream::read(n);
        cltstream::read(m);
        x=(m>>1)+1;
        p=n/x;
        q=n%x;
        for(;p&&x+q<=m;--p,q+=x);
        cltstream::write((n-p-(q>0)+1)&1);
        putchar(10);
    }
    return 0;
}
