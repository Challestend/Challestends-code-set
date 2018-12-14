#include<cstdio>
#define re register
#define maxn 1000

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
	inline void read(_tp& x,_tp mod=2147483647){
		int sn=1,e=0;
		char c=gc();
		for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
		if(c==45&&c!=EOF)
			sn=-1,c=gc();
		for(x=0;c>=48&&c<=57&&c!=EOF;c=gc()){
			x=(x<<3)+(x<<1)+(c^48);
			for(;x>=mod;x-=mod,e=mod);
		}
		x*=sn;
		x+=e;
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

int a,m,n,phi=1,b;
int f[maxn+1],g[maxn+1];

int main(){
	cltstream::read(a);
	cltstream::read(m);
	a%=m;
	for(;(n+1)*(n+1)<=m;++n);
	for(re int i=2;i<=n;++i){
		if(!f[i])
			g[++g[0]]=i;
		for(re int j=1;j<=g[0]&&i*g[j]<=n;++j){
			f[i*g[j]]=1;
			if(i%g[j]==0)
				break;
		}
	}
	re int _m=m;
	for(re int i=1;i<=g[0];++i)
		if(_m%g[i]==0)
			for(_m/=g[i],phi*=g[i]-1;_m%g[i]==0;_m/=g[i],phi*=g[i]);
	if(_m>1)
		phi*=_m-1;
	cltstream::read(b,phi);
	re int ans=1;
	for(;b;a=1LL*a*a%m,b>>=1)
		if(b&1)
			ans=1LL*ans*a%m;
	cltstream::write(ans);
	clop();
	return 0;
}
