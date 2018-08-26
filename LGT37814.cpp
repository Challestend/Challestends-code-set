#include<cstdio>
#define maxn 1000
#define eps 1e-5
#define abs(a) ((a)>=0?(a):(-(a)))

int n,L,R;
double a[maxn+1],b[maxn+1];

double pow0(double x,int y){
    if(y==0)
        return 1;
    if(y==1)
        return x;
    double res=pow0(x,y>>1);
    res*=res;
    return (y&1)?res*x:res;
}

double fa(double x){
    double res=0;
    for(int i=0;i<=n;++i)
        res+=a[i]*pow0(x,i);
    return res;
}

double fb(double x){
    double res=0;
    for(int i=0;i<n;++i)
        res+=b[i]*pow0(x,i);
    return res;
}

void solve(double l,double r){
    for(;;){
        double mid=(l+r)/2,fl=fb(l),fr=fb(r),fm=fb(mid);
        printf("[%lf,%lf,%lf]\n",l,mid,r);
        printf("[%lf,%lf,%lf]\n\n",fl,fm,fb);
        if(abs(fm)<eps)
            break;
        else
            if(r-l<eps)
                return;
            else
                if(fb(l)*fb(mid)<=0)
                    r=mid;
                else
                    l=mid;
    }
    printf("%lf\n",fa(l));
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<=n;++i)
        scanf("%lf",&a[i]);
    for(int i=1;i<=n;++i)
        b[i-1]=i*a[i];
    for(int i=0;i<n;++i)
        printf("%lf ",b[i]);
    printf("\n");
    scanf("%d%d",&L,&R);
    for(int i=L;i<R;++i)
        solve(i,i+1);
    return 0;
}
