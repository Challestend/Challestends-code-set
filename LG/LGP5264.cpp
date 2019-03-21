#include<cstdio>
#define re register
#define maxn 524288
#define mod 998244353
#define I 86583718
#define swap(a,b) a^=b,b^=a,a^=b

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

int n,tp;
int unit[2][24],inv[maxn+1],rev[maxn+1];
int tmp[11][maxn+1];
int F[maxn+1],G[maxn+1];

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

inline void NTT(re int* F,re int n,re int tp){
	for(re int i=0;i<n;++i)
		if(i<(rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0)))
			swap(F[i],F[rev[i]]);
	for(re int k=1,p=1;p<n;++k,p<<=1)
		for(re int i=0;i<n;i+=p<<1)
			for(re int j=i,tmp=1;j<i+p;++j,tmp=1LL*tmp*unit[tp][k]%mod){
				re int x=F[j],y=1LL*F[j+p]*tmp%mod;
				F[j]=(x+y)%mod;
				F[j+p]=(x-y+mod)%mod;
			}
	re int v=cltpow(n,tp*(mod-2));
	for(re int i=0;i<n;++i)
		F[i]=1LL*F[i]*v%mod;
}

inline void Inv(re int* F,re int* G,re int n){
	re int N=1;
	for(;N<n;N<<=1);
	N<<=1;
	for(re int i=0;i<N;++i)
		G[i]=0;
	G[0]=cltpow(F[0],mod-2);
	for(re int i=1,j=4;i<n;i<<=1,j<<=1){
		for(re int k=0;k<(i<<1);++k)
			tmp[1][k]=F[k];
		for(re int k=(i<<1);k<j;++k)
			tmp[1][k]=0;
		NTT(G,j,0);
		NTT(tmp[1],j,0);
		for(re int k=0;k<j;++k)
			G[k]=(2-1LL*tmp[1][k]*G[k]%mod+mod)*G[k]%mod;
		NTT(G,j,1);
		for(re int k=(i<<1);k<j;++k)
			G[k]=0;
	}
	for(re int i=n;i<N;++i)
		G[i]=0;
}

inline void Ln(re int* F,re int* G,re int n){
	re int N=1;
	for(;N<n;N<<=1);
	N<<=1;
	for(re int i=1;i<n;++i)
		G[i-1]=1LL*F[i]*i%mod;
	for(re int i=n-1;i<N;++i)
		G[i]=0;
	Inv(F,tmp[2],n);
	NTT(G,N,0);
	NTT(tmp[2],N,0);
	for(re int i=0;i<N;++i)
		G[i]=1LL*G[i]*tmp[2][i]%mod;
	NTT(G,N,1);
	for(re int i=n-1;i>=1;--i)
		G[i]=1LL*G[i-1]*inv[i]%mod;
	G[0]=0;
	for(re int i=n;i<N;++i)
		G[i]=0;
}

inline void Exp(re int* F,re int* G,re int n){
	re int N=1;
	for(;N<n;N<<=1);
	N<<=1;
	for(re int i=0;i<N;++i)
		G[i]=0;
	G[0]=1;
	for(re int i=1,j=2;i<(n<<1);i<<=1,j<<=1){
		Ln(G,tmp[3],i);
		for(re int k=0;k<i;++k)
			tmp[4][k]=F[k];
		for(re int k=i;k<j;++k)
			tmp[4][k]=0;
		NTT(G,j,0);
		NTT(tmp[3],j,0);
		NTT(tmp[4],j,0);
		for(re int k=0;k<j;++k)
			G[k]=G[k]*(1LL-tmp[3][k]+tmp[4][k]+mod)%mod;
		NTT(G,j,1);
	}
	for(re int i=n;i<N;++i)
		G[i]=0;
}

inline void Sin(re int* F,re int* G,re int n){
	for(re int i=0;i<n;++i){
		tmp[5][i]=1LL*I*F[i]%mod;
		tmp[6][i]=(mod-tmp[5][i])%mod;
	}
	Exp(tmp[5],tmp[7],n);
	Exp(tmp[6],tmp[8],n);
	re int v=cltpow(2*I,mod-2);
	for(re int i=0;i<n;++i)
		cltstream::write(1LL*(tmp[7][i]-tmp[8][i]+mod)*v%mod,32);
}

inline void Cos(re int* F,re int* G,re int n){
	for(re int i=0;i<n;++i){
		tmp[5][i]=1LL*I*F[i]%mod;
		tmp[6][i]=(mod-tmp[5][i])%mod;
	}
	Exp(tmp[5],tmp[7],n);
	Exp(tmp[6],tmp[8],n);
	re int v=cltpow(2,mod-2);
	for(re int i=0;i<n;++i)
		cltstream::write(1LL*(tmp[7][i]+tmp[8][i])*v%mod,32);
}

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	inv[0]=inv[1]=1;
	for(re int i=2;i<=maxn;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	cltstream::read(n);
	cltstream::read(tp);
	for(re int i=0;i<n;++i)
		cltstream::read(F[i]);
	clop();
	return 0;
}
