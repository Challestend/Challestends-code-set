#include<cstdio>
#include<queue>
#define re register
#define maxn 20
#define maxsize 1048576

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

int n,size;
int a[maxn+1],b[maxn+1],f[maxsize+1],ex[maxsize+1];
std::queue<int> h;

int main(){
    cltstream::read(n);
    size=1<<n;
    for(re int i=1;i<=n;++i){
        int x;
        cltstream::read(x);
        for(re int j=1;j<=x;++j){
            int y;
            cltstream::read(y);
            a[i]^=1<<(y-1);
        }
    }
    for(re int i=1;i<=n;++i){
        b[i]=a[i]^(1<<(i-1));
        for(re int j=1;j<=n;++j)
            if((a[i]>>(j-1))&1)
                b[i]^=a[j];
    }
    for(re int i=1;i<size;++i)
        f[i]=100;
    h.push(0);
    ex[0]=1;
    for(;!h.empty();){
        int x=h.front();
        h.pop();
        ex[x]=0;
        for(re int i=1;i<=n;++i)
            if(f[x^b[i]]>f[x]+1){
                f[x^b[i]]=f[x]+1;
                if(!ex[x^b[i]]){
                    h.push(x^b[i]);
                    ex[x^b[i]]=1;
                }
            }
    }
    if(f[size-1]<=100)
        cltstream::write(f[size-1]);
    else
        printf("Change an alarm clock,please!");
    return 0;
}
