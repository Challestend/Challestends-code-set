#include<cstdio>
#include<algorithm>
#define il inline
#define re register
#define maxn 50000
#define maxm 50000
#define maxv 50000

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
int a[maxn+1],cnt[maxv+1],ans[maxm+1][2];
struct Query{
    int id,ql,qr;
};
Query Q[maxm+1];

il bool cmp(Query p,Query q){
    return (p.ql-1)/size==(q.ql-1)/size?p.qr<q.qr:p.ql<q.ql;
}

int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=m;++i){
        Q[i].id=i;
        cltstream::read(Q[i].ql);
        cltstream::read(Q[i].qr);
    }
    for(;size*size<=m;++size);
    size=(n-1)/size;
    std::sort(Q+1,Q+m+1,cmp);
    cnt[a[1]]=1;
    for(re int i=1;i<=m;++i)
        if(Q[i].ql<Q[i].qr){
            for(;R<Q[i].qr;++R,cnt[0]+=cnt[a[R]],++cnt[a[R]]);
            for(;R>Q[i].qr;cnt[0]-=cnt[a[R]]-1,--cnt[a[R]],--R);
            for(;L<Q[i].ql;cnt[0]-=cnt[a[L]]-1,--cnt[a[L]],++L);
            for(;L>Q[i].ql;--L,cnt[0]+=cnt[a[L]],++cnt[a[L]]);
            int sum=1LL*(Q[i].qr-Q[i].ql)*(Q[i].qr-Q[i].ql+1)>>1,g=gcd(cnt[0],sum);
            ans[Q[i].id][0]=cnt[0]/g;
            ans[Q[i].id][1]=sum/g;
        }
        else
            ans[Q[i].id][1]=1;
    for(re int i=1;i<=m;++i){
        cltstream::write(ans[i][0]);
        putchar('/');
        cltstream::write(ans[i][1]);
        putchar(10);
    }
    return 0;
}
