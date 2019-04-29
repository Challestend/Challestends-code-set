#include<cstdio>
#define re register

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

int P,Q,n,m;
long long T,R,ans;

inline int gcd(re int x,re int y){
	for(;y^=x^=y^=x%=y;);
	return x;
}

inline long long calc(re long long N){
	return N/R*(N/R-1)/2+(N%R)*(N/R);
}

int main(){
	cltstream::read(P);
	cltstream::read(Q);
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(T);
	R=1LL*P*Q/gcd(P,Q);
	for(re int i=0;i<n;++i){
		int x;
		cltstream::read(x);
		ans+=(T-x)/P;
	}
	for(re int i=0;i<m;++i){
		int x;
		cltstream::read(x);
		ans+=(T-x)/Q;
	}
	// ans-=calc(T)-calc(T-R);
	cltstream::write(ans);
	clop();
	return 0;
}
