#include<cstdio>
#include<algorithm>
#define re register
#define ull unsigned long long
#define maxn 1000

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
            int digit[24];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
    }
}

int n,m,d;
int a[maxn+1];
ull ans1=1,ans2=1;


ull gcd(ull x,ull y){
    return  y?gcd(y,x%y):x;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(d);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        a[0]+=a[i];
    }
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        ans1*=a[y];
        ans2*=a[0];
        if(!ans1){
            printf("1/0");
            return 0;
        }
        ull g=gcd(ans1,ans2);
        ans1/=g;
        ans2/=g;
        a[y]+=d;
        a[0]+=d;
    }
    cltstream::write(ans1);
    putchar('/');
    cltstream::write(ans2);
    return 0;
}
