#include<cstdio>
#define re register
#define maxn 200000
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m;
int x[maxn+1],y[maxn+1],len[maxn+1];
int ans;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(x[i]);
        cltstream::read(y[i]);
        len[i]=y[i]-x[i]+len[i-1];
    }
    for(re int head=0,tail=0;tail<n;++head){
        for(;tail<n&&x[tail+1]-x[head+1]-len[tail]+len[head]<m;++tail);
        ans=max(ans,y[tail]-x[tail]+len[tail-1]-len[head]+m);
    }
    cltstream::write(ans);
    return 0;
}
