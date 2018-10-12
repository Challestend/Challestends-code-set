#include<cstdio>
#define re register
#define maxn 12
#define maxm 12
#define maxsize 4096
#define mod 100000000

namespace cltstream{
    #define LOCAL

    #ifdef LOCAL
        #define gc getchar
    #else
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

int n,m,size;
int a[maxn+1],b[maxsize+1]={1},f[maxn+1][maxsize+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    size=1<<m;
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j){
            int x;
            cltstream::read(x);
            a[i]=(a[i]<<1)|x;
        }
    for(re int i=1;i<size;++i)
        b[i]=b[i>>1]&(~(i&(i>>1)&1));
    for(re int i=0;i<size;++i)
        if((i|a[1])==a[1]&&b[i])
            f[1][i]=1;
    for(re int i=2;i<=n;++i)
        for(re int j=0;j<size;++j)
            if((j|a[i])==a[i]&&b[j])
                for(re int k=0;k<size;++k)
                    if((k|a[i-1])==a[i-1]&&(k&j)==0)
                        (f[i][j]+=f[i-1][k])%=mod;
    for(re int i=1;i<size;++i)
        (f[n][0]+=f[n][i])%=mod;
    cltstream::write(f[n][0],'\n');
    return 0;
}
