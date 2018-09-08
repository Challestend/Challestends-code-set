#include<cstdio>
#define re register
#define maxn 500000
#define max(a,b) ((a)>=(b)?(a):(b))
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

int n,s,ec;
int des[(maxn<<1)+1],len[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
long long f[maxn+1],g[maxn+1];

inline void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    g[cur]=0;
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs(des[i],cur);
            g[cur]=max(g[cur],g[des[i]]+len[i]);
        }
    for(int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr)
            f[cur]+=f[des[i]]+g[cur]-g[des[i]]-len[i];
}

int main(){
    cltstream::read(n),cltstream::read(s);
    for(int i=1;i<n;++i){
        int x,y,z;
        cltstream::read(x),cltstream::read(y),cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    dfs(s,0);
    cltstream::write(f[s]);
    return 0;
}
