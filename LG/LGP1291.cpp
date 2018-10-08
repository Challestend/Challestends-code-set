#include<cstdio>
#include<cmath>
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

long long gcd(long long x,long long y){
    return y?gcd(y,x%y):x;
}

int n;
struct fraction{
    long long son,mth;

    inline void init(long long _son,long long _mth){
        long long g=gcd(_son,_mth);
        son=_son/g;
        mth=_mth/g;
    }

    fraction(long long _son,long long _mth){
        init(_son,_mth);
    }
};
fraction ans(0,1);

inline fraction operator+(fraction& _x,fraction& _y){
    if(!_x.son)
        return _y;
    else{
        int g=gcd(_x.mth,_y.mth);
        fraction res(_y.mth*_x.son/g+_x.mth*_y.son/g,_x.mth*_y.mth/g);
        return res;
    }
}

inline void operator+=(fraction& _x,fraction& _y){
    _x=_x+_y;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        fraction res(1LL*n,1LL*(n-i+1));
        ans+=res;
    }
    int len1=log10(ans.son/ans.mth)+1,len2=log10(ans.mth)+1;
    if(ans.son%ans.mth==0)
        cltstream::write(ans.son);
    else{
        if(ans.son>ans.mth)
            for(re int i=1;i<=len1;++i)
                putchar(32);
        cltstream::write(ans.son%ans.mth);
        putchar(10);
        if(ans.son>ans.mth)
            cltstream::write(ans.son/ans.mth);
        for(re int i=1;i<=len2;++i)
            putchar(45);
        putchar(10);
        if(ans.son>ans.mth)
            for(re int i=1;i<=len1;++i)
                putchar(32);
        cltstream::write(ans.mth);
    }
    return 0;
}
