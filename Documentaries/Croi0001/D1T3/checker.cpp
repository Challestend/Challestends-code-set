#ifdef ONLINE_JUDGE
	#include"testlib.h"
#else
	#include"F:/clt/testlib-0.9.12/testlib.h"
#endif
#include<cmath>
#define re register

int main(int argc,char* argv[]){
	registerTestlibCmd(argc,argv);
	re double pans=ouf.readDouble(),jans=ans.readDouble();
	if(abs(pans-jans)<1e-4)
		quitf(_ok,"Congratulations! You've AKed IOI!");
	else
		quitf(_wa,"Your idiot! Get away with your 0 point!");
}
