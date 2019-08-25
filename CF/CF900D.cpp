#include<cstdio>
#define re register
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

int n,m,ans;
int g[10];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;y>>=1,x=1LL*x*x%mod)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

void dfs(re int cnt,re int prd,re int k){
	if(cnt==g[0])
		ans=(ans+k*cltpow(2,m/prd-1))%mod;
	else{
		dfs(cnt+1,prd,k);
		dfs(cnt+1,prd*g[cnt+1],-k);
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	if(m%n==0){
		m/=n;
		n=m;
		for(re int i=2;i*i<=n;++i)
			if(n%i==0){
				g[++g[0]]=i;
				for(;n%i==0;n/=i);
			}
		if(n>1)
			g[++g[0]]=n;
		dfs(0,1,1);
	}
	cltstream::write((ans+mod)%mod);
	clop();
	return 0;
}
