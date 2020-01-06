#include<cstdio>
#define re register
#define maxn 131072
#define mod 998244353
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define swap(a,b) a^=b^=a^=b

int unit[2][24],rev[maxn],inv[maxn];
struct poly{
	int n,a[maxn];

	inline void clear(re int N=maxn){
		for(re int i=n;i<N;++i)
			a[i]=0;
	}

	inline int operator[](re int x)const{
		return a[x];
	}

	inline int& operator[](re int x){
		return a[x];
	}

	poly(re int c=0){
		n=1;
		a[0]=c;
		for(re int i=1;i<maxn;++i)
			a[i]=0;
	}
};

inline int cltpow(re int x,re int k){
	re int res=1;
	for(;k;k>>=1,x=1LL*x*x%mod)
		if(k&1)
			res=1LL*res*x%mod;
	return res;
}

inline poly Der(const poly& F){
	poly G;
	G.n=F.n-1;
	for(re int i=0;i<G.n;++i)
		G[i]=1LL*(i+1)*F[i+1]%mod;
	return G;
}

inline poly Int(const poly& F){
	poly G;
	G.n=F.n+1;
	G[0]=0;
	for(re int i=1;i<G.n;++i)
		G[i]=1LL*inv[i]*F[i-1]%mod;
	return G;
}

inline poly Rev(const poly& F){
	poly G;
	G.n=F.n;
	for(re int i=0;i<G.n;++i)
		G[i]=F[F.n-i-1];
	return G;
}

inline poly operator+(const poly& F,const poly& G){
	poly H;
	H.n=max(F.n,G.n);
	for(re int i=0;i<H.n;++i)
		H[i]=(F[i]+G[i])%mod;
	return H;
}

inline poly operator-(const poly& F,const poly& G){
	poly H;
	H.n=max(F.n,G.n);
	for(re int i=0;i<H.n;++i)
		H[i]=(F[i]-G[i]+mod)%mod;
	return H;
}

inline poly operator^(const poly& F,const poly& G){
	poly H;
	H.n=max(F.n,G.n);
	for(re int i=0;i<H.n;++i)
		H[i]=1LL*F[i]*G[i]%mod;
	return H;
}

inline poly NTT(const poly& F,re int N,re int tp){
	poly G;
	G.n=N;
	for(re int i=0;i<N;++i)
		G[i]=F[rev[i]=(rev[i>>1]>>1)|((i&1)?(N>>1):0)];
	for(re int k=1,p=1;p<N;++k,p<<=1)
		for(re int i=0;i<N;i+=p<<1)
			for(re int j=i,tmp=1;j<i+p;++j,tmp=1LL*tmp*unit[tp][k]%mod){
				re int x=G[j],y=1LL*G[j+p]*tmp%mod;
				G[j]=(x+y)%mod;
				G[j+p]=(x-y+mod)%mod;
			}
	re int v=cltpow(N,tp*(mod-2));
	for(re int i=0;i<N;++i)
		G[i]=1LL*G[i]*v%mod;
	return G;
}

inline poly operator*(const poly& F,const poly& G){
	re int N=1;
	for(;N<(F.n+G.n-1);N<<=1);
	poly H=NTT(NTT(F,N,0)^NTT(G,N,0),N,1);
	H.n=F.n+G.n-1;
	H.clear(N);
	return H;
}

inline poly Inv(const poly& F){
	poly G(cltpow(F[0],mod-2)),tmp;
	for(re int i=1,j=4;i<F.n;i<<=1,j<<=1){
		G.n=i;
		tmp.n=i<<1;
		for(re int k=0;k<tmp.n;++k)
			tmp[k]=F[k];
		G=(poly(2)-tmp*G)*G;
		G.n=i<<1;
		G.clear(j);
	}
	G.n=F.n;
	re int N=1;
	for(;N<G.n;N<<=1);
	G.clear(N);
	return G;
}

inline poly operator/(const poly& F,const poly& G){
	return F*Inv(G);
}

inline poly Ln(const poly& F){
	poly G=Int(Der(F)/F);
	G.n=F.n;
	G.clear((F.n-1)<<1);
	return G;
}

inline poly Exp(const poly& F){
	poly G(1),tmp;
	for(re int i=1,j=4;i<F.n;i<<=1,j<<=1){
		G.n=i<<1;
		tmp.n=i<<1;
		for(re int k=0;k<tmp.n;++k)
			tmp.a[k]=F[k];
		G=(poly(1)-Ln(G)+tmp)*G;
		G.n=i<<1;
		G.clear(j);
	}
	G.n=F.n;
	re int N=1;
	for(;N<G.n;N<<=1);
	G.clear(N);
	return G;
}

inline poly Div(const poly& F,const poly& G){
	poly H=Rev(G);
	H.n=F.n-G.n+1;
	H=Rev(F)/H;
	H.n=F.n-G.n+1;
	H.clear(F.n+G.n-1);
	return Rev(H);
}

inline poly Mod(const poly& F,const poly& G){
	poly H=F-Div(F,G)*G;
	for(;H.n>1&&!H[H.n-1];--H.n);
	return H;
}

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

int n,k;
poly G,A,Q(1);
int a[maxn];

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	inv[0]=inv[1]=1;
	for(re int i=2;i<maxn;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	cltstream::read(n);
	cltstream::read(k);
	G.n=k+1;
	G[k]=1;
	for(re int i=k-1;i>=0;--i){
		cltstream::read(G[i]);
		G[i]=(G[i]%mod+mod)%mod;
		G[i]=(mod-G[i])%mod;
	}
	for(re int i=0;i<k;++i){
		cltstream::read(a[i]);
		a[i]=a[i]>=0?a[i]:a[i]+mod;
	}
	A.n=2;
	A[1]=1;
	for(;n;n>>=1,A=A*A,A=Mod(A,G))
		if(n&1){
			Q=Q*A;
			Q=Mod(Q,G);
		}
	re int ans=0;
	for(re int i=0;i<k;++i)
		ans=(ans+1LL*Q[i]*a[i]%mod)%mod;
	cltstream::write(ans);
	clop();
	return 0;
}
