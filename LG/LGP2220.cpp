#include<cstdio>
#include<algorithm>
#define re register
#define maxk 100000
#define mod 1000000007

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

int n,m,k;
std::pair<int,int> a[maxk+2];
int res=1,ans=1;

int cltpow(int x,int y){
    if(y==0)
        return 1;
    if(y==1)
        return x;
    int res=cltpow(x,y>>1);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(k);
    for(re int i=1;i<=k;++i){
        cltstream::read(a[i].first);
        cltstream::read(a[i].second);
    }
    std::sort(a+1,a+k+1);
    k=std::unique(a+1,a+k+1)-a-1;
    a[k+1].first=m+1;
    for(re int i=1;i<=k+1;++i){
        if(a[i].first>a[i-1].first){
            ans=1LL*ans*res%mod;
            ans=1LL*ans*cltpow(res=(1LL*n*(n+1)>>1)%mod,a[i].first-a[i-1].first-1)%mod;
        }
        res=(res-a[i].second+mod)%mod;
    }
    cltstream::write(ans,'\n');
    return 0;
}
