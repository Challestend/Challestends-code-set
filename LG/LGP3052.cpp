#include<cstdio>
#define re register
#define maxn 18
#define maxsize 300000
#define max(a,b) ((a)>=(b)?(a):(b))

int n,w,size;
int c[maxn+1],f[maxsize+1],g[maxsize+1];

void binprint(int x){
    int digit[maxn+1];
    for(re int i=0;i<n;digit[i++]=x&1,x>>=1);
    for(re int i=n-1;i>=0;putchar(digit[i--]^48));
}

int main(){
    scanf("%d%d",&n,&w);
    for(re int i=1;i<=n;++i)
        scanf("%d",&c[i]);
    size=1<<n;
    for(re int i=1;i<size;++i)
        f[i]=n+1;
    for(re int i=0;i<size;++i)
        for(re int j=1;j<=n;++j){
            if(i>>(j-1)&1)
                continue;
            if(g[i]>=c[j]&&f[i|(1<<(j-1))]>=f[i]){
                f[i|(1<<(j-1))]=f[i];
                g[i|(1<<(j-1))]=max(g[i|(1<<(j-1))],g[i]-c[j]);
                continue;
            }
            if(g[i]<c[j]&&f[i|(1<<(j-1))]>=f[i]+1){
                f[i|(1<<(j-1))]=f[i]+1;
                g[i|(1<<(j-1))]=max(g[i|(1<<(j-1))],max(g[i],w-c[j]));
                continue;
            }
        }
    printf("%d",f[size-1]);
    return 0;
}
