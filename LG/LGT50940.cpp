#include<cstdio>
#define re register
#define mod 1000000007

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

int n,a,k,ans;

int cltpow(int x,int y){
    if(y==0)
        return 1;
    if(y==1)
        return x;
    else{
        int res=cltpow(x,y>>1);
        res=1LL*res*res%mod;
        if(y&1)
            res=1LL*res*x%mod;
        return res;
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(a);
    cltstream::read(k);
    for(re int i=1;i<=n;++i)
        ans=(1LL*ans+1LL*cltpow(i,k)*cltpow(a,i)%mod)%mod;
    cltstream::write(ans,'\n');
    return 0;
}
