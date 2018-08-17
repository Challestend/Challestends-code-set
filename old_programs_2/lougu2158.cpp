#include<cstdio>
#define maxn 40000
using namespace std;

int n,ans;
int f[maxn+1],g[maxn+1],phi[maxn+1]={0,1};

int main(){
    scanf("%d",&n);
    if(n==1){
        putchar(48);
        return 0;
    }
    for(int i=2;i<n;++i){
        if(!f[i])
            g[++g[0]]=i,phi[i]=i-1;
        for(int j=1;j<=g[0]&&i*g[j]<n;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                phi[i*g[j]]=phi[i]*phi[g[j]];
            else{
                phi[i*g[j]]=phi[i]*g[j];
                break;
            }
        }
    }
    for(int i=1;i<n;++i)
        phi[i]+=phi[i-1];
    printf("%d",phi[n-1]<<1|1);
    return 0;
}
