#include<cstdio>
#define re register
#define maxn 20000
#define maxm 40000
#define min(a,b) ((a)<=(b)?(a):(b))
#define swap(a,b) a^=b,b^=a,a^=b

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

int n,m,q,ec,vc;
int des[(maxm<<2)+1],suc[(maxm<<2)+1],las[(maxn<<1)+1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],g[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs0(re int cur,re int ftr){
	dfn[cur]=low[cur]=++vc;
	st[++st[0]]=cur;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			if(!dfn[des[i]]){
				dfs0(des[i],cur);
				low[cur]=min(low[cur],low[des[i]]);
			}
			else
				low[cur]=min(low[cur],dfn[des[i]]);
		}
	if(low[cur]==dfn[cur])
		for(;st[st[0]+1]!=cur;g[st[st[0]--]]=cur);
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur+n];i;i=suc[i])
		if(des[i]-n!=f[cur]&&!f[des[i]-n]){
			dfs1(des[i]-n,cur);
			size[cur]+=size[des[i]-n];
			if(maxsize<size[des[i]-n]){
				maxsize=size[des[i]-n];
				hes[cur]=des[i]-n;
			}
		}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	top[cur]=curtop;
	if(!hes[cur])
		return;
	else{
		dfs2(hes[cur],curtop);
		for(re int i=las[cur+n];i;i=suc[i])
			if(des[i]-n!=f[cur]&&!id[des[i]-n])
				dfs2(des[i]-n,des[i]-n);
	}
}

inline int pthdis(re int x,re int y){
	re int res=0;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=id[y]-id[top[y]]+1;
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return res+id[y]-id[x];
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		re int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs0(1,0);
	for(re int i=1;i<=n;++i)
		for(re int j=las[i];j;j=suc[j])
			if(g[i]!=g[des[j]]){
				connect(g[i]+n,g[des[j]]+n);
				connect(g[des[j]]+n,g[i]+n);
			}
	dfs1(1,0);
	dfs2(1,1);
	cltstream::read(q);
	for(re int i=1;i<=q;++i){
		re int x,y;
		cltstream::read(x);
		cltstream::read(y);
		re int ans=pthdis(g[x],g[y]);
		if(ans>0)
			cltstream::write(ans,10);
		else
			cltstream::pc('A'),
			cltstream::pc('n'),
			cltstream::pc('g'),
			cltstream::pc('r'),
			cltstream::pc('y'),
			cltstream::pc('!'),
			cltstream::pc('\n');
	}
	clop();
	return 0;
}
