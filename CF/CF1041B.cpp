#include<cstdio>
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

long long a,b,x,y;

long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}

int main(){
    cltstream::read(a);
    cltstream::read(b);
    cltstream::read(x);
    cltstream::read(y);
    long long g=gcd(x,y);
    x/=g;
    y/=g;
    cltstream::write(min(a/x,b/y));
    return 0;
}
