#include<cstdio>
#define maxn 50
#define maxm 1000
#define maxq 50

int n,m,q;
double pi[maxn+1],a[maxn+1][maxq+1],b[maxn+1][maxn+1];
int O[maxm+1];
double f[maxm+1][maxn+1];

int main(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)
        scanf("%lf",&pi[i]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=q;++j)
            scanf("%lf",&a[i][j]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            scanf("%lf",&b[i][j]);
    for(int i=1;i<=m;++i)
        scanf("%d",&O[i]),++O[i];
    for(int i=1;i<=n;++i)
        f[1][i]=pi[i]*a[i][O[1]];
    for(int i=2;i<=m;++i)
        for(int j=1;j<=n;++j)
            for(int k=1;k<=n;++k)
                f[i][j]+=f[i-1][k]*b[k][j]*a[j][O[i]];
    for(int i=1;i<=n;++i)
        f[m][0]+=f[m][i];
    printf("%0.4lf",f[m][0]);
    return 0;
}
