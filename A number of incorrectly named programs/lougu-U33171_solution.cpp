#include<cstdio>
#define maxn 40
using namespace std;

int t,n,ans;
int a[maxn+1],b[(maxn>>1)+1],c[(maxn>>1)+1];

void dfs(int cur){
    if(cur==n)
        ans=1;
    else{
        if(b[0]<(n>>1)&&b[0]>=c[0]||(b[0]<c[0]&&a[cur+1]==c[b[0]+1])){
            b[++b[0]]=a[cur+1];
            dfs(cur+1);
            --b[0];
        }
        if(c[0]<(n>>1)&&c[0]>=b[0]||(c[0]<b[0]&&a[cur+1]==b[c[0]+1])){
            c[++c[0]]=a[cur+1];
            dfs(cur+1);
            --c[0];
        }
    }
}

int main(){
    freopen("lougu-U33171.in","r",stdin);
    freopen("lougu-U33171.ans","w",stdout);
    scanf("%d",&t);
    for(;t;--t){
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        ans=0;
        dfs(0);
        if(ans)
            puts("Yes.");
        else
            puts("No.");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
