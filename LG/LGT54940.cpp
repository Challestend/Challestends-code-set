#include<cstdio>
#define re register
#define maxn 1000000
#define mod 100000007

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

int n,tp,ec;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int size[maxn+1],f[maxn+1],g[maxn+1];

inline void connect(int x,int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

int cltpow(int x,int y){
	if(y==1)
		return x;
	else{
		int res=cltpow(x,y>>1);
		res=1LL*res*res%mod;
		if(y&1)
			res=1LL*res*x%mod;
		return res;
	}
}

void dfs(int cur,int ftr){
	f[cur]=1;
	g[cur]=tp?cur:1;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			dfs(des[i],cur);
			f[cur]=1LL*f[cur]*(f[des[i]]+1)%mod;
		}
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			int tmp=1LL*f[cur]*cltpow(f[des[i]]+1,mod-2)%mod;
			g[cur]=(1LL*g[cur]+1LL*tmp*g[des[i]]%mod)%mod;
		}
}

int main(){
	cltstream::read(n);
	cltstream::read(tp);
	for(re int i=1;i<n;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs(1,0);
	cltstream::write(g[1]);
	clop();
	return 0;
}
