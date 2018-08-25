#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100010
#define INF 1e9
#define FOR(i,l,r) for(re int i=l;i<=r;i++)
using namespace std;

int cnt[maxn],val[maxn],ans[maxn],ch[maxn][2],siz[maxn],fa[maxn];
int n,m,k,t,tot,num,x,z,root,anss;

inline void in(int &x){
    x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c==-1) return;
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    x=x*f;
}

int New(int v,int f){
    ans[++tot]=v;
    siz[tot]=1;
    fa[tot]=f;
    cnt[tot]=1;
    return tot;
}

void push_up(int k){
    siz[k]=cnt[k]+siz[ch[k][0]]+siz[ch[k][1]];
}

bool pd(int x){
    return ch[fa[x]][1]==x;
}

void rotate(int id){
    int f=fa[id];
    int ff=fa[f];
    int d=pd(id),d1=pd(f);//如果id为f的左子节点则为0，右子节点则为1 d1同理
    fa[ch[id][d^1]]=f;
    ch[f][d]=ch[id][d^1];
    fa[f]=id;
    ch[id][d^1]=f;
    fa[id]=ff;
    ch[ff][d1]=id;
    push_up(f),push_up(id);
}

inline void splay(int x){
    for(int y;y=fa[x];rotate(x))
      if(fa[y])
        rotate(pd(x)==pd(y)?y:x);
    root=x;
}

inline void build(){
    root=New(-INF,0),ch[0][1]=root,ch[root][1]=New(INF,root);
    push_up(root);
    // splay(root);
}

void insert(int cur,int v){
    for(int side;;cur=ch[cur][side]){
        if(v==val[cur]){
            ++cnt[cur];
            splay(cur);
            return;
        }
        side=v>val[cur];
        if(!ch[cur][side]){
            ch[cur][side]=New(v,cur);
            splay(ch[cur][side]);
            return;
        }
    }
}

inline int get_pre(int x){
    int tem=ch[x][0];
    while(ch[tem][1]) tem=ch[tem][1];
    return val[tem];
}

inline int get_next(int x){
    int tem=ch[x][1];
    while(ch[tem][0]) tem=ch[tem][0];
    return val[tem];
}

int main(){
    in(n);
    build();//先加INF和-INF进去（没有半点卵用）
    FOR(i,1,n){
        in(x);
        insert(root,x);
        if(i==1) anss+=x;
        else
          if(cnt[root]<=1)
            printf("pre=%d, suc=%d.\n",get_pre(root),get_next(root)),
            anss+=min(abs(x-get_pre(root)),abs(x-get_next(root)));
        printf("Current ans is %d.\n",anss);
    }
    printf("%d",anss);
}
