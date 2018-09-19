#include<cstdio>
#define maxn 200000
using namespace std;

int n;
long long ans;
int f[maxn+1],g[maxn+1],phi[maxn+1]={0,1};

int main(){
    for(int i=2;i<=maxn;++i){
        if(!f[i])
            g[++g[0]]=i,phi[i]=i-1;
        for(int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                phi[i*g[j]]=phi[i]*(g[j]-1);
            else{
                phi[i*g[j]]=phi[i]*g[j];
                break;
            }
        }
    }
    scanf("%d",&n);
    for(;n;){
        ans=0;
        for(int i=1;i<=n;++i)
            ans+=1LL*phi[i]*(n/i)*(n/i);
        printf("%lld\n",ans-(1LL*n*(n+1)>>1)>>1);
        scanf("%d",&n);
    }
    return 0;
}
