#include<cstdio>
#define re register
#define maxn 5000000
#define mod 1000000007
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

int t,k,n,m;
int f[maxn+1],g[maxn+1],h[maxn+1]={0,1};

int cltpow(int x,int y){
	if(y==0)
		return 1;
	else{
		int res=cltpow(x,y>>1);
		res=1LL*res*res%mod;
		if(y&1)
			res=1LL*res*x%mod;
		return res;
	}
}

int main(){
	cltstream::read(t);
	cltstream::read(k);
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			h[i]=(cltpow(i,k)+mod-1)%mod;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			h[i*g[j]]=1LL*h[i]*(h[g[j]]+(i%g[j]==0))%mod;
			if(i%g[j]==0)
				break;
		}
	}
	for(re int i=1;i<=maxn;++i)
		h[i]=(h[i-1]+h[i])%mod;
	for(;t;--t){
		cltstream::read(n);
		cltstream::read(m);
		re int ans=0;
		for(re int l=1,r;l<=n&&l<=m;l=r+1){
			r=min(n/(n/l),m/(m/l));
			ans=(ans+1LL*(n/l)*(m/l)%mod*((h[r]-h[l-1])%mod+mod)%mod)%mod;
		}
		cltstream::write(ans,10);
	}
	clop();
	return 0;
}
