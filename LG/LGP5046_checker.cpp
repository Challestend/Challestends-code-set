#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register

int main(){
	for(re int cnt=1;;++cnt){
		system("cls");
		printf("Running on test %d...\n",cnt);
		system("LGP5046_data_generator.exe");
		system("LGP5046_solution.exe");
		int t1=clock();
		system("LGP5046.exe");
		int t2=clock();
		printf("Participant's program exited after %d ms.\n",t2-t1);
		if(system("fc LGP5046.out LGP5046.ans > nul")){
			printf("Wrong answer.\n");
			system("fc LGP5046.out LGP5046.ans");
			return 0;
		}
		else
			printf("Accepted.\n");
		for(re int i=1;i<2147483647;++i);
	}
	return 0;
}
