#include<cstdio>
#include<cmath>
#define re register
#define maxn 1000000

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

int t,sq;
long long n,m;
int f[maxn+1],g[maxn+1],id[(maxn<<1)+1];
long long w[(maxn<<1)+1],prmCnt[(maxn<<1)+1];

unsigned long long S(re long long x,re int y){
	if(x<=1||g[y]>x)
		return 0;
	else{
		re int k=id[x<=sq?x:n/x+sq];
		re unsigned long long res=1ULL*(m+1)*(prmCnt[k]-y+1);
		for(re int i=y;i<=g[0]&&1LL*g[i]*g[i]<=x;++i){
			re long long p=g[i];
			for(re int j=1;p*g[i]<=x;++j,p*=g[i])
				res+=(1ULL*j*m+1)*(S(x/p,i+1)+1)+m;
		}
		return res;
	}
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
	cltstream::read(t);
	for(;t;--t){
		cltstream::read(n);
		m=2;
		sq=sqrt(n);
		re int cnt=0;
		for(re long long i=1;i<=n;i=n/(n/i)+1){
			w[++cnt]=n/i;
			prmCnt[cnt]=w[cnt]-1;
			if(w[cnt]<=sq)
				id[w[cnt]]=cnt;
			else
				id[n/w[cnt]+sq]=cnt;
		}
		for(re int j=1;j<=g[0]&&1LL*g[j]*g[j]<=n;++j)
			for(re int i=1;i<=cnt&&w[i]>=1LL*g[j]*g[j];++i){
				re int k=id[w[i]/g[j]<=sq?w[i]/g[j]:n/(w[i]/g[j])+sq];
				prmCnt[i]-=prmCnt[k]-j+1;
			}
		cltstream::write(S(n,1)+1,10);
	}
	clop();
	return 0;
}
