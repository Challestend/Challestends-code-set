#include<cstdio>
#define re register
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,ans;

int main(){
    cltstream::read(n);
    ans+=min(max(n-5000,0),3000)*3/100;
    ans+=min(max(n-8000,0),9000)*10/100;
    ans+=min(max(n-17000,0),13000)*20/100;
    ans+=min(max(n-30000,0),10000)*25/100;
    ans+=min(max(n-40000,0),20000)*30/100;
    ans+=min(max(n-60000,0),25000)*35/100;
    ans+=max(n-85000,0)*45/100;
    cltstream::write(n-ans);
    return 0;
}
