#include<cstdio>
#define re register
#define maxn 200000

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

int n,m,ans;
int s[maxn+1],p[maxn+1];

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i)
        cltstream::read(s[i]);
    for(re int i=1;i<=n;++i)
        cltstream::read(p[i]);
    for(;s[m]+p[1]<s[ans+1]+p[n];++ans);
    for(re int i=1;ans+i<m;++i)
        if(s[ans+i]+p[n-i+1]>s[m]+p[1])
            ++ans;
    cltstream::write(ans+1);
    return 0;
}
