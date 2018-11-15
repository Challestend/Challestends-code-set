#include<cstdio>
#define re register

int n;
double ans;

int main(){
	scanf("%d",&n);
	for(re int i=1;i<n;ans+=1.0/i,++i);
	printf("%0.5lf",ans+(n>1));
	return 0;
}
