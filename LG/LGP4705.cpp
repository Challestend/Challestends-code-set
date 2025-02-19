#include<cstdio>
#define re register
#define maxn 524288
#define mod 998244353
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

int n,m,t;
int unit[2][24],rev[maxn+1],inv[maxn+1]={1,1};
int A[maxn+1],B[maxn+1],F[maxn+1],G[maxn+1],tmp1[maxn+1],tmp2[maxn+1];

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
		NTT(G,j,0);
		for(re int k=0;k<(i<<1);++k)
			tmp1[k]=F[k];
		for(re int k=(i<<1);k<j;++k)
			tmp1[k]=0;
		NTT(tmp1,j,0);
		for(re int k=0;k<j;++k)
			G[k]=(2-1LL*tmp1[k]*G[k]%mod+mod)*G[k]%mod;
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
	G[n-1]=0;
	for(re int i=n;i<N;++i)
		G[i]=0;
	NTT(G,N,0);
	Inv(F,tmp2,n);
	NTT(tmp2,N,0);
	for(re int i=0;i<N;++i)
		G[i]=1LL*G[i]*tmp2[i]%mod;
	NTT(G,N,1);
	for(re int i=n-1;i>=1;--i)
		G[i]=1LL*G[i-1]*inv[i]%mod;
	G[0]=0;
	for(re int i=n;i<N;++i)
		G[i]=0;
}

void calc(re int* P,re int l,re int r){
	if(l<r){
		re int mid=(l+r)>>1,N=1;
		calc(P,l,mid);
		calc(P,mid+1,r);
		for(;N<r-l+2;N<<=1);
		F[0]=1;
		for(re int i=1;i<=mid-l+1;++i)
			F[i]=P[l+i-1];
		for(re int i=mid-l+2;i<N;++i)
			F[i]=0;
		NTT(F,N,0);
		G[0]=1;
		for(re int i=1;i<=r-mid;++i)
			G[i]=P[mid+i];
		for(re int i=r-mid+1;i<N;++i)
			G[i]=0;
		NTT(G,N,0);
		for(re int i=0;i<N;++i)
			F[i]=1LL*F[i]*G[i]%mod;
		NTT(F,N,1);
		for(re int i=1;i<=r-l+1;++i)
			P[l+i-1]=F[i];
	}
}

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	for(re int i=2;i<=maxn;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	cltstream::read(n);
	cltstream::read(m);
	A[0]=1;
	for(re int i=1;i<=n;++i)
		cltstream::read(A[i]);
	B[0]=1;
	for(re int i=1;i<=m;++i)
		cltstream::read(B[i]);
	cltstream::read(t);
	calc(A,1,n);
	calc(B,1,m);
	Ln(A,F,t+1);
	Ln(B,G,t+1);
	F[0]=n;
	for(re int i=1,j=1;i<=t;j=1LL*j*(mod-inv[i])%mod,++i)
		F[i]=1LL*F[i]*j%mod;
	G[0]=m;
	for(re int i=1,j=1;i<=t;j=1LL*j*(mod-inv[i])%mod,++i)
		G[i]=1LL*G[i]*j%mod;
	re int N=1;
	for(;N<(t<<1|1);N<<=1);
	for(re int i=t+1;i<N;++i)
		F[i]=G[i]=0;
	NTT(F,N,0);
	NTT(G,N,0);
	for(re int i=0;i<N;++i)
		F[i]=1LL*F[i]*G[i]%mod;
	NTT(F,N,1);
	N=cltpow(1LL*n*m%mod,mod-2);
	for(re int i=1,j=N;i<=t;++i,j=1LL*j*i%mod)
		cltstream::write(1LL*F[i]*j%mod,10);
	clop();
	return 0;
}
