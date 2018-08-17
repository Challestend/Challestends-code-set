#include<cstdio>
#include<cstring>
#define maxn 1000
#define maxk 20
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,k,m,ec=-1,s,t,maxflow;
struct edge{
    int des,cap,suc;
};
edge e[((maxn+1)*(maxk+1)<<1)+1];
int a[maxk+1],las[maxn+maxk+3],arc[maxn+maxk+3],h[maxn+maxn+3],dep[maxn+maxk+3],cnt[maxn+maxk+3],pre[maxn+maxk+3];

int read(){
    int sn=1,x=0;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45){
        sn=-1;
        c=getchar();
    }
    for(;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    return sn*x;
}

void write(int x){
    if(x<0){
        putchar(45);
        x=-x;
    }
    if(x>=10)
        write(x/10);
    putchar(x%10^48);
}

void connect(int x,int y,int p){
    e[++ec].des=y;
    e[ec].cap=p;
    e[ec].suc=las[x];
    las[x]=ec;
}

void initdepth(){
    for(int i=1;i<=n+k+2;++i)
        arc[i]=las[i],dep[i]=n+k+2;
    dep[h[1]=t]=0;
    for(int head=0,tail=1;head<tail;){
        int x=h[++head];
        for(int i=las[x];i>=0;i=e[i].suc)
            if(e[i^1].cap&&dep[e[i].des]==n+k+2)
                dep[h[++tail]=e[i].des]=dep[x]+1;
    }
    for(int i=1;i<=n+k+2;++i)
        ++cnt[dep[i]];
}

void addflow(){
    int res=2e9;
    for(int cur=t;cur!=s;cur=e[pre[cur]^1].des)
        res=min(res,e[pre[cur]].cap);
    maxflow+=res;
    for(int cur=t;cur!=s;cur=e[pre[cur]^1].des)
        e[pre[cur]].cap-=res,e[pre[cur]^1].cap+=res;
}

void solve(){
    initdepth();
    for(int cur=s;dep[s]<n+k+2;){
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
            int mind=n+k+1;
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
    k=read(),n=read();
    memset(las,-1,sizeof(las));
    s=n+k+1,t=n+k+2;
    for(int i=1;i<=n;++i){
        connect(s,i,1);
        connect(i,s,0);
    }
    for(int i=1;i<=k;++i){
        int x=read();
        connect(n+i,t,x);
        connect(t,n+i,0);
    }
    for(int i=1;i<=n;++i){
        int x=read();
        memset(a,0,sizeof(a));
        for(int j=1;j<=x;++j){
            int y=read();
            if(!a[y]){
                connect(i,n+y,1);
                connect(n+y,i,0);
                a[y]=1;
            }
        }
    }
    solve();
    for(int i=1;i<=k;++i){
        write(i);
        putchar(':');
        for(int j=las[n+i];j>=0;j=e[j].suc)
            if(e[j].des<=n&&e[j].cap)
                putchar(32),write(e[j].des);
        putchar(10);
    }
    return 0;
}
