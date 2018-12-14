#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define maxlog 20

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
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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

int n,m,ec,vc,lastans;
int w[maxn+1],p[maxn+1];
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],top[maxn+1];
int root[maxn+1],lc[maxlog*maxn+1],rc[maxlog*maxn+1],cnt[maxlog*maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

int build(re int l,re int r){
	if(l==r)
		return ++vc;
	else{
		re int p=++vc,mid=(l+r)>>1;
		lc[p]=build(l,mid);
		rc[p]=build(mid+1,r);
		return p;
	}
}

int update(re int L,re int cur,re int l,re int r){
	if(l==r){
		++vc;
		cnt[vc]=cnt[cur]+1;
		return vc;
	}
	else{
		re int p=++vc,mid=(l+r)>>1;
		if(L<=mid){
			lc[p]=update(L,lc[cur],l,mid);
			rc[p]=rc[cur];
		}
		else{
			lc[p]=lc[cur];
			rc[p]=update(L,rc[cur],mid+1,r);
		}
		cnt[p]=cnt[lc[p]]+cnt[rc[p]];
		return p;
	}
}

int query(re int L,re int R,re int curl,re int curr,re int l,re int r){
	if(l>=L&&r<=R)
		return cnt[curr]-cnt[curl];
	else{
		re int mid=(l+r)>>1,res=0;
		if(L<=mid)
			res+=query(L,R,lc[curl],lc[curr],l,mid);
		if(R>mid)
			res+=query(L,R,rc[curl],rc[curr],mid+1,r);
		return res;
	}
}

void dfs1(re int cur,re int ftr){
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
}

void dfs2(re int cur,re int curtop){
	w[cur]=std::lower_bound(p+1,p+p[0]+1,w[cur])-p;
	top[cur]=curtop;
	root[cur]=update(w[cur],root[f[cur]],1,p[0]);
	if(!hes[cur])
		return;
	else{
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
}

inline int LCA(re int x,re int y){
	for(;top[x]!=top[y];y=f[top[y]])
		if(dep[top[x]]>dep[top[y]])
			std::swap(x,y);
	return dep[x]<=dep[y]?x:y;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(w[i]);
		p[i]=w[i];
	}
	std::sort(p+1,p+n+1);
	p[0]=std::unique(p+1,p+n+1)-p-1;
	for(re int i=1;i<n;++i){
		re int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	root[0]=build(1,p[0]);
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=m;++i){
		re int x,y,z,k;
		cltstream::read(x);
		cltstream::read(y);
		cltstream::read(k);
		x^=lastans;
		z=LCA(x,y);
		re int L=1,R=p[0];
		for(;L<R;){
			re int mid=(L+R)>>1;
			if(query(1,mid,root[z],root[x],1,p[0])+query(1,mid,root[z],root[y],1,p[0])+(w[z]<=mid)>=k)
				R=mid;
			else
				L=mid+1;
		}
		cltstream::write(lastans=p[L],10);
	}
	clop();
	return 0;
}
