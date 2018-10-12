#include<cstdio>
#define re register
#define maxn 100000
#define maxm 500000
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #define LOCAL
    #ifdef LOCAL
        #define gc getchar
    #else
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

int n,m,k,ec,cnt;
int src[(maxm<<1)+1],des[(maxn<<1)+1],col[(maxm<<1)+1],suc[(maxm<<1)+1];
int dfn[maxn+1],low[maxn+1],las[maxn+1],st[maxn+2],f[maxn+1],ufs[maxn+1];

inline void connect(int x,int y,int z){
    src[++ec]=x;
    des[ec]=y;
    col[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs(int cur,int ftr){
    dfn[cur]=low[cur]=++dfn[0];
    st[++st[0]]=cur;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            if(!dfn[des[i]]){
                dfs(des[i],cur);
                low[cur]=min(low[cur],low[des[i]]);
            }
            else
                low[cur]=min(low[cur],dfn[des[i]]);
        }
    if(low[cur]==dfn[cur])
        for(;st[st[0]+1]!=cur;f[st[st[0]--]]=cur,++f[0]);
}

inline int find(int x){
    if(ufs[x]!=x)
        ufs[x]=find(ufs[x]);
    return ufs[x];
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        connect(x,y,z);
        connect(y,x,z);
    }
    dfs(1,0);
    if(f[0]<n){
        printf("no solution");
        return 0;
    }
    for(re int i=1;i<=n;++i)
        ufs[i]=i;
    for(re int i=1;i<=ec;i+=2)
        if(!col[i]&&f[src[i]]!=f[des[i]]){
            ufs[find(src[i])]=find(des[i]);
            suc[i]=-1;
            ++cnt;
        }
    for(re int i=1;i<=ec&&cnt<k;i+=2)
        if(!col[i]&&find(src[i])!=find(des[i])){
            ufs[ufs[src[i]]]=ufs[des[i]];
            suc[i]=-1;
            ++cnt;
        }
    if(cnt!=k){
        printf("no solution");
        return 0;
    }
    for(re int i=1;i<=ec&&cnt<n-1;i+=2)
        if(col[i]&&find(src[i])!=find(des[i])){
            ufs[ufs[src[i]]]=ufs[des[i]];
            suc[i]=-1;
            ++cnt;
        }
    for(re int i=1;i<=ec;i+=2)
        if(suc[i]==-1){
            cltstream::write(src[i]);
            cltstream::write(des[i]);
            cltstream::write(col[i],'\n');
        }
    return 0;
}
