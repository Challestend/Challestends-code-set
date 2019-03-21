#include<cstdio>
#define re register
#define mod 1000000007
#define sqrt2 59713600

int n;

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;){
		if(y&1)
			res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}

int main(){
	scanf("%d",&n);
	printf("%lld",1LL*(cltpow(1+sqrt2,n)-cltpow(1-sqrt2+mod,n)+mod)*cltpow(sqrt2<<1,mod-2)%mod);
	return 0;
}
