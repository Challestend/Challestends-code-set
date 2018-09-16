#include<cstdio>
#include<cstring>
#define re register
#define maxn 5000
#define maxm 50000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,m,s,t,ec=-1,maxflow,mincost;
struct edge{
    int des,cap,cost,suc;
};
edge e[(maxm<<1)+1];
int las[maxn+1],h[(maxn+1)<<3],ex[maxn+1],dis[maxn+1],flow[maxn+1],pre[maxn+1];

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
        x=-1;
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

bool spfa(){
    for(re int i=1;i<=n;++i)
        dis[i]=2e9;
    dis[s]=0;
    flow[s]=2e9;
    ex[h[1]=s]=1;
    for(re int head=0,tail=1;head<tail;){
        int x=h[++head];
        ex[x]=0;
        for(re int i=las[x];i>=0;i=e[i].suc)
            if(e[i].cap>0&&dis[e[i].des]>dis[x]+e[i].cost){
                dis[e[i].des]=dis[x]+e[i].cost;
                flow[e[i].des]=min(flow[x],e[i].cap);
                pre[e[i].des]=i;
                if(!ex[e[i].des])
                    ex[h[++tail]=e[i].des]=1;
            }
    }
    return dis[t]!=2e9;
}

void addflow(){
    for(re int cur=t;cur!=s;cur=e[pre[cur]^1].des){
        e[pre[cur]].cap-=flow[t];
        e[pre[cur]^1].cap+=flow[t];
    }
    maxflow+=flow[t];
    mincost+=dis[t]*flow[t];
}

int main(){
    n=read(),m=read(),s=read(),t=read();
    memset(las,-1,sizeof(las));
    for(re int i=1;i<=m;++i){
        int x=read(),y=read(),p=read(),q=read();
        connect(x,y,p,q);
        connect(y,x,0,-q);
    }
    for(;spfa();addflow());
    write(maxflow);
    putchar(32);
    write(mincost);
    return 0;
}
