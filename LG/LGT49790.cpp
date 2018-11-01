#include<cstdio>
#include<cmath>
#define re register
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) max(a,-(a))

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

int t;

int main(){
    cltstream::read(t);
    for(re int i=1;i<=t;++i){
        long long a,b;
        cltstream::read(a);
        cltstream::read(b);
        long long sa=sqrt(a<<1),sb=sqrt(b<<1);
        if((sa*(sa+1)>>1)<a)
            ++sa;
        if((sb*(sb+1)>>1)<b)
            ++sb;
        long long maxs=max(sa,sb),mins=min(sa,sb);
        long long c=a-(sa*(sa-1)>>1),d=b-(sb*(sb-1)>>1);
        if(c<d){
            c=sa-c+1;
            d=sb-d+1;
        }
        long long e=abs(c-d),ans=mins*(mins-1)-(mins-e)*(mins-e-1);
        ans+=(maxs*(maxs-1)-mins*(mins-1))>>1;
        cltstream::write(ans,10);
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
