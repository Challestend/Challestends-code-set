#include<cstdio>
#include<cstdlib>
using namespace std;

int main(){
    for(unsigned long long i=1;;++i){
        system("lougu-U33171_data_generator.exe");
        system("lougu-U33171.exe");
        system("lougu-U33171_solution.exe");
        printf("Data #%llu:\n",i);
        if(system("fc lougu-U33171.out lougu-U33171.ans"))
            system("pause");
    }
    return 0;
}
