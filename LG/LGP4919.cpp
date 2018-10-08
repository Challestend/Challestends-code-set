#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000000
#define maxm 1000000
#define maxsize 1000
#define maxval 1000000
#define block(a) (((a)-1)/size)

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

int n,m,k,size;
int a[maxn+1],sum[maxval+1],cnt[maxval+1],ans[maxm+1];
struct query{
    int id,ql,qr;
};
query q[maxm+1];

inline bool cmp(query _p,query _q){
    return block(_p.ql)==block(_q.ql)?(block(_p.ql)&1)?_p.qr>_q.qr:_p.qr<_q.qr:_p.ql<_q.ql;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        ++sum[a[i]];
    }
    for(re int i=1;i<=m;++i){
        q[i].id=i;
        cltstream::read(q[i].ql);
        cltstream::read(q[i].qr);
    }
    for(;(size+1)*(size+1)<=m;++size);
    size=n/size;
    std::sort(q+1,q+m+1,cmp);
    int L=1,R=1;
    cnt[a[1]]=1;
    ans[0]=((cnt[a[1]]<<1)>=sum[a[1]]-k&&(cnt[a[1]]<<1)<=sum[a[1]]+k);
    for(re int i=1;i<=m;++i){
        for(;R<q[i].qr;){
            ++R;
            ans[0]-=((cnt[a[R]]<<1)>=sum[a[R]]-k&&(cnt[a[R]]<<1)<=sum[a[R]]+k&&cnt[a[R]]);
            ++cnt[a[R]];
            ans[0]+=((cnt[a[R]]<<1)>=sum[a[R]]-k&&(cnt[a[R]]<<1)<=sum[a[R]]+k);
        }
        for(;R>q[i].qr;){
            ans[0]-=((cnt[a[R]]<<1)>=sum[a[R]]-k&&(cnt[a[R]]<<1)<=sum[a[R]]+k);
            --cnt[a[R]];
            ans[0]+=((cnt[a[R]]<<1)>=sum[a[R]]-k&&(cnt[a[R]]<<1)<=sum[a[R]]+k&&cnt[a[R]]);
            --R;
        }
        for(;L>q[i].ql;){
            --L;
            ans[0]-=((cnt[a[L]]<<1)>=sum[a[L]]-k&&(cnt[a[L]]<<1)<=sum[a[L]]+k&&cnt[a[L]]);
            ++cnt[a[L]];
            ans[0]+=((cnt[a[L]]<<1)>=sum[a[L]]-k&&(cnt[a[L]]<<1)<=sum[a[L]]+k);
        }
        for(;L<q[i].ql;){
            ans[0]-=((cnt[a[L]]<<1)>=sum[a[L]]-k&&(cnt[a[L]]<<1)<=sum[a[L]]+k);
            --cnt[a[L]];
            ans[0]+=((cnt[a[L]]<<1)>=sum[a[L]]-k&&(cnt[a[L]]<<1)<=sum[a[L]]+k&&cnt[a[L]]);
            ++L;
        }
        ans[q[i].id]=ans[0];
    }
    for(re int i=1;i<=m;++i){
        cltstream::write(ans[i]);
        putchar(10);
    }
    return 0;
}
