#include<cstdio>
#define re register
#define maxn 10000

int n,m;
double p0;
double p[maxn+1],ans[2][maxn+1];

inline double cltpow(re double x,re int y){
	re double res=1;
	for(;y;y>>=1){
		if(y&1)
			res*=x;
		x*=x;
	}
	return res;
}

int main(){
	scanf("%lf%d%d",&p0,&n,&m);
	if(p0==0){
		printf("0");
		return 0;
	}
	if(p0==1){
		printf("%d",m==n);
		return 0;
	}
	p[0]=1;
	for(re int i=1;i<=n;++i)
		p[i]=p[i-1]*(1-p0);
	ans[1][1]=1;
	for(re int i=2;i<=n;++i){
		re double res=0;
		for(re int j=1;j<i;++j)
			res=(1-p0)*res+ans[(i-1)&1][j%i];
		for(re int j=1;j<=i;++j){
			res=(1-p0)*res+(1-p[i])*ans[(i-1)&1][j-1];
			ans[(i)&1][j]=p0/(1-p[i])*res;
			printf("%d %d %0.16lf\n",i,j,ans[i&1][j]);
		}
	}
	printf("%0.16lf",ans[n&1][m]);
	return 0;
}
