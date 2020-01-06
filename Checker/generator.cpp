#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register

int n=10000,m=10000;

int main(){
	srand(time(0));
	srand(998244353);
	freopen("data.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		printf("%d ",rand()%n+1);
	puts("");
	for(re int i=1;i<=m;++i){
		re int l=rand()%n+1,r=rand()%n+1;
		if(l>r)
			l^=r^=l^=r;
		printf("%d %d\n",l,r);
	}
	return 0;
}
