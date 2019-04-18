#include<cstdio>
#define re register
#define maxn 1048576
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

int n,mx,N;
int p[maxn],F[maxn];

inline void FWT(re int* F,re int n,re int tp){
	for(re int p=1;p<n;p<<=1)
		for(re int i=0;i<n;i+=p<<1)
			for(re int j=i;j<i+p;++j)
				F[j]=!tp?(F[j]+F[j+p])%mod:(F[j]-F[j+p]+mod)%mod;
}

int main(){
	cltstream::read(n);
	p[0]=1;
	for(re int i=1;i<=n;++i)
		p[i]=2LL*p[i-1]%mod;
	for(re int i=1;i<=n;++i){
		int x;
		cltstream::read(x);
		++F[x];
		(mx<x)&&(mx=x);
	}
	for(N=1;N<mx+1;N<<=1);
	FWT(F,N,0);
	for(re int i=0;i<N;++i)
		F[i]=p[F[i]];
	FWT(F,N,1);
	cltstream::write(F[0]-!mx);
	clop();
	return 0;
}
