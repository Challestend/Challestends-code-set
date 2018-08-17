#include<cstdio>
#define maxn 100
#define max(a,b) ((a)>=(b)?(a):(b))
using namespace std;

int n;
int a[maxn<<1|1],f[maxn<<1|1][maxn+1];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]),a[n+i]=a[i];
    for(int j=2;j<=n;++j)
        for(int i=1;i<=n;++i)
            for(int k=1;k<j;++k)
                f[i][j]=max(f[i][j],f[i][k]+f[i+k][j-k]+a[i]*a[i+k]*a[i+j]),f[n+i][j]=f[i][j];
    for(int i=1;i<=n;++i)
        f[1][n]=max(f[1][n],f[i][n]);
    printf("%d",f[1][n]);
    return 0;
}
