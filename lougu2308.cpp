#include<cstdio>
#define maxn 20

int n;
int a[maxn+1],f[maxn+1][maxn+1],g[maxn+1][maxn+1];

void printquote(int l,int r){
    if(l<r){
        putchar('(');
        printquote(l,g[l][r-l+1]);
        putchar('+');
        printquote(g[l][r-l+1]+1,r);
        putchar(')');
    }
    else
        printf("%d",a[l]-a[l-1]);
}

void printsum(int l,int r){
    if(l<r){
        printsum(l,g[l][r-l+1]);
        printsum(g[l][r-l+1]+1,r);
        printf("%d ",a[r]-a[l-1]);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]),a[i]+=a[i-1];
    for(int i=1;i<=n;++i)
        for(int j=2;i+j-1<=n;++j)
            f[i][j]=2e9;
    for(int j=2;j<=n;++j)
        for(int i=1;i+j-1<=n;++i)
            for(int k=1;k<j;++k)
                if(f[i][j]>=f[i][k]+f[i+k][j-k]+a[i+j-1]-a[i-1])
                    f[i][j]=f[i][k]+f[i+k][j-k]+a[i+j-1]-a[i-1],g[i][j]=i+k-1;
    printquote(1,n);
    printf("\n%d\n",f[1][n]);
    printsum(1,n);
}
