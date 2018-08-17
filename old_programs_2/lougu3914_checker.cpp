#include<cstdlib>
using namespace std;

int main(){
    for(;;){
        system("lougu3914_data_generator.exe");
        system("lougu3914.exe");
        system("lougu3914_solution.exe");
        if(system("fc lougu3914.out lougu3914.ans"))
            system("pause");
    }
    return 0;
}
