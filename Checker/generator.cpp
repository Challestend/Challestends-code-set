#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define re register
#define rnd() ((int)(rand()*rand()))

int n=100000,m=100000,lwr=60000;
int a[100001];

int main(){
	srand(2281703177LL*time(0));
	freopen("data.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		a[i]=i;
	for(re int i=1;i<=n;++i)
		std::swap(a[i],a[rnd()%n+1]);
	for(re int i=1;i<=n;++i)
		printf("%d%c",a[i],i<n?32:10);
	for(re int i=1;i<=m;++i){
		int len=rnd()%(n-lwr+1)+lwr,l=rnd()%(n-len+1)+1,r=l+len-1;
		printf("%d %d\n",l,r);
	}
	return 0;
}
