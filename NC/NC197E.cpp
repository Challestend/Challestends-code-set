#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 300000
#define maxm 300000
#define min(a,b) ((a)<=(b)?(a):(b))

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
std::string s;
int lc[(maxn<<2)+1],rc[(maxn<<2)+1],mc[(maxn<<2)+1],sum[(maxn<<2)+1];

inline void pushUp(int cur,int ln,int rn){
    lc[cur]=lc[cur<<1]+(lc[cur<<1]==ln)*lc[cur<<1|1];
    rc[cur]=rc[cur<<1|1]+(rc[cur<<1|1]==rn)*rc[cur<<1];
    mc[cur]=mc[cur<<1]+mc[cur<<1|1];
    sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    if(rc[cur<<1]&&lc[cur<<1|1]){
        --mc[cur];
        sum[cur]-=(rc[cur<<1]<=(ln>>1))*rc[cur<<1];
        sum[cur]-=(lc[cur<<1|1]<=(rn>>1))*lc[cur<<1|1];
    }
}

void update(int L,int x,int cur,int l,int r){
    if(l==r)
        lc[cur]=rc[cur]=mc[cur]=sum[cur]=x;
    else{
        int mid=(l+r)>>1;
        if(L<=mid)
            update(L,x,cur<<1,l,mid);
        else
            update(L,x,cur<<1|1,mid+1,r);
        pushUp(cur,mid-l+1,r-mid);
    }
}

void getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R){
        mc[0]=mc[0]+mc[cur];
        sum[0]+=sum[cur];
        if(rc[0]&&lc[cur]){
            --mc[0];
            sum[0]-=(rc[0]<=((l-L)>>1))*rc[0];
            sum[0]-=(lc[cur]<=((r-l+1)>>1))*lc[cur];
        }
        lc[0]+=(lc[0]==l-L)*lc[cur];
        rc[0]=rc[cur]+(rc[0]==l-L)*rc[0];
    }
    else{
        int mid=(l+r)>>1;
        if(L<=mid)
            getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            getsum(L,R,cur<<1|1,mid+1,r);
    }
}

void check(int cur,int l,int r){
    if(l==r)
        return;
    else{
        int mid=(l+r)>>1;
        check(cur<<1,l,mid);
        check(cur<<1|1,mid+1,r);
        printf("[%d,%d]=(%d,%d,%d,%d)\n",l,r,lc[cur],mc[cur],rc[cur],sum[cur]);
    }
}

int main(){
    cltstream::read(n);
    std::cin>>s;
    for(re int i=1;i<=n;++i)
        update(i,s[i-1]^48,1,1,n);
    cltstream::read(m);
    for(re int i=1;i<=m;++i){
        int opt,x,y;
        cltstream::read(opt);
        cltstream::read(x);
        cltstream::read(y);
        if(opt==1){
            lc[0]=rc[0]=mc[0]=0;
            getsum(x,y,1,1,n);
            cltstream::write((mc[0]<<1)-sum[0]);
            putchar(10);
        }
        else
            update(x,y,1,1,n);
        check(1,1,n);
        putchar(10);
    }
    return 0;
}
