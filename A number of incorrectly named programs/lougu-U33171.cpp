#include<cstdio>
#define maxn 40
#define max(a,b) ((a)>=(b)?(a):(b))
using namespace std;

int t,n;
int a[maxn+1];

int main(){
    freopen("lougu-U33171.in","r",stdin);
    freopen("lougu-U33171.out","w",stdout);
    scanf("%d",&t);
    for(;t;--t){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        int f=1;
        for(int i=1,frt=0,las=0;i<=(n>>1)&&f;++i){
            for(++frt;frt<n&&!a[frt];++frt);
            for(las=max(las,frt+1);las<=n&&a[las]!=a[frt];++las);
            if(las>n)
                f=0;
            else
                a[frt]=a[las]=0;
        }
        if(f)
            puts("Yes.");
        else
            puts("No.");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
