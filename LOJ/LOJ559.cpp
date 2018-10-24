#include<cstdio>

int n,m,l,d;

int main(){
    scanf("%d%d%d%d",&n,&m,&l,&d);
    puts("move_left");
    fflush(stdout);
    scanf("%d",&n);
    if(!n)
        puts("reverse");
    for(;;){
        puts("move_left");
        fflush(stdout);
        scanf("%d",&n);
        puts("reach_dest");
        fflush(stdout);
        scanf("%d",&n);
    }
    return 0;
}
