#include<cstdio>
#define re register
#define maxm 20

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

int n,m,mod,ans;
struct matrix{
    int a[maxm][maxm];

    inline void init(){
        for(re int i=0;i<m;++i)
            for(re int j=0;j<m;++j)
                a[i][j]=0;
    }

    matrix(){
        init();
    }
};
matrix A,B;

inline matrix operator*(matrix& x,matrix& y){
    matrix z;
    for(re int i=0;i<m;++i)
        for(re int j=0;j<m;++j)
            for(re int k=0;k<m;++k)
                z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
    return z;
}

void matpow(int x){
    if(x){
        matpow(x>>1);
        B=B*B;
        if(x&1)
            B=B*A;
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(mod);
    for(re int i=0;i<m-1;++i)
        A.a[i][i+1]=1;
    for(re int i=0;i<m;++i){
        A.a[m-1][i]=9;
        B.a[i][i]=1;
    }
    matpow(n-1);
    for(re int i=0;i<m;++i)
        ans=(ans+B.a[i][m-2]+B.a[i][m-1]*9)%mod;
    cltstream::write(ans,'\n');
    return 0;
}
