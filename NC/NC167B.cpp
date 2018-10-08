#include<cstdio>
#define re register
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
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
    }
}

int n;
int a[maxn+1][maxn+1];

int main(){
    cltstream::read(n);
    a[0][1]=1;
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=i;++j){
            a[i][j]+=a[i-1][j]*5;
            a[i][j+1]+=a[i][j]/10;
            a[i][j]%=10;
        }
    putchar(48);
    putchar(46);
    for(re int i=n;i>=1;--i)
        cltstream::write(a[n][i]);
    return 0;
}
