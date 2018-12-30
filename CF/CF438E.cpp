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
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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
int unit[2][23],rev[maxn+1],F[maxn+1],G[maxn+1],tmp1[maxn+1],tmp2[maxn+1];
// unit是预处理好的原根

inline void print(re int* F,re int n){
	putchar('{');
	for(re int i=0;i<n;++i)
		printf("%d%c",F[i],i<n-1?',':'}');
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

inline void NTT(re int* F,re int n,re int tp){
// tp=0 系数转点值; tp=1 点值转系数
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
	for(re int i=n;i<N;G[i]=0,++i);
	printf("");
	print(F,n);
	printf("^{-1}=");
	print(G,n);
	printf("\n\n");
}

inline void Sqrt(re int* F,re int* G,re int n){
	re int N=1;
	for(;N<n;N<<=1);
	N<<=1;
	for(re int i=0;i<N;++i)
		G[i]=0;
	G[0]=1;
	for(re int i=1,j=4;i<n;i<<=1,j<<=1){
		Inv(G,tmp2,i);
		NTT(G,j,0);
		for(re int k=0;k<(i<<1);++k)
			tmp1[k]=F[k];
		for(re int k=(i<<1);k<j;++k)
			tmp1[k]=0;
		NTT(tmp1,j,0);
		NTT(tmp2,j,0);
		for(re int k=0,tmp=1;k<j;++k,tmp=1LL*tmp*unit[0][j==4?2:3]%mod)
			printf("G(%9d)=%9d F(%9d)=%9d G^{-1}(%9d)=%9d",tmp,G[k],tmp,tmp1[k],tmp,tmp2[k]),
			printf(" => %d\n",499122177*(1LL*G[k]*G[k]%mod+tmp1[k])%mod*tmp2[k]%mod);
		for(re int k=0;k<j;++k)
			G[k]=499122177*(1LL*G[k]*G[k]%mod+tmp1[k])%mod*tmp2[k]%mod;
		NTT(G,j,1);
		for(re int k=(i<<1);k<j;++k)
			G[k]=0;
		print(G,i<<1);
		puts("\n");
	}
	for(re int i=n;i<N;G[i]=0,++i);
}

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	cltstream::read(n);
	cltstream::read(m);
	++m;
	for(re int i=1;i<=n;++i){
		re int x;
		cltstream::read(x);
		F[x]=mod-4;
	}
	++F[0];
	print(F,m);
	printf("\n\n");
	Sqrt(F,G,m);
	print(F,m);
	printf("^{1/2}=");
	print(G,m);
	printf("\n\n");
	++G[0];
	Inv(G,F,m);
	for(re int i=1;i<m;++i)
		cltstream::write(2LL*F[i]%mod,10);
	--G[0];
	print(G,m);
	printf("^{2}=");
	re int M=1;
	for(;M<m;M<<=1);
	M<<=1;
	NTT(G,M,0);
	for(re int i=0;i<M;++i)
		G[i]=1LL*G[i]*G[i]%mod;
	NTT(G,M,1);
	print(G,m);
	printf("\n\n");
	clop();
	return 0;
}
