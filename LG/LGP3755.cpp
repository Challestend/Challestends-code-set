#include<cstdio>
#include<algorithm>
#define re register
#define PINF 2147483647
#define NINF int(-2147483648)
#define maxn 100000
#define maxc 20
#define pii std::pair<int,int>
#define ppi std::pair<pii,int>
#define mp(a,b) std::make_pair(a,b)

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

int n,m,vc;
ppi p[maxn+1];
int x[maxn+2],y[maxn+2];
long long sum[maxc*maxn+1],lc[maxc*maxn+1],rc[maxc*maxn+1];
int root[maxn+1];

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

long long getsum(int x1,int x2,int y1,int y2,int l,int r){
    if(l>=y1&&r<=y2)
        return sum[x2]-sum[x1];
    else{
        int mid=(l+r)>>1;
        long long res=0;
        if(y1<=mid)
            res+=getsum(lc[x1],lc[x2],y1,y2,l,mid);
        if(y2>mid)
            res+=getsum(rc[x1],rc[x2],y1,y2,mid+1,r);
        return res;
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(p[i].first.first);
        cltstream::read(p[i].first.second);
        cltstream::read(p[i].second);
        x[i]=p[i].first.first;
        y[i]=p[i].first.second;
    }
    std::sort(x+1,x+n+1);
    x[0]=std::unique(x+1,x+n+1)-x-1;
    std::sort(y+1,y+n+1);
    y[0]=std::unique(y+1,y+n+1)-y-1;
    for(re int i=1;i<=n;++i){
        p[i].first.first=std::lower_bound(x+1,x+x[0]+1,p[i].first.first)-x;
        p[i].first.second=std::lower_bound(y+1,y+y[0]+1,p[i].first.second)-y;
    }
    for(re int i=1;i<=x[0];++i)
        printf("%d ",x[i]);
    printf("\n");
    for(re int i=1;i<=y[0];++i)
        printf("%d ",y[i]);
    printf("\n");
    std::sort(p+1,p+n+1);
    root[0]=build(1,y[0]);
    for(re int i=1;i<=n;++i)
        root[i]=update(p[i].first.second,p[i].second,root[i-1],1,y[0]);
    for(re int i=1;i<=m;++i){
        int x1,y1,x2,y2;
        cltstream::read(x1);
        cltstream::read(y1);
        cltstream::read(x2);
        cltstream::read(y2);
        x1=std::lower_bound(x+1,x+x[0]+1,x1)-x;
        x1=std::lower_bound(p+1,p+n+1,mp(mp(x1,y1),NINF))-p;
        y1=std::lower_bound(y+1,y+y[0]+1,y1)-y;
        x2=std::upper_bound(x+1,x+x[0]+1,x2)-x-1;
        x2=std::upper_bound(p+1,p+n+1,mp(mp(x2,y2),PINF))-p-1;
        y2=std::upper_bound(y+1,y+y[0]+1,y2)-y-1;
        if(x1<=x2&&y1<=y2)
            cltstream::write(getsum(root[x1-1],root[x2],y1,y2,1,y[0]));
        else
            putchar(48);
        putchar(10);
    }
    return 0;
}
