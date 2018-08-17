#include<cstdio>
#define maxn 1000000

int n;
int f[maxn+1],g[maxn+1];
long long las[maxn+1],sigma[maxn+1]={0,1};
long long ans;

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;++i){
        if(!f[i])
            g[++g[0]]=i,sigma[i]=1+i,las[i]=1+i;
        for(int j=1;j<=g[0]&&i*g[j]<=n;++j){
            f[i*g[j]]=1;
            if(i%g[j]){
                sigma[i*g[j]]=sigma[i]*sigma[g[j]];
                las[i*g[j]]=las[g[j]];
            }
            else{
                sigma[i*g[j]]=sigma[i]*(las[i]*g[j]+1)/las[i];
                las[i*g[j]]=las[i]*g[j]+1;
                break;
            }
        }
    }
    for(int i=1;i<=n;++i)
        printf("%lld ",ans=ans+n-sigma[i]);
    return 0;
}
