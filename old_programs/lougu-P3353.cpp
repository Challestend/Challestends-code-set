#include<cstdio>
#include<algorithm>
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))
using namespace std;

int n,m,head,tail,sum,ans;
struct star{
    int x,y;
};
star a[maxn+5];

bool cmp(star p,star q){
    return p.x<=q.x;
}

int main(){
    scanf("%d%d",&n,&m);
    if(m==0){
        putchar(48);
        return 0;
    }
    for(int i=1;i<=n;++i)
        scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp);
    sum=a[tail=1].y;
    for(;;){
        for(;tail<n&&a[tail+1].x-a[head+1].x<m;sum+=a[++tail].y);
        ans=max(ans,sum);
        if(tail==n)
            break;
        for(;a[tail+1].x-a[head+1].x>=m;sum-=a[++head].y);
    }
    printf("%d",ans);
    return 0;
}
