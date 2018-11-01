#include<cstdio>
#include<queue>
#define re register
#define maxn 100000
#define maxm 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(oh==ot){
            fwrite(cltout,1,size,stdout);
            oh=cltout;
        }
        *oh++=c;
    }
    #undef size

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
    inline void write(_tp x,char text=-1){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        if(text>=0)
            pc(text);
    }
}

int n,m,ec,vc,ans;
int des[(maxm<<1)+maxm+1],suc[(maxm<<1)+maxm+1],las[(maxn<<1)+1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],ex[maxn+1],id[(maxn<<1)+1],cnt[(maxn<<1)+1];
std::queue<int> h;
int dis[(maxn<<1)+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur){
    dfn[cur]=low[cur]=++vc;
    st[++st[0]]=cur;
    ex[cur]=1;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]<=n){
            if(!dfn[des[i]]){
                dfs(des[i]);
                low[cur]=min(low[cur],low[des[i]]);
            }
            else
                if(ex[des[i]])
                    low[cur]=min(low[cur],dfn[des[i]]);
        }
    if(low[cur]==dfn[cur])
        for(;st[st[0]+1]!=cur;){
            re int x=st[st[0]--];
            ex[x]=0;
            id[x]=cur;
            id[x+n]=cur;
            ++cnt[cur];
            ++cnt[cur+n];
        }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        re int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x+n);
        connect(x+n,y+n);
    }
    for(re int i=1;i<=n;++i)
        if(!dfn[i])
            dfs(i);
    dis[1]=1;
    h.push(1);
    for(;!h.empty();){
        int x=h.front();
        h.pop();
        if(x<=n)
            printf("dis[%d]=%d\n",x,dis[x]);
        else
            printf("dis(%d)=%d\n",x-n,dis[x]);
        for(re int i=las[x];i;i=suc[i])
            if(id[des[i]]!=id[x-1]){
                if(dis[des[i]]<dis[x]+cnt[id[des[i]]]){
                    dis[des[i]]=dis[x]+cnt[id[des[i]]];
                    h.push(des[i]);
                }
            }
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
