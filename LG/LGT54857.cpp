#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 20
#define mod 998244353

int n,m;
std::string s;
int cnt[(1<<maxn)+1],w[(1<<maxn)+1],f[(1<<maxn)+1],g[(1<<maxn)+1];

int main(){
    scanf("%d%d",&n,&m);
    for(re int i=1;i<(1<<n);++i)
        cnt[i]=cnt[i>>1]+(i&1);
    for(re int i=1;i<=m;++i){
        std::cin>>s;
        int status=0;
        for(re int j=n;j>=1;--j)
            status=(status<<1)|(s[j-1]^48);
        scanf("%d",&w[status]);
    }
    f[0]=1;
    g[0]=w[0];
    for(re int i=0;i<(1<<n);++i)
        for(re int j=1;j<(1<<(n-cnt[i]));++j){
            int nxt=i,las=0;
            for(re int st=j,k=1;k<=n-cnt[i];st>>=1,++k){
                if((st&1)^1)
                    las|=(~nxt)&(-(~nxt));
                nxt|=(~nxt)&(-(~nxt));
            }
            nxt^=las;
            f[nxt]=(f[nxt]+f[i])%mod;
            g[nxt]=(1LL*f[i]*w[nxt]%mod+g[nxt]+g[i])%mod;
        }
    printf("%d",g[(1<<n)-1]);
    return 0;
}
