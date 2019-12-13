#include<cstdio>
#define re register
#define maxn 500001
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
long long lastans;
int a[maxn+1],stk[maxn+1],nxt[maxn+1];
int des[maxn+1],suc[maxn+1],lst[maxn+1];
int lg[maxn+1],f[maxn+1][maxlog+1],dep[maxn+1];
long long g[maxn+1][maxlog+1];

inline void connect(re int u,re int v){
	des[++ec]=v;
	suc[ec]=lst[u];
	lst[u]=ec;
}

void dfs(re int cur){
	for(re int i=1;i<=lg[dep[cur]];++i){
		f[cur][i]=f[f[cur][i-1]][i-1];
		g[cur][i]=g[f[cur][i-1]][i-1]+g[cur][i-1];
	}
	for(re int i=lst[cur];i;i=suc[i]){
		f[des[i]][0]=cur;
		dep[des[i]]=dep[cur]+1;
		g[des[i]][0]=1LL*(cur-des[i])*a[des[i]];
		dfs(des[i]);
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		for(;stk[0]>0&&a[stk[stk[0]]]<a[i];nxt[stk[stk[0]--]]=i);
		stk[++stk[0]]=i;
	}
	a[++n]=2E9;
	for(;stk[0]>0;nxt[stk[stk[0]--]]=n);
	for(re int i=1;i<n;++i)
		connect(nxt[i],i);
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	dfs(n);
	for(re int i=1;i<=m;++i){
		long long l,x;
		cltstream::read(l);
		cltstream::read(x);
		l=(l^lastans)%(n-1)+1;
		x=(x^(lastans+1))%(n-l)+1;
		lastans=0;
		for(re int j=lg[dep[l]];j>=0;--j)
			if(x>f[l][j]-l){
				x-=f[l][j]-l;
				lastans+=g[l][j];
				l=f[l][j];
			}
		cltstream::write(lastans+=1LL*x*a[l],10);
	}
	clop();
	return 0;
}
