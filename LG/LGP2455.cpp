#include<cstdio>
#define re register
#define maxn 50
#define eps 1e-4
#define max(a,b) ((a)-(b)>eps?(a):(b))
#define abs(a) max(a,-(a))

int n;
double a[maxn+1][maxn+2];
int b[maxn+1],c[maxn+1];

int main(){
    scanf("%d",&n);
    for(re int i=1;i<=n;++i){
        b[i]=1;
        for(re int j=1;j<=n+1;++j)
            scanf("%lf",&a[i][j]);
    }
    for(re int i=1;i<=n;++i){
        int cur=0;
        for(re int j=1;j<=n&&!cur;++j)
            if(abs(a[j][i])>eps&&b[j])
                    cur=j;
        if(!cur)
            continue;
        b[cur]=0;
        c[i]=cur;
        for(re int j=1;j<=n+1;++j)
            if(j!=i)
                a[cur][j]/=a[cur][i];
        a[cur][i]=1;
        for(re int j=1;j<=n;++j)
            if(j!=cur){
                for(re int k=1;k<=n+1;++k)
                    if(k!=i)
                        a[j][k]-=a[j][i]*a[cur][k];
                a[j][i]=0;
            }
        }
    for(re int i=1;i<=n;++i)
        if(!c[i])
            for(re int j=1;j<=n;++j)
                if(b[j]){
                    b[j]=0;
                    c[i]=j;
                    break;
                }
    for(re int i=1;i<=n;++i)
        if(abs(a[c[i]][i])<eps&&abs(a[c[i]][n+1])>eps){
                putchar(45);
                putchar(49);
                putchar(10);
                return 0;
        }
    for(re int i=1;i<=n;++i)
        if(abs(a[c[i]][i])<eps&&abs(a[c[i]][n+1])<eps){
                putchar(48);
                putchar(10);
                return 0;
        }
    for(re int i=1;i<=n;++i)
        printf("x%d=%0.2lf\n",i,a[c[i]][n+1]);
    return 0;
}
