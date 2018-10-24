#include<cstdio>
#include<algorithm>
#define re register
#define maxn 500000
#define maxm 500000
#define maxv 1000001
#define ID(a) ((a-1)/size)

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
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,size,L=1,R=1;
int a[maxn+1],cnt[maxv+1],ans[maxm+1];
struct query{
    int id,ql,qr;
};
query q[maxm+1];

inline bool operator<(query _p,query _q){
    return ID(_p.ql)==ID(_q.ql)?(ID(_p.ql)&1)?_p.qr>_q.qr:_p.qr<_q.qr:_p.ql<_q.ql;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++a[i],++i)
        cltstream::read(a[i]);
    cltstream::read(m);
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;i<=m;++i){
        q[i].id=i;
        cltstream::read(q[i].ql);
        cltstream::read(q[i].qr);
    }
    std::sort(q+1,q+m+1);
    cnt[0]=cnt[a[1]]=1;
    for(re int i=1;i<=m;++i){
        for(;R<q[i].qr;++R,cnt[0]+=(cnt[a[R]]==0),++cnt[a[R]]);
        for(;R>q[i].qr;cnt[0]-=(cnt[a[R]]==1),--cnt[a[R]],--R);
        for(;L<q[i].ql;cnt[0]-=(cnt[a[L]]==1),--cnt[a[L]],++L);
        for(;L>q[i].ql;--L,cnt[0]+=(cnt[a[L]]==0),++cnt[a[L]]);
        ans[q[i].id]=cnt[0];
    }
    for(re int i=1;i<=m;++i){
        cltstream::write(ans[i]);
        putchar(10);
    }
    return 0;
}
