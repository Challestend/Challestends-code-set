#include<cstdio>
#define re register
#define maxn 100000
#define maxlog 17

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

int n,m,ec,Log,ans;
int a[maxn+1],des[maxn+1],suc[maxn+1],las[maxn+1];
int dep[maxn+1],f[maxn+1][maxlog+1],g[maxn+1][maxlog+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur){
    dep[cur]=dep[f[cur][0]]+1;
    for(re int i=1;(1<<i)<=dep[cur]+1;++i)
        f[cur][i]=f[f[cur][i-1]][i-1],
        g[cur][i]=g[f[cur][i-1]][i-1]+g[cur][i-1];
    for(re int i=las[cur];i;i=suc[i])
        dfs(des[i]);
}

int main(){
    read(n),read(m);
    for(re int i=1;i<=n;++Log,i<<=1);
    for(re int i=1;i<=n;++i)
        read(a[i]),ans+=(a[i]==m);
    for(re int i=1;i<n;++i){
        int x,y;
        read(x),read(y);
        connect(x,y);
        f[y][0]=x;
        g[y][0]=a[x];
    }
    dfs(1);
    for(re int i=1;i<=n;++i)
        for(re int j=i,k=Log,res=a[i];k>=0&&res<m;--k)
            if(f[j][k]&&res+g[j][k]<=m)
                res+=g[j][k],j=f[j][k],ans+=(res==m);
    write(ans);
    return 0;
}
