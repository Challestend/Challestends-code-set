#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 100
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,s,t,ec=-1,mincost;
struct edge{
    int des,cap,cost,suc;
};
edge e[(maxn*(maxn+2)<<1)+1];
int a[maxn+1][maxn+1],las[(maxn<<1)+3],ex[(maxn<<1)+3],dis[(maxn<<1)+3],flow[(maxn<<1)+3],pre[(maxn<<1)+3];
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
    for(int i=1;i<=(n<<1)+2;++i)
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
    n=read();
    s=(n<<1)+1,t=(n<<1)+2;
    memset(las,-1,sizeof(las));
    for(int i=1;i<=n;++i){
        connect(s,i,1,0);
        connect(i,s,0,0);
        connect(n+i,t,1,0);
        connect(t,n+i,0,0);
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j){
            a[i][j]=read();
            connect(i,n+j,1,a[i][j]);
            connect(n+j,i,0,-a[i][j]);
        }
    for(;spfa(0);addflow());
    write(mincost);
    putchar(10);
    for(int i=0;i<=ec;i+=2)
        if(!e[i].cap)
            ++e[i].cap,--e[i+1].cap;
    mincost=0;
    for(;spfa(1);addflow());
    write(mincost);
    return 0;
}
