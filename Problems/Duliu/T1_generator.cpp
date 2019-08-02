#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register
#define rnd() (1LL*rand()*rand()*rand()*rand())

int w=2,n=4,m=20,sz=1;

int main(){
	srand(rand()*time(0));
	printf("%d %d %d\n",w,n,m);
	for(re int i=1;i<=w;++i)
		sz*=n;
	for(re int i=1;i<=sz;++i)
		printf("%lld%c",rnd()%2147483648LL,i%n?32:10);
	for(re int i=1;i<=m;++i){
		re int v=1;
		for(re int j=1;j<=w;++j){
			re int d=rnd()%n+1,l=rnd()%(n-d+1)+1;
			printf("%d %d ",l,l+d-1);
			v*=d;
		}
		printf("%lld\n",rnd()%v+1);
	}
	return 0;
}
