#include<cstdio>
#include<cmath>
#define maxsqrtn 3200000

long long n;
int m;
int f[maxsqrtn+1],g[maxsqrtn+1];
long long h[maxsqrtn+1];

int main(){
    scanf("%lld",&n);
    if(n==1){
        putchar(49);
        putchar(10);
        putchar(48);
        return 0;
    }
    m=sqrt(n);
    for(int i=2;i<=m;++i){
        if(!f[i]){
            g[++g[0]]=i;
            for(;n%i==0;h[++h[0]]=i,n/=i);
        }
        for(int j=1;j<=g[0]&&i*g[j]<=m;++j){
            f[i*g[j]]=1;
            if(i%g[j]==0)
                break;
        }
    }
    if(n>1)
        h[++h[0]]=n;
    if(h[0]==2)
        putchar(50);
    else{
        putchar(49);
        putchar(10);
        printf("%lld",h[1]*h[2]);
    }
    return 0;
}
