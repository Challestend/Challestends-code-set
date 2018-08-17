#include<cstdio>
#include<queue>
#define re register
#define maxn 100000
#define maxm 100000
#define pli std::pair<long long,int>
#define mp(a,b) std::make_pair(a,b)

int n,m,ec;
int des[maxm+1<<1],len[maxm+1<<1],suc[maxm+1<<1],las[maxn+1];
long long dis[maxn+1];
int pre[maxn+1],vis[maxn+1];
std::priority_queue<pli,std::vector<pli>,std::greater<pli> > h;

inline void read(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48|c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void write(int x){
    if(x<0)
        putchar(45),x=-x;
    int digit[20];
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void getroute(int cur){
    if(cur!=1)
        getroute(pre[cur]);
    write(cur);
    putchar(32);
}

int main(){
    read(n),read(m);
    for(int i=1;i<=m;++i){
        int x,y,z;
        read(x),read(y),read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    for(int i=2;i<=n;++i)
        dis[i]=1e18;
    h.push(mp(0,1));
    for(int i=1;i<=n;++i){
        int x=h.top().second;
        h.pop();
        if(!vis[x])
            vis[x]=1;
        else
            continue;
        for(int j=las[x];j;j=suc[j])
            if(dis[des[j]]>dis[x]+len[j])
                dis[des[j]]=dis[x]+len[j],pre[des[j]]=x,h.push(mp(dis[des[j]],des[j]));
    }
    if(dis[n]<1e18)
        getroute(n);
    else
        write(-1);
    return 0;
}
