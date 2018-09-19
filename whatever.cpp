#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;

const int maxn=10000,maxm=100000;

int n,m,e,time,sum;
int a[maxn+1<<1];
int des[maxm+1<<1],suc[maxm+1<<1],las[maxn+1<<1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],ex[maxn+1],f[maxn+1];
int ind[maxn+1],ans[maxn+1];
queue<int> h;

void dfs(int cur){
    dfn[cur]=low[cur]=++time;
    st[++st[0]]=cur;
    ex[cur]=1;
    for(int i=las[cur];i;i=suc[i]){
        int x=des[i];
        if(!dfn[x]){
            dfs(x);
            low[cur]=min(low[cur],low[x]);
        }
        else
            if(ex[x])
                low[cur]=min(low[cur],dfn[x]);
    }
    if(low[cur]==dfn[cur]){
        sum++;
        for(;st[st[0]+1]!=cur;){
            int x=st[st[0]--];
            ex[x]=0;
            f[x]=sum;
            a[n+sum]+=a[x];
        }
        ans[sum]=a[n+sum];
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        des[++e]=v;
        suc[e]=las[u];
        las[u]=e;
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
    for(int i=1;i<=n;i++)
        for(int j=las[i];j;j=suc[j]){
            int x=des[j];
            if(f[i]!=f[x]){
                des[++e]=n+f[x];
                suc[e]=las[n+f[i]];
                las[n+f[i]]=e;
                ind[f[x]]++;
            }
        }
    for(int i=1;i<=sum;i++)
        if(!ind[i])
            h.push(i);
    for(;!h.empty();){
        int x=h.front();
        ans[0]=max(ans[0],ans[x]);
        h.pop();
        for(int i=las[n+x];i;i=suc[i]){
            int y=des[i]-n;
            ind[y]--;
            ans[y]=max(ans[y],ans[x]+a[n+y]);
            if(!ind[y])
                h.push(y);
        }
    }
    printf("%d",ans[0]);
    for(int i=1;i<=n;++i)
        printf("\nf[%d]=%d",i,f[i]);
    return 0;
}
