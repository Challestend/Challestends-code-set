#include<cstdio>
#define re register
#define maxn 50000
#define maxm 100000
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m,ec,vc;
int des[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1],slc[maxm+1];
long long val[(maxm<<1)+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
long long bit[maxn+1],base[63];

inline void connect(re int x,re int y,re long long z){
	des[++ec]=y;
	val[ec]=z;
	suc[ec]=las[x];
	las[x]=ec;
}

inline void update(re int x,re long long y){
	for(;x<=n;x+=x&(-x))
		bit[x]^=y;
}

inline long long getsum(re int x){
	re long long res=0;
	for(;x>=1;x-=x&(-x))
		res^=bit[x];
	return res;
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur]&&!dep[des[i]]){
			slc[(i+1)>>1]=1;
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			if(maxsize<size[des[i]]){
				hes[cur]=des[i];
				maxsize=size[des[i]];
			}
		}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	top[cur]=curtop;
	if(hes[cur]){
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur]&&!id[des[i]])
				dfs2(des[i],des[i]);
	}
}

inline long long pthsum(re int x,re int y){
	re long long res=0;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			x^=y,y^=x,x^=y;
		res^=getsum(id[y])^getsum(id[top[y]]-1);
		y=f[top[y]];
	}
	return res^getsum(id[x])^getsum(id[y]);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		int x,y;
		long long z;
		cltstream::read(x);
		cltstream::read(y);
		cltstream::read(z);
		connect(x,y,z);
		connect(y,x,z);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=m;++i)
		if(slc[i])
			update(id[dep[des[(i<<1)-1]]>dep[des[i<<1]]?des[(i<<1)-1]:des[i<<1]],val[i<<1]);
	for(re int i=1;i<=m;++i)
		if(!slc[i]){
			re long long x=pthsum(des[(i<<1)-1],des[i<<1])^val[i<<1];
			for(re int j=62;j>=0;--j)
				if(x>>j&1){
					if(!base[j]){
						base[j]=x;
						break;
					}
					else
						x^=base[j];
				}
		}
	re long long ans=pthsum(1,n);
	for(re int j=62;j>=0;--j)
		ans=max(ans,ans^base[j]);
	cltstream::write(ans);
	clop();
	return 0;
}
