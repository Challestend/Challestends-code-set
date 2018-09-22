#include<cstdio>
#define re register
#define maxn 50000
#define maxm 1000
#define maxc 10
#define mod 987654321

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

int n,m,c;
int a[maxn+1][maxc+1],b[maxn+1],f[maxn+1][maxc+1][maxc+1];

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(c);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=c;++j)
            a[i][j]=1;
    for(re int i=1;i<=m;++i){
        int opt,x,y;
        cltstream::read(opt);
        cltstream::read(x);
        cltstream::read(y);
        switch(opt){
            case 1:
                if(!a[x][y]){
                    putchar(48);
                    return 0;
                }
                for(re int j=1;j<=c;++j)
                    a[x][j]=0;
                a[x][y]=1;
                break;
            case 2:
                a[x][y]=0;
                break;
            case 3:
                if(x>y)
                    swap(x,y);
                b[y]=1;
        }
    }
    for(re int i=1;i<=c;++i)
        if(a[1][i])
            f[1][i][0]+=f[1][i][i]=1;
    for(re int j=1;j<=c;++j)
        if(a[1][j])
            for(re int i=2;i<=n;++i)
                for(re int k=1;k<=c;++k)
                    if(a[i][k]){
                        f[i][j][k]=b[i]?f[i-1][j][k]:(f[i-1][j][0]-f[i-1][j][k]+mod)%mod;
                        f[i][j][0]=(f[i][j][0]+f[i][j][k])%mod;
                    }
    for(re int i=1;i<=c;++i)
        for(re int j=i+1;j<=c;++j){
            f[n][0][0]=(f[n][0][0]+f[n][i][j])%mod;
            f[n][0][0]=(f[n][0][0]+f[n][j][i])%mod;
        }
    cltstream::write(f[n][0][0]);
    return 0;
}
