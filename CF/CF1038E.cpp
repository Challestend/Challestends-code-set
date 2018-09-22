#include<cstdio>
#define re register
#define maxn 100
#define max(a,b) ((a)>=(b)?(a):(b))

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
int c[maxn+1][2],v[maxn+1],dis[maxn+1][maxn+1];

int main(){
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(c[i][0]);
        cltstream::read(v[i]);
        cltstream::read(c[i][1]);
    }
    for(re int i=1;i<=n;++i)
        for(re int j=i+1;j<=n;++j)
            if(c[i][0]==c[j][0]||c[i][0]==c[j][1]||c[i][1]==c[j][0]||c[i][1]==c[j][1]){
                dis[i][j]=v[j];
                dis[j][i]=v[i];
            }
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=n;++j)
            printf("%d ",dis[i][j]);
        printf("\n");
    }
    for(re int k=1;k<=n;++k)
        for(re int i=1;i<=n;++i)
            for(re int j=1;j<=n;++j)
                dis[i][j]=max(dis[i][j],dis[i][k]+dis[k][j]);
    for(re int i=1;i<=n;++i){
        for(re int j=1;j<=n;++j)
            printf("%d ",dis[i][j]);
        printf("\n");
    }
    return 0;
}
