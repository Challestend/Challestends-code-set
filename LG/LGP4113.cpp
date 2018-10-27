#include<cstdio>
#include<algorithm>
#define re register
#define maxn 2000000
#define maxm 2000000
#define maxval 2000000
#define id(a) ((a-1)/size)

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(oh==ot){
            fwrite(cltout,1,size,stdout);
            oh=cltout;
        }
        *oh++=c;
    }
    #undef size

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
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        if(text>=0)
            pc(text);
    }
}

int n,m,c,size;
int a[maxn+1],cnt[maxval+1],ans[maxm+1];
struct query{
    int id,ql,qr;
};
query q[maxm+1];

inline bool operator<(query p,query q){
    return id(p.ql)==id(q.ql)?id(p.ql)?p.qr>q.qr:p.qr<q.qr:p.ql<q.ql;
}

int main(){
    cltstream::read(n);
    cltstream::read(c);
    cltstream::read(m);
    for(;(size+1)*(size+1)<=m;++size);
    size=n/size;
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=m;++i){
        q[i].id=i;
        cltstream::read(q[i].ql);
        cltstream::read(q[i].qr);
    }
    std::sort(q+1,q+m+1);
    re int L=1,R=1;
    cnt[a[1]]=1;
    for(re int i=1;i<=m;++i){
        for(;L>q[i].ql;--L,cnt[0]+=(cnt[a[L]]==1),++cnt[a[L]]);
        for(;L<q[i].ql;cnt[0]-=(cnt[a[L]]==2),--cnt[a[L]],++L);
        for(;R<q[i].qr;++R,cnt[0]+=(cnt[a[R]]==1),++cnt[a[R]]);
        for(;R>q[i].qr;cnt[0]-=(cnt[a[R]]==2),--cnt[a[R]],--R);
        ans[q[i].id]=cnt[0];
    }
    for(re int i=1;i<=m;++i)
        cltstream::write(ans[i],10);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
