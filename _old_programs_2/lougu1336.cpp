#include<cstdio>
#define maxn 200
#define maxm 20
#define min(a,b) ((a)<=(b)?(a):(b))

int n,m;
int a[maxm+1],b[maxm+1];
long long f[maxn+1][maxm+1];

long long pow0(int x,int y){
    if(y==1)
        return x;
    long long res=pow0(x,y>>1);
    return (y&1)?res*res*x:res*res;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
        scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=n;++i)
        f[i][1]=a[1]*pow0(i,b[1]);
    for(int i=1;i<=n;++i)
        for(int j=2;j<=m;++j)
            f[i][j]=1e18;
    for(int i=1;i<=n;++i)
        for(int j=2;j<=m;++j)
            for(int k=0;k<=i;++k)
                f[i][j]=min(f[i][j],f[k][j-1]+1LL*a[j]*pow0(i-k,b[j]));
    printf("%lld",f[n][m]);
    return 0;
}
