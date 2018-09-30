#include<cstdio>
#define re register
#define maxn 100000
#define maxm 1000000

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
int h[maxn+1];
int src[(maxm<<1)+1],des[(maxm<<1)+1],len[(maxm<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1],g[maxn+1];
long long dis[maxn+1];

inline void connect(int x,int y,int z){
    src[++ec]=x;
    des[ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

inline void swap(int x,int y){
    int tmp=f[x];
    f[x]=f[y];
    f[y]=tmp;
    tmp=g[f[x]];
    g[f[x]]=g[f[y]];
    g[f[y]]=tmp;
}

inline void push(int x){
    if(!g[x]){
        g[x]=++f[0];
        f[g[x]]=x;
    }
    for(int p=g[x],q=p>>1;q>=1;)
        if(dis[f[p]]<dis[f[q]]){
            swap(p,q);
            p=q;
            q=p>>1;
        }
        else
            break;
}

inline int pop(){
    int res=f[1];
    f[1]=f[f[0]--];
    for(int p=1,q=p<<1;q<=f[0];){
        if(q<f[0]&&dis[f[q+1]]<dis[f[q]])
            ++q;
        if(dis[f[q]]<dis[f[p]]){
            swap(p,q);
            p=q;
            q=p<<1;
        }
        else
            break;
    }
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(h[i]);
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        if(h[x]>=h[y])
            connect(x,y,z);
        if(h[y]>=h[x])
            connect(y,x,z);
    }
    for(re int i=2;i<=n;++i)
        dis[i]=4e18;
    push(1);
    for(re int i=1;i<=n;++i){
        int x=pop();
        for(re int j=las[x];j;j=suc[j])
            if(dis[des[j]]>dis[x]+len[j]){
                dis[des[j]]=dis[x]+len[j];
                push(des[j]);
            }
    }
    int sum=0;
    for(re int i=1;i<=n;++i)
        sum+=(dis[i]<4e18);
    cltstream::write(sum);
    putchar(32);
    long long ans=0;
    for(re int i=1;i<=ec;++i)
        if(dis[des[i]]==dis[src[i]]+len[i])
            ans+=len[i];
    cltstream::write(ans);
    return 0;
}
