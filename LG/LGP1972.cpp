#include<cstdio>
#include<algorithm>
#define re register
#define maxn 500000
#define maxm 500000
#define maxv 1000001
#define id(a) ((a-1)/size)

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

int n,m,size,L=1,R=1;
int a[maxn+1],cnt[maxv+1],ans[maxm+1];
struct query{
    int id,l,r;
};
query Q[maxm+1];

inline bool cmp(query p,query q){
    return (id(p.l)==id(q.l))?p.r<q.r:p.l<q.l;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++a[i],++i)
        cltstream::read(a[i]);
    cltstream::read(m);
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;i<=m;++i){
        Q[i].id=i;
        cltstream::read(Q[i].l);
        cltstream::read(Q[i].r);
    }
    std::sort(Q+1,Q+m+1,cmp);
    cnt[0]=cnt[a[1]]=1;
    for(re int i=1;i<=m;++i){
        for(;R<Q[i].r;++R,cnt[0]+=(cnt[a[R]]==0),++cnt[a[R]]);
        for(;R>Q[i].r;cnt[0]-=(cnt[a[R]]==1),--cnt[a[R]],--R);
        for(;L<Q[i].l;cnt[0]-=(cnt[a[L]]==1),--cnt[a[L]],++L);
        for(;L>Q[i].l;--L,cnt[0]+=(cnt[a[L]]==0),++cnt[a[L]]);
        ans[Q[i].id]=cnt[0];
    }
    for(re int i=1;i<=m;++i){
        cltstream::write(ans[i]);
        putchar(10);
    }
    return 0;
}
