#include<cstdio>
#define re register
#define maxn 12
#define maxsize 4096
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
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,size,ans=2e9;
int w[maxn+1][maxn+1],f[maxsize+1],dis[maxsize+1][maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    size=1<<n;
    for(re int i=1;i<=n;++i)
        for(re int j=i+1;j<=n;++j)
            w[i][j]=w[j][i]=2e9;
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        w[x][y]=w[y][x]=z;
    }
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<size;++j)
            f[j]=2e9;
        for(re int j=1;j<=n;++j)
            if(w[i][j]<2e9){
                f[1<<(j-1)]=w[i][j];
                dis[1<<(j-1)][j]=(j!=i);
            }
        for(re int j=1;j<size;++j)
            for(re int l=1;l<=n;++l)
                if((j>>(l-1))&1)
                    for(re int r=1;r<=n;++r)
                        if(((j>>(r-1))&1)^1)
                            f[j|(1<<(r-1))]=min(f[j|(1<<(r-1))],1LL*f[j]+1LL*(dis[j][l]+1)*w[l][r]);
        ans=min(ans,f[size-1]);
        printf("%d %d\n",i,f[size-1]);
    }
    cltstream::write(ans,'\n');
    return 0;
}
