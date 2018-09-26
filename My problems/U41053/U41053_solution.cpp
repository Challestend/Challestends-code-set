#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define maxn 1000

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

int n,ec,gcdsum;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1],dep[maxn+1];
int a[maxn+1],b[maxn+1][maxn+1],cnt[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

int dfs(int cur,int ftr){
    dep[cur]=dep[ftr]+1;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=ftr)
            dfs(des[i],cur);
    if(!suc[las[cur]]&&ftr)
        a[++a[0]]=dep[cur];
}

int gcd(int x,int y){
    return y?gcd(y,x%y):x;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<n;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs(1,0);
    std::sort(a+1,a+a[0]+1);
    a[0]=std::unique(a+1,a+a[0]+1)-a-1;
    if(a[0]==1){
        putchar(45);
        putchar(49);
        putchar(10);
        return 0;
    }
    gcdsum=gcd(a[1],a[2]);
    for(re int i=3;i<=a[0];++i)
        gcdsum=gcd(gcdsum,a[i]);
    if(gcdsum>1){
        putchar(45);
        putchar(49);
        putchar(10);
        return 0;
    }
    for(re int i=1;i<=a[0];++i)
        b[i][0]=cnt[i]=1;
    for(re int i=0;;++i){
        re int res=0;
        for(re int j=1;j<=a[0];++j)
            res|=b[j][i%a[j]];
        for(re int j=1;j<=a[0]&&res;++j)
            if(!b[j][i%a[j]]){
                ++cnt[j];
                b[j][i%a[j]]=1;
            }
        res=1;
        for(re int j=1;j<=a[0]&&res;++j)
            if(cnt[j]<a[j])
                res=0;
        if(res){
            cltstream::write(i);
            break;
        }
    }
    return 0;
}
