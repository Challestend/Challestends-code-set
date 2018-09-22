#include<cstdio>

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

int main(){
    cltstream::read(n);
    cltstream::read(m);
    ++m;
    int y=n%m,x=m-y,a=n/m;
    cltstream::write(1LL*x*(x-1)*a*a/2+1LL*x*y*a*(a+1)+1LL*y*(y-1)*(a+1)*(a+1)/2);
    return 0;
}
