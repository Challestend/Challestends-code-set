#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define maxn 100010
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

long long n,m,ans1,ans2;

int main(){
	cltstream::read(n);
	cltstream::read(m);
	if(n==1)
		ans1=(m+1)/3;
	else{
		re long long z=(m+1)/2;
		ans1=(n+1)/3*z;
		if(n%3==1)
			ans1+=(m+1)/3;
	}
	std::swap(n,m);
	if(n==1)
		ans2=(m+1)/3;
	else{
		re long long z=(m+1)/2;
		ans2=(n+1)/3*z;
		if(n%3==1)
			ans2+=(m+1)/3;
	}
	cltstream::write(std::max(ans1,ans2));
	clop();
	return 0;
}
