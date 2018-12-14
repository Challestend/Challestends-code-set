#include<cstdio>
#include<tr1/unordered_map>
#define re register
#define maxn 1700000

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

int t;
unsigned n;
int f[maxn+1],g[maxn+1];
long long phi[maxn+1]={0,1},mu[maxn+1]={0,1};
std::tr1::unordered_map<unsigned,long long> ans1,ans2;

void getSum(unsigned n){
	if(n<=maxn||ans1.count(n))
		return;
	else{
		re long long res1=1LL*n*(n+1)>>1,res2=1;
		for(re unsigned l=2,r;l<=n;l=r+1){
			r=n/(n/l);
			getSum(n/l);
			res1-=(r-l+1)*(n/l<=maxn?phi[n/l]:ans1[n/l]);
			res2-=(r-l+1)*(n/l<=maxn?mu[n/l]:ans2[n/l]);
		}
		ans1[n]=res1;
		ans2[n]=res2;
	}
}

int main(){
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(i%g[j]){
				phi[i*g[j]]=phi[i]*phi[g[j]];
				mu[i*g[j]]=mu[i]*mu[g[j]];
			}
			else{
				phi[i*g[j]]=phi[i]*g[j];
				mu[i*g[j]]=0;
				break;
			}
		}
	}
	for(re int i=1;i<=maxn;++i){
		phi[i]+=phi[i-1];
		mu[i]+=mu[i-1];
	}
	cltstream::read(t);
	for(;t;--t){
		cltstream::read(n);
		getSum(n);
		cltstream::write(n<=maxn?phi[n]:ans1[n],32);
		cltstream::write(n<=maxn?mu[n]:ans2[n],10);
	}
	clop();
	return 0;
}
