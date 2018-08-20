#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#define maxn 200010
#define re register
#define FOR(i,l,r) for(re int i=l;i<=r;i++)
using namespace std;

int n,m,k,t,cnt,num,x,y,z,r,p,mod;
int head[maxn],dis[maxn],fa[maxn],son[maxn],ans[maxn*4];
int depth[maxn],tag[maxn*4],siz[maxn],id[maxn],top[maxn];
//fa数组储存父节点，son数组储存重儿子，ans，tag为线段树数组
//depth储存深度，siz储存子树大小，id储存新的位置，top储存每个点所在链最上面的点

struct hz{
	int next;
	int to;
}h[maxn];

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

inline void out(int a){
	if(a<0){
		a*=-1;
		putchar('-');
	}
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

inline void add(int from,int to){
	h[++num].next=head[from];
	h[num].to=to;
	head[from]=num;
}

inline int ls(int k){
	return k<<1;
}

inline int rs(int k){
	return k<<1|1;
}

inline void push_up(int k){
	ans[k]=ans[ls(k)]+ans[rs(k)];
}

inline void ff(int p,int l,int r,int k){
	tag[p]=k;
	ans[p]=(r-l+1)*k;
}

inline void push_down(int p,int l,int r){
	int mid=(l+r)>>1;
	ff(ls(p),l,mid,tag[p]);
	ff(ls(p),mid+1,r,tag[p]);
	tag[p]=0;
}

void build(int p,int l,int r){
	tag[p]=0;
	if(l==r){
		ans[p]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	push_up(p);
}

void update(int nl,int nr,int l,int r,int p,int k){
	if(nl<=l&&r<=nr){
		ans[p]=(r-l+1)*k;
		tag[p]=k;
		return;
	}
	push_down(p,l,r);
	int mid=(l+r)>>1;
	if(nl<=mid) update(nl,nr,l,mid,ls(p),k);
	if(nr>mid) update(nl,nr,mid+1,r,rs(p),k);
	push_up(p);
}

int query(int q_x,int q_y,int l,int r,int p){
	if(q_x<=l&&r<=q_y)
	  return ans[p];
	push_down(p,l,r);
    int res=0;
    int mid=(l+r)>>1;
    if(q_x<=mid) res+=query(q_x,q_y,l,mid,ls(p));
    if(q_y>mid) res+=query(q_x,q_y,mid+1,r,rs(p));
    return res;
}

void dfs1(int f,int ff){
	fa[f]=ff;
	depth[f]=depth[ff]+1;
	siz[f]=1;
	int maxson=-1;
	for(re int i=head[f];i!=0;i=h[i].next){
		if(h[i].to==fa[f])
		  continue;
		dfs1(h[i].to,f);
		siz[f]+=siz[h[i].to];
	    if(siz[h[i].to]>maxson){
	    	maxson=siz[h[i].to];
	    	son[f]=h[i].to;
		}
	}
}

void dfs2(int x,int topf){
	top[x]=topf;
	id[x]=++cnt;
	if(!son[x])
	  return;
	dfs2(son[x],topf);
	for(re int i=head[x];i!=0;i=h[i].next){
		if(h[i].to==son[x]||h[i].to==fa[x])
		  continue;
		dfs2(h[i].to,h[i].to);
	}
}

void updrange(int x,int y,int k){
	while(top[x]!=top[y]){
		if(depth[top[x]]<depth[top[y]])
		  swap(x,y);
		update(id[top[x]],id[x],1,n,1,k);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y])
	  swap(x,y);
	update(id[x],id[y],1,n,1,k);
}

int qrange(int x,int y){
	int anss=0;
	while(top[x]!=top[y]){
		if(depth[top[x]]<depth[top[y]])
		  swap(x,y);
		anss+=query(id[top[x]],id[x],1,n,1);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y])
	  swap(x,y);
	return anss+query(id[x],id[y],1,n,1);
}

void updson(int x,int k){
	update(id[x],id[x]+siz[x]-1,1,n,1,k);
}

int qson(int x){
	return query(id[x],id[x]+siz[x]-1,1,n,1);
}

int main(){  //所有点被我 +1 了
	in(n);
	FOR(i,2,n){
		in(x);
		x+=1;
		add(i,x);
		add(x,i);
	}
	in(m);
	dfs1(1,n+1000);
	dfs2(1,1);
    for(int i=1;i<=n;++i)
        printf("%d ",depth[i]);
    putchar(10);
	build(1,1,n);
	string s;
	FOR(i,1,m){
		cin>>s;
		in(y);
		y+=1;
		if(s[0]=='i'){
            printf("%d\n",qrange(1,y));
			out(depth[y]-qrange(1,y)+1);
			puts("");
			updrange(1,y,1);
		}
		else{
			out(qson(y));
			puts("");
			updson(y,0);
		}
	}
}
