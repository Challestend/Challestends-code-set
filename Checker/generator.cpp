#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define re register
#define rnd() (1LL*rand()*rand())

int n=10,m=10,lwr=1;

int main(){
	srand(2281703177LL*time(0));
	freopen("data.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		printf("%d%c",rand()&1,i<n?32:10);
	for(re int i=1;i<=m;++i){
		re int len=rnd()%(n-lwr+1)+lwr,l=rnd()%(n-len+1)+1;
		printf("%d %d %d\n",rand()%7+1,l,l+len-1);
	}
	return 0;
}
