#include<cstdio>
#include<cstdlib>
#include<ctime>
#define re register
#define maxn 10
#define max1 10000000
#define max2 10000
#define random(a,b) (rand()%((b)-(a)+1)+(a))

int main(){
    srand(time(0));
    freopen("LGP1251.in","w",stdout);
    printf("%d\n",maxn);
    for(re int i=1;i<=maxn;++i)
        printf("%d ",random(1,max1));
    printf("\n");
    int t1=random(1,maxn),p1=random(1,max2);
    printf("%d %d %d %d %d",random(1,max2),t1,p1,random(t1,maxn),random(1,p1));
    fclose(stdout);
    return 0;
}
