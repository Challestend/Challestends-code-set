#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register

double T1,T2;

int main(){
	int n;
	scanf("%d",&n);
	for(re int i=0;i<=n;++i){
		system("generator.exe");
		re double t0=clock();
		system("clt.exe");
		re double t1=clock();
		system("solution.exe");
		re double t2=clock();
		system("cls");
		printf("Test Case #%d/%d:\n",i,n);
		printf("Current:\n\t%9.3lf ms/%9.3lf ms\n",t1-t0,t2-t1);
		if(i>0)
			printf("Averange:\n\t%9.3lf ms/%9.3lf ms\n",(T1+=t1-t0)/i,(T2+=t2-t1)/i);
		if(system("fc data.out data.ans > nul")){
			printf("FAQ");
			return 0;
		}
	}
	return 0;
}
