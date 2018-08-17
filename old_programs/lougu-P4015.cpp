#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 100
#define maxm 100
using namespace std;

int n,m,s,t,ec=-1,mincost;
struct edge{
    int des,cap,cost,suc;
};
edge e[((maxn+1)*(maxm+1)<<1)+1];
int las[maxn+maxn+3],ex[maxn+maxn+3],dis[maxn+maxn+3],flow[maxn+maxn+3],pre[maxn+maxn+3];
queue<int> h;

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

void connect(int x,int y,int p,int q){
    e[++ec].des=y;
    e[ec].cap=p;
    e[ec].cost=q;
    e[ec].suc=las[x];
    las[x]=ec;
}

bool cmp(int p,int q,int r,int tp){
    return tp?dis[p]<dis[q]+e[r].cost:dis[p]>dis[q]+e[r].cost;
}

bool spfa(int tp){
    for(int i=1;i<=n+m+2;++i)
        dis[i]=tp?-2e9:2e9;
    dis[s]=0;
    flow[s]=2e9;
    h.push(s);
    for(;!h.empty();){
        int x=h.front();
        h.pop();
        ex[x]=0;
        for(int i=las[x];i>=0;i=e[i].suc)
            if(e[i].cap&&cmp(e[i].des,x,i,tp)){
                dis[e[i].des]=dis[x]+e[i].cost;
                flow[e[i].des]=min(flow[x],e[i].cap);
                pre[e[i].des]=i;
                if(!ex[e[i].des]){
                    h.push(e[i].des);
                    ex[e[i].des]=1;
                }
            }
    }
    return tp?dis[t]!=-2e9:dis[t]!=2e9;
}

void addflow(){
    for(int cur=t;cur!=s;cur=e[pre[cur]^1].des)
        e[pre[cur]].cap-=flow[t],e[pre[cur]^1].cap+=flow[t];
    mincost+=dis[t]*flow[t];
}

int main(){
    n=read(),m=read();
    s=n+m+1,t=n+m+2;
    memset(las,-1,sizeof(las));
    for(int i=1;i<=n;++i){
        int x=read();
        connect(s,i,x,0);
        connect(i,s,0,0);
    }
    for(int i=1;i<=m;++i){
        int x=read();
        connect(n+i,t,x,0);
        connect(t,n+i,0,0);
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j){
            int x=read();
            connect(i,n+j,2e9,x);
            connect(n+j,i,0,-x);
        }
    for(;spfa(0);addflow());
    write(mincost);
    putchar(10);
    for(int i=0;i<=ec;i+=2)
        e[i].cap+=e[i^1].cap,e[i^1].cap=0;
    mincost=0;
    for(;spfa(1);addflow());
    write(mincost);
    return 0;
}
