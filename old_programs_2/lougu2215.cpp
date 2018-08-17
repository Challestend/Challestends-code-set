#include<cstdio>
#define maxn 10000
#define maxm 1000
using namespace std;

int n,m;
int a[maxn+1]={2e9},f[maxn+1],g[maxn+1],suc[maxn+1];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    for(int i=n;i>=1;--i)
        if(a[i]<a[g[g[0]]])
            suc[i]=g[g[0]],g[f[i]=++g[0]]=i;
        else{
            int l=0,r=g[0]-1;
            for(;l<r;){
                int mid=l+r+1>>1;
                if(a[i]<a[g[mid]])
                    l=mid;
                else
                    r=mid-1;
            }
            suc[i]=l?g[l]:0;
            g[f[i]=l+1]=i;
        }
    scanf("%d",&m);
    for(int i=1;i<=m;++i){
        int x;
        scanf("%d",&x);
        if(g[0]<x)
            printf("Impossible");
        else
            for(int j=1;j<=n&&f[j-1]<x;++j)
                if(f[j]>=x)
                    for(int k=j,cnt=0;cnt<x;++cnt,printf("%d ",a[k]),k=suc[k]);
        putchar(10);
    }
    return 0;
}
