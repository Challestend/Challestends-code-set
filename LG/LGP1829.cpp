#include<cstdio>
#define re register
#define maxn 10000000
#define mod 20101009
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

int n,m,ans;
int sum[maxn+1],f[maxn+1],g[maxn+1],h[maxn+1]={0,1};

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n||i<=m;++i)
		sum[i]=(sum[i-1]+i)%mod;
	for(re int i=2;i<=n&&i<=m;++i){
		if(!f[i]){
			g[++g[0]]=i;
			h[i]=mod-i+1;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=n&&i*g[j]<=m;++j){
			f[i*g[j]]=1;
			if(i%g[j])
				h[i*g[j]]=1LL*h[i]*h[g[j]]%mod;
			else{
				h[i*g[j]]=h[i];
				break;
			}
		}
	}
	for(re int i=1;i<=n&&i<=m;++i)
		h[i]=(h[i-1]+1LL*i*h[i]%mod)%mod;
	for(re int l=1,r;l<=n&&l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans=(ans+1LL*sum[n/l]*sum[m/l]%mod*((h[r]-h[l-1])%mod+mod)%mod)%mod;
	}
	cltstream::write(ans);
	clop();
	return 0;
}
