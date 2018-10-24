#include<cstdio>
#define re register
#define maxn 1000000
#define maxm 1000000
#define mod 998244353
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

int n,m,ec,vc,head,tail;
int src[maxm+1],des[maxm+1],len[maxm+1],suc[maxm+1],las[maxn+1],ind[maxn+1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],ex[maxn+1],id[maxn+1];
int h[maxn+1],maxl[maxn+1],nxt[maxn+1],inf[maxn+1],ans[maxn+1];

inline void connect(int x,int y,int z){
    src[++ec]=x;
    des[ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur){
    dfn[cur]=low[cur]=++vc;
    st[++st[0]]=cur;
    ex[cur]=1;
    for(re int i=las[cur];i;i=suc[i])
        if(!dfn[des[i]]){
            dfs(des[i]);
            low[cur]=min(low[cur],low[des[i]]);
        }
        else
            if(ex[des[i]])
                low[cur]=min(low[cur],dfn[des[i]]);
    if(low[cur]==dfn[cur]){
        inf[cur]=(st[st[0]]!=cur);
        for(;st[st[0]+1]!=cur;){
            int x=st[st[0]--];
            ex[x]=0;
            id[x]=cur;
            inf[x]=inf[cur];
        }
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        connect(y,x,z);
        ++ind[x];
    }
    for(re int i=1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    for(re int i=1;i<=n;++i)
        if(!ind[i])
            h[++tail]=i;
        else
            maxl[i]=-1;
    for(;head<tail;){
        int x=h[++head];
        ans[x]=(29LL*ans[src[nxt[x]]]%mod+len[nxt[x]])%mod;
        for(re int i=las[x];i;i=suc[i]){
            if(maxl[des[i]]<maxl[x]+1||(maxl[des[i]]==maxl[x]+1&&len[nxt[des[i]]]>len[i])){
                maxl[des[i]]=maxl[x]+1;
                nxt[des[i]]=i;
            }
            inf[des[i]]|=inf[x];
            if(!(--ind[des[i]]))
                h[++tail]=des[i];
        }
    }
    for(re int i=1;i<=n;++i)
        if(inf[i]||maxl[i]<0)
            puts("Infinity");
        else
            cltstream::write(29LL*ans[i]%mod,'\n');
    return 0;
}
