#include<cstdio>
#define re register
#define maxn 100000
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

int n,m,ec;
int des[(maxn<<1)+1],len[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int cnt[maxn+1];
long long dis[maxn+1]={4e18};

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs1(des[i],cur);
            cnt[cur]+=cnt[des[i]];
            dis[cur]+=dis[des[i]]+len[i]*cnt[des[i]];
        }
}

void dfs2(int cur,int ftr){
    dis[0]=min(dis[0],dis[cur]);
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dis[des[i]]=dis[cur]+len[i]*(cnt[1]-(cnt[des[i]]<<1));
            dfs2(des[i],cur);
        }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<n;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        ++cnt[x];
        ++cnt[y];
    }
    dfs1(1,0);
    dfs2(1,0);
    cltstream::write(dis[0]);
    return 0;
}
