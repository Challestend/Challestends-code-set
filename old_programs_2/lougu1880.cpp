#include<cstdio>
#define maxn 100
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n;
int a[maxn+1<<1],f[maxn+1<<1][maxn+1],g[maxn+1<<1][maxn+1];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]),a[i]+=a[i-1];
    for(int i=1;i<=n;++i)
        a[n+i]=a[n]+a[i];
    for(int i=1;i<=n;++i)
        for(int j=2;j<=n;++j)
            f[i][j]=2e9;
    for(int j=2;j<=n;++j)
        for(int k=1;k<j;++k)
            for(int i=1;i<=n;++i)
                f[i][j]=f[n+i][j]=min(f[i][j],f[i][k]+f[i+k][j-k]+a[i+j-1]-a[i-1]),
                g[i][j]=g[n+i][j]=max(g[i][j],g[i][k]+g[i+k][j-k]+a[i+j-1]-a[i-1]);
    for(int i=2;i<=n;++i)
        f[1][n]=min(f[1][n],f[i][n]),
        g[1][n]=max(g[1][n],g[i][n]);
    printf("%d\n%d",f[1][n],g[1][n]);
    return 0;
}
