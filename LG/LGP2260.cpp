#include<cstdio>
#define re register
#define mod 19940417
#define min(a,b) ((a)<=(b)?(a):(b))
#define sum(a) ((1LL*(a)*((a)+1)>>1)%mod)
#define sqrsum(a) (((1LL*(a)*((a)+1)%mod)*(2*(a)+1)%mod)*I6%mod)

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

int n,m,n2,m2,I6=3323403,ans,ans1,ans2;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    n2=1LL*n*n%mod;
    m2=1LL*m*m%mod;
    ans=1LL*n2*m2%mod;
    for(int l=1,r;l<=m;l=r+1){
        r=m/(m/l);
        ans1=(1LL*ans1+(sum(r)-sum(l-1))*(m/l)%mod)%mod;
    }
    for(int l=1,r;l<=n;l=r+1){
        r=n/(n/l);
        ans2=(1LL*ans2+(sum(r)-sum(l-1))*(n/l)%mod)%mod;
    }
    ans=(1LL*ans-1LL*n2*ans1%mod-1LL*m2*ans2%mod+1LL*ans1*ans2%mod)%mod;
    ans=(1LL*ans-(1LL*n*m%mod)*min(n,m)%mod)%mod;
    for(int l=1,r;l<=n&&l<=m;l=r+1){
        r=min(n/(n/l),m/(m/l));
        ans=(1LL*ans+((sum(r)-sum(l-1))*n%mod)*(m/l)%mod)%mod;
        ans=(1LL*ans+((sum(r)-sum(l-1))*m%mod)*(n/l)%mod)%mod;
        ans=(1LL*ans-((sqrsum(r)-sqrsum(l-1))*(n/l)%mod)*(m/l)%mod)%mod;
    };
    cltstream::write((ans+mod)%mod,'\n');
    return 0;
}
