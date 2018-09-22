#include<cstdio>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))
#define Dist(x1,y1,x2,y2) max(abs(1LL*x1-x2),abs(1LL*y1-y2))

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

int n;
int x[maxn+1],y[maxn+1];
int a=2e9,b=-2e9,c=2e9,d=-2e9;
long long ans=4e18;
int cnt=0;

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(x[i]);
        a=min(a,x[i]);
        b=max(b,x[i]);
        cltstream::read(y[i]);
        c=min(c,y[i]);
        d=max(d,y[i]);
    }
    for(re int x0=a;x0<=b;++x0)
        for(re int y0=c;y0<=d;++y0){
            long long sum=0;
            for(re int i=1;i<=n&&sum<=ans;++i)
                sum+=Dist(x0,y0,x[i],y[i]);
            if(ans>sum){
                ans=sum;
                cnt=1;
            }
            else
                if(ans==sum)
                    ++cnt;
        }
    cltstream::write(ans);
    putchar(10);
    cltstream::write(cnt);
    return 0;
}
