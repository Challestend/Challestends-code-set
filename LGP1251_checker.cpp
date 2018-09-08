#include<cstdlib>

int main(){
    for(;;){
        system("LGP1251_data_generator.exe");
        system("LGP1251.exe");
        system("LGP1251_solution.exe");
        if(system("fc LGP1251.out LGP1251.ans"))
            system("pause");
    }
    return 0;
}
