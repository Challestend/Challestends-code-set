#include<cstdio>
#define maxn 5000
#define maxm 5000
#define mod 1000000007
using namespace std;

int n,m,ec;
int des[maxn+1<<1],suc[maxn+1<<1],las[maxn+1],f[maxn+1][maxm+1];

void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    if(suc[las[cur]])
        for(int i=las[cur];i;i=suc[i])
            if(des[i]!=ftr){
                dfs(des[i],cur);
                for(int j=1;j<=m;++j)
                    f[cur][j]=(1LL*f[cur][j]*(f[des[i]][0]-f[des[i]][j])%mod+mod)%mod;
            }
    for(int i=1;i<=m;++i)
        f[cur][0]=(f[cur][0]+f[cur][i])%mod;
}

int main(){
    freopen("lougu3914.in","r",stdin);
    freopen("lougu3914.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        int x;
        scanf("%d",&x);
        for(int j=1;j<=x;++j){
            int y;
            scanf("%d",&y);
            f[i][y]=1;
        }
    }
    connect(1,0);
    for(int i=1;i<n;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        connect(x,y);
        connect(y,x);
    }
    dfs(1,0);
    printf("%d",f[1][0]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
