#include<cstdio>
#include<cmath>
#define re register
#define maxs 100000
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

long long n;
int sq,m;
int f[maxs+1],g[maxs+1],id[2*maxs+1];
long long w[2*maxs+1];
int D1[2*maxs+1],D2[2*maxs+1];

int getD1(re long long x,re int y){
	if(x<=1||g[y]>x)
		return 0;
	else{
		re int k=id[x<=sq?x:n/x+sq],res=D1[k]-2*(y-1);
		for(re int i=y;i<=g[0]&&1LL*g[i]*g[i]<=x;++i)
			for(re long long c=1,p=g[i];p*g[i]<=x;++c,p*=g[i])
				res=(res+1LL*(c+1)*getD1(x/p,i+1)%mod+c+2)%mod;
		return res;
	}
}

int getD2(re long long x,re int y){
	if(x<=1||g[y]>x)
		return 0;
	else{
		re int k=id[x<=sq?x:n/x+sq],res=D2[k]-4*(y-1);
		for(re int i=y;i<=g[0]&&1LL*g[i]*g[i]<=x;++i)
			for(re long long c=1,p=g[i];p*g[i]<=x;++c,p*=g[i])
				res=(res+1LL*(c+1)*(c+1)%mod*getD1(x/p,i+1)%mod+1LL*(c+2)*(c+2)%mod)%mod;
		return res;
	}
}

int main(){
	cltstream::read(n);
	sq=sqrt(n);
	for(re int i=2;i<=sq;++i){
		if(!f[i])
			g[++g[0]]=i;
		for(re int j=1;j<=g[0]&&i*g[j]<=sq;++j){
			f[i*g[j]]=1;
			if(!(i%g[j]))
				break;
		}
	}
	for(re long long l=1;l<=n;l=n/(n/l)+1){
		w[++m]=n/l;
		D1[m]=2*(w[m]-1);
		D2[m]=4*(w[m]-1);
		id[w[m]<=sq?w[m]:n/w[m]+sq]=m;
	}
	for(re int j=1;j<=g[0];++j)
		for(re int i=1;i<=m&&w[i]>=1LL*g[j]*g[j];++i){
			re int k=id[w[i]/g[j]<=sq?w[i]/g[j]:n/(w[i]/g[j])+sq];
			D1[i]-=(D1[k]-2*(j-1));
			D2[i]-=(D2[k]-4*(j-1));
		}
	for(re int i=1;i<=n;++i)
		printf("%d %d %d\n",i,getD1(i,1)-getD1(i-1,1),getD2(i,1)-getD2(i-1,1));
	clop();
	return 0;
}
