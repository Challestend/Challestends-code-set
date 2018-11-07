#include<cstdio>
#define re register
#define maxn 100000
#define mod 1000000007
#define lowbit(a) ((a)&(-(a)))

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
int a[maxn+1],fwt[maxn+1][2];

inline void update(re int x,re int y,re int z){
	for(re int i=x;i<=n;i+=lowbit(i)){
		fwt[i][0]=((fwt[i][0]+y-z)%mod+mod)%mod;
		fwt[i][1]=((fwt[i][1]+1LL*y*y%mod-1LL*z*z%mod)%mod+mod)%mod;
	}
}

inline int getsum(re int x){
	re int res=0;
	for(re int i=x;i>=1;i-=lowbit(i))
		res=(res+fwt[i][0])%mod;
	return res;
}

inline int getsqrsum(re int x){
	re int res=0;
	for(re int i=x;i>=1;i-=lowbit(i))
		res=(res+fwt[i][1])%mod;
	return res;
}

int cltpow(re int x,re int y){
	if(y==1)
		return x;
	else{
		int res=cltpow(x,y>>1);
		res=1LL*res*res%mod;
		if(y&1)
			res=1LL*res*x%mod;
		return res;
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		update(i,a[i],0);
	}
	for(re int i=1;i<=m;++i){
		re int opt,x,y;
		cltstream::read(opt);
		cltstream::read(x);
		cltstream::read(y);
		if(opt==1){
			update(x,y,a[x]);
			a[x]=y;
		}
		else{
			re int s1=((getsum(y)-getsum(x-1))%mod+mod)%mod;
			re int s2=((getsqrsum(y)-getsqrsum(x-1))%mod+mod)%mod;
			cltstream::write(((1LL*s2*cltpow(y-x+1,mod-2)%mod
			-1LL*s1*s1%mod*cltpow(1LL*(y-x+1)*(y-x+1)%mod,mod-2)%mod)%mod+mod)%mod,10);
		}
	}
	clop();
	return 0;
}
