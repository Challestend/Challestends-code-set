#include<cstdio>
#include<algorithm>
#include<vector>
#define re register
#define maxn 10000000
#define mod 1000000007

int n;
int f[maxn+1]={0,0,1};

int main(){
	scanf("%d",&n);
	for(re int i=3;i<=n;++i)
		for(re int j=2;j<=i;++j)
			if(i%j){
				f[i]=f[j]+1;
				break;
			}
	for(re int i=1;i<=n;++i)
		if(i%12!=6&&i%840!=420&&f[i]==4)
			printf("f(%d)=%d\n",i,f[i]);
	// for(re int i=1;i<=n;++i){
	// 	printf("%d",f[i]);
	// 	if(i%12==0)
	// 		putchar(10);
	// }
	putchar(10);
	for(re int i=3;i<=n;++i)
		f[i]=1LL*f[i-1]*f[i]%mod;
	printf("%d",f[n]);
    return 0;
}
