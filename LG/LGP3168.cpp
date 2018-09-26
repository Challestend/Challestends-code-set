#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define maxc 22
#define maxm 100000
#define abs(a) ((a)>=0?(a):(-(a)))
#define sign(a) ((a)>0?1:(a)<0?-1:0)

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

int m,n,vc;
long long ans=1;
std::pair<int,int> a[(maxm<<1)+1];
int lev[maxm+1];
long long sum[maxc*maxn+1];
int cnt[maxc*maxn+1],lc[maxc*maxn+1],rc[maxc*maxn+1],root[maxn+1];

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

void update0(int L,int x,int cur,int l,int r){
    if(l==r){
        sum[cur]+=x;
        ++cnt[cur];
    }
    else{
        int mid=(l+r)>>1;
        if(L<=mid)
            update0(L,x,lc[cur],l,mid);
        else
            update0(L,x,rc[cur],mid+1,r);
        sum[cur]=sum[lc[cur]]+sum[rc[cur]];
        cnt[cur]=cnt[lc[cur]]+cnt[rc[cur]];
    }
}

int update1(int L,int x,int cur,int l,int r){
    if(l==r){
        sum[++vc]=sum[cur]+x;
        cnt[vc]=cnt[cur]+1;
        return vc;
    }
    else{
        int mid=(l+r)>>1,p=++vc;
        if(L<=mid){
            lc[p]=update1(L,x,lc[cur],l,mid);
            rc[p]=rc[cur];
        }
        else{
            lc[p]=lc[cur];
            rc[p]=update1(L,x,rc[cur],mid+1,r);
        }
        sum[p]=sum[lc[p]]+sum[rc[p]];
        cnt[p]=cnt[lc[p]]+cnt[rc[p]];
        return p;
    }
}

long long getksum(int L,int k,int l,int r){
    long long res=0;
    for(;l<r;){
        int mid=(l+r)>>1,ln=cnt[lc[L]];
        if(k==ln)
            return res+sum[lc[L]];
        else
            if(k<ln){
                L=lc[L];
                r=mid;
            }
            else{
                res+=sum[lc[L]];
                k-=ln;
                L=rc[L];
                l=mid+1;
            }
    }
    return res+sum[L];
}

int main(){
    cltstream::read(m);
    cltstream::read(n);
    for(re int i=1;i<=m;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        a[(i<<1)-1]=std::make_pair(x,z);
        a[i<<1]=std::make_pair(y+1,-z);
        lev[i]=z;
    }
    std::sort(lev+1,lev+m+1);
    lev[0]=std::unique(lev+1,lev+m+1)-lev-1;
    for(re int i=1;i<=(m<<1);++i)
        a[i].second=sign(a[i].second)*(std::lower_bound(lev+1,lev+lev[0]+1,abs(a[i].second))-lev);
    std::sort(a+1,a+(m<<1)+1);
    root[0]=build(1,n);
    for(re int i=1;i<=(m<<1);++i)
        if(a[i].first<=n){
            int x=a[i].first,x0=a[i-1].first,y=a[i].second;
            if(x>x0)
                root[x]=update1(abs(y),sign(y)*lev[abs(y)],root[x0],1,n);
            else
                update0(abs(y),sign(y)*lev[abs(y)],root[x0],1,n);
        }
    for(re int i=1;i<=n;++i){
        int s,x,y,z,k;
        cltstream::read(s);
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        k=(1LL*x*ans+y)%z+1;
        ans=getksum(root[s],k,1,n);
        cltstream::write(ans);
        putchar(10);
    }
    return 0;
}
