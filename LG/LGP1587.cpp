#include<cstdio>
#include<tr1/unordered_map>
#define re register
#define maxn 1000000
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,k;
int d[50],f[maxn+1],g[maxn+1],mu[maxn+1],F[maxn+1];
std::tr1::unordered_map<int,long long> ans;

long long T(re int x){
	re long long res=0;
	for(re int i=1;i<=d[0];++i)
		res+=1LL*(x/d[i])*mu[d[i]];
	return res;
}

long long S(re int N){
	if(N<=maxn)
		return F[N];
	if(ans.count(N))
		return ans[N];
	re long long res=1,lst=T(1);
	for(re int l=2,r;l<=N;l=r+1){
		r=N/(N/l);
		re long long tmp=T(r);
		res-=S(N/l)*(tmp-lst);
		lst=tmp;
	}
	return ans[N]=res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(k);
	for(re int i=1;i<=k;++i)
		if(k%i==0)
			d[++d[0]]=i;
	mu[1]=F[1]=1;
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			mu[i]=-1;
			F[i]=-(k%i!=0);
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(i%g[j]){
				mu[i*g[j]]=mu[i]*mu[g[j]];
				F[i*g[j]]=F[i]*F[g[j]];
			}
			else
				break;
		}
	}
	for(re int i=1;i<=maxn;++i)
		F[i]+=F[i-1];
	re long long res=0,lst=0;
	for(re int l=1,r;l<=n&&l<=m;l=r+1){
		r=min(n/(n/l),m/(m/l));
		re long long tmp=S(r);
		res+=(n/l)*T(m/l)*(tmp-lst);
		lst=tmp;
	}
	cltstream::write(res);
	clop();
	return 0;
}
