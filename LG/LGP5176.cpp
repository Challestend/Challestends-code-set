#include<cstdio>
#define re register
#define maxn 20000000
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

int T;
int f[maxn+1],g[maxn+1],F[maxn+1],lst[maxn+1];

inline int calc(re int n,re int m){
	re int res=0;
	for(re int l=1,r;l<=n&&l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		res=(res+1LL*(n/l)*(m/l)%mod*(F[r]-F[l-1]+mod)%mod)%mod;
	}
	return res;
}

int main(){
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			F[i]=1;
			lst[i]=(1LL*i*i-1)%mod;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j)
			if(i%g[j]){
				f[i*g[j]]=1;
				F[i*g[j]]=1LL*F[i]*lst[i]%mod;
				lst[i*g[j]]=lst[g[j]];
			}
			else{
				f[i*g[j]]=1;
				F[i*g[j]]=F[i];
				lst[i*g[j]]=1LL*lst[i]*g[j]%mod*g[j]%mod;
				break;
			}
	}
	F[1]=lst[1]=1;
	for(re int i=1;i<=maxn;++i)
		F[i]=(F[i-1]+1LL*F[i]*lst[i]%mod)%mod;
	cltstream::read(T);
	for(;T;--T){
		int n,m,c;
		cltstream::read(n);
		cltstream::read(m);
		cltstream::read(c);
		cltstream::write((1LL*calc(n,m)*c%mod+1LL*calc(n,c)*m%mod+1LL*calc(m,c)*n%mod)%mod,10);
	}
	clop();
	return 0;
}
