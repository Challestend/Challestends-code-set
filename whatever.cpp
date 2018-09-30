#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
#define maxn 100600
#define maxnn 320
#define re register
#define FOR(i,l,r) for(re int i=l;i<=r;++i)
using namespace std;

int n,m,c,r,t,g,y,z,x,sq;
int fa[maxn],rt[maxnn][maxn],a[maxn],b[maxn],pos[maxn],tag[maxnn],maxx[maxnn],minn[maxnn];
set<int> se[maxnn];

#ifdef ONLINE_JUDGE
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){if(A==B){B=(A=ss)+fread(ss,1,1<<17,stdin);if(A==B)return EOF;}return*A++;}
template<class T>inline void read(T&x){
    static char c;static int y;
    for(c=gc(),x=0;c<48||57<c;c=gc())
    for(;48<=c&&c<=57;c=gc())x=((x+(x<<2))<<1)+(c^'0');
}
#else
void read(re int&x){scanf("%d",&x);}
#endif

inline void out(re int a){
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

inline int find(re int x){
    while(x!=fa[x])x=fa[x]=fa[fa[x]];
    return x;
}

inline void pre(re int x){
//	maxx[x]=0;
	minn[x]=100001;
	FOR(i,(x-1)*sq+1,min(x*sq,n)){
//		if(a[i]>maxx[x])
//		  maxx[x]=a[i];
		if(a[i]<minn[x])
		  minn[x]=a[i];
		if(rt[x][a[i]]!=0){
			fa[i]=rt[x][a[i]];
		}
		else{
			pos[i]=a[i],
			rt[x][a[i]]=i,
			fa[i]=i;
			se[x].insert(a[i]);
		}
	}
}

inline void del(re int x){
	FOR(i,(x-1)*sq+1,x*sq){
		a[i]=pos[find(i)],
		rt[x][a[i]]=0,
		a[i]+=tag[x];
	}
	FOR(i,(x-1)*sq+1,x*sq)
	  fa[i]=0;
	tag[x]=0;
	se[x].clear();
}

inline void solve(re int x,re int z){
	if((maxn-z)*2>=maxn-minn[x]-tag[x]){
		FOR(i,z-tag[x]+1,maxn){
			if(rt[x][i]){
				se[x].erase(i);
		  		if(rt[x][i-z]!=0){
		  			fa[rt[x][i]]=rt[x][i-z];
				}
				else{
					rt[x][i-z]=rt[x][i],
					pos[rt[x][i]]=i-z;
					se[x].insert(i-z);
				}
		  		rt[x][i]=0;
		  	}
		}
		tag[x]+=z;
	}
	else{
		FOR(i,minn[x],z-tag[x]){
			if(rt[x][i]){
				se[x].erase(i);
				if(rt[x][i+z]!=0){
					fa[rt[x][i]]=rt[x][i+z];
				}
				else{
					rt[x][i+z]=rt[x][i],
					pos[rt[x][i]]=i+z;
					se[x].insert(i+z);
				}
				rt[x][i]=0;
			}
		}
		minn[x]=max(minn[x],z-tag[x]);
	}
}

inline void doit(re int x,re int y,re int z){
    del(b[x]);
    FOR(i,x,min(y,b[x]*sq)){
    	if(a[i]<z)
		  a[i]+=z;
	}
	pre(b[x]);
    if(b[x]!=b[y]){
    	del(b[y]);
    	FOR(i,(b[y]-1)*sq+1,y){
      	  if(a[i]<z)
			a[i]+=z;
		}
		pre(b[y]);
	}
    FOR(i,b[x]+1,b[y]-1){
    	solve(i,z);
	}
}

inline int query(int x,int y,int z){
	int ans=-1;
	FOR(i,x,min(y,b[x]*sq))
	  if(pos[find(i)]+tag[b[x]]<z) ans=max(ans,pos[find(i)]+tag[b[x]]);
	if(b[x]!=b[y])
	  FOR(i,(b[y]-1)*sq+1,y)
	    if(pos[find(i)]+tag[b[y]]<z) ans=max(ans,pos[find(i)]+tag[b[y]]);
	FOR(i,b[x]+1,b[y]-1){
		set<int>::iterator it=se[i].lower_bound(z-tag[i]);
		if(it==se[i].begin())
		  continue;
		--it;
		ans=max(ans,*it+tag[i]);
	}
	return ans;
}

int main(){
//	freopen("a.in","r",stdin);
//	freopen("a1.out","w",stdout);
	read(n),read(m);
	sq=sqrt(n);
	FOR(i,1,n)
	  read(a[i]),b[i]=(i-1)/sq+1;
    FOR(i,1,b[n]){
    	pre(i);
	}
	while(m--){
		read(t),read(x),read(y),read(z);
		if(t==1){
			doit(x,y,z);
		}
		else{
			out(query(x,y,z));
			puts("");
		}
	}
}
