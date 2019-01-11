#include<cstdio>
#define re register
#define mod 998244353

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

int t,a,b,c,n,I2=499122177,I6=166374059;
struct Query{
	int f,g,h;

	Query(re int _f,re int _g,re int _h){
		f=_f;
		g=_g;
		h=_h;
	}
};

inline Query query(re int a,re int b,re int c,re int n){
	if(!n){
		b/=c;
		return Query(b,0,1LL*b*b%mod);
	}
	if(!a){
		b/=c;
		return Query(1LL*(n+1)*b%mod,1LL*n*(n+1)%mod*I2%mod*b%mod,1LL*(n+1)*b%mod*b%mod);
	}
	if(a>=c||b>=c){
		re Query res=query(a%c,b%c,c,n);
		a/=c,
		b/=c;
		return Query(
			(res.f+1LL*n*(n+1)%mod*I2%mod*a%mod+1LL*(n+1)*b%mod)%mod,
			(res.g+1LL*n*(n+1)%mod*(2*n+1)%mod*I6%mod*a%mod+1LL*n*(n+1)%mod*I2%mod*b%mod)%mod,
			(res.h+2LL*a*res.g%mod+2LL*b*res.f%mod
				  +1LL*n*(n+1)%mod*(2*n+1)%mod*I6%mod*a%mod*a%mod
				  +1LL*(n+1)*b%mod*b%mod+1LL*n*(n+1)%mod*a%mod*b%mod)%mod
		);
	}
	else{
		re int m=(1LL*a*n+b)/c;
		re Query res=query(c,c-b-1,a,m-1);
		re int tmp=((1LL*m*n%mod-res.f)%mod+mod)%mod;
		return Query(
			tmp,
			((1LL*m*n%mod*(n+1)%mod-res.h-res.f)%mod+mod)*I2%mod,
			((1LL*m*(m+1)%mod*n%mod-2LL*res.g%mod-2LL*res.f%mod-tmp)%mod+mod)%mod
		);
	}
}

int main(){
	cltstream::read(t);
	for(;t;--t){
		cltstream::read(n);
		cltstream::read(a);
		cltstream::read(b);
		cltstream::read(c);
		Query ans=query(a,b,c,n);
		cltstream::write(ans.f,32);
		cltstream::write(ans.h,32);
		cltstream::write(ans.g,10);
	}
	clop();
	return 0;
}
