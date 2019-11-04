#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register

double T1,T2;

int main(){
	for(re int i=1;;++i){
		// system("generator1.exe");
		re double t0=clock();
		system("std1_new.exe < data/l1.in > data.ans");
		re double t1=clock();
		system("std1_new_new.exe < data/l1.in > data.out");
		// system("std1_new_new_new.exe < data/l1.in > data.out");
		re double t2=clock();
		system("cls");
		printf("Test Case #%d:\n",i);
		printf("Current:\n\t%20.12lf ms/%20.12lf ms\n",t1-t0,t2-t1);
		printf("Averange:\n\t%20.12lf ms/%20.12lf ms\n",(T1+=t1-t0)/i,(T2+=t2-t1)/i);
		if(system("fc data.out data.ans > nul")){
			printf("FAQ");
			return 0;
		}
	}
	return 0;
}
