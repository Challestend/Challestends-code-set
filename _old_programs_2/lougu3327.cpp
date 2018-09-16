#include<cstdio>
#define re register
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int t,n,m;
int digit[20];

inline void read(int& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48|c>57);c=getchar());
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
    read(t);
    for(;t;--t){
        read(n),read(m);
        long long ans=0;
        for(re int l=1,r;l<=n;l=r+1)
            r=n/(n/l),ans+=1LL*m*(r-l+1)*(n/l);
        for(re int l=1,r;l<=m;l=r+1)
            r=m/(m/l),ans+=1LL*n*(r-l+1)*(m/l);
        for(re int l=1,r;l<=n&&l<=m;l=r+1)
            r=min(n/(n/l),m/(m/l)),ans-=1LL*(r-l+1)*(n/l)*(m/l);
        write(ans);
        putchar(10);
    }
    return 0;
}
