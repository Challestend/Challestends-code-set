#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 100000
#define maxm 100000
using namespace std;

int T,n,m,ec,sum;
int des[maxm+1],suc[maxm+1],las[maxn+1],ind[maxn+1],ans[maxn+1];
priority_queue<int> h;

void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
    ++ind[y];
}

int main(){
    scanf("%d",&T);
    for(int t=1;t<=T;++t){
        scanf("%d%d",&n,&m);
        ec=0;
        memset(las,0,sizeof(las));
        memset(ind,0,sizeof(ind));
        for(int i=1;i<=m;++i){
            int x,y;
            scanf("%d%d",&x,&y);
            connect(y,x);
        }
        sum=0;
        for(int i=1;i<=n;++i)
            if(!ind[i])
                ++sum,h.push(i);
        for(int i=1;i<=n;++i){
            ans[i]=h.top();
            h.pop();
            for(int j=las[ans[i]];j;j=suc[j])
                if(!(--ind[des[j]]))
                    ++sum,h.push(des[j]);
            if(sum<n&&h.empty())
                break;
        }
        if(sum==n)
            for(int i=n;i>=1;--i)
                printf("%d ",ans[i]);
        else
            printf("Impossible!");
        putchar(10);
    }
    return 0;
}
