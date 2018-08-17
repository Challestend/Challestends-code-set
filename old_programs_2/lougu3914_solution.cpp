# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>
# define R register
# define mod 1000000007

using namespace std;

int e,n,m,f[5010][5010],h[5010],tot[5010],sum[5010],x,y,d;
struct pp{int v,pre;}ed[10010];

inline void in(R int &a){
    R char c = getchar();R int x=0, f=1;
    while(!isdigit(c)) {if(c == '-') f=-1; c = getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a=x*f;
}

inline void add(R int x,R int y){
    ed[++e] = (pp){y,h[x]};
    h[x] = e;
}

inline void dfs(R int fa,R int x){//树形DP一般用DFS来实现
    for(R int i=h[x]; i; i=ed[i].pre)
    {
        R int p = ed[i].v;
        if(p == fa) continue;
        dfs(x,p);
    }
    for(R int j=1; j<=m; ++j)
    {
        if(!f[x][j]) continue;//没有这种颜色
        for(R int i=h[x]; i; i=ed[i].pre)
        {
            R int p = ed[i].v;
            if(p == fa) continue;
            f[x][j] = 1LL*f[x][j]*(tot[p]-f[p][j])%mod;
        }
        while(f[x][j]<0) f[x][j] += mod;//上边(tot[p]-f[p][j])可能会变成负数，这里把它变回来。
        tot[x] = (1LL*tot[x]+1LL*f[x][j])%mod;
    }
}

inline int yg(){
    in(n),in(m);
    for(R int i=1; i<=n; ++i)
    {
        in(sum[i]);
        for(R int j=1; j<=sum[i]; ++j) in(d),f[i][d]++;
    }
    for(R int i=1; i<n; ++i)
    {
        in(x),in(y);
        add(x,y),add(y,x);
    }
    add(0,1);//为了好写，新建一个原点连向1，这样就不用额外求tot[1]了
    dfs(0,0);
    cout << tot[1];//tot[1]就是最终的答案
}


int main(){
    freopen("lougu3914.in","r",stdin);
    freopen("lougu3914.ans","w",stdout);
    int youngsc = yg();
    fclose(stdin);
    fclose(stdout);
}
