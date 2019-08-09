#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define re register
#define rndInt() ((((1LL*rand())<<15|rand())<<15|rand())<<15|rand())
#define rndPer() 1.0*rndInt()/(1LL<<60)

const double PI=acos(-1);

double W=200,H=200;
int n=64;

int main(){
	freopen("1.in","w",stdout);
	srand(time(0));
	srand(rndInt());
	printf("%0.2lf %0.2lf %d\n",W,H,n);
	for(re int i=1;i<=n;++i)
		printf("%0.2lf %0.2lf %0.2lf ",rndPer()*W,rndPer()*H,rndPer()*2.99+1.64),
		printf("%0.2lf %0.2lf\n",rndPer(),rndPer()*2*PI);
	printf("%0.2lf %0.2lf 2.50\n",W/2,H/2);
	return 0;
}
