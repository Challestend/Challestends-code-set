#include<cstdio>
#define re register
#define maxa 50000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,a,b,c,d,k;
int f[maxa+1],g[maxa+1];
long long mu[maxa+1]={0,1};
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
    for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
    if(!digit[0])
        putchar(48);
    else
        for(;digit[0];putchar(digit[digit[0]--]^48));
}

inline long long solve(int x,int y){
    x/=k,y/=k;
    long long res=0;
    for(re int l=1,r;l<=x&&l<=y;l=r+1)
        r=min(x/(x/l),y/(y/l)),res+=1LL*(x/l)*(y/l)*(mu[r]-mu[l-1]);
    return res;
}

int main(){
    for(re int i=2;i<=maxa;++i){
        if(!f[i])
            mu[g[++g[0]]=i]=-1;
        for(re int j=1;j<=g[0]&&i*g[j]<=maxa;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                mu[i*g[j]]=-mu[i];
            else
                break;
        }
    }
    for(re int i=1;i<=maxa;++i)
        mu[i]+=mu[i-1];
    read(n);
    for(re int i=1;i<=n;++i){
        read(a),read(b),read(c),read(d),read(k);
        write(solve(b,d)-solve(a-1,d)-solve(b,c-1)+solve(a-1,c-1));
        putchar(10);
    }
    return 0;
}
