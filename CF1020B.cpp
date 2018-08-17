#include<cstdio>
#define maxn 1000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,ec,n0;
int des[maxn+1],suc[maxn+1],las[maxn+1],ind[maxn+1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],ex[maxn+1],f[maxn+1],ans[maxn+1];

void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur){
    dfn[cur]=low[cur]=++dfn[0];
    st[++st[0]]=cur;
    ex[cur]=1;
    for(int i=las[cur];i;i=suc[i])
        if(!dfn[des[i]])
            dfs(des[i]),low[cur]=min(low[cur],low[des[i]]);
        else
            low[cur]=min(low[cur],dfn[des[i]]);
    if(low[cur]==dfn[cur])
        for(++n0;st[st[0]+1]!=cur;f[st[st[0]--]]=n0);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int x;
        scanf("%d",&x);
        connect(x,i);
    }
    for(int i=1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    for(int i=1;i<=n;++i)
        for(int j=las[i];j;j=suc[j])
            if(f[i]!=f[des[j]])
                ++ind[f[des[j]]];
    int head=0,tail=0;
    for(int i=1;i<=n;++i)
        if(!ind[f[i]])
            ans[st[++tail]=i]=i;
    for(;head<tail;){
        int x=st[++head];
        for(int i=las[x];i;i=suc[i])
            if(f[des[i]]!=f[x])
                ans[st[++tail]=des[i]]=ans[x];
    }
    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]);
    return 0;
}
