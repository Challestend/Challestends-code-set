#include<cstdio>
#include<cstdlib>
#include<ctime>

int main(){
    for(int cnt=1;;++cnt){
        system("LGP4247_data_generator.exe");
        printf("Now test %d.\n",cnt);
        int t0=clock();
        system("LGP4247_solution.exe");
        int t1=clock();
        printf("Jury's program used %dms.\n",t1-t0);
        system("LGP4247.exe");
        int t2=clock();
        if(t2-t1>6000){
            printf("TLE on test %d.\n",cnt);
            printf("Participant's program used %dms.\n",t2-t1);
            return 0;
        }
        printf("Participant's program used %dms.\n",t2-t1);
        if(system("fc LGP4247.out LGP4247.ans > nul")){
            printf("WA on test %d\nDetails:\n",cnt);
            system("fc LGP4247.out LGP4247.ans");
            return 0;
        }
        printf("OK. Correst answer.\n");
    }
}
