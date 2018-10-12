#include<cstdio>
#define re register
#define maxn 18
#define maxsize 262144
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m,k,size;
int a[maxn+1],b[maxn+1][maxn+1],cnt[maxsize+1];
long long f[maxsize+1][maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        f[1<<(i-1)][i]=a[i];
    }
    for(re int i=1;i<=k;++i){
        int x,y,z;
        cltstream::read(x);
        cltstream::read(y);
        cltstream::read(z);
        b[x][y]=z;
    }
    size=1<<n;
    for(re int i=1;i<size;++i)
        cnt[i]=cnt[i>>1]+(i&1);
    for(re int i=1;i<size;++i)
        for(re int j=1;j<=n;++j)
            if((i>>(j-1))&1){
                if(cnt[i]==m)
                    f[size][0]=max(f[size][0],f[i][j]);
                for(re int l=1;l<=n;++l)
                    if(((i>>(l-1))&1)^1)
                        f[i|(1<<(l-1))][l]=max(f[i|(1<<(l-1))][l],f[i][j]+b[j][l]+a[l]);
            }
    cltstream::write(f[size][0],'\n');
    return 0;
}
