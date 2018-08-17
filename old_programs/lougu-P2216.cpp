#include<cstdio>
#define maxn 1000
#define maxm 1000
#define min(a,b) ((a)<=(b)?(a):(b))

int n,m,k,ans=2e9;
int a[maxn+1][maxm+1],h[maxn+1],x[maxn+1][maxm+1],y[maxn+1][maxm+1];

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;++i)
        for(int j=1,head=0,tail=0;j<=m;++j){
            for(;head<tail&&a[i][h[tail]]<=a[i][j];--tail);
            h[++tail]=j;
            for(;h[head+1]+k-1<j;++head);
            if(j>=k)
                x[i][j-k+1]=a[i][h[head+1]];
        }
    for(int i=1;i+k-1<=m;++i)
        for(int j=1,head=0,tail=0;j<=n;++j){
            for(;head<tail&&x[h[tail]][i]<=x[j][i];--tail);
            h[++tail]=j;
            for(;h[head+1]+k-1<j;++head);
            if(j>=k)
                y[j-k+1][i]=x[h[head+1]][i];
        }
    for(int i=1;i<=n;++i)
        for(int j=1,head=0,tail=0;j<=m;++j){
            for(;head<tail&&a[i][h[tail]]>=a[i][j];--tail);
            h[++tail]=j;
            for(;h[head+1]+k-1<j;++head);
            if(j>=k)
                x[i][j-k+1]=a[i][h[head+1]];
        }
    for(int i=1;i+k-1<=m;++i)
        for(int j=1,head=0,tail=0;j<=n;++j){
            for(;head<tail&&x[h[tail]][i]>=x[j][i];--tail);
            h[++tail]=j;
            for(;h[head+1]+k-1<j;++head);
            if(j>=k)
                ans=min(ans,y[j-k+1][i]-x[h[head+1]][i]);
        }
    printf("%d",ans);
    return 0;
}
