#include<cstdio>
#include<algorithm>
#define re register
#define maxm 50
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

int t,m;
long long n,a[maxm+1];
int f[maxm+2][maxm+4],inv[maxm+4];

inline int F(re int k,re int x){
	re int res=0;
	for(re int i=1;i<=k+2;++i){
		re int tmp=f[k][i];
		for(re int j=1;j<i;++j)
			tmp=1LL*tmp*(x-j+mod)%mod*inv[i-j]%mod;
		for(re int j=i+1;j<=k+2;++j)
			tmp=1LL*tmp*(x-j+mod)%mod*(mod-inv[j-i])%mod;
		res=(res+tmp)%mod;
	}
	return res;
}

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;){
		if(y&1)
			res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}

int main(){
	for(re int i=1;i<=maxm+3;++i)
		f[0][i]=1;
	for(re int i=1;i<=maxm+1;++i)
		for(re int j=1;j<=maxm+3;++j)
			f[i][j]=1LL*f[i-1][j]*j%mod;
	for(re int i=0;i<=maxm+1;++i)
		for(re int j=1;j<=maxm+3;++j)
			f[i][j]=(f[i][j]+f[i][j-1])%mod;
	inv[1]=1;
	for(re int i=2;i<=maxm+3;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	cltstream::read(t);
	for(;t;--t){
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<=m;++i)
			cltstream::read(a[i]);
		std::sort(a+1,a+m+1);
		re int ans=0;
		for(re int i=0;i<=m;++i)
			ans=(ans+F(m+1,(n-a[i])%mod))%mod;
		for(re int i=1;i<=m;++i)
			for(re int j=i;j<=m;++j)
				ans=(ans-cltpow((a[j]-a[i-1])%mod,m+1)+mod)%mod;
		cltstream::write(ans,10);
	}
	clop();
	return 0;
}
