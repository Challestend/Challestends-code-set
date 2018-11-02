#include<cstdio>
#define re register
#define maxn 1000000

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
int a[maxn+1];

int main(){
    cltstream::read(m);
    cltstream::read(n);
    for(re int i=1;i<=m;++i){
        int x,v;
        cltstream::read(x);
        cltstream::read(v);
        if(x-2*v+1>=1){
            --a[x-2*v+1];
            ++a[x+1];
            if(x-3*v+1>=1){
                ++a[x-3*v+1];
                --a[x-2*v+1];
            }
            else{
                ++a[1];
                --a[x-2*v+1];
            }
        }
        else{
            --a[1];
            ++a[x+1];
        }
        if(x+1<=n){
            ++a[x+1];
            if(x+2*v+1<=n){
                a[x+2*v+1]-=2;
                if(x+3*v+2<=n)
                    ++a[x+3*n+2];
            }
        }
    }
    for(re int i=1;i<=n;++i)
        cltstream::write(a[i],i<n?32:10);
    for(re int i=1;i<=n;++i)
        a[i]+=a[i-1];
    for(re int i=1;i<=n;++i)
        a[i]+=a[i-1];
    for(re int i=1;i<=n;++i)
        cltstream::write(a[i],i<n?32:10);
    fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
    return 0;
}
