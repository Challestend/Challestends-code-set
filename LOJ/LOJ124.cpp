#include<cstdio>
#define re register
#define maxn 10000000
#define maxg 664579
#define mod 1000000007

int n,m;
int f[maxn+1],g[maxg+1],las[maxn+1]={0,1},sigma[maxn+1]={0,1};

int cltpow(int x,int y){
    if(y==1)
        return x;
    int res=cltpow(x,y>>1);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

int main(){
    scanf("%d%d",&n,&m);
    for(re int i=2;i<=n;++i){
        if(!f[i]){
            g[++g[0]]=i;
            las[i]=(cltpow(i,m)+1)%mod;
            sigma[i]=1;
        }
        for(re int j=1;j<=g[0]&&1LL*i*g[j]<=1LL*n;++j){
            f[i*g[j]]=1;
            if(i%g[j]){
                sigma[i*g[j]]=1LL*sigma[i]*las[i]%mod;
                las[i*g[j]]=las[g[j]];
            }
            else{
                sigma[i*g[j]]=sigma[i];
                las[i*g[j]]=(1LL*las[i]*(las[g[j]]-1+mod)%mod+1)%mod;
                break;
            }
        }
    }
    for(re int i=1;i<=n;++i)
        sigma[0]=(1LL*sigma[i]*las[i]%mod+sigma[0])%mod;
    printf("%d",sigma[0]);
    return 0;
}
