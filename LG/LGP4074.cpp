#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 100000
#define maxq 100000
#define add(a) (++cnt[a],res+=1LL*w[cnt[a]]*v[a])
#define del(a) (res-=1LL*w[cnt[a]]*v[a],--cnt[a])
#define ADD(x) (tmp[x]?del(a[x]):add(a[x]),++tmp[x])
#define DEL(x) (--tmp[x],tmp[x]?add(a[x]):del(a[x]))
#define swap(a,b) (a^=b,b^=a,a^=b)

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

int n,m,q,c0,c1,sq,ec,vc;
long long res;
int w[maxn+1],v[maxm+1],a[maxn+1],opt[maxq+1][2];
int des[2*maxn+1],suc[2*maxn+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],eu[2*maxn+1],st[maxn+1],ed[maxn+1];
int id[maxn+1],top[maxn+1];
struct Query{
	int id,l,r,t,ex;
};
Query query[maxq+1];
int tmp[maxn+1],cnt[maxm+1];
long long ans[maxq+1];

inline bool operator<(const Query& p1,const Query& p2){
	return p1.l/sq!=p2.l/sq?p1.l<p2.l:p1.r/sq!=p2.r/sq?p1.r<p2.r:((p1.r/sq)&1)?p1.t>p2.t:p1.t<p2.t;
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
			if(maxsize<size[des[i]]){
				maxsize=size[des[i]];
				hes[cur]=des[i];
			}
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
	cltstream::read(q);
	for(re int i=1;i<=m;++i)
		cltstream::read(v[i]);
	for(re int i=1;i<=n;++i)
		cltstream::read(w[i]);
	for(re int i=1;i<n;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<=q;++i){
		int c,x,y;
		cltstream::read(c);
		cltstream::read(x);
		cltstream::read(y);
		if(!c){
			++c0;
			opt[c0][0]=x;
			opt[c0][1]=y;
		}
		else{
			++c1;
			if(st[x]>st[y])
				swap(x,y);
			re int z=lca(x,y);
			if(z==x){
				query[c1].id=c1;
				query[c1].l=st[x];
				query[c1].r=st[y];
				query[c1].t=c0;
				query[c1].ex=0;
			}
			else{
				query[c1].id=c1;
				query[c1].l=ed[x];
				query[c1].r=st[y];
				query[c1].t=c0;
				query[c1].ex=z;
			}
		}
	}
	sq=pow(2*n,2.0/3);
	std::sort(query+1,query+c1+1);
	for(re int i=1,L=1,R=0,T=0;i<=c1;++i){
		for(;T<query[i].t;){
			++T;
			tmp[opt[T][0]]==1&&del(a[opt[T][0]]);
			swap(a[opt[T][0]],opt[T][1]);
			tmp[opt[T][0]]==1&&add(a[opt[T][0]]);
		}
		for(;T>query[i].t;){
			tmp[opt[T][0]]==1&&del(a[opt[T][0]]);
			swap(a[opt[T][0]],opt[T][1]);
			tmp[opt[T][0]]==1&&add(a[opt[T][0]]);
			--T;
		}
		for(;R<query[i].r;++R,ADD(eu[R]));
		for(;R>query[i].r;DEL(eu[R]),--R);
		for(;L>query[i].l;--L,ADD(eu[L]));
		for(;L<query[i].l;DEL(eu[L]),++L);
		query[i].ex&&ADD(query[i].ex);
		ans[query[i].id]=res;
		query[i].ex&&DEL(query[i].ex);
	}
	for(re int i=1;i<=c1;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
