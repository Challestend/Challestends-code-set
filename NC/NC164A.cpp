#include<cstdio>
#define re register

int n;
double a,b,x,y;

int main(){
    scanf("%d",&n);
    for(re int i=1;i<=n;++i)
        scanf("%lf%lf",&x,&y),a+=x*y,b+=y;
    printf("%0.1lf",a/b);
    return 0;
}
