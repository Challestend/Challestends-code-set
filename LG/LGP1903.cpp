#include<cstdio>
#include<algorithm>
#define re register
#define maxn 50000
#define maxm 50000
#define maxv 1000000
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

int n,m,uc,qc,size,L=1,R=1,T;
int a[maxn+1],upd[maxm+1][2],cnt[maxv+1],ans[maxm+1];
struct Query{
    int id,ql,qr,qt;
};
Query Q[maxm+1];

inline bool cmp(Query p,Query q){
    if(id(p.ql)!=id(q.ql))
        return p.ql<q.ql;
    else
        if(p.qr!=q.qr)
            return p.qr<q.qr;
        else
            return p.qt<q.qt;
}

inline void swap(int& p,int& q){
    int tmp=p;
    p=q;
    q=tmp;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=m;++i){
        char opt=getchar();
        for(;opt!='Q'&&opt!='R';opt=getchar());
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        if(opt=='Q'){
            ++qc;
            Q[qc].id=qc;
            Q[qc].ql=x;
            Q[qc].qr=y;
            Q[qc].qt=uc;
        }
        else{
            ++uc;
            upd[uc][0]=x;
            upd[uc][1]=y;
        }
    }
    for(;size*size+2*size+1<=n;++size);
    size*=15;
    std::sort(Q+1,Q+qc+1,cmp);
    cnt[0]=cnt[a[1]]=1;
    for(re int i=1;i<=qc;++i){
        for(;T<Q[i].qt;){
            ++T;
            cnt[0]-=(cnt[a[upd[T][0]]]==1);
            --cnt[a[upd[T][0]]];
            cnt[0]+=(cnt[upd[T][1]]==0);
            ++cnt[upd[T][1]];
            swap(a[upd[T][0]],upd[T][1]);
        }
        for(;T>Q[i].qt;){
            cnt[0]-=(cnt[a[upd[T][0]]]==1);
            --cnt[a[upd[T][0]]];
            cnt[0]+=(cnt[upd[T][1]]==0);
            ++cnt[upd[T][1]];
            swap(a[upd[T][0]],upd[T][1]);
            --T;
        }
        for(;R<Q[i].qr;++R,cnt[0]+=(cnt[a[R]]==0),++cnt[a[R]]);
        for(;R>Q[i].qr;cnt[0]-=(cnt[a[R]]==1),--cnt[a[R]],--R);
        for(;L<Q[i].ql;cnt[0]-=(cnt[a[L]]==1),--cnt[a[L]],++L);
        for(;L>Q[i].ql;--L,cnt[0]+=(cnt[a[L]]==0),++cnt[a[L]]);
        ans[Q[i].id]=cnt[0];
    }
    for(re int i=1;i<=qc;++i){
        cltstream::write(ans[i]);
        putchar(10);
    }
    return 0;
}
