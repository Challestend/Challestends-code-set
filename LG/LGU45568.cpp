#include<cstdio>
#include<algorithm>
#define re register
#define maxn 2000
#define maxm 2000
#define mod 998244353

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

int n,m,ans;
long long a[maxn+1],b[maxm+1],x[maxn*maxm+1];

int cltpow(int x,int y){
    if(y==1)
        return x;
    else{
        int res=cltpow(x,y>>1);
        res=1LL*res*res%mod;
        if(y&1)
            res=1LL*res*x%mod;
        return res;
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;a[i]+=a[i-1],++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=m;b[i]+=b[i-1],++i)
        cltstream::read(b[i]);
    for(re int i=1;i<=m;++i)
        for(re int j=i;j<=m;++j)
            x[++x[0]]=b[j]-b[i-1];
    std::sort(x+1,x+x[0]+1);
    for(re int i=1;i<=n;++i)
        for(re int j=i;j<=n;++j)
            ans=(1LL*ans+(std::lower_bound(x+1,x+x[0]+1,a[j]-a[i-1])-x-1))%mod;
    ans=1LL*ans*cltpow(n*(n+1)>>1,mod-2)%mod;
    ans=1LL*ans*cltpow(m*(m+1)>>1,mod-2)%mod;
    cltstream::write(ans);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
