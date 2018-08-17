#include<cstdio>
#include<algorithm>
#define maxn 300
#define max(a,b) ((a)>=(b)?(a):(b))
using namespace std;

int T,n;
struct alien{
    int app,lat,dis;
};
alien a[maxn+1];

bool cmp(alien x,alien y){
    if(x.lat<y.lat)
        return true;
    else
        if(x.app<y.app)
            return true;
        else
            if(x.dis<y.dis)
                return true;
            else
                return false;
}

int main(){
    scanf("%d",&T);
    for(int t=1;t<=T;++t){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d%d%d",&a[i].app,&a[i].lat,&a[i].dis);
        sort(a+1,a+n+1,cmp);
        int ans=0,atk=0,cur=0,maxdis=0;
        for(int i=1;i<=n;++i){
            if(a[i].app>atk)
                if(!cur)
                    cur=a[i].lat,maxdis=a[i].dis;
                else
                    if(a[i].lat==cur)
                        maxdis=max(maxdis,a[i].dis);
                    else
                        atk=cur,cur=0,ans+=maxdis,maxdis=0,--i;
            printf("i=%d,atk=%d,cur=%d,maxdis=%d,ans=%d;\n",i,atk,cur,maxdis,ans);
        }
        printf("%d\n",ans+maxdis);
    }
    return 0;
}
