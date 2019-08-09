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

int n,m;
int a[maxn+1],b[maxn+1],c[maxn+1],d[maxn+1];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;y>>=1,x=1LL*x*x%mod)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	a[0]=b[0]=c[0]=1;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		a[i]=1LL*a[i-1]*a[i]%mod;
	}
	for(re int i=1;i<=n;++i){
		b[i]=(b[i-1]+a[i])%mod;
		c[i]=(c[i-1]+cltpow(a[i],mod-2))%mod;
		d[i]=(d[i-1]+1LL*c[i-1]*a[i]%mod)%mod;
	}
	for(re int i=1;i<=m;++i){
		int l,r;
		cltstream::read(l);
		cltstream::read(r);
		re int ans=(d[r]-d[l-1]+mod)%mod;
		if(l>1)
			ans=(ans-1LL*(b[r]-b[l-1]+mod)*c[l-2]%mod+mod)%mod;
		cltstream::write(1LL*ans*cltpow(1LL*(r-l+1)*(r-l+2)/2,mod-2)%mod,10);
	}
	clop();
	return 0;
}
