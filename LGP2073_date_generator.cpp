#include<cstdio>
#include<cstdlib>
#include<ctime>
#define maxn 20
#define maxv 1000000
#define random(a,b) (rand()%((b)-(a)+1)+(a))

int main(){
    srand(time(0));
    freopen("LGP2073.in","w",stdout);
    for(int i=1;i<=maxn;++i){
        int x=random(1,3);
        printf("%d ",x);
        if(x==1)
            printf("%d %d\n",random(1,maxv),random(1,maxv));
        else
            putchar(10);
    }
    puts("-1");
    return 0;
}
