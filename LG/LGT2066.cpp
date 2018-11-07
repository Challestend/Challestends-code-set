#include<cstdio>
#define re register
#define maxm 500000
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

int n,m,k,ans=1;
long long q;
int a[maxm+1];

int cltpow(int x,int y){
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
	cltstream::read(k);
	cltstream::read(q);
	q%=mod;
	for(re int i=0;i<=m;cltstream::read(a[i]),++i);
	for(re int i=m-1;i>=0;a[i]=(1LL*a[i+1]*q%mod+a[i])%mod,--i);
	for(re int i=1;i<=k;ans=1LL*ans*i%mod,++i);
	for(re int i=1;i<=n-k;ans=1LL*ans*i%mod,++i);
	ans=cltpow(ans,mod-2);
	for(re int i=1;i<=n;ans=1LL*ans*i%mod,++i);
	cltstream::write(1LL*ans*a[0]%mod);
	clop();
	return 0;
}
