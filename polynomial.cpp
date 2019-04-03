#include<cstdio>
#include<algorithm>
#define re register
#define maxn 524288
#define mod 998244353

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

int inv[maxn],rev[maxn];
struct poly{
	int n;
	int a[maxn];

	inline void read(){
		for(re int i=0;i<n;++i)
			cltstream::read(a[i]);
	}

	inline void write(char text=-1){
		for(re int i=0;i<n;++i)
			cltstream::write(a[i],32);
		if(text>=0)
			cltstream::pc(text);
	}

	poly(re int _n=0){
		n=_n;
		for(re int i=0;i<maxn;++i)
			a[i]=0;
	}
};

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

inline void clear(poly F){
	for(re int i=F.n;i<maxn;++i)
		F.a[i]=0;
}

inline poly Derivative(poly F){
	poly G(F.n-1);
	for(re int i=0;i<G.n;++i)
		G.a[i]=1LL*F.a[i+1]*(i+1)%mod;
	return G;
}

inline poly Integral(poly F){
	inv[0]=inv[1]=1;
	for(re int i=2;i<F.n;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	poly G(F.n+1);
	for(re int i=1;i<G.n;++i)
		G.a[i]=1LL*F.a[i-1]*inv[i]%mod;
	return G;
}

inline poly reverse(poly F){
	for(re int i=0;i<F.n-i-1;++i)
		std::swap(F.a[i],F.a[F.n-i-1]);
	return F;
}

inline poly operator+(poly F,poly G){
	F.n=std::max(F.n,G.n);
	for(re int i=0;i<F.n;++i)
		F.a[i]=(F.a[i]+G.a[i])%mod;
	return F;
}

inline poly operator+(poly F,re int x){
	F.a[0]=(F.a[0]+x)%mod;
	return F;
}

inline poly operator-(poly F,poly G){
	F.n=std::max(F.n,G.n);
	for(re int i=0;i<F.n;++i)
		F.a[i]=(F.a[i]-G.a[i]+mod)%mod;
	return F;
}

inline poly operator-(poly F,re int x){
	F.a[0]=(F.a[0]-x+mod)%mod;
	return F;
}

inline poly operator-(re int x,poly F){
	for(re int i=0;i<F.n;++i)
		F.a[i]=mod-F.a[i];
	F.a[0]=(F.a[0]+x)%mod;
	return F;
}

inline void NTT(poly& F,re int N,re int tp){
	F.n=N;
	for(re int i=0;i<N;++i)
		if(i<(rev[i]=(rev[i>>1]>>1)|((i&1)?(N>>1):0)))
			std::swap(F.a[i],F.a[rev[i]]);
	for(re int k=1,p=1;p<N;++k,p<<=1)
		for(re int i=0;i<N;i+=p<<1)
			for(re int j=i,unit=cltpow(!tp?3:332748118,(mod-1)>>k),tmp=1;j<i+p;++j,tmp=1LL*tmp*unit%mod){
				re int x=F.a[j],y=1LL*F.a[j+p]*tmp%mod;
				F.a[j]=(x+y)%mod;
				F.a[j+p]=(x-y+mod)%mod;
			}
	re int v=cltpow(N,tp*(mod-2));
	for(re int i=0;i<N;++i)
		F.a[i]=1LL*F.a[i]*v%mod;
}

inline poly operator*(poly F,poly G){
	re int n=F.n+G.n-1,N=1;
	for(;N<n;N<<=1);
	NTT(F,N,0);
	NTT(G,N,0);
	for(re int i=0;i<N;++i)
		F.a[i]=1LL*F.a[i]*G.a[i]%mod;
	NTT(F,N,1);
	F.n=n;
	clear(F);
	return F;
}

inline poly operator*(poly F,re int x){
	for(re int i=0;i<F.n;++i)
		F.a[i]=1LL*F.a[i]*x%mod;
	return F;
}

inline poly Inversion(poly F){
	poly G(1);
	G.a[0]=cltpow(F.a[0],mod-2);
	for(re int i=1;i<F.n;i<<=1){
		poly _F(i<<1);
		for(re int j=0;j<(i<<1);++j)
			_F.a[j]=F.a[j];
		G=G*(2-_F*G);
		G.n=i<<1;
		clear(G);
		cltstream::write(i<<1,':');
		G.write(10);
	}
	G.n=F.n;
	clear(G);
	return G;
}

inline poly Logarithm(poly F){
	poly _G=Inversion(F);
	F.write(10);
	_G.write(10);
	poly _H=F*_G;
	_H.write(10);
	_H.n=0;
	clear(_H);
	for(re int i=0;i<F.n;++i)
		for(re int j=0;j<_G.n;++j)
			_H.a[i+j]=(_H.a[i+j]+1LL*F.a[i]*_G.a[j]%mod)%mod;
	_H.n=15;
	_H.write(10);
	poly G=Integral(Derivative(F)*Inversion(F));
	G.n=F.n;
	clear(G);
	return G;
}

inline poly Exponential(poly F){
	poly G(1);
	G.a[0]=1;
	for(re int i=1;i<(F.n<<3);i<<=1){
		poly _F(i);
		for(re int j=0;j<i;++j)
			_F.a[j]=F.a[j];
		G=G*(1-Logarithm(G)+_F);
		G.n=i<<1;
		clear(G);
		G.write(10);
		cltstream::pc(10);
	}
	G.n=F.n;
	clear(G);
	return G;
}

inline poly Pow(poly F,re int x){
	F=Logarithm(F);
	for(re int i=0;i<F.n;++i)
		F.a[i]=1LL*F.a[i]*x%mod;
	F=Exponential(F);
	return F;
}

inline poly operator/(poly F,poly G){
	poly H=reverse(F)*Inversion(reverse(G));
	H.n=F.n-G.n;
	clear(H);
	return H;
}

inline poly operator%(poly F,poly G){
	poly H=F-F/G*G;
	H.n=G.n-1;
	clear(H);
	return H;
}

int main(){
	int n;
	cltstream::read(n);
	poly F(n);
	F.read();
	// poly G=Exponential(F);
	poly G=Logarithm(F);
	G.write();
	clop();
	return 0;
}
