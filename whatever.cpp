// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<cstdio>
#include<ctime>
#define re register
#define maxn 30000
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
    #define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout),cltstream::oh=cltstream::cltout
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
int f[maxn+1];

int main(){
    f[0]=1;
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        re unsigned long long x;
        cltstream::read(x);
        if(x==1)
            ++m;
        else{
            x=(x-2)%mod;
            for(re int j=i-m;j>=1;--j)
                f[j]=(f[j]+f[j-1]*x%mod)%mod;
        }
    }
    for(re int i=1;i<=(m<<1);++i)
        cltstream::write(0,32);
    for(re int i=0,j=1;i<=n-m;++i,j=2LL*j%mod)
        cltstream::write(1LL*j*f[n-m-i]%mod,32);
    for(re int i=1;i<=n-m;++i)
        cltstream::write(0,32);
    clop();
    // freopen("con","w",stdout);
    // printf("%d\n",clock());
    return 0;
}
