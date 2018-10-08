#include<cstdio>
#define re register

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
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

long long n,m,p,s,w;
struct matrix{
    long long a[4][4];

    inline void init(){
        for(re int i=0;i<4;++i)
            for(re int j=0;j<4;++j)
                a[i][j]=0;
    }

    matrix(){
        init();
    }
};
matrix A,B;
long long u[4],v[4];

inline matrix operator*(matrix& _x,matrix& _y){
    matrix _z;
    for(re int i=0;i<4;++i)
        for(re int j=0;j<4;++j)
            for(re int k=0;k<4;++k)
                _z.a[i][j]=(_z.a[i][j]+_x.a[i][k]*_y.a[k][j]%p)%p;
    return _z;
}

void matpow(long long x){
    if(x==0){
        for(re int i=0;i<4;++i)
            B.a[i][i]=1;
        return;
    }
    if(x==1){
        B=A;
        return;
    }
    matpow(x>>1);
    B=B*B;
    if(x&1)
        B=B*A;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(p);
    cltstream::read(s);
    cltstream::read(w);
    if(!s)
        s=n;
    A.a[0][0]=(n-1)%p;
    A.a[0][1]=A.a[2][3]=(1-n+p)%p;
    A.a[1][0]=A.a[2][0]=A.a[3][2]=1;
    A.a[2][2]=p-1;
    u[0]=(n%p)*((n-1)%p)%p;
    u[1]=n%p;
    u[2]=(n-1)%p;
    u[3]=1;
    matpow(s-1);
    for(re int i=0;i<4;++i)
        for(re int j=0;j<4;++j)
            v[i]=(v[i]+B.a[i][j]*u[j]%p)%p;
    for(re int i=0;i<4;++i){
        u[i]=v[i];
        v[i]=0;
    }
    for(re int i=0;i<4;++i)
        printf("%lld ",u[i]);
    printf("\n");
    u[0]=((u[0]+(n-1)*(u[3]-u[1]))%p+p)%p;
    u[1]=u[3];
    for(re int i=0;i<4;++i)
        printf("%lld ",u[i]);
    printf("\n");
    B.init();
    matpow(n-s);
    for(re int i=0;i<4;++i){
        for(re int j=0;j<4;++j)
            printf("%lld ",B.a[i][j]);
        printf("\n");
    }
    printf("\n");
    for(re int i=0;i<4;++i)
        for(re int j=0;j<4;++j)
            v[i]=(v[i]+B.a[i][j]*u[j]%p)%p;
    for(re int i=0;i<4;++i){
        u[i]=v[i];
        v[i]=0;
    }
    for(re int i=0;i<4;++i)
        printf("%lld ",u[i]);
    printf("\n");
    cltstream::write(u[1]);
    return 0;
}
