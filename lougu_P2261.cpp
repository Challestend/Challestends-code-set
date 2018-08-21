#include<cstdio>
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))

int n,k;
long long ans;

int main(){
    scanf("%d%d",&n,&k);
    for(int l=1,r;l<=k&&l<=n;l=r+1)
        r=min(k/(k/l),n),ans+=1LL*(r-l+1)*k-1LL*(r-l+1)*(r+l)*(k/l)/2;
    printf("%lld",ans+1LL*max((n-k),0)*k);
    return 0;
}
