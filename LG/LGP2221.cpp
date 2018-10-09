#include<cstdio>
#define re register
#define maxn 100000
#define sum(a) (1LL*(a)*((a)+1)/2)
#define sqrsum(a) (1LL*(a)*((a)+1)*((a)*2+1)/6)

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
int A[(maxn<<2)+1],B[(maxn<<2)+1],add[(maxn<<2)+1];

inline void pushDown(int cur,int l,int r){
    int mid=(l+r)>>1;
    A[cur<<1]+=(sum(mid)-sum(l-1))*add[cur];
    B[cur<<1]+=(sqrsum(mid)-sqrsum(l-1))*add[cur];
    A[cur<<1|1]+=(sum(r)-sum(mid))*add[cur];
    B[cur<<1|1]+=(sqrsum(r)-sqrsum(mid))*add[cur];
    add[cur]=0;
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        A[cur]+=(sum(r)-sum(l-1))*x;
        B[cur]+=(sqrsum(r)-sqrsum(l-1))*x;
        add[cur]+=x;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,l,r);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        A[cur]=A[cur<<1]+A[cur<<1|1];
        B[cur]=B[cur<<1]+B[cur<<1|1];
    }
}

long long getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return 1LL*(R+1)*A[cur]-B[cur];
    else{
        int mid=(l+r)>>1;
        long long res=0;
        pushDown(cur,l,r);
        if(L<=mid)
            res+=getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

long long gcd(long long x,long long y){
    return y?gcd(y,x%y):x;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    --n;
    for(re int i=1;i<=m;++i){
        char opt=getchar();
        for(;opt!='C'&&opt!='Q';opt=getchar());
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        --y;
        if(opt=='C'){
            cltstream::read(z);
            update(x,y,z,1,1,n);
        }
        else{
            long long ans1=getsum(x,y,1,1,n),ans2=1LL*(y-x+1)*(y-x+2)>>1,g=gcd(ans1,ans2);
            cltstream::write(ans1);
            putchar('/');
            cltstream::write(ans2);
            putchar(10);
        }
    }
    return 0;
}
