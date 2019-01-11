#include<cstdio>
#define re register
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

int n,a,c;

int simEuc(re int n,re int a,re int b,re int c){
	if(!n)
		return b/c;
	if(!a)
		return 1LL*(n+1)*(b/c)%mod;
	if(a>=c||b>=c){
		re int res=simEuc(n,a%c,b%c,c);
		return (res+1LL*n*(n+1)/2%mod*(a/c)%mod+1LL*(n+1)*(b/c)%mod)%mod;
	}
	else{
		re int m=(1LL*a*n+b)/c;
		return (1LL*m*n%mod-simEuc(m-1,c,c-b-1,a)+mod)%mod;
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(a);
	cltstream::read(c);
	cltstream::write(simEuc(n,a,0,c));
	clop();
	return 0;
}
