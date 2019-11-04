#include<cstdio>
#include<cmath>
#define re register
#define maxn 60
#define maxs 100000
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,mod,sq,ans;
int inv[maxn+1],fac[maxn+1],fav[maxn+1],p[2][maxs+1],a[maxn+1];

inline int gcd(re int x,re int y){
	for(;y%=x^=y^=x^=y;);
	return x;
}

void dfs(re int sum,re int mx,re int cnt,re int t,re int c,re int r){
	if(sum==n)
		ans=(ans+1LL*c*p[1][r/sq]%mod*p[0][r%sq]%mod)%mod;
	else
		for(re int i=1;i<=mx;++i){
			re int _t,_c,_r;
			if(i==a[cnt]){
				_t=t+1;
				_c=1LL*c*inv[i]%mod*inv[_t]%mod;
			}
			else{
				_t=1;
				_c=1LL*c*inv[i]%mod;
			}
			_r=(r+(i>>1))%(mod-1);
			for(re int j=1;j<=cnt;++j)
				_r=(_r+gcd(i,a[j]))%(mod-1);
			a[cnt+1]=i;
			dfs(sum+i,min(i,n-sum-i),cnt+1,_t,_c,_r);
		}
}

int main(){
	cltstream::read(n);
	m=2;
	mod=997;
	inv[0]=inv[1]=1;
	for(re int i=2;i<=n;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	fac[0]=fav[0]=1;
	for(re int i=1;i<=n;++i){
		fac[i]=1LL*fac[i-1]*i%mod;
		fav[i]=1LL*fav[i-1]*inv[i]%mod;
	}
	sq=sqrt(mod);
	p[0][0]=1;
	for(re int i=1;i<=sq;++i)
		p[0][i]=1LL*p[0][i-1]*m%mod;
	p[1][0]=1;
	for(re int i=1;i<=mod/sq;++i)
		p[1][i]=1LL*p[1][i-1]*p[0][sq]%mod;
	dfs(0,n,0,0,1,0);
	cltstream::write(ans);
	clop();
	return 0;
}
