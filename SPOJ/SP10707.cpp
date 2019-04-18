#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 40000
#define maxm 100000
#define swap(a,b) (a^=b,b^=a,a^=b)
#define add(a) (cnt[a]||(++cnt[0]),++cnt[a])
#define del(a) (--cnt[a],cnt[a]||(--cnt[0]))

namespace cltstream{
	#define size 1048576
	char cltin[size+1],*ih=cltin,*it=cltin;
	inline char gc(){
		#ifdef ONLINE_JUDGE
			if(ih==it){
				it=(ih=cltin)+fread(cltin,1,size,stdin);
				if(ih==it)
					return EOF;
			}
			return *ih++;
		#else
			return getchar();
		#endif
	}

	char cltout[size+1],*oh=cltout,*ot=cltout+size;
	inline void pc(char c){
		if(oh==ot){
			fwrite(cltout,1,size,stdout);
			oh=cltout;
		}
		*oh++=c;
	}
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout),cltstream::oh=cltstream::cltout
	#undef size

	template <typename _tp>
	inline void read(_tp& x){
		int sn=1;
		char c=gc();
		for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
		if(c==45&&c!=EOF)
			sn=-1,c=gc();
		for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
		x*=sn;
	}

	template <typename _tp>
	inline void write(_tp x,char text=-1){
		if(x<0)
			pc(45),x=-x;
		if(!x)
			pc(48);
		else{
			int digit[22];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

int n,m,sq,ec,vc;
int a[maxn+1],p[maxn+1];
int des[2*maxn+1],suc[2*maxn+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],eu[2*maxn+1],st[maxn+1],ed[maxn+1];
int id[maxn+1],top[maxn+1];
struct Query{
	int id,l,r,ex;
};
Query q[maxm+1];
int tmp[maxn+1],cnt[maxn+1],ans[maxm+1];

inline bool operator<(const Query& p1,const Query& p2){
	return p1.l/sq!=p2.l/sq?p1.l<p2.l:((p1.l/sq)&1)?p1.r>p2.r:p1.r<p2.r;
}

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs1(re int cur,re int ftr){
	eu[st[cur]=++eu[0]]=cur;
	f[cur]=ftr;
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur]){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			maxsize<size[des[i]]&&(maxsize=size[des[i]],hes[cur]=des[i]);
		}
	eu[ed[cur]=++eu[0]]=cur;
}

void dfs2(re int cur,re int ftr){
	id[cur]=++vc;
	top[cur]=ftr;
	if(hes[cur]){
		dfs2(hes[cur],ftr);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
}

inline int lca(re int x,re int y){
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=f[top[y]];
	}
	return dep[x]<=dep[y]?x:y;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=2*n/sqrt(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		p[++p[0]]=a[i];
	}
	std::sort(p+1,p+p[0]+1);
	p[0]=std::unique(p+1,p+p[0]+1)-p-1;
	for(re int i=1;i<=n;++i)
		a[i]=std::lower_bound(p+1,p+p[0]+1,a[i])-p;
	for(re int i=1;i<n;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=m;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		st[x]>st[y]&&swap(x,y);
		re int z=lca(x,y);
		if(z==x){
			q[i].id=i;
			q[i].l=st[x];
			q[i].r=st[y];
			q[i].ex=0;
		}
		else{
			q[i].id=i;
			q[i].l=ed[x];
			q[i].r=st[y];
			q[i].ex=z;
		}
	}
	std::sort(q+1,q+m+1);
	for(re int i=1,L=1,R=0;i<=m;++i){
		for(;R<q[i].r;++R,tmp[eu[R]]?del(a[eu[R]]):add(a[eu[R]]),++tmp[eu[R]]);
		for(;R>q[i].r;--tmp[eu[R]],tmp[eu[R]]?add(a[eu[R]]):del(a[eu[R]]),--R);
		for(;L>q[i].l;--L,tmp[eu[L]]?del(a[eu[L]]):add(a[eu[L]]),++tmp[eu[L]]);
		for(;L<q[i].l;--tmp[eu[L]],tmp[eu[L]]?add(a[eu[L]]):del(a[eu[L]]),++L);
		q[i].ex&&add(a[q[i].ex]);
		ans[q[i].id]=cnt[0];
		q[i].ex&&del(a[q[i].ex]);
	}
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
