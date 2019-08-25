#include<cstdio>
#define re register
#define mod 490019

int a[mod];

int main(){
	// for(re int i=2;i<mod;++i)
	// 	if(mod%i==0)
	// 		printf("%d\n",i);
	for(re int i=0,j=1;i<mod;++i,j=2LL*j%mod){
		a[j]&&printf("%d %d %d\n",a[j],i,j);
		a[j]=i;
	}
	return 0;
}
