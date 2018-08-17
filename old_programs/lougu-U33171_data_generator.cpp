#include<cstdio>
#include<algorithm>
#define maxt 5
#define maxn 40
using namespace std;

int a[(maxn>>1)+1],b[maxn+1];

int main(){
    freopen("lougu-U33171.in","w",stdout);
    printf("%d\n",maxt);
    for(int i=1;i<=maxt;++i){
        printf("%d\n",maxn);
        for(int j=1;j<=maxn;++j)
            printf("%d ",rand()%(maxn>>1)+1);
        printf("\n");
    }
    fclose(stdout);
    return 0;
}
