#include<cstdio>
#define re register
#define maxn 200
#define maxm 200
#define maxk 200
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

int n,m,k;
int a[maxn+1][maxm+1],b[maxn+1][maxm+1],w[maxm+1][maxk+1],v[maxm+1][maxk+1],f[maxm+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j){
            cltstream::read(a[i][j]);
            char c=getchar();
            for(;c!='Y'&&c!='N';c=getchar());
            b[i][j]=(c=='Y');
        }
    for(re int i=1;i<=m;++i)
        for(re int j=1,cnt=0;j-cnt<=k&&j<=n;++j){
            int res=w[i][j-cnt-1];
            cnt+=b[n-j+1][i];
            w[i][j-cnt]=res+a[n-j+1][i];
            v[i][j-cnt]=b[n-j+1][i];
        }
    for(re int i=1;i<=m;++i)
        for(re int j=k;j>=0;--j)
            for(re int l=0;l<=j;++l)
                if(!(v[i][l]&&j==l))
                    f[j]=max(f[j],f[j-l]+w[i][l]);
    cltstream::write(f[k]);
    return 0;
}
