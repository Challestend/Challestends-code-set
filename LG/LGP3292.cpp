#include<cstdio>
#define re register
#define maxn 20000
#define maxlog 15
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

int n,m,ec;
int lg[maxn+1];
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1][maxlog+1],dep[maxn+1];
long long val[maxn+1],base[maxn+1][maxlog+1][63];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

inline void insert(re long long* a,re long long x){
	if(x)
		for(re int i=62;i>=0;--i)
			if(x>>i&1){
				if(!a[i]){
					a[i]=x;
					break;
				}
				else
					x^=a[i];
			}
}

inline void merge(re long long* a,re long long* b){
	for(re int i=62;i>=0;--i)
		insert(a,b[i]);
}

void dfs(re int cur,re int ftr){
	f[cur][0]=ftr;
	dep[cur]=dep[f[cur][0]]+1;
	insert(base[cur][0],val[cur]);
	for(re int i=1;f[cur][i-1]&&f[f[cur][i-1]][i-1];++i){
		f[cur][i]=f[f[cur][i-1]][i-1];
		for(re int j=62;j>=0;--j)
			base[cur][i][j]=base[cur][i-1][j];
		merge(base[cur][i],base[f[cur][i-1]][i-1]);
	}
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur][0])
			dfs(des[i],cur);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(re int i=1;i<=n;++i)
		cltstream::read(val[i]);
	for(re int i=1;i<n;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs(1,0);
	for(re int i=1;i<=m;++i){
		for(re int j=62;j>=0;--j)
			base[0][0][j]=0;
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		if(dep[x]>dep[y])
			x^=y,y^=x,x^=y;
		re int dx=dep[y]-dep[x];
		for(;dx;){
			re int dy=dx&(-dx);
			merge(base[0][0],base[y][lg[dy]]);
			y=f[y][lg[dy]];
			dx-=dy;
		}
		if(x!=y){
			for(re int j=lg[n];j>=0&&f[x][0]!=f[y][0];--j)
				if(f[x][j]!=f[y][j]){
					merge(base[0][0],base[x][j]);
					x=f[x][j];
					merge(base[0][0],base[y][j]);
					y=f[y][j];
				}
			insert(base[0][0],val[x]);
			insert(base[0][0],val[y]);
			x=f[x][0];
		}
		insert(base[0][0],val[x]);
		re long long ans=0;
		for(re int j=62;j>=0;--j)
			ans=max(ans,ans^base[0][0][j]);
		cltstream::write(ans,10);
	}
	clop();
	return 0;
}
