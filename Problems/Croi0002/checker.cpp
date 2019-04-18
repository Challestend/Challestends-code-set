#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register

double T1,T2;

int main(){
	for(re int i=1;;++i){
		printf(".");
		system("generator1.exe");
		printf("\b#.");
		re double t0=clock();
		system("force1.exe");
		printf("\b#.");
		re double t1=clock();
		system("std1_new.exe");
		printf("\b#");
		// system("std1.exe");
		re double t2=clock();
		system("cls");
		printf("Test Case #%d:\n",i);
		printf("Current:\n\t%20.12lf ms/%20.12lf ms\n",t1-t0,t2-t1);
		printf("Averange:\n\t%20.12lf ms/%20.12lf ms\n",(T1+=t1-t0)/i,(T2+=t2-t1)/i);
		if(system("fc data1.ans data1.out > nul")){
			printf("FAQ");
			return 0;
		}
	}
	return 0;
}
