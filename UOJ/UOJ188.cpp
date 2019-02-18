#include<cstdio>
#include<cmath>
#define re register
#define maxn 320000

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

long long l,r;
int sq,m;
int f[maxn+1],g[maxn+1],id[(maxn<<1)+1];
long long w[(maxn<<1)+1],prmCnt[(maxn<<1)+1];

long long S(re long long n,re long long x,re int y){
	if(x<=1||g[y]>x)
		return 0;
	else{
		re int k=id[x<=sq?x:n/x+sq];
		re long long res=(y>1?g[y-1]:0)*(prmCnt[k]-y+1);
		for(re int i=y;i<=g[0]&&1LL*g[i]*g[i]<=x;++i)
			for(re long long p=g[i];p*g[i]<=x;p*=g[i])
				res+=S(n,x/p,i+1)+g[i];
		return res;
	}
}

inline long long solve(re long long n){
	sq=sqrt(n);
	m=0;
	for(re long long i=1;i<=n;i=n/(n/i)+1){
		w[++m]=n/i;
		if(w[m]<=sq)
			id[w[m]]=m;
		else
			id[n/w[m]+sq]=m;
		prmCnt[m]=w[m]-1;
	}
	for(re int j=1;j<=g[0];++j)
		for(re int i=1;i<=m&&w[i]>=1LL*g[j]*g[j];++i){
			re int k=id[w[i]/g[j]<=sq?w[i]/g[j]:n/(w[i]/g[j])+sq];
			prmCnt[i]-=prmCnt[k]-j+1;
		}
	return S(n,n,1);
}

int main(){
	for(re int i=2;i<=maxn;++i){
		if(!f[i])
			g[++g[0]]=i;
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(!(i%g[j]))
				break;
		}
	}
	cltstream::read(l);
	cltstream::read(r);
	cltstream::write(solve(r)-solve(l-1));
	clop();
	return 0;
}
