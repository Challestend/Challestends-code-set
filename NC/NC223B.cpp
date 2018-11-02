#include<cstdio>
#define re register
#define mod 100000007

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

long long n;

int cltpow(int x,long long y){
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
    cltstream::write((((1LL*cltpow(2,2LL*n)+cltpow(2,n+1)+cltpow(2,n)-cltpow(3,n+1)-1))*cltpow(2,mod-2)%mod+mod)%mod);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
