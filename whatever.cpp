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

int n,m;
int s2[100][100];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        s2[i][1]=1;
        for(re int j=2;j<=i&&j<=m;++j)
            s2[i][j]=j*s2[i-1][j]+s2[i-1][j-1];
    }
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=i&&j<=m;++j){
            cltstream::write(s2[i][j]);
            putchar(32);
        }
        putchar(10);
    }
    return 0;
}
