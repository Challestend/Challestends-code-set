#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register

int n=20,m=20;

int main(){
	srand(time(0));
	srand(998244353);
	freopen("data.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		printf("%d ",rand()%n+1);
	puts("");
	for(re int i=1;i<=m;++i)
		printf("%d %d\n",rand(),rand());
	return 0;
}
