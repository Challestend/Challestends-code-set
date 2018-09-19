#include<cstdio>
#define re register
#define maxn 10000000
#define maxm 10000000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int t,n,m;
int f[maxn+1],g[maxn+1],mu[maxn+1]={0,1};
long long sum[maxn+1];
int digit[20];

inline void read(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void write(long long x){
    if(x<0)
        putchar(45),x=-x;
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

int main(){
    for(re int i=2;i<=maxn;++i){
        if(!f[i])
            mu[g[++g[0]]=i]=-1;
        for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                mu[i*g[j]]=-mu[i];
            else
                break;
            }
    }
    for(re int i=1;i<=g[0];++i)
        for(re int j=1;j*g[i]<=maxn;++j)
            sum[j*g[i]]+=mu[j];
    for(re int i=1;i<=maxn;++i)
        sum[i]+=sum[i-1];
    read(t);
    for(;t;--t){
        read(n),read(m);
        long long ans=0;
        for(re int l=1,r;l<=n&&l<=m;l=r+1)
            r=min(n/(n/l),m/(m/l)),ans+=1LL*(n/l)*(m/l)*(sum[r]-sum[l-1]);
        write(ans);
        putchar(10);
    }
    return 0;
}
