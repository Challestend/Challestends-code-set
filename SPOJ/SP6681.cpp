#include<cstdio>
#include<algorithm>
#define re register
#define maxn 300000
#define maxm 100000
#define maxc 22

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

int n,m,vc;
std::pair<int,int> a[maxn+1];
int x0[maxn+1],y0[maxn+1];
int root[maxn+1],sum[maxc*maxn+1],lc[maxc*maxn+1],rc[maxc*maxn+1];

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

int update(int L,int cur,int l,int r){
    if(l==r){
        sum[++vc]=sum[cur]+1;
        return vc;
    }
    else{
        int mid=(l+r)>>1,p=++vc;
        if(L<=mid){
            lc[p]=update(L,lc[cur],l,mid);
            rc[p]=rc[cur];
        }
        else{
            lc[p]=lc[cur];
            rc[p]=update(L,rc[cur],mid+1,r);
        }
        sum[p]=sum[lc[p]]+sum[rc[p]];
        return p;
    }
}

int getsum(int L,int R,int curl,int curr,int l,int r){
    if(l>=L&&r<=R)
        return sum[curr]-sum[curl];
    else{
        int mid=(l+r)>>1,res=0;
        if(L<=mid)
            res+=getsum(L,R,lc[curl],lc[curr],l,mid);
        if(R>mid)
            res+=getsum(L,R,rc[curl],rc[curr],mid+1,r);
        return res;
    }
}

inline int query(int x1,int y1,int x2,int y2){
    x1=std::lower_bound(x0+1,x0+x0[0]+1,x1)-x0;
    x1=std::lower_bound(a+1,a+n+1,std::make_pair(x1,0))-a;
    y1=std::lower_bound(y0+1,y0+y0[0]+1,y1)-y0;
    x2=std::upper_bound(x0+1,x0+x0[0]+1,x2)-x0-1;
    x2=std::upper_bound(a+1,a+n+1,std::make_pair(x2,n+1))-a-1;
    y2=std::upper_bound(y0+1,y0+y0[0]+1,y2)-y0-1;
    return getsum(y1,y2,root[x1-1],root[x2],1,n);
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i].first);
        cltstream::read(a[i].second);
        x0[i]=a[i].first;
        y0[i]=a[i].second;
    }
    std::sort(x0+1,x0+n+1);
    x0[0]=std::unique(x0+1,x0+n+1)-x0-1;
    std::sort(y0+1,y0+n+1);
    y0[0]=std::unique(y0+1,y0+n+1)-y0-1;
    for(re int i=1;i<=n;++i){
        a[i].first=std::lower_bound(x0+1,x0+x0[0]+1,a[i].first)-x0;
        a[i].second=std::lower_bound(y0+1,y0+y0[0]+1,a[i].second)-y0;
    }
    std::sort(a+1,a+n+1);
    root[0]=build(1,n);
    for(re int i=1;i<=n;++i)
        root[i]=update(a[i].second,root[i-1],1,n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int x1,y1,x2,y2;
        cltstream::read(x1);
        cltstream::read(y1);
        cltstream::read(x2);
        cltstream::read(y2);
        cltstream::write(query(x1,y1,x2,y2)-query(x1+1,y1+1,x2-1,y2-1),'\n');
    }
    return 0;
}
