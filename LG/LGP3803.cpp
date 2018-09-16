#include<cstdio>
#include<cmath>
#define re register
#define maxn 2097152

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=10*x+(c^48),c=getchar());
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

const double Pi=acos(-1.0);

int n,m;
struct complex{
    double r,c;

    complex(double x=0,double y=0){
        r=x;
        c=y;
    }
};
complex A[maxn+1],B[maxn+1];
int rev[maxn+1];

inline complex operator+(complex& a,complex& b){
    return complex(a.r+b.r,a.c+b.c);
}

inline complex operator-(complex& a,complex& b){
    return complex(a.r-b.r,a.c-b.c);
}

inline complex operator*(complex& a,complex& b){
    return complex(a.r*b.r-a.c*b.c,a.r*b.c+a.c*b.r);
}

inline void swap(complex& x,complex& y){
    complex tmp=x;
    x=y;
    y=tmp;
}

inline void FFT(complex f[],int tp){
    for(re int i=0;i<n;++i)
        if(i<rev[i])
            swap(f[i],f[rev[i]]);
    for(re int len=2,p=1;len<=n;len<<=1,p<<=1){
        re complex unit(cos(Pi/p),tp*sin(Pi/p));
        for(re int l=0;l<n;l+=len){
            re complex cur(1,0);
            for(re int i=l;i<l+p;++i){
                re complex tmp=f[i+p]*cur;
                f[i+p]=f[i]-tmp;
                f[i]=f[i]+tmp;
                cur=cur*unit;
            }
        }
    }
}

int main(){
    cltstream::read(n),cltstream::read(m);
    for(re int i=0;i<=n;++i)
        cltstream::read(A[i].r);
    for(re int i=0;i<=m;++i)
        cltstream::read(B[i].r);
    for(m+=n,n=1;n<=m;n<<=1);
    for(re int i=0;i<n;++i)
        rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0);
    FFT(A,1);
    FFT(B,1);
    for(re int i=0;i<n;++i)
        A[i]=A[i]*B[i];
    FFT(A,-1);
    for(re int i=0;i<=m;++i){
        cltstream::write(int(A[i].r/n+0.5));
        putchar(32);
    }
    return 0;
}
