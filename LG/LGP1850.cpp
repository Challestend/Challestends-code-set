#include<cstdio>
#define re register
#define maxn 2000
#define maxm 2000
#define maxv 300
#define maxe 90000
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

int n,m,v,e;
int a[maxn+1],b[maxn+1];
double p[maxn+1];
int dis[maxv+1][maxv+1];
double f[maxn+1][maxm+1][2];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(v);
    cltstream::read(e);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=n;++i)
        cltstream::read(b[i]);
    for(re int i=1;i<=n;++i)
        scanf("%lf",&p[i]);
    for(re int i=1;i<=v;++i)
        for(re int j=1;j<i;++j)
            dis[i][j]=dis[j][i]=1e9;
    for(re int i=1;i<=e;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        dis[x][y]=min(dis[x][y],z);
        dis[y][x]=min(dis[y][x],z);
    }
    for(re int k=1;k<=v;++k)
        for(re int i=1;i<=v;++i)
            for(re int j=1;j<=v;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    for(re int i=1;i<=n;++i)
        for(re int j=0;j<=m;++j)
            for(re int k=0;k<2;++k)
                f[i][j][k]=4e18;
    for(re int i=1;i<=n;++i)
        f[i][0][0]=f[i-1][0][0]+dis[a[i-1]][a[i]];
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=i&&j<=m;++j){
            f[i][j][0]=min(f[i-1][j][0]+dis[a[i-1]][a[i]],
                           f[i-1][j][1]+p[i-1]*dis[b[i-1]][a[i]]+(1-p[i-1])*dis[a[i-1]][a[i]]);
            f[i][j][1]=min(f[i-1][j-1][0]+p[i]*dis[a[i-1]][b[i]]+(1-p[i])*dis[a[i-1]][a[i]],
                           f[i-1][j-1][1]+p[i-1]*p[i]*dis[b[i-1]][b[i]]
                                         +p[i-1]*(1-p[i])*dis[b[i-1]][a[i]]
                                         +(1-p[i-1])*p[i]*dis[a[i-1]][b[i]]
                                         +(1-p[i-1])*(1-p[i])*dis[a[i-1]][a[i]]);
        }
    for(re int i=0;i<=n&&i<=m;++i)
        f[n][0][0]=min(f[n][0][0],min(f[n][i][0],f[n][i][1]));
    printf("%0.2lf",f[n][0][0]);
    return 0;
}
