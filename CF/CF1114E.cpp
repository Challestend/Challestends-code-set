#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define re register
#define maxn 1000000
#define maxval 1000000000
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))

int n;
int p[maxn+1],a[maxn+1];

inline int gcd(re int x,re int y){
	for(;y^=x^=y^=x%=y;);
	return x;
}

int main(){
	srand(998244353LL*time(0));
	scanf("%d",&n);
	for(re int i=1;i<=n;++i)
		p[i]=i;
	for(re int i=1;i<=n;++i)
		std::swap(p[i],p[1LL*rand()*rand()%n+1]);
	if(n==2){
		printf("? %d\n",1);
		fflush(stdout);
		scanf("%d",&a[1]);
		printf("? %d\n",2);
		fflush(stdout);
		scanf("%d",&a[2]);
		printf("! %d %d\n",min(a[1],a[2]),abs(a[1]-a[2]));
	}
	else{
		for(re int i=1;i<=n&&i<=30;++i){
			printf("? %d\n",p[i]);
			fflush(stdout);
			scanf("%d",&a[i]);
		}
		re int g=gcd(abs(a[2]-a[1]),abs(a[3]-a[2]));
		for(re int i=4;i<=n&&i<=30;++i)
			g=gcd(g,abs(a[i]-a[i-1]));
		re int L=a[1],R=min(a[1]+(n-1)*g,maxval);
		for(;L<R;){
			re int mid=(L+R+1)>>1;
			int ex;
			printf("> %d\n",mid-1);
			fflush(stdout);
			scanf("%d",&ex);
			ex?(L=mid):(R=mid-1);
		}
		L-=(n-1)*g;
		printf("! %d %d\n",L,g);
	}
	return 0;
}
