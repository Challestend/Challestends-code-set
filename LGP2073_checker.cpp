#include<cstdlib>

int main(){
    for(;;){
        system("LGP2073_date_generator.exe");
        system("LGP2073.exe");
        system("LGP2073_solution.exe");
        if(system("fc LGP2073.out LGP2073.ans"))
            system("pause");
    }
    return 0;
}
