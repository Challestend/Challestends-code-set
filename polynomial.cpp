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

int n,m;
int unit[2][24],rev[maxn],inv[maxn];
int F[maxn],G[maxn];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;x=1LL*x*x%mod,y>>=1)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

inline void Der(re int* F,re int* G,re int n){
	for(re int i=0;i<n-1;++i)
		G[i]=1LL*(i+1)*F[i+1]%mod;
	for(re int i=n-1;i<maxn;++i)
		G[i]=0;
}

inline void Int(re int* F,re int* G,re int n){
	inv[0]=inv[1]=1;
	for(re int i=2;i<n;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	for(re int i=n-1;i>0;--i)
		G[i]=1LL*inv[i]*F[i-1]%mod;
	G[0]=0;
	for(re int i=n;i<maxn;++i)
		G[i]=0;
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
	int tmp[maxn];
	for(re int i=0;i<maxn;++i)
		G[i]=tmp[i]=0;
	G[0]=cltpow(F[0],mod-2);
	for(re int i=1,j=4;i<n;i<<=1,j<<=1){
		for(re int k=0;k<(i<<1);++k)
			tmp[k]=F[k];
		NTT(G,j,0);
		NTT(tmp,j,0);
		for(re int k=0;k<j;++k)
			G[k]=(2-1LL*tmp[k]*G[k]%mod+mod)*G[k]%mod;
		NTT(G,j,1);
		for(re int k=(i<<1);k<j;++k)
			G[k]=0;
	}
	for(re int i=n;i<maxn;++i)
		G[i]=0;
}

inline void Ln(re int* F,re int* G,re int n){
	int tmp[maxn];
	Der(F,G,n);
	Inv(F,tmp,n);
	re int N=1;
	for(;N<(n<<1)-1;N<<=1);
	NTT(G,N,0);
	NTT(tmp,N,0);
	for(re int i=0;i<N;++i)
		tmp[i]=1LL*G[i]*tmp[i]%mod;
	NTT(tmp,N,1);
	Int(tmp,G,n);
}

inline void Exp(re int* F,re int* G,re int n){
	int tmp1[maxn],tmp2[maxn];
	for(re int i=0;i<maxn;++i)
		G[i]=tmp1[i]=tmp2[i]=0;
	G[0]=1;
	for(re int i=1,j=4;i<n;i<<=1,j<<=1){
		Ln(G,tmp1,i<<1);
		for(re int k=0;k<(i<<1);++k)
			tmp2[k]=F[k];
		NTT(G,j,0);
		NTT(tmp1,j,0);
		NTT(tmp2,j,0);
		for(re int k=0;k<j;++k)
			G[k]=1LL*(1-tmp1[k]+tmp2[k]+mod)*G[k]%mod;
		NTT(G,j,1);
		for(re int k=(i<<1);k<j;++k)
			G[k]=0;
	}
	for(re int i=n;i<maxn;++i)
		G[i]=0;
}

inline void Pow(re int* F,re int* G,re int n,re int k){
	int tmp[maxn];
	Ln(F,tmp,n);
	for(re int i=0;i<n;++i)
		tmp[i]=1LL*k*tmp[i]%mod;
	Exp(tmp,G,n);
}

inline void Cos(re int* F,re int* G,re int n){
	int tmp[maxn],tmp1[maxn],tmp2[maxn];
	for(re int i=0;i<n;++i)
		tmp[i]=1LL*I*F[i]%mod;
	Exp(tmp,tmp1,n);
	for(re int i=0;i<n;++i)
		tmp[i]=(mod-tmp[i])%mod;
	Exp(tmp,tmp2,n);
	re int v=cltpow(2,mod-2);
	for(re int i=0;i<n;++i)
		G[i]=1LL*(tmp1[i]+tmp2[i])*v%mod;
}

inline void Sin(re int* F,re int* G,re int n){
	int tmp[maxn],tmp1[maxn],tmp2[maxn];
	for(re int i=0;i<n;++i)
		tmp[i]=1LL*I*F[i]%mod;
	Exp(tmp,tmp1,n);
	for(re int i=0;i<n;++i)
		tmp[i]=(mod-tmp[i])%mod;
	Exp(tmp,tmp2,n);
	re int v=cltpow(2*I,mod-2);
	for(re int i=0;i<n;++i)
		G[i]=1LL*(tmp1[i]-tmp2[i]+mod)*v%mod;
}

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	clop();
	return 0;
}
