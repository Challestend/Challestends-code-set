#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"F:/clt/Libraries/cltrnd.h"
#define re register

int n,l,r;

int main(){
	cltlib::srnd(998244353*time(0));
	scanf("%d%d%d",&n,&l,&r);
	for(re int i=1;i<=n;putchar(cltlib::rnd()%(r-l+1)+l),++i);
	return 0;
}
