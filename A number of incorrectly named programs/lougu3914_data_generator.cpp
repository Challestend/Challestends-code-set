#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<set>
#define maxn 2000
#define maxm 2000
#define random(a) rand()*rand()%(a)+1
using namespace std;

set<int> s;
set<int>::iterator p;
struct edge{
    int src,des;
};
edge e[maxn+1];

int main(){
    srand(time(0));
    freopen("lougu3914.in","w",stdout);
    printf("%d %d\n",maxn,maxm);
    for(int i=1;i<=maxn;++i){
        int x=random(maxm);
        printf("%d ",x);
        s.clear();
        for(;s.size()<x;s.insert(random(maxm)));
        for(p=s.begin();p!=s.end();++p)
            printf("%d ",*p);
        printf("\n");
    }
    for(int i=2;i<=maxn;++i)
        e[i-1].src=random(i-1),e[i-1].des=i;
    random_shuffle(e+1,e+maxn);
    for(int i=1;i<maxn;++i)
        printf("%d %d\n",e[i].src,e[i].des);
    fclose(stdout);
    return 0;
}
