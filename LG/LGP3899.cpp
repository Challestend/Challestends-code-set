#include<cstdio>
#define re register
#define maxn 300000
#define maxc 24
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

int n,q,ec,vc;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int dep[maxn+1],size[maxn+1],id[maxn+1];
int root[maxn+1],lc[maxc*maxn+1],rc[maxc*maxn+1];
long long sum[maxc*maxn+1];

int build(int l,int r){
    if(l==r)
        return ++vc;
    else{
        int mid=(l+r)>>1,p=++vc;
        lc[p]=build(l,mid);
        rc[p]=build(mid+1,r);
        return p;
    }
}

int update(int L,int x,int cur,int l,int r){
    if(l==r){
        sum[++vc]=sum[cur]+x;
        return vc;
    }
    else{
        int mid=(l+r)>>1,p=++vc;
        if(L<=mid){
            lc[p]=update(L,x,lc[cur],l,mid);
            rc[p]=rc[cur];
        }
        else{
            lc[p]=lc[cur];
            rc[p]=update(L,x,rc[cur],mid+1,r);
        }
        sum[p]=sum[lc[p]]+sum[rc[p]];
        return p;
    }
}

long long getsum(int L,int R,int k,int l,int r){
    long long res=0;
    for(;l<r;){
        int mid=(l+r)>>1;
        if(k==mid)
            return res+sum[lc[R]]-sum[lc[L]];
        else
            if(k<mid){
                L=lc[L];
                R=lc[R];
                r=mid;
            }
            else{
                res+=sum[lc[R]]-sum[lc[L]];
                L=rc[L];
                R=rc[R];
                l=mid+1;
            }
    }
    return res;
}

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(int cur,int ftr){
    dep[cur]=dep[ftr]+1;
    size[cur]=1;
    id[cur]=++id[0];
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr){
            dfs1(des[i],cur);
            size[cur]+=size[des[i]];
        }
}

void dfs2(int cur,int ftr){
    root[id[cur]]=update(dep[cur],size[cur]-1,root[id[cur]-1],1,n);
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr)
            dfs2(des[i],cur);
}

int main(){
    cltstream::read(n);
    cltstream::read(q);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    root[0]=build(1,n);
    dfs1(1,0);
    dfs2(1,0);
    for(re int i=1;i<=q;++i){
        int x,k;
        cltstream::read(x);
        cltstream::read(k);
        long long ans=1LL*min(dep[x]-1,k)*(size[x]-1)+getsum(root[id[x]],root[id[x]+size[x]-1],dep[x]+k,1,n);
        cltstream::write(ans);
        putchar(10);
    }
    return 0;
}
