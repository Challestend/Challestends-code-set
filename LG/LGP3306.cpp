#include<cstdio>
#include<cmath>
#include<map>
#define re register

int T,p,a,b,x,t;
int A,B,g,c,n,m,ans;
std::map<int,int> P;

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

int cpow(int x,int y,int p){
    if(y==1)
        return x%p;
    int res=cpow(x,y>>1,p);
    res=1LL*res*res%p;
    if(y&1)
        res=1LL*res*x%p;
    return res;
}

int exgcd(int a,int b,int& x,int& y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    int res=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return res;
}

int main(){
    cltstream::read(T);
    for(re int i=1;i<=T;++i){
        cltstream::read(p);
        cltstream::read(a);
        cltstream::read(b);
        cltstream::read(x);
        cltstream::read(t);
        if(x==t){
            putchar(49);
            putchar(10);
            continue;
        }
        if(!a){
            cltstream::write(b==t?2:-1);
            putchar(10);
            continue;
        }
        if(a==1){
            if(!b){
                putchar(45);
                putchar(49);
                putchar(10);
                continue;
            }
            else{
                t=(1LL*t-x+b+p)%p;
                g=exgcd(b,p,A,B);
                cltstream::write(t%g?-1:(1LL*t/g*A%p+p)%p);
                putchar(10);
                continue;
            }
        }
        c=1LL*b*cpow(a-1,p-2,p)%p;
        t=1LL*(t+c)*cpow(x+c,p-2,p)%p;
        n=ceil(sqrt(p));
        m=1;
        P.clear();
        for(re int j=0;j<n;++j,m=1LL*m*x%p)
            if(!P[m])
                P[m]=j+1;
        ans=-1;
        for(re int j=0,k=1;j<n&&ans<0;++j,k=1LL*k*m%p){
            g=exgcd(k,p,A,B);
            if(t%g)
                continue;
            else{
                c=(1LL*t/g*A%p+p)%p;
                if(P[c])
                    ans=j*n+P[c];
            }
        }
        cltstream::write(ans);
        putchar(10);
    }
    return 0;
}
