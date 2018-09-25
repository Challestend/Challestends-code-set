#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000
#define maxlog 60

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
std::pair<int,long long> a[maxn+1];
long long base[maxlog+1];

bool cmp(std::pair<int,long long> p,std::pair<int,long long> q){
    return p.first>q.first||(p.first==q.first&&p.second>q.second);
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i].second);
        cltstream::read(a[i].first);
    }
    std::sort(a+1,a+n+1,cmp);
    for(re int i=1;i<=n;++i)
        for(re int j=maxlog;j>=0;--j)
            if(a[i].second>>j&1){
                if(!base[j]){
                    base[j]=a[i].second;
                    ans+=a[i].first;
                    break;
                }
                else
                    a[i].second^=base[j];
            }
    cltstream::write(ans);
    return 0;
}
