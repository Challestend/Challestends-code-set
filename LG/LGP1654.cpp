#include<cstdio>
#define re register
int n;
double A,B,C;

int main(){
    scanf("%d",&n);
    for(re int i=1;i<=n;++i){
        double x;
        scanf("%lf",&x);
        C+=x*(3*B+3*A+1);
        B=x*(B+2*A+1);
        A=x*(A+1);
        printf("%lf %lf %lf\n",A,B,C);
    }
    printf("%lf",C);
    return 0;
}
