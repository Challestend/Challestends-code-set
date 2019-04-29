#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define re register
#define rnd() ((int)(rand()*rand()))

int n=50000,m=50000,mx1=1000000,mx2=100;

int main(){
	srand(2281703177LL*time(0));
	freopen("data.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		printf("%d%c",rnd()%mx1+1,i<n?32:10);
	for(re int i=2;i<=n;++i)
		printf("%d %d\n",rnd()%(i-1)+1,i);
	for(re int i=1;i<=m;++i)
		if(rnd()%4<=2)
			printf("%d %d %d\n",rnd()%3<=1?rnd()%2+1:4,rnd()%n+1,rnd()%n+1);
		else
			printf("%d %d %d %d\n",3,rnd()%n+1,rnd()%n+1,rnd()%mx2+1);
	return 0;
}
