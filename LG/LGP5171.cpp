#include<cstdio>
#define re register
#ifdef ONLINE_JUDGE
	#define int __int128_t
#endif

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
		signed sn=1;
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
			signed digit[50];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

int a,b,c;

inline int simEuc(re int n,re int a,re int b,re int c){
	if(!n)
		return b/c;
	if(!a)
		return (n+1)*(b/c);
	if(a>=c||b>=c){
		re int res=simEuc(n,a%c,b%c,c);
		return res+n*(n+1)*(a/c)/2+(n+1)*(b/c);
	}
	else{
		re int m=(a*n+b)/c;
		return m*n-simEuc(m-1,c,c-b-1,a);
	}
}

signed main(){
	cltstream::read(a);
	cltstream::read(b);
	cltstream::read(c);
	cltstream::write(simEuc(c/a,a,c%a,b)+c/a+1);
	clop();
	return 0;
}
