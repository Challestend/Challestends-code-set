#include<cstdio>
#include<ctime>
#include"F:\clt\Random Data Generators\cltrnd.h"
#define re register
#define min(a,b) ((a)<=(b)?(a):(b))

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

// int n=10,m=10,maxval=201,clt=(maxval-1)>>1;
// int n=5,m=5,maxval=10,clt=0;
int n=10000,m=10000,maxval=2000000001,clt=(maxval-1)>>1;

int main(){
    freopen("LGP4247.in","w",stdout);
    cltrnd::srnd(time(0));
    cltstream::write(n,32);
    cltstream::write(m,10);
    for(re int i=1;i<=n;++i)
        cltstream::write((int)(cltrnd::rnd()%maxval)-clt,i<n?32:10);
    for(re int i=1;i<=m;++i){
        int opt=cltrnd::rnd()%3+1;
        int len=cltrnd::rnd()%n+1,l=cltrnd::rnd()%(n-len+1)+1,r=l+len-1;
        switch(opt){
            case 1:
                cltstream::pc('I');
                cltstream::pc(32);
                cltstream::write(l,32);
                cltstream::write(r,32);
                cltstream::write((int)(cltrnd::rnd()%maxval)-clt,10);
                break;
            case 2:
                // cltstream::pc('R');
                // cltstream::pc(32);
                // cltstream::write(l,32);
                // cltstream::write(r,10);
                // break;
            case 3:
                cltstream::pc('Q');
                cltstream::pc(32);
                cltstream::write(l,32);
                cltstream::write(r,32);
                cltstream::write(cltrnd::rnd()%min(r-l+1,20)+1,10);
                break;
        }
    }
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
