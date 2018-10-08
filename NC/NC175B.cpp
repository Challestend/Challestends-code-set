#include<cstdio>
#define re register
#define maxn 200000
#define maxlog 17
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

int n;
int lg[maxn+1];
long long m[maxn+1][maxlog+1],g[maxn+1][maxlog+1];

long long gcd(long long x,long long y){
    return y?gcd(y,x%y):x;
}

int solve(int l,int r){
    if(l==r)
        return 1;
    int x=lg[r-l+1];
    int minp=g[m[l][x]][0]<=g[m[r-(1<<x)][x]][0]?m[l][x]:m[r-(1<<x)][x];
    int gcdw=gcd(g[l][x],g[r-(1<<x)][x]);
    if(g[minp][0]==gcdw)
        return r-l+1;
    else
        return max(solve(l,minp),solve(minp+1,r));
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        lg[i]=lg[i>>1]+1;
    for(re int i=1;i<=n;++i){
        cltstream::read(g[i][0]);
        m[i][0]=i;
    }
    for(re int i=1;i<=lg[n];++i)
        for(re int j=1;j+(1<<i)-1<=n;++j){
            m[j][i]=g[m[j][i-1]][0]<=g[m[j+(1<<(i-1))][i-1]][0]?m[j][i-1]:m[j+(1<<(i-1))][i-1];
            g[j][i]=gcd(g[j][i-1],g[j+(1<<(i-1))][i-1]);
        }
    for(re int i=1;i<=n;++i){
        for(re int j=0;j<=lg[n];++j)
            printf("(%d,%d) ",g[m[i][j]][0],g[i][j]);
        printf("\n");
    }
    cltstream::write(solve(1,n));
    return 0;
}
