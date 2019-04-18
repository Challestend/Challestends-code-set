#include<cstdio>
#include<algorithm>
#define re register
#define maxn 250
#define mod 10007

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

int n,m;
int a[maxn+1][maxn+1];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;x=x*x%mod,y>>=1)
		if(y&1)
			res=res*x%mod;
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		a[x][x]=(a[x][x]+1)%mod;
		a[x][y]=(a[x][y]+mod-1)%mod;
	}
	re int ans=1;
	for(re int i=2;i<=n;++i){
		re int cur=i;
		for(;cur<=n&&!a[cur][i];++cur);
		if(cur>i)
			std::swap(a[cur],a[i]),ans=ans*(mod-1)%mod;
		for(re int j=i+1;j<=n;++j)
			for(re int tmp=a[j][i]*cltpow(a[i][i],mod-2)%mod,k=i;k<=n;++k)
				a[j][k]=(a[j][k]-tmp*a[i][k]%mod+mod)%mod;
	}
	for(re int i=2;i<=n;++i)
		ans=ans*a[i][i]%mod;
	cltstream::write(ans);
	clop();
	return 0;
}
