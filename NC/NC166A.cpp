#include<cstdio>
#include<cmath>
#define re register
#define Pi acos(-1.0)

int r;

int main(){
    scanf("%d",&r);
    double a=Pi/17,ans=17.0*r*r*cos(a)*sin(a);
    printf("%0.6lf",ans);
    return 0;
}
