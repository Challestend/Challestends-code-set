#include<cstdio>
#include<queue>
#define re register
#define maxn 50000
#define maxm 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define pii std::pair<int,int>
#define mp(a,b) std::make_pair(a,b)

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
    }
}

int n,m,k,ec,t1,t2,ans;
int f[maxn+1],des[(maxm<<1)+1],len[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
std::priority_queue<pii,std::vector<pii >,std::greater<pii > > h;
int v[maxn+1],dis[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void Dijkstra(int src,int tp){
    if(tp&&f[src])
        return;
    for(re int i=1;i<=n;++i){
        v[i]=0;
        dis[i]=1e9;
    }
    for(;!h.empty();h.pop());
    h.push(mp(dis[src]=0,src));
    for(;!h.empty();){
        int x=h.top().second;
        for(;v[x];){
            h.pop();
            if(!h.empty())
                x=h.top().second;
            else
                return;
        }
        h.pop();
        v[x]=1;
        for(re int i=las[x];i;i=suc[i])
            if(dis[des[i]]>dis[x]+len[i]&&(!tp||!f[des[i]]))
                h.push(mp(dis[des[i]]=dis[x]+len[i],des[i]));
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=k;++i){
        int x;
        cltstream::read(x);
        f[x]=1;
    }
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    cltstream::read(t1);
    cltstream::read(t2);
    Dijkstra(1,0);
    int d1=dis[t1],d2=dis[t2];
    Dijkstra(t1,0);
    ans=min(d1,d2)+dis[t2];
    Dijkstra(1,1);
    ans=min(ans,min(max(d1,dis[t2]),max(d2,dis[t1])));
    d1=dis[t1],d2=dis[t2];
    Dijkstra(t1,1);
    ans=min(ans,min(d1,d2)+dis[t2]);
    cltstream::write(ans);
}
