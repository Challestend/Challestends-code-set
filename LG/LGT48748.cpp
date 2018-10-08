#include<cstdio>
#define re register
#define maxn 500

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
int a[maxn+1][maxn+1],b[maxn+1][maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=n;++j)
            a[i][j]=(i-1)*n+j;
    for(re int i=1;i<=m;++i){
        int x,y,r,d;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(r);
        cltstream::read(d);
        x-=r;
        y-=r;
        r+=r+1;
        for(re int j=1;j<=r;++j)
            for(re int k=1;k<=r;++k)
                b[x+j-1][y+k-1]=a[x+j-1][y+k-1];
        for(re int j=1;j<=r;++j)
            for(re int k=1;k<=r;++k)
                if(!d)
                    a[x+k-1][y+r-j]=b[x+j-1][y+k-1];
                else
                    a[x+r-k][y+j-1]=b[x+j-1][y+k-1];
    }
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=n;++j){
            cltstream::write(a[i][j]);
            putchar(32);
        }
        putchar(10);
    }
    return 0;
}
