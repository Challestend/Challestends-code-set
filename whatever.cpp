#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register

int P,Q,T,R;
int a[1001][1001];

inline int gcd(re int x,re int y){
	for(;y^=x^=y^=x%=y;);
	return x;
}

inline int check(re int x,re int y){
	for(re int i=0;i<R;++i)
		if(i%P==x&&i%Q==y)
			return i;
	return -1;
}

int main(){
	scanf("%d%d%d",&P,&Q,&T);
	R=P*Q/gcd(P,Q);
	for(re int i=0;i<P;++i)
		for(re int j=0;j<Q;++j)
			a[i][j]=check(i,j);
	// for(re int i=0;i<P;++i)
	// 	for(re int j=0;j<Q;++j)
	// 		printf("%2d%c",a[i][j]>=0?a[i][j]:0,j<Q-1?32:10);
	for(re int i=0;i<P;puts(""),++i)
		for(re int j=0;j<Q;++j)
			if(i%P==0||i%P==1||i%P==3)
				printf("%0.0lf ",a[i%P][j%Q]>=0?std::max(ceil(1.0*(T-a[i%P][j%Q])/R),0.0):0);
			else
				printf("  ");
	for(re int i=0;i<P;puts(""),++i)
		for(re int j=0;j<Q;++j)
			if(j%Q==2||j%Q==4||j%Q==5)
				printf("%0.0lf ",a[i%P][j%Q]>=0?std::max(ceil(1.0*(T-a[i%P][j%Q])/R),0.0):0);
			else
				printf("  ");
	return 0;
}
