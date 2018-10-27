#include<cstdio>
#define maxn 1000
#define maxm 1000
#define min(a,b) ((a)<=(b)?(a):(b))

int n,m;
int a[maxn+1],b[maxm+1],f[maxn+1][maxm+1];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;++i)
        scanf("%d",&b[i]);
    for(int i=1;i<=n;++i){
        f[i][i]=f[i-1][i-1]+a[i]*b[i];
        for(int j=i+1;j<=m;++j)
            f[i][j]=min(f[i-1][j-1]+a[i]*b[j],f[i][j-1]);
    }
    printf("%d",f[n][m]);
    return 0;
}
