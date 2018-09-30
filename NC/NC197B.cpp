#include<cstdio>
#include<cmath>
#define Pi acos(-1.0)
#define eps 1e-6

double n,r1,r0;

int main(){
    scanf("%lf%lf%lf",&n,&r1,&r0);
    double a=Pi/n,r2=r1*cos(a),ans=Pi*r0*r0+n*r1*r2*sin(a);
    if(r0-r1>=-eps){
        printf("%0.2lf",ans-n*r1*r2*sin(a));
        return 0;
    }
    if(r2-r0>=-eps){
        printf("%0.2lf",ans-Pi*r0*r0);
        return 0;
    }
    double r3=sqrt(r0*r0-r2*r2),a1=a-acos(r2/r0);
    printf("%0.2lf",ans-n*(r2*r3+a1*r0*r0));
    return 0;
}
