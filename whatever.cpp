#include<cstdio>
#define re register

int n,l=20;

int main(){
	scanf("%d",&n);
	for(re int n0=0;n0<=n;++n0)
		for(re int i=0,m;i<=n0&&i<=l;++i)
			printf("%2d%c",i==0?n0:m=i==1?1:2*m<=n0?2*m:(2*m-1)%n0,i<n0&&i<l?32:10);
	return 0;
}
