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

int n,m;
int unit[2][24],rev[maxn+1],inv[maxn+1];
int F[maxn+1],G[maxn+1],P[maxn+1],Q[maxn+1],tmp[maxn+1];

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
	G[0]=cltpow(F[0],mod-2);
	for(re int i=1,j=4;i<n;i<<=1,j<<=1){
		NTT(G,j,0);
		for(re int k=0;k<(i<<1);++k)
			tmp[k]=F[k];
		for(re int k=(i<<1);k<j;++k)
			tmp[k]=0;
		NTT(tmp,j,0);
		for(re int k=0;k<j;++k)
			G[k]=(2-1LL*tmp[k]*G[k]%mod+mod)*G[k]%mod;
		NTT(G,j,1);
		for(re int k=(i<<1);k<j;++k)
			G[k]=0;
	}
}

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	inv[1]=1;
	for(re int i=2;i<=maxn;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	cltstream::read(n);
	++n;
	cltstream::read(m);
	++m;
	for(re int i=0;i<n;++i)
		cltstream::read(F[n-i-1]);
	for(re int i=0;i<m;++i)
		cltstream::read(G[m-i-1]);
	re int N;
	for(N=1;N<n;N<<=1);
	Inv(G,P,N);
	N<<=1;
	NTT(F,N,0);
	NTT(P,N,0);
	for(re int i=0;i<N;++i)
		P[i]=1LL*F[i]*P[i]%mod;
	NTT(F,N,1);
	NTT(P,N,1);
	for(re int i=0;i<n-i-1;++i)
		swap(F[i],F[n-i-1]);
	for(re int i=0;i<m-i-1;++i)
		swap(G[i],G[m-i-1]);
	for(re int i=0;i<n-m-i;++i)
		swap(P[i],P[n-m-i]);
	for(re int i=0;i<n-m+1;++i)
		cltstream::write(P[i],32);
	cltstream::pc(10);
	for(N=1;N<n;N<<=1);
	for(re int i=n-m+1;i<N;++i)
		P[i]=0;
	NTT(F,N,0);
	NTT(G,N,0);
	NTT(P,N,0);
	for(re int i=0;i<N;++i)
		Q[i]=(F[i]-1LL*P[i]*G[i]%mod+mod)%mod;
	NTT(Q,N,1);
	for(re int i=0;i<m-1;++i)
		cltstream::write(Q[i],32);
	clop();
	return 0;
}
