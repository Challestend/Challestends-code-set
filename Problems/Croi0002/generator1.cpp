#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register
#define rnd() (1LL*rand()*rand())
// #define rnd() rand()

int n=20,m=20,lwr=1,upr=n,maxval=1E9;
int _opt[]={1,1,1,2,2,2,3,3,3,3};

int main(){
	srand(2281701377LL*time(0));
	freopen("data1.in","w",stdout);
	printf("%d %d\n",n,m);
	for(re int i=1;i<=n;++i)
		printf("%d ",2*(int)(rnd()%maxval)+1);
	puts("");
	for(re int i=1;i<n;++i)
		printf("%d ",(int)(rnd()&1));
		// printf("1 ");
	puts("");
	for(re int i=1;i<=m;++i){
		re int opt=_opt[rnd()%10],len=rnd()%(upr-lwr)+lwr,l=rnd()%(n-len+1)+1,r=l+len-1;
		if(opt==1)
			printf("%d %d %d %d\n",opt,l,r,2*(int)(rnd()%maxval)+1);
		if(opt==2)
			printf("%d %d %d %lld\n",opt,l-(l==n),r-(r==n),rnd()&1);
		if(opt==3)
			printf("%d %d %d\n",opt,l,r);
	}
	return 0;
}
