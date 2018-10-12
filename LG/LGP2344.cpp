#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define mod 1000000009
#define lowbit(a) ((a)&(-(a)))

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
long long a[maxn+1],sum[maxn+1];
int fwt[maxn+1],f[maxn+1];

inline void update(int L,int x){
    for(re int i=L;i<=sum[0];i+=lowbit(i))
        fwt[i]=(fwt[i]+x)%mod;
}

inline int getsum(int L){
    int res=0;
    for(re int i=L;i>=1;i-=lowbit(i))
        res=(res+fwt[i])%mod;
    return res;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        a[i]+=a[i-1];
        sum[i]=a[i];
    }
    std::sort(sum+1,sum+n+1);
    sum[0]=std::unique(sum+1,sum+n+1)-sum-1;
    for(re int i=1;i<=n;++i){
        a[i]=std::lower_bound(sum+1,sum+sum[0]+1,a[i])-sum;
        f[i]=(getsum(a[i])+(sum[a[i]]>=0))%mod;
        update(a[i],f[i]);
    }
    cltstream::write(f[n],'\n');
    return 0;
}
