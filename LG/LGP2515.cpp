#include<cstdio>
#define re register
#define maxn 100
#define maxm 500
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=gc();
        for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
        if(c==45&&c!=EOF)
            sn=-1,c=gc();
        for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
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

int n,m,ec,vc;
int w[maxn+1],v[maxn+1];
int des[maxn+1],suc[maxn+1],las[maxn+1],fst[maxn+1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],ex[maxn+1],id[maxn+1],vis[maxn+1]={1};
int size[maxn+1],f[maxn+1][maxm+1],g[maxm+1],ans[maxm+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
    if(!fst[x])
        fst[x]=ec;
}

void dfs1(int cur){
    dfn[cur]=low[cur]=++vc;
    st[++st[0]]=cur;
    ex[cur]=1;
    for(re int i=las[cur];i;i=suc[i])
        if(!dfn[des[i]]){
            dfs1(des[i]);
            low[cur]=min(low[cur],low[des[i]]);
        }
        else
            if(ex[des[i]])
                low[cur]=min(low[cur],dfn[des[i]]);
    if(low[cur]==dfn[cur]){
        vis[cur]=(st[st[0]]!=cur);
        for(;st[st[0]+1]!=cur;){
            int x=st[st[0]--];
            ex[x]=0;
            id[x]=cur;
            if(x!=cur){
                w[cur]+=w[x];
                v[cur]+=v[x];
                suc[fst[st[st[0]]]]=las[x];
            }
        }
    }
}

void dfs2(int cur){
    f[cur][size[cur]=w[cur]]=v[cur];
    for(re int i=las[cur];i;i=suc[i])
        if(id[des[i]]!=cur){
            dfs2(des[i]);
            for(re int j=w[cur];j<=size[cur];++j)
                for(re int k=0;k<=size[des[i]]&&j+k<=m;++k)
                    g[j+k]=max(g[j+k],f[cur][j]+f[des[i]][k]);
            size[cur]=min(size[cur]+size[des[i]],m);
            for(re int j=w[cur];j<=size[cur];++j){
                f[cur][j]=max(f[cur][j],g[j]);
                g[j]=0;
            }
        }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(w[i]);
    for(re int i=1;i<=n;++i)
        cltstream::read(v[i]);
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        connect(x,i);
    }
    for(re int i=1;i<=n;++i)
        if(!dfn[i])
            dfs1(i);
    for(re int i=0;i<=n;++i)
        if(id[i]==i&&vis[i]&&w[i]<=m){
            vis[i]=0;
            dfs2(i);
            for(re int j=0;j<=m;++j)
                for(re int k=0;k<=size[i]&&j+k<=m;++k)
                    g[j+k]=max(g[j+k],ans[j]+f[i][k]);
            for(re int j=0;j<=m;++j){
                ans[j]=max(ans[j],g[j]);
                g[j]=0;
            }
        }
    cltstream::write(ans[m],'\n');
    return 0;
}
