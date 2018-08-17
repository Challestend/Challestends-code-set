#include<cstdio>
#include<cstring>
#define maxn 500000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int n,m,k,head,tail;
int pos[maxn+1],scr[maxn+1],h[maxn+1];
long long f[maxn+1];

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&pos[i],&scr[i]);
    for(int i=1;i<=n&&scr[0]<k;++i)
        if(scr[i]>0)
            scr[0]+=scr[i];
    if(scr[0]<k){
        printf("-1");
        return 0;
    }
    int L=0,R=pos[n];
    for(;L<R;){
        int mid=L+R>>1;
        head=tail=0;
        memset(f,254,sizeof(f));
        f[0]=0;
        int cur=1;
        for(;pos[cur]<m-mid;++cur);
        for(int i=cur,j=1;i<=n&&!f[0];++i){
            for(;j<=n&&pos[j]+max(m-mid,1)<=pos[i];++j){
                for(;head<tail&&f[h[tail]]<f[j];--tail);
                h[++tail]=j;
            }
            for(;head<tail&&pos[h[head+1]]+m+mid<pos[i];++head);
            if(head<tail)
                if(pos[i]<=m+mid)
                    f[i]=max(scr[i],f[h[head+1]]+scr[i]);
                else
                    f[i]=f[h[head+1]]+scr[i];
            else
                if(pos[i]<=m+mid)
                    f[i]=scr[i];
            if(f[i]>=k)
                f[0]=1;
        }
        if(f[0])
            R=mid;
        else
            L=mid+1;
    }
    printf("%d",R);
    return 0;
}
