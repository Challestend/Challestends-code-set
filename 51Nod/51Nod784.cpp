#include<cstdio>
#include<algorithm>
#include<queue>
#define re register
#define maxn 1000000
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

int n,k,ans;
unsigned int sd;
int a[maxn+1],f[maxn+1],b[maxn+1];

inline unsigned int rnd(){
	sd^=sd<<13;
	sd^=sd>>17;
	sd^=sd<<5;
	return sd;
}

inline int FAQ(){
	re int res=0,tmp=0;
	std::priority_queue<int> h;
	for(re int i=1;i<=k;++i)
		h.push(b[i]);
	for(re int i=1;i<=n;++i){
		(tmp+=h.top())%=mod;
		(res+=tmp)%=mod;
		h.pop();
		if(k+i<=n)
			h.push(b[k+i]);
	}
	return res;
}

void dfs(re int cur){
	if(cur<n){
		for(re int i=1;i<=n;++i)
			if(!f[i]){
				f[i]=1;
				b[cur+1]=a[i];
				dfs(cur+1);
				f[i]=0;
			}
	}
	else
		(ans+=FAQ())%=mod;
}

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;){
		if(y&1)
			res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(k);
	cltstream::read(sd);
	re int tmp=1;
	for(re int i=1;i<=n;a[i]=rnd()%n+1,tmp=1LL*tmp*i%mod,++i);
	std::sort(a+1,a+n+1);
	dfs(0);
	cltstream::write(1LL*ans*cltpow(tmp,mod-2)%mod);
	clop();
	return 0;
}
