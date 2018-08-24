#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100000
#define sum(a,b) (1LL*((b)-(a)+1)*((a)+(b))>>1)

int n,m;
long long val[maxn<<2|1],sum[maxn<<2|1];

inline void readInt(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void readLL(long long& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void write(long long x){
    char digit[20];
    if(x<0)
        putchar(45),x=-x;
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

void update(int L,long long x,int cur,int l,int r){
    if(l==r)
        val[cur]+=x,sum[cur]+=x;
    else{
        int mid=l+r>>1;
        if(L<=mid)
            update(L,x,cur<<1,l,mid);
        else
            update(L,x,cur<<1|1,mid+1,r);
        val[cur]=val[cur<<1]+val[cur<<1|1];
        sum[cur]=sum[cur<<1]+1LL*(mid-l+1)*(r-mid)*val[cur<<1]+sum[cur<<1|1];
    }
}

long long getsum(int L,int R,int cur,int l,int r){
    if(l>=L&&r<=R)
        return sum[cur]+1LL*(r-l+1)*(R-r)*val[cur];
    else{
        int mid=l+r>>1;
        long long res=0;
        if(L<=mid)
            res+=getsum(L,R,cur<<1,l,mid);
        if(R>mid)
            res+=getsum(L,R,cur<<1|1,mid+1,r);
        return res;
    }
}

int main(){
    readInt(n),readInt(m);
    for(re int i=1;i<=n;++i){
        long long x;
        readLL(x);
        update(i,x,1,1,n);
    }
    for(re int i=1;i<=m;++i){
        int opt,x,z;
        long long y;
        readInt(opt),readInt(x);
        if(opt==1)
            readLL(y),update(x,y,1,1,n);
        else
            readInt(z),write(getsum(x,z,1,1,n)),putchar(10);
    }
    return 0;
}
