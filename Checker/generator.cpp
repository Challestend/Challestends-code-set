#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register
#define maxval 100000000

int n=100000;
int f[maxval+1],g[maxval+1];

int main(){
	srand(time(0));
	srand(998244353);
	freopen("data.in","w",stdout);
	puts("FAQ");
	for(re int i=2;i<=maxval;++i){
		if(!f[i])
			g[++g[0]]=i;
		for(re int j=1;j<=g[0]&&i*g[j]<=maxval;++j){
			f[i*g[j]]=1;
			if(i%g[j]==0)
				break;
		}
	}
	printf("%d\n",n);
	for(re int i=2;i<=n;++i)
		printf("%lld %d %d\n",1LL*rand()*rand()%(i-1)+1,i,g[1LL*rand()*rand()%(g[0]/2)+g[0]/2]);
	return 0;
}
