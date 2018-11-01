#include<cstdio>
#define re register
#define maxn 50000
#define maxc 20
#define mod 19940417
#define min(a,b) ((a)<=(b)?(a):(b))
#define FILE(filename) freopen(filename".in","r",stdin);freopen(filename".out","w",stdout)

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
    inline void write(_tp x,char text=-1){
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

int n,m;
int C[maxn+1][maxc+1],u[maxc+1]={1},v[maxc+1]={1};
struct node{
    int f[maxc+1],add,neg;

    inline node(){
        for(re int i=0;i<=maxc;f[i]=0,++i);
        add=neg=0;
    }
};
node a[(maxn<<2)+1],ans;

inline node operator+(re node& x,re node& y){
    re node z;
    for(re int i=0;i<=maxc;++i)
        for(re int j=0;i+j<=maxc;++j)
            z.f[i+j]=(1LL*z.f[i+j]+1LL*x.f[i]*y.f[j]%mod)%mod;
    return z;
}

void build(re int cur,re int l,re int r){
    if(l==r){
        a[cur].f[0]=1;
        cltstream::read(a[cur].f[1]);
        a[cur].f[1]=(a[cur].f[1]%mod+mod)%mod;
    }
    else{
        re int mid=(l+r)>>1;
        build(cur<<1,l,mid);
        build(cur<<1|1,mid+1,r);
        a[cur]=a[cur<<1]+a[cur<<1|1];
    }
}

inline void pushDown(re int cur,re int ln,re int rn){
    if(a[cur].neg){
        for(re int i=1;i<=ln&&i<=maxc;i+=2)
            a[cur<<1].f[i]=(mod-a[cur<<1].f[i])%mod;
        a[cur<<1].add=(mod-a[cur<<1].add)%mod;
        a[cur<<1].neg^=1;
        for(re int i=1;i<=rn&&i<=maxc;i+=2)
            a[cur<<1|1].f[i]=(mod-a[cur<<1|1].f[i])%mod;
        a[cur<<1|1].add=(mod-a[cur<<1|1].add)%mod;
        a[cur<<1|1].neg^=1;
        a[cur].neg=0;
    }
    if(a[cur].add){
        for(re int i=1;i<=maxc;v[i]=1LL*v[i-1]*a[cur].add%mod,++i);
        for(re int i=min(ln,maxc);i>=1;--i)
            for(re int j=0;j<i;++j)
                a[cur<<1].f[i]=(1LL*a[cur<<1].f[i]+1LL*C[ln-j][i-j]*a[cur<<1].f[j]%mod*v[i-j]%mod)%mod;
        a[cur<<1].add=(a[cur<<1].add+a[cur].add)%mod;
        for(re int i=min(rn,maxc);i>=1;--i)
            for(re int j=0;j<i;++j)
                a[cur<<1|1].f[i]=(1LL*a[cur<<1|1].f[i]+1LL*C[rn-j][i-j]*a[cur<<1|1].f[j]%mod*v[i-j]%mod)%mod;
        a[cur<<1|1].add=(a[cur<<1|1].add+a[cur].add)%mod;
        a[cur].add=0;
    }
}

void IntervalAdd(re int L,re int R,re int cur,re int l,re int r){
    if(l>=L&&r<=R){
        for(re int i=min(r-l+1,maxc);i>=1;--i)
            for(re int j=0;j<i;++j)
                a[cur].f[i]=(1LL*a[cur].f[i]+1LL*C[r-l+1-j][i-j]*a[cur].f[j]%mod*u[i-j]%mod)%mod;
        a[cur].add=(a[cur].add+u[1])%mod;
    }
    else{
        re int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            IntervalAdd(L,R,cur<<1,l,mid);
        if(R>mid)
            IntervalAdd(L,R,cur<<1|1,mid+1,r);
        a[cur]=a[cur<<1]+a[cur<<1|1];
    }
}

void IntervalNeg(re int L,re int R,re int cur,re int l,re int r){
    if(l>=L&&r<=R){
        for(re int i=1;i<=r-l+1&&i<=maxc;i+=2)
            a[cur].f[i]=(mod-a[cur].f[i])%mod;
        a[cur].add=(mod-a[cur].add)%mod;
        a[cur].neg^=1;
    }
    else{
        re int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            IntervalNeg(L,R,cur<<1,l,mid);
        if(R>mid)
            IntervalNeg(L,R,cur<<1|1,mid+1,r);
        a[cur]=a[cur<<1]+a[cur<<1|1];
    }
}

void IntervalChoose(re int L,re int R,re int cur,re int l,re int r){
    if(l>=L&&r<=R){
        if(l==L)
            ans=a[cur];
        else
            ans=ans+a[cur];
    }
    else{
        re int mid=(l+r)>>1;
        pushDown(cur,mid-l+1,r-mid);
        if(L<=mid)
            IntervalChoose(L,R,cur<<1,l,mid);
        if(R>mid)
            IntervalChoose(L,R,cur<<1|1,mid+1,r);
    }
}

int main(){
    // FILE("LGP4247");
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=0;i<=n;++i){
        C[i][0]=C[i][i]=1;
        for(re int j=1;j<i&&j<=maxc;++j)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    build(1,1,n);
    for(re int i=1;i<=m;++i){
        re char opt=cltstream::gc();
        for(;opt<'A'||opt>'Z';opt=cltstream::gc());
        re int l,r,x;
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 'I':
                cltstream::read(x);
                x=(x%mod+mod)%mod;
                for(re int j=1;j<=r-l+1&&j<=maxc;u[j]=1LL*u[j-1]*x%mod,++j);
                IntervalAdd(l,r,1,1,n);
                break;
            case 'R':
                IntervalNeg(l,r,1,1,n);
                break;
            case 'Q':
                cltstream::read(x);
                IntervalChoose(l,r,1,1,n);
                cltstream::write(ans.f[x],10);
                break;
        }
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
