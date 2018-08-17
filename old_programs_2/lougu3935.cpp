#include<cstdio>
#define re register
#define maxn 10000000
#define mod 998244353
using namespace std;

long long n,m;
int ans;
int digit[20];

inline void read(long long& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

inline void write(int x){
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

int main(){
    read(n),read(m);
    for(re long long l=1,r;l<=m;l=r+1)
        r=m/(m/l),ans=(1LL*ans+(r-l+1)*(m/l))%mod;
    --n;
    for(re long long l=1,r;l<=n;l=r+1)
        r=n/(n/l),ans=(1LL*ans-(r-l+1)*(n/l))%mod;
    write((ans+mod)%mod);
    return 0;
}
