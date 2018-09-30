#include<cstdio>
#define re register
#define maxn 100000

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
int a[maxn+1];
long long s,sum[(maxn<<2)+1],add[(maxn<<2)+1];

inline void pushDown(int cur,int ln,int rn){
    sum[cur<<1]+=add[cur]*ln;
    add[cur<<1]+=add[cur];
    sum[cur<<1|1]+=add[cur]*rn;
    add[cur<<1|1]+=add[cur];
    add[cur]=0;
}

void update(int L,int R,long long x,int cur,int l,int r){
    if(l>=L&&r<=R){
        sum[cur]+=x*(r-l+1);
        add[cur]+=x;
    }
    else{
        int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
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

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        s+=a[i];
        update(i,i,s,1,1,n);
    }
    for(re int i=1;i<=m;++i){
        char opt=getchar();
        for(;opt!='Q'&&opt!='M';opt=getchar());
        int x,y;
        cltstream::read(x);
        if(opt=='M'){
            cltstream::read(y);
            update(x,n,y-a[x],1,1,n);
            a[x]=y;
        }
        else{
            cltstream::write(getsum(1,x,1,1,n));
            putchar(10);
        }
    }
    return 0;
}
