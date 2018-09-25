#include<cstdio>
#include<algorithm>
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

int n,m;
int a[maxn+1],b[(maxn<<1)+2];
long long ans;

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        b[i]=i-a[i];
        b[i+n]=i+a[i];
    }
    b[(n<<1)+1]=2e9;
    std::sort(b+1,b+(n<<1)+1);
    for(re int i=1,cnt=0;i<=(n<<1)+1;++i,++cnt)
        if(b[i]>b[i-1]){
            ans+=1LL*cnt*(cnt-1)>>1;
            cnt=0;
        }
    cltstream::write(ans);
    return 0;
}
