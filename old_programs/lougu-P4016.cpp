#include<cstdio>
#include<cstring>
#define maxn 100
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))
using namespace std;

int n,s,t,ec=-1,maxflow,mincost;
struct edge{
    int des,cap,cost,suc;
};
edge e[maxn*(maxn+1)+1];
int a[maxn+1],las[maxn+3],h[(maxn+2<<3)+1],ex[maxn+3],dis[maxn+3],flow[maxn+2],pre[maxn+3];

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

bool spfa(){
    for(int i=1;i<=n+2;++i)
        dis[i]=2e9;
    dis[s]=0;
    flow[s]=2e9;
    ex[h[1]=s]=1;
    for(int head=0,tail=1;head<tail;){
        int x=h[++head];
        ex[x]=0;
        for(int i=las[x];i>=0;i=e[i].suc)
            if(e[i].cap&&dis[e[i].des]>dis[x]+e[i].cost){
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
    for(int cur=t;cur!=s;cur=e[pre[cur]^1].des){
        e[pre[cur]].cap-=flow[t];
        e[pre[cur]^1].cap+=flow[t];
    }
    maxflow+=flow[t];
    mincost+=dis[t]*flow[t];
}

int main(){
    memset(las,-1,sizeof(las));
    n=read();
    s=n+1,t=n+2;
    for(int i=1;i<=n;++i)
        a[i]=read(),a[0]+=a[i];
    a[n+1]=a[0]/=n;
    for(int i=1;i<=n;++i)
        if(a[i]>a[0]){
            connect(s,i,a[i]-a[0],0);
            connect(i,s,0,0);
        }
        else{
            connect(i,t,a[0]-a[i],0);
            connect(t,i,0,0);
        }
    for(int i=1;i<=n;++i){
        connect(i,i%n+1,2e9,1);
        connect(i%n+1,i,0,-1);
        connect(i%n+1,i,2e9,1);
        connect(i,i%n+1,0,-1);
    }
    for(;spfa();addflow());
    write(mincost);
    return 0;
}
