#include<cstdio>
#define maxn 100000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,ec;
int des[maxn<<1|1],len[maxn<<1|1],suc[maxn<<1|1],las[maxn+1];
int f[maxn<<1|1],cnt[maxn<<1|1],size[maxn<<1|1];
long long ans[maxn<<1|1];

void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    f[cur]=ftr;
    size[cur]=cnt[cur];
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur])
            dfs1(des[i],cur),size[cur]+=size[des[i]],ans[cur]+=ans[des[i]]+1LL*len[i]*size[des[i]];
}

void dfs2(int cur){
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur])
            ans[des[i]]=ans[cur]+1LL*len[i]*(size[1]-(size[des[i]]<<1)),dfs2(des[i]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&cnt[i]);
    for(int i=1;i<n;++i){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        connect(x,y,z);
        connect(y,x,z);
    }
    dfs1(1,0);
    dfs2(1);
    for(int i=1;i<=n;++i)
        ans[1]=min(ans[1],ans[i]);
    printf("%lld",ans[1]);
    return 0;
}
