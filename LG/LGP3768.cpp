#include<cstdio>
#include<tr1/unordered_map>
#define re register
#define maxn 5000000

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

int mod,I4,I6,ans;
long long n;
int f[maxn+1],g[maxn+1],phi[maxn+1]={0,1};
std::tr1::unordered_map<long long,int> phisum;

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

int getPhi(long long n){
	if(n<=maxn)
		return phi[n];
	if(phisum.count(n))
		return phisum[n];
	re int res=n%mod;
	res=1LL*res*res%mod*(res+1)%mod*(res+1)%mod*I4%mod;
	for(re long long l=2,r;l<=n;l=r+1){
		r=n/(n/l);
		re int x=r%mod;
		x=1LL*x*(x+1)%mod*(2*x+1)%mod*I6%mod;
		re int y=l%mod;
		y=1LL*y*(y-1)%mod*(2*y-1)%mod*I6%mod;
		res=((res-1LL*(x-y+mod)*getPhi(n/l)%mod)%mod+mod)%mod;
	}
	return phisum[n]=res;
}

int main(){
	cltstream::read(mod);
	I4=cltpow(4,mod-2);
	I6=cltpow(6,mod-2);
	cltstream::read(n);
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			phi[i]=i-1;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(i%g[j])
				phi[i*g[j]]=1LL*phi[i]*phi[g[j]]%mod;
			else{
				phi[i*g[j]]=1LL*phi[i]*g[j]%mod;
				break;
			}
		}
	}
	for(re int i=1;i<=maxn;++i)
		phi[i]=(phi[i-1]+1LL*i*i%mod*phi[i]%mod)%mod;
	for(re long long l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		re int x=(n/r)%mod;
		x=1LL*x*x%mod*(x+1)%mod*(x+1)%mod*I4%mod;
		re int y=(n/(r+1))%mod;
		y=1LL*y*y%mod*(y+1)%mod*(y+1)%mod*I4%mod;
		ans=(ans+1LL*(x-y+mod)*getPhi(r)%mod)%mod;
	}
	cltstream::write(ans);
	clop();
	return 0;
}
