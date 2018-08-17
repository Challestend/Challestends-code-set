#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#define maxn 16
#define max(a,b) ((a)>=(b)?(a):(b))
using namespace std;

int n,ans;
string s[maxn+1];
int len[maxn+1],a[26],g[maxn+1],h[maxn+1],c[maxn+1][maxn+1],f[maxn+1][maxn+1];

bool cmp(string x,string y){
    return x.length()>y.length();
}

void dfs(int cur,int las,int res){
    printf("%d %d %d %d\n",cur,las,res,f[cur][las]);
    if(res<f[cur][las])
        return;
    else
        f[cur][las]=res;
    ans=max(ans,f[cur][las]);
    for(int i=1;i<=n;++i)
        if(c[las][i]&&!h[i]){
            h[i]=1;
            dfs(cur+1,i,res+len[i]);
            h[i]=0;
        }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        cin>>s[i];
    putchar(10);
    sort(s+1,s+n+1,cmp);
    for(int i=1;i<=n;++i)
        cout<<s[i]<<endl;
    for(int i=1;i<=n;++i){
        len[i]=s[i].length();
        if(!a[s[i][len[i]-1]-'A'])
            a[s[i][len[i]-1]-'A']=1;
        else
            g[i]=1;
        c[0][i]=1;
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(i!=j&&s[i][len[i]-1]==s[j][0])
                c[i][j]=1;
    for(int i=1;i<=n;++i)
        if(!g[i]){
            h[i]=1;
            dfs(1,i,len[i]);
            h[i]=0;
        }
    printf("%d",ans);
    return 0;
}
