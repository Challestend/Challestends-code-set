#include<cstdio>
#define re register
#define maxn 1048576
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

int n,m,N;
int unit[2][24],rev[maxn+1],A[3][maxn+1],B[3][maxn+1],p[maxn+1];

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

inline void NTT(re int* F,re int tp){
	for(re int i=0;i<N;++i)
		if(i<rev[i])
			swap(F[i],F[rev[i]]);
	for(re int k=1,p=1;p<N;++k,p<<=1)
		for(re int i=0;i<N;i+=p<<1)
			for(re int j=i,tmp=1;j<i+p;++j,tmp=1LL*tmp*unit[tp][k]%mod){
				re int x=F[j],y=1LL*F[j+p]*tmp%mod;
				F[j]=(x+y)%mod;
				F[j+p]=(x-y+mod)%mod;
			}
	re int v=cltpow(N,tp*(mod-2));
	for(re int i=0;i<N;++i)
		F[i]=1LL*F[i]*v%mod;
}

int main(){
	cltstream::read(m);
	cltstream::read(n);
	for(re int i=m-1;i>=0;--i){
		for(A[0][i]=cltstream::gc();(A[0][i]<'a'||A[0][i]>'z')&&A[0][i]!='*';A[0][i]=cltstream::gc());
		A[0][i]=A[0][i]=='*'?0:A[0][i]-'a'+1;
		A[1][i]=A[0][i]*A[0][i];
		A[2][i]=A[1][i]*A[0][i];
	}
	for(re int i=0;i<n;++i){
		for(B[0][i]=cltstream::gc();(B[0][i]<'a'||B[0][i]>'z')&&B[0][i]!='*';B[0][i]=cltstream::gc());
		B[0][i]=B[0][i]=='*'?0:B[0][i]-'a'+1;
		B[1][i]=B[0][i]*B[0][i];
		B[2][i]=B[1][i]*B[0][i];
	}
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	for(N=1;N<(n+m-1);N<<=1);
	for(re int i=0;i<N;++i)
		rev[i]=(rev[i>>1]>>1)|((i&1)?(N>>1):0);
	NTT(A[0],0);
	NTT(A[1],0);
	NTT(A[2],0);
	NTT(B[0],0);
	NTT(B[1],0);
	NTT(B[2],0);
	for(re int i=0;i<N;++i){
		B[0][i]=1LL*A[2][i]%mod*B[0][i]%mod;
		B[1][i]=1LL*A[1][i]%mod*B[1][i]%mod;
		B[2][i]=1LL*A[0][i]%mod*B[2][i]%mod;
	}
	NTT(B[0],1);
	NTT(B[1],1);
	NTT(B[2],1);
	for(re int i=0;i<=n-m;++i)
		if(((B[0][i+m-1]-(B[1][i+m-1]<<1)+B[2][i+m-1])%mod+mod)%mod==0)
			p[++p[0]]=i+1;
	cltstream::write(p[0],10);
	for(re int i=1;i<=p[0];++i)
		cltstream::write(p[i],32);
	clop();
	return 0;
}
