#include<cstdio>
#include<queue>
#define maxn 30000
#define maxm 5000
using namespace std;

int n,m,ec;
int des[3*maxn+maxm+1],len[3*maxn+maxm+1],suc[3*maxn+maxm+1],las[maxn+1];
int ex[maxn+1],dis[maxn+1];
queue<int> h;

void connect(int x,int y,int z){
    des[++ec]=y;
    len[ec]=z;
    suc[ec]=las[x];
    las[x]=ec;
}

void spfa(){
    for(int i=1;i<=n;++i)
        dis[i]=-2e9;
    h.push(0),ex[0]=1;
    for(;!h.empty();){
        int x=h.front();
        h.pop();
        ex[x]=0;
        for(int i=las[x];i;i=suc[i])
            if(dis[des[i]]<dis[x]+len[i]){
                dis[des[i]]=dis[x]+len[i];
                if(!ex[des[i]])
                    h.push(des[i]),ex[des[i]]=1;
            }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;++i)
        connect(0,i,0);
    for(int i=1;i<=n;++i)
        connect(i-1,i,0),connect(i,i-1,-1);
    for(int i=1;i<=m;++i){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        connect(x-1,y,z);
    }
    spfa();
    printf("%d",dis[n]);
    return 0;
}
