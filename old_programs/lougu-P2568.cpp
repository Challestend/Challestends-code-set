#include<cstdio>
#define maxn 10000000
#define maxprimecnt 6645480
using namespace std;

int n;
bool f[maxn+1];
int g[maxprimecnt+1],phi[maxn+1]={0,1};
long long phisum[(maxn>>1)+1];
long long ans;

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;++i){
        if(!f[i])
            g[++g[0]]=i,phi[i]=i-1;
        for(int j=1;j<=g[0]&&i*g[j]<=n;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                phi[i*g[j]]=phi[i]*(g[j]-1);
            else{
                phi[i*g[j]]=phi[i]*g[j];
                break;
            }
        }
    }
    for(int i=1;i<=(n>>1)+1;++i)
        phisum[i]=phisum[i-1]+phi[i];
    for(int i=1;i<=g[0];++i)
        ans+=(phisum[n/g[i]]<<1)-1;
    printf("%lld",ans);
    return 0;
}
