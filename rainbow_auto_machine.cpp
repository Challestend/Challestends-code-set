#include<cstdio>

int n;

void memory_limit_exceeding_auto_machine(int x){
    int y=x;
    memory_limit_exceeding_auto_machine(y);
}

int main(){
    scanf("%d",&n);
    switch(n){
        case 3:
            printf("%d",1/0);
            break;
        case 4:
            while(1);
            break;
        case 5:
            memory_limit_exceeding_auto_machine(0);
            break;
        case 6:
            while(1)
                puts("...............................................................................");
            break;
        default:
            putchar(49);
    }
    return 0;
}
