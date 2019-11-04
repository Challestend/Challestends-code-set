#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<set>
#define re register
#define maxn 100000
#define maxval 10000

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

int n,ec;
int f[maxval+1],g[maxval+1];
long long h[maxval+1];
int des[2*maxn+1],suc[2*maxn+1],len[2*maxn+1],las[maxn+1];
long long val[maxn+1];
std::multiset<long long> S;

inline void connect(re int u,re int v,re int w){
	des[++ec]=v;
	suc[ec]=las[u];
	len[ec]=w;
	las[u]=ec;
}

void dfs(re int cur,re int ftr){
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			val[des[i]]^=val[cur];
			for(re int j=1;j<=g[0]&&g[j]<=len[i];++j)
				for(;len[i]%g[j]==0;len[i]/=g[j],val[des[i]]^=h[j]);
			dfs(des[i],cur);
		}
}

int main(){
	srand(time(0));
	srand(998244353);
	freopen("data.in","r",stdin);
	for(re int i=2;i<=maxval;++i){
		if(!f[i]){
			g[++g[0]]=i;
			h[g[0]]|=((long long)rand())<<45;
			h[g[0]]|=((long long)rand())<<30;
			h[g[0]]|=((long long)rand())<<15;
			h[g[0]]|=((long long)rand());
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxval;++j){
			f[i*g[j]]=1;
			if(i%g[j]==0)
				break;
		}
	}
	cltstream::read(n);
	for(re int i=1;i<n;++i){
		int u,v,w;
		cltstream::read(u);
		cltstream::read(v);
		cltstream::read(w);
		connect(u,v,w);
		connect(v,u,w);
	}
	dfs(1,0);
	for(re int i=1;i<=n;++i)
		S.insert(val[i]);
	re long long ans=0;
	for(long long v,c;!S.empty();v=*S.begin(),c=S.count(v),ans+=c*(c-1)/2,S.erase(v));
	cltstream::write(ans);
	clop();
	return 0;
}
