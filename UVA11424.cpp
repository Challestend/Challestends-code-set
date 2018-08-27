#include<cstdio>
#define re register
#define maxn 200000

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

int n;
int f[maxn+1],g[maxn+1];
long long phi[maxn+1]={0,1};

int main(){
    for(re int i=2;i<=maxn;++i){
        if(!f[i])
            g[++g[0]]=i,phi[i]=i-1;
        for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
            f[i*g[j]]=1;
            if(i%g[j])
                phi[i*g[j]]=phi[i]*phi[g[j]];
            else{
                phi[i*g[j]]=phi[i]*g[j];
                break;
            }
        }
    }
    for(re int i=1;i<=maxn;++i)
        phi[i]+=phi[i-1];
    for(;;){
        read(n);
        if(!n)
            break;
        else{
            long long res=0;
            for(re int l=1,r;l<=n;l=r+1)
                r=n/(n/l),res+=1LL*(r-l+1)*(l+r)*(2*phi[n/l]-1)/2;
            write((res-1LL*n*(n+1)/2)/2);
            putchar(10);
        }
    }
    return 0;
}
