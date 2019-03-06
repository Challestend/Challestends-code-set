#include"F:/clt/testlib-0.9.12/testlib.h"
#include<cstdlib>
#include<cmath>
#define re register
#define BIGINT 2000000000
#define MAXINT 2147483647
#define BIGLL 9000000000000000000LL

long long _n[]={0,20,20,20,BIGINT,BIGLL,BIGLL,BIGLL,BIGLL,BIGLL,BIGLL};
int _m[]={0,10,10,10,1,24,24,24,32,32,32};

int main(int argc,char* argv[]){
	registerGen(argc,argv,1);
	for(re int i=1;i<=10;++i){
		startTest(i);
		printf("%lld %d %d %d\n",_n[i],_m[i],rnd.next(1,MAXINT/10)*10+1,rnd.next(1,MAXINT/10)*10+1);
	}
}
