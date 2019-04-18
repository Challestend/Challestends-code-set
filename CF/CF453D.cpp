#include<cstdio>
#define re register
#define maxn 20

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

int n;
long long m,mod;
int cnt[1<<maxn],a[maxn+1];
long long F[1<<maxn],G[1<<maxn];

inline long long cltmul(re long long x,re long long y){
	re long long res=0;
	for(;y;y>>=12){
		if(y&4095)
			res=(res+(y&4095)*x%mod)%mod;
		x=(x<<12)%mod;
	}
	return res;
}

inline long long cltpow(re long long x,re int y){
	re long long res=1;
	for(;y;y>>=1){
		if(y&1)
			res=cltmul(res,x);
		x=cltmul(x,x);
	}
	return res;
}

inline void FWT(re long long* F,re int n,re int tp){
	for(re int p=1;p<n;p<<=1)
		for(re int i=0;i<n;i+=p<<1)
			for(re int j=i;j<i+p;++j){
				re long long x=F[j],y=F[j+p];
				F[j]=(x+y)%mod;
				F[j+p]=(x-y+mod)%mod;
				if(tp){
					F[j]>>=1;
					F[j+p]>>=1;
				}
			}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(mod);
	mod<<=n;
	for(re int i=0;i<(1<<n);++i){
		cltstream::read(F[i]);
		F[i]%=mod;
	}
	for(re int i=1;i<(1<<n);++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(re int i=0;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=0;i<(1<<n);++i)
		G[i]=a[cnt[i]]%mod;
	FWT(F,1<<n,0);
	FWT(G,1<<n,0);
	for(re int i=0;i<(1<<n);++i)
		F[i]=cltmul(F[i],cltpow(G[i],m));
	FWT(F,1<<n,1);
	mod>>=n;
	for(re int i=0;i<(1<<n);++i)
		cltstream::write(F[i]%mod,10);
	clop();
	return 0;
}
