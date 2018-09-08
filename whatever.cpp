#include<cstdio>
#define re register
#define maxn 1000000
#define mod 1000000007

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=10*x+(c^48),c=getchar());
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
int f[maxn+1],g[maxn+1],las[maxn+1]={0,1},pow[maxn+1],ans[maxn+1];

inline void breakDown(int x){
    if(x==1)
        putchar(49);
    else{
        for(re int i=1;g[i]*g[i]<=x;++i)
            for(;x%g[i]==0;){
                printf("%d",g[i]);
                x/=g[i];
                if(x>1)
                    printf("*");
            }
        if(x>1)
            printf("%d",x);
    }
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i)
        ans[i]=1;
    for(re int i=2;i<=n;++i){
        if(!f[i])
            g[++g[0]]=i,las[i]=i,pow[i]=1,ans[i]=1;
        for(re int j=1;j<=g[0]&&i*g[j]<=n;++j){
            f[i*g[j]]=1;
            if(i%g[j]){
                ans[i*g[j]]=ans[i]*(las[i]^pow[i]);
                las[i*g[j]]=g[j];
                pow[i*g[j]]=1;
            }
            else{
                ans[i*g[j]]=ans[i];
                las[i*g[j]]=las[i];
                pow[i*g[j]]=pow[i]+1;
                break;
            }
        }
    }
    for(re int i=1;i<=n;++i)
        ans[i]*=las[i]^pow[i],
        ans[i]+=ans[i-1],
        printf("sumf(%d)=%d\n",i,ans[i]);
    return 0;
}
