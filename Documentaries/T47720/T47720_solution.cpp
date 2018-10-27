#include<cstdio>
#define re register
#define maxt 1000000
#define maxn 1000000
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

int t,n,m,ans;
int inv[maxn+1]={0,1};

int main(){
    for(re int i=2;i<=maxn;++i)
        inv[i]=(-1LL*(mod/i)*inv[mod%i]%mod+mod)%mod;
    for(re int i=maxn;i>=2;--i)
        inv[i]=1LL*inv[i]*inv[i-1]%mod;
    cltstream::read(t);
    for(re int i=1;i<=t;++i){
        cltstream::read(n);
        cltstream::read(m);
        if(n==1)
            cltstream::write(m==1?1:0,'\n');
        else
            if(n==2)
                cltstream::write(m==1?3LL*inv[2]%mod:0,'\n');
            else{
                ans=1LL*(n+1)*m%mod;
                ans=1LL*ans*(n-m)%mod;
                ans=1LL*ans*(n-m+1)%mod;
                ans=1LL*ans*inv[2]%mod;
                ans=1LL*ans*inv[n]%mod;
                cltstream::write(ans,'\n');
            }
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
