#include<cstdio>
#include<cmath>
#define re register

int n,sum;
double a[100001];
int c[100001],f[100001];

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i){
		scanf("%lf",&a[i]);
		c[i]=ceil(a[i]);
		f[i]=floor(a[i]);
		sum+=c[i];
	}
	if(sum){
		sum=sum>0?sum:-sum;
		for(re int i=1;i<=sum;++i)
			if(c[i]!=f[i])
				c[i]=f[i];
			else
				sum++;
	}
	for(re int i=1;i<=n;++i)
		printf("%d\n",c[i]);
	return 0;
}
