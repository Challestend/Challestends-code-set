#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 200000
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

int n,m,q,ec,vc;
int ord[maxn+1],tp[maxn+1];
struct edge{
    int src,des,cap,suc;
};
edge e[maxm+maxn+1];
int las[maxn+1],ufs[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],lw[maxn+1],id[maxn+1],top[maxn+1];
int minw[(maxn<<2)+1];

inline bool operator<(edge p,edge q){
    return p.cap>q.cap;
}

int find(int x){
    return ufs[x]==x?x:ufs[x]=find(ufs[x]);
}

void update(int L,int x,int cur,int l,int r){
    if(l==r)
        minw[cur]=x;
    else{
        int mid=(l+r)>>1;
        if(L<=mid)
            update(L,x,cur<<1,l,mid);
        else
            update(L,x,cur<<1|1,mid+1,r);
        minw[cur]=min(minw[cur<<1],minw[cur<<1|1]);
    }
}

int getmin(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return minw[cur];
    else{
        int mid=(l+r)>>1,res=2e9;
        if(L<=mid)
            res=min(res,getmin(L,R,cur<<1,l,mid));
        if(R>mid)
            res=min(res,getmin(L,R,cur<<1|1,mid+1,r));
        return res;
    }
}

void dfs1(int cur,int ftr){
    dep[cur]=dep[f[cur]=ftr]+1;
    size[cur]=1;
    int maxsize=0;
    for(re int i=las[cur];i;i=e[i].suc)
        if(e[i].des!=f[cur]){
            dfs1(e[i].des,cur);
            size[cur]+=size[e[i].des];
            if(maxsize<size[e[i].des]){
                maxsize=size[e[i].des];
                hes[cur]=e[i].des;
            }
            lw[e[i].des]=e[i].cap;
        }
}

void dfs2(int cur,int curtop){
    update(id[cur]=++vc,lw[cur],1,1,n);
    top[cur]=curtop;
    if(!hes[cur])
        return;
    dfs2(hes[cur],curtop);
    for(re int i=las[cur];i;i=e[i].suc)
        if(e[i].des!=f[cur]&&e[i].des!=hes[cur])
            dfs2(e[i].des,e[i].des);
}

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

inline int pthmin(int x,int y){
    int res=2e9;
    for(;top[x]!=top[y];){
        if(dep[top[x]]>dep[top[y]])
            swap(x,y);
        res=min(res,getmin(id[top[y]],id[y],1,1,n));
        y=f[top[y]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    return min(res,getmin(id[x]+1,id[y],1,1,n));
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(q);
    for(re int i=1;i<=n;++i)
        cltstream::read(ord[i]);
    for(re int i=1;i<=n;++i)
        cltstream::read(tp[i]);
    int x,y,z;
    for(re int i=1;i<=m;++i){
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        e[++ec].src=x;
        e[ec].des=y;
        e[ec].cap=z;
    }
    if(q)
        cltstream::read(x);
    for(re int i=2;i<=q;++i){
        cltstream::read(y);
        e[++ec].src=x;
        e[ec].des=y;
        e[ec].cap=2e9;
        x=y;
    }
    std::sort(e+1,e+ec+1);
    for(re int i=1;i<=n;++i)
        ufs[i]=i;
    ec=0;
    for(re int i=1;ec<n-1;++i)
        if(find(e[i].src)!=find(e[i].des)){
            e[++ec]=e[i];
            ufs[ufs[e[i].src]]=ufs[e[i].des];
        }
    for(re int i=1;i<=ec;++i){
        x=e[i].src,y=e[i].des,z=e[i].cap;
        e[i].suc=las[x];
        las[x]=i;
        e[ec+i].src=y;
        e[ec+i].des=x;
        e[ec+i].cap=z;
        e[ec+i].suc=las[y];
        las[y]=ec+i;
    }
    dfs1(1,0);
    dfs2(1,1);
    long long GoldCnt=max(tp[ord[1]],0);
    for(re int i=2;i<=n;++i){
        x=ord[i-1],y=ord[i];
        GoldCnt=min(GoldCnt,pthmin(x,y));
        if(tp[y]>0)
            GoldCnt+=tp[y];
        else{
            cltstream::write(min(GoldCnt,-tp[y]),'\n');
            GoldCnt-=min(GoldCnt,-tp[y]);
        }
    }
    return 0;
}
