#include<cstdio>
#define maxn 100000
#define maxm 100000
using namespace std;

int n,m;
int f[maxn+1],g[maxn+1],phi[maxn+1]={0,1};
long long ans;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n&&i<=m;++i){
        if(!f[i])
            g[++g[0]]=i,phi[i]=i-1;
        for(int j=1;j<=g[0]&&i*g[j]<=n&&i*g[j]<=m;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                phi[i*g[j]]=phi[i]*phi[g[j]];
            else{
                phi[i*g[j]]=phi[i]*g[j];
                break;
            }
        }
    }
    for(int i=1;i<=n&&i<=m;++i)
        ans+=1LL*(n/i)*(m/i)*phi[i];
    ans=(ans<<1)-1LL*n*m;
    printf("%lld",ans);
    return 0;
}
