#include<cstdio>
#include<cstdlib>
#include<ctime>

unsigned long long sum;

int main(){
	for(int i=1;;++i){
		system("LGP4278_data_generator.exe");
		int t1=clock();
		system("LGP4278.exe");
		int t2=clock();
		system("cls");
		printf("Time used: %d ms\n",t2-t1);
		printf("Avarage speed: %lf ms/test\n",1.0*(sum+=t2-t1)/i);
	}
	return 0;
}
