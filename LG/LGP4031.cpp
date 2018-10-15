#include<cstdio>
#include<cmath>
#define re register

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

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
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int t;
long long a1,l,r,n,p,m;
long long F1,F2,x,y,g,z,tmp;
struct matrix{
    int a[2][2];

    inline void init(){
        for(re int i=0;i<2;++i)
            for(re int j=0;j<2;++j)
                a[i][j]=0;
    }

    matrix(){
        init();
    }
};
matrix A,B;

inline matrix operator*(matrix& X,matrix& Y){
    matrix Z;
    for(re int i=0;i<2;++i)
        for(re int j=0;j<2;++j)
            for(re int k=0;k<2;++k)
                Z.a[i][j]=(1LL*Z.a[i][j]+1LL*X.a[i][k]*Y.a[k][j]%p)%p;
    return Z;
}

void matpow(int x){
    if(!x){
        B.a[0][1]=B.a[1][0]=0;
        B.a[0][0]=B.a[1][1]=1;
    }
    else{
        matpow(x>>1);
        B=B*B;
        if(x&1)
            B=B*A;
    }
}

long long exgcd(long long a,long long b,long long& x,long long& y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    else{
        long long g=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return g;
    }
}

int main(){
    A.a[0][0]=A.a[0][1]=A.a[1][0]=1;
    cltstream::read(t);
    for(;t;--t){
        cltstream::read(a1);
        cltstream::read(l);
        cltstream::read(r);
        cltstream::read(n);
        cltstream::read(p);
        cltstream::read(m);
        matpow(n-3);
        F1=(B.a[1][0]+B.a[1][1])%p;
        F2=(B.a[0][0]+B.a[0][1])%p;
        g=exgcd(F2,p,x,y);
        z=((m-F1*a1)%p+p)%p;
        if(z%g)
            puts("0");
        else{
            tmp=p/g;
            x=(x*z/g%tmp+tmp)%tmp;
            cltstream::write<long long>((floor(double(r-x)/tmp)-ceil(double(l-x)/tmp)+1),'\n');
        }
    }
    return 0;
}
