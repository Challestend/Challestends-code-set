#include<cstdio>
#define maxm 15
#define mod 1000000007

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
    #define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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
int m,ans;
int a[maxm+1][maxm+1],b[maxm+1][maxm+1],c[maxm+1][maxm+1];

void matpow(long long x){
    if(x==1){
        for(int i=0;i<=m;++i)
            for(int j=0;j<=m;++j)
                b[i][j]=a[i][j];
    }
    else{
        matpow(x>>1);
        for(int i=0;i<=m;++i)
            for(int j=0;j<=m;++j){
                c[i][j]=0;
                for(int k=0;k<=m;++k)
                    c[i][j]=(1LL*c[i][j]+1LL*b[i][k]*b[k][j]%mod)%mod;
            }
        for(int i=0;i<=m;++i)
            for(int j=0;j<=m;++j)
                b[i][j]=c[i][j];
        if(x&1){
            for(int i=0;i<=m;++i)
                for(int j=0;j<=m;++j){
                    c[i][j]=0;
                    for(int k=0;k<=m;++k)
                        c[i][j]=(1LL*c[i][j]+1LL*b[i][k]*a[k][j]%mod)%mod;
                }
            for(int i=0;i<=m;++i)
                for(int j=0;j<=m;++j)
                    b[i][j]=c[i][j];
        }
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(int i=0;i<m;++i)
        a[i][i+1]=1;
    a[m][0]=a[m][m]=1;
    if(n>m+1)
        matpow(n-m-1);
    else
        ans=n+1;
    for(int i=0;i<=m;++i)
        ans=(1LL*ans+1LL*b[m][i]*(i+2)%mod)%mod;
    cltstream::write(ans);
    clop();
    return 0;
}
