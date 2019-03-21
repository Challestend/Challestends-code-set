#include<cstdio>

int n;

int main(){
	scanf("%d",&n);
	printf("%0.16lf",1.0*n*(n+1)/(2*n-1)/2);
	return 0;
}
