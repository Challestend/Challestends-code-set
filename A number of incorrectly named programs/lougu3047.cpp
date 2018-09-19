#include<cstdio>
#define maxn 100000
#define maxm 20
using namespace std;

int n,m,ec;
int des[maxn<<1|1],suc[maxn<<1|1],las[maxn+1];
int f[maxn+1],g[maxn+1][maxm+1];

void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    f[cur]=ftr;
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]){
            dfs1(des[i],cur);
            for(int j=1;j<=m;++j)
                g[cur][j]+=g[des[i]][j-1];
        }
}

void dfs2(int cur){
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]){
            for(int j=m;j>=2;--j)
                g[des[i]][j]+=g[cur][j-1]-g[des[i]][j-2];
            g[des[i]][1]+=g[cur][0];
            dfs2(des[i]);
        }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        connect(x,y);
        connect(y,x);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&g[i][0]);
        for(int j=1;j<=m;++j)
            g[i][j]=g[i][j-1];
    }
    dfs1(1,0);
    dfs2(1);
    for(int i=1;i<=n;++i)
        printf("%d\n",g[i][m]);
    return 0;
}
