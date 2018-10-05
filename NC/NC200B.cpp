#include<cstdio>
#define re register
#define maxn 10000

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

int n,m;
long long sum[maxn<<2|1],sqr[maxn<<2|1],mul[maxn<<2|1],add[maxn<<2|1];

inline void pushDown(int cur,int ln,int rn){
    sqr[cur<<1]=mul[cur]*mul[cur]*sqr[cur<<1]+2*mul[cur]*add[cur]*sum[cur<<1]+1LL*ln*add[cur]*add[cur];
    sum[cur<<1]=mul[cur]*sum[cur<<1]+1LL*ln*add[cur];
    mul[cur<<1]*=mul[cur];
    add[cur<<1]*=mul[cur];
    add[cur<<1]+=add[cur];
    sqr[cur<<1|1]=mul[cur]*mul[cur]*sqr[cur<<1|1]+2*mul[cur]*add[cur]*sum[cur<<1|1]+1LL*rn*add[cur]*add[cur];
    sum[cur<<1|1]=mul[cur]*sum[cur<<1|1]+1LL*rn*add[cur];
    mul[cur<<1|1]*=mul[cur];
    add[cur<<1|1]*=mul[cur];
    add[cur<<1|1]+=add[cur];
    mul[cur]=1;
    add[cur]=0;
}

void update1(int L,int R,long long x,int cur,int l,int r){
    if(l>=L&&r<=R){
        sqr[cur]*=x*x;
        sum[cur]*=x;
        mul[cur]*=x;
        add[cur]*=x;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update1(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update1(L,R,x,cur<<1|1,mid+1,r);
        sqr[cur]=sqr[cur<<1]+sqr[cur<<1|1];
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
}

void update2(int L,int R,long long x,int cur,int l,int r){
    if(l>=L&&r<=R){
        sqr[cur]+=2*x*sum[cur]+1LL*(r-l+1)*x*x;
        sum[cur]+=1LL*(r-l+1)*x;
        add[cur]+=x;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update2(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update2(L,R,x,cur<<1|1,mid+1,r);
        sqr[cur]=sqr[cur<<1]+sqr[cur<<1|1];
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
}

long long getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return sum[cur];
    else{
        int mid=(l+r)>>1;
        long long res=0;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            res+=getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

long long getsqr(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return sqr[cur];
    else{
        int mid=(l+r)>>1;
        long long res=0;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            res+=getsqr(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsqr(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=(n<<1);mul[i]=1,++i);
    for(re int i=1;i<=n;++i){
        long long x;
        cltstream::read(x);
        update2(i,i,x,1,1,n);
    }
    for(re int i=1;i<=m;++i){
        int opt,l,r;
        long long x;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 1:
                cltstream::write(getsum(l,r,1,1,n));
                putchar(10);
                break;
            case 2:
                cltstream::write(getsqr(l,r,1,1,n));
                putchar(10);
                break;
            case 3:
                cltstream::read(x);
                update1(l,r,x,1,1,n);
                break;
            case 4:
                cltstream::read(x);
                update2(l,r,x,1,1,n);
                break;
        }
    }
    return 0;
}
