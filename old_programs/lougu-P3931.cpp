#include<cstdio>
#include<cstring>
#define maxn 100000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,s,t,ec=-1,maxflow;
struct edge{
    int des,cap,suc;
};
edge e[maxn<<2+1];
int las[maxn+2],d[maxn+2],arc[maxn+2],h[maxn+2],dep[maxn+2],cnt[maxn+2],pre[maxn+2];

void connect(int x,int y,int p){
    e[++ec].des=y;
    e[ec].cap=p;
    e[ec].suc=las[x];
    las[x]=ec;
}

void swap(int x,int y){
    int tmp=e[x].cap;
    e[x].cap=e[y].cap;
    e[y].cap=tmp;
}

void dfs(int cur,int ftr){
    for(int i=las[cur];i>=0;i=e[i].suc)
        if(e[i].des!=ftr){
            if(!e[i].cap)
                swap(i,i^1);
            dfs(e[i].des,cur);
        }
}

void initdepth(){
    for(int i=1;i<=n+1;++i){
        arc[i]=las[i];
        dep[i]=n+1;
    }
    dep[h[1]=t]=0;
    for(int head=0,tail=1;head<tail;){
        int x=h[++head];
        for(int i=las[x];i>=0;i=e[i].suc)
            if(e[i^1].cap&&dep[e[i].des]==n+1)
                dep[h[++tail]=e[i].des]=dep[x]+1;
    }
    for(int i=1;i<=n+1;++i)
        ++cnt[dep[i]];
}

void addflow(){
    int res=2e9;
    for(int cur=t;cur!=s;cur=e[pre[cur]^1].des)
        res=min(res,e[pre[cur]].cap);
    maxflow+=res;
    for(int cur=t;cur!=s;cur=e[pre[cur]^1].des){
        e[pre[cur]].cap-=res;
        e[pre[cur]^1].cap+=res;
    }
}

void solve(){
    initdepth();
    for(int cur=s;dep[s]<n+1;){
        if(cur==t){
            addflow();
            cur=s;
        }
        int f=0;
        for(int i=arc[cur];i>=0;i=e[i].suc)
            if(e[i].cap&&dep[e[i].des]<dep[cur]){
                f=1;
                arc[cur]=i;
                pre[cur=e[i].des]=i;
                break;
            }
        if(!f){
            if(!(--cnt[dep[cur]]))
                break;
            arc[cur]=las[cur];
            int mind=n;
            for(int i=las[cur];i>=0;i=e[i].suc)
                if(e[i].cap&&dep[e[i].des]<mind)
                    mind=dep[e[i].des];
            ++cnt[dep[cur]=mind+1];
            if(cur!=s)
                cur=e[pre[cur]^1].des;
        }
    }
}

int main(){
    scanf("%d%d",&n,&s);
    t=n+1;
    memset(las,-1,sizeof(las));
    for(int i=1;i<n;++i){
        int x,y,p;
        scanf("%d%d%d",&x,&y,&p);
        connect(x,y,p);
        connect(y,x,0);
        ++d[x],++d[y];
    }
    dfs(s,0);
    for(int i=1;i<=n;++i)
        if(i!=s&&d[i]==1){
            connect(i,n+1,2e9);
            connect(n+1,i,0);
        }
    solve();
    printf("%d",maxflow);
    return 0;
}
