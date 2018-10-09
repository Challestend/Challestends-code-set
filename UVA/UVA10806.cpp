#include<cstdio>
#include<cstring>
#include<queue>
#define re register
#define maxn 100
#define maxm 10000
#define min(a,b) ((a)<=(b)?(a):(b))

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
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,s,t,ec,mf,mc;
int des[(maxm<<2)+(maxn<<2)+1],cap[(maxm<<2)+(maxn<<1)+1];
int cost[(maxm<<2)+(maxn<<1)+1],suc[(maxm<<2)+(maxn<<1)+1],las[maxn+3];
int ex[maxn+3],dis[maxn+3],pre[maxn+3];
std::queue<int> h;

inline void connect(int x,int y,int p,int q){
    des[++ec]=y;
    cap[ec]=p;
    cost[ec]=q;
    suc[ec]=las[x];
    las[x]=ec;
}

inline bool spfa(){
    for(re int i=1;i<=n+2;++i)
        dis[i]=2e9;
    dis[s]=0;
    for(;!h.empty();h.pop());
    h.push(s);
    ex[s]=1;
    for(;!h.empty();){
        int x=h.front();
        h.pop();
        ex[x]=0;
        for(re int i=las[x];i>=0;i=suc[i])
            if(cap[i]&&dis[des[i]]>dis[x]+cost[i]){
                dis[des[i]]=dis[x]+cost[i];
                pre[des[i]]=i;
                if(!ex[des[i]]){
                    h.push(des[i]);
                    ex[des[i]]=1;
                }
            }
    }
    return dis[t]<2e9;
}

inline void addflow(){
    int res=2e9;
    for(re int cur=t;cur!=s;cur=des[pre[cur]^1])
        res=min(res,cap[pre[cur]]);
    mf+=res;
    mc+=res*dis[t];
    for(re int cur=t;cur!=s;cur=des[pre[cur]^1]){
        cap[pre[cur]]-=res;
        cap[pre[cur]^1]+=res;
    }
}

int main(){
    for(;;){
        cltstream::read(n);
        if(!n)
            break;
        cltstream::read(m);
        s=n+1;
        t=n+2;
        ec=-1;
        memset(las,-1,sizeof(las));
        connect(s,1,2,0);
        connect(1,s,0,0);
        connect(n,t,2,0);
        connect(t,n,0,0);
        for(re int i=1;i<=m;++i){
            int x,y,z;
            cltstream::read(x);
            cltstream::read(y);
            cltstream::read(z);
            connect(x,y,1,z);
            connect(y,x,0,-z);
            connect(y,x,1,z);
            connect(x,y,0,-z);
        }
        mf=mc=0;
        for(;spfa();addflow());
        if(mf==2)
            cltstream::write(mc,'\n');
        else
            puts("Back to jail");
    }
    return 0;
}
