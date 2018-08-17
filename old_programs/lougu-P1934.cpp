#include<cstdio>
#define maxn 1000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n;
long long m;
long long a[maxn+1],b[maxn+1],f[maxn+1];

int main(){
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%lld",&a[i]),b[i]=b[i-1]+a[i];
    for(int i=1;i<=n;++i){
        f[i]=f[i-1]+n*n*a[i];
        for(int j=i-2;j>=0;--j)
            if(a[i]+a[j+1]<=m)
                f[i]=min(f[i],f[j]+(a[i]+a[j+1])*(b[i]-b[j]));
    }
    printf("%lld",f[n]);
    return 0;
}
