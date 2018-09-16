#include<cstdio>
#define re register
#define maxn 300000
#define maxk 50
#define maxlog 18
#define mod 998244353
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))

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
int lg[maxn+1],des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int h[maxn+1],f[maxn+1][maxlog+1],dep[maxn+1],po[maxn+1][maxk+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

inline int LCA(int x,int y){
    if(dep[x]>dep[y])
        swap(x,y);
    for(re int z=dep[y]-dep[x];z;y=f[y][lg[z]],z-=(1<<lg[z]));
    for(re int i=lg[dep[x]];i>=0&&f[x][i]!=f[y][i];--i)
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    return x==y?x:f[x][0];
}

int main(){
    cltstream::read(n);
    for(re int i=0;(1<<i)<=n;++i)
        for(re int j=(1<<i);j<(1<<(i+1))&&j<=n;++j)
            lg[j]=i;
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x),cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    h[1]=1;
    for(re int head=0,tail=1;head<tail;){
        int x=h[++head];
        dep[0]=max(dep[0],dep[x]);
        for(re int i=1;i<=maxlog&&f[f[x][i-1]][i-1];++i)
            f[x][i]=f[f[x][i-1]][i-1];
        for(re int i=las[x];i;i=suc[i])
            if(des[i]!=f[x][0]){
                f[des[i]][0]=x;
                dep[des[i]]=dep[x]+1;
                h[++tail]=des[i];
            }
    }
    for(re int i=1;i<=dep[0];++i)
        po[i][0]=1;
    for(re int i=1;i<=dep[0];++i)
        for(re int j=1;j<=maxk;++j)
            po[i][j]=1LL*po[i][j-1]*i%mod;
    for(re int i=1;i<=dep[0];++i)
        for(re int j=1;j<=maxk;++j)
            po[i][j]=(1LL*po[i][j]+1LL*po[i-1][j])%mod;
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int x,y,z,w,ans;
        cltstream::read(x),cltstream::read(y),cltstream::read(z);
        w=LCA(x,y),ans=(1LL*po[dep[x]][z]+1LL*po[dep[y]][z])%mod;
        ans=dep[w]?(1LL*ans-1LL*po[dep[w]][z]-1LL*po[dep[w]-1][z])%mod:ans;
        cltstream::write((1LL*ans+1LL*mod)%mod);
        putchar(10);
    }
    return 0;
}
