#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define re register
#define maxn 1000000
#define maxm 1000000
#define rnd() (rand()*rand())

int n=10,m=10;
int a[maxn+1],l[maxm+1],r[maxm+1];

int main(){
	srand((1000000007*time(0))^998244353);
	freopen("data.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		a[i]=i;
	for(re int i=2;i<=n;++i)
		std::swap(a[i],a[rnd()%(i-1)+1]);
	for(re int i=1;i<=n;++i)
		printf("%d ",a[i]);
	puts("");
	for(re int i=1;i<=m;++i){
		re int x=rnd()%n+1;
		l[i]=rnd()%(n-x+1)+1;
		r[i]=l[i]+x-1;
	}
	for(re int i=1;i<=m;++i)
		printf("%d ",l[i]);
	puts("");
	for(re int i=1;i<=m;++i)
		printf("%d ",r[i]);
	puts("");
	return 0;
}
