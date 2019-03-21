#include<cstdio>
#define re register

long long x,y;
long long a[100];

int main(){
	scanf("%lld%lld",&x,&y);
	for(;y;a[++a[0]]=y%x,y/=x);
	printf("%lld\n",a[0]);
	for(re int i=1;i<=a[0];++i)
		printf("%lld ",a[i]);
	return 0;
}
