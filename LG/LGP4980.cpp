#include<cstdio>
#include<cmath>
#define re register
#define maxn 100000
#define maxc 10
#define mod 1000000007

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

int T,n,sq,m,c,ans;
int f[maxn+1],g[maxn+1],a[2][maxn+1],p[maxc+1],r[maxc+1];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;y>>=1,x=1LL*x*x%mod)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

void dfs(re int cur,re int prd,re int phi){
	if(cur>c)
		ans=(ans+1LL*phi*a[1][(n/prd-1)/sq]%mod*a[0][(n/prd-1)%sq]%mod)%mod;
	else
		for(re int i=0,j=1;i<=r[cur];++i,j*=p[cur])
			dfs(cur+1,prd*j,phi*(i?j/p[cur]*(p[cur]-1):1));
}

int main(){
	for(re int i=2;i<=maxn;++i){
		if(!f[i])
			g[++g[0]]=i;
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(i%g[j]==0)
				break;
		}
	}
	cltstream::read(T);
	for(;T;--T){
		cltstream::read(n);
		sq=sqrt(n);
		a[0][0]=1;
		for(re int i=1;i<=sq;++i)
			a[0][i]=1LL*a[0][i-1]*n%mod;
		a[1][0]=1;
		for(re int i=1;i<=n/sq;++i)
			a[1][i]=1LL*a[1][i-1]*a[0][sq]%mod;
		m=n;
		c=0;
		for(re int i=0;i<=maxc;++i)
			p[i]=r[i]=0;
		for(re int i=1;i<=g[0]&&g[i]*g[i]<=n;++i)
			if(m%g[i]==0){
				p[++c]=g[i];
				for(;m%g[i]==0;m/=g[i],++r[c]);
			}
		if(m>1){
			p[++c]=m;
			r[c]=1;
		}
		ans=0;
		dfs(1,1,1);
		cltstream::write(ans,10);
	}
	clop();
	return 0;
}
