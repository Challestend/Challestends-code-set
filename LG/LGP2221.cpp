#include<cstdio>
#define re register
#define maxn 100000
#define sum(a) (1LL*(a)*((a)+1)/2)
#define sqrsum(a) (1LL*(a)*((a)+1)*(2*(a)+1)/6)

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=10*x+(c^48),c=getchar());
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
long long A[(maxn<<2)+1],B[(maxn<<2)+1],C[(maxn<<2)+1],add[(maxn<<2)+1];

inline void pushDown(int cur,int l,int r){
    int mid=(l+r)>>1;
    A[cur<<1]+=1LL*(mid-l+1)*add[cur];
    B[cur<<1]+=(sum(mid)-sum(l-1))*add[cur];
    C[cur<<1]+=(sqrsum(mid)-sqrsum(l-1))*add[cur];
    A[cur<<1|1]+=1LL*(r-mid)*add[cur];
    B[cur<<1|1]+=(sum(r)-sum(mid))*add[cur];
    C[cur<<1|1]+=(sqrsum(r)-sqrsum(mid))*add[cur];
    add[cur]=0;
}

inline void pushUp(int cur){
    A[cur]=A[cur<<1]+A[cur<<1|1];
    B[cur]=B[cur<<1]+B[cur<<1|1];
    C[cur]=C[cur<<1]+C[cur<<1|1];
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        A[cur]+=1LL*(r-l+1)*x;
        B[cur]+=(sum(r)-sum(l-1))*x;
        C[cur]+=(sqrsum(r)-sqrsum(l-1))*x;
        add[cur]+=x;
    }
    else{
        pushDown(cur,l,r);
        int mid=(l+r)>>1;
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        pushUp(cur);
    }
}

long long getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return 1LL*(1-L)*(R+1)*A[cur]+1LL*(L+R)*B[cur]-C[cur];
    else{
        pushDown(cur,l,r);
        int mid=(l+r)>>1;
        long long res=0;
        if(L<=mid)
            res+=getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}

int main(){
    cltstream::read(n),cltstream::read(m);
    for(int i=1;i<=m;++i){
        char opt=getchar();
        for(;opt!='C'&&opt!='Q';opt=getchar());
        int x,y,z;
        if(opt=='C'){
            cltstream::read(x),cltstream::read(y),cltstream::read(z);
            update(x,y-1,z,1,1,n);
        }
        else{
            cltstream::read(x),cltstream::read(y);
            long long a=getsum(x,y-1,1,1,n),b=1LL*(y-x)*(y-x+1)/2,g=gcd(a,b);
            cltstream::write(a/g),putchar('/'),cltstream::write(b/g),putchar(10);
        }
    }
    return 0;
}
