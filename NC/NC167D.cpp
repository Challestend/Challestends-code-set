#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define mod 10007

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

struct matrix{
    int a[3][3];

    inline void init(int tp){
        for(re int i=0;i<3;++i)
            for(re int j=0;j<3;++j)
                a[i][j]=0;
        for(re int i=0;i<3;++i)
            a[i][i]=tp;
    }

    matrix(int tp){
        init(tp);
    }
};
matrix A(0),B(1),C(1);
std::string s;
int len;

inline matrix operator*(matrix& X,matrix& Y){
    matrix Z(0);
    for(re int i=0;i<3;++i)
        for(re int j=0;j<3;++j)
            for(re int k=0;k<3;++k)
                Z.a[i][j]=(Z.a[i][j]+X.a[i][k]*Y.a[k][j]%mod)%mod;
    return Z;
}

int main(){
    A.a[0][0]=2;
    A.a[0][2]=A.a[1][0]=A.a[2][1]=1;
    std::cin>>s;
    len=s.length();
    for(re int i=1;i<=len;++i){
        C.init(1);
        for(re int j=1;j<=10;++j)
            C=C*B;
        B=C;
        for(re int j=49;j<=s[i-1];++j)
            B=B*A;
    }
    B.a[0][0]=(5*B.a[0][0]+2*B.a[0][1]+B.a[0][2])%mod;
    B.a[1][0]=(5*B.a[1][0]+2*B.a[1][1]+B.a[1][2])%mod;
    cltstream::write(((B.a[0][0]-2*B.a[1][0])%mod+mod)%mod);
    return 0;
}
