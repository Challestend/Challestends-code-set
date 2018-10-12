#include<cstdio>
#define re register
#define maxn 100000
#define maxlog 31
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

int n;
int a[maxn+1],f[maxn+1],g[maxlog+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;i<=n;++i){
        for(re int j=0;a[i]>>j;++j)
            if((a[i]>>j)&1)
                f[i]=max(f[i],f[g[j]]+1);
        for(re int j=0;a[i]>>j;++j)
            if((a[i]>>j)&1)
                g[j]=f[i]>=f[g[j]]?i:g[j];
    }
    for(re int i=1;i<=n;++i)
        f[0]=max(f[0],f[i]);
    cltstream::write(f[0],'\n');
    return 0;
}
