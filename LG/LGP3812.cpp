#include<cstdio>
#define re register
#define maxn 50
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
long long base[maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        long long x;
        cltstream::read(x);
        for(re int j=maxn;j>=0&&x;--j)
            if(x>>j&1){
                if(!base[j]){
                    base[j]=x;
                    break;
                }
                else
                    x^=base[j];
            }
    }
    long long res=0;
    for(re int i=maxn;i>=0;--i)
        res=max(res,res^base[i]);
    cltstream::write(res);
    return 0;
}
