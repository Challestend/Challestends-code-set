#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 15
#define maxm 225

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

const double eps=1E-18,t0=2000,delta=0.995,tk=1e-14,MAX_TIME=985;

int n,m,ec;
long long ans;
struct edge{
	int src,des,val;
};
edge e[maxm+1];
int f[maxn+1];
int des[2*maxn+1],val[2*maxn+1],suc[2*maxn+1],las[maxn+1],size[maxn+1];
long long sum[maxn+1];

int find(re int x){
	return f[x]==x?f[x]:f[x]=find(f[x]);
}

inline void connect(re int x,re int y,re int z){
	des[++ec]=y;
	val[ec]=z;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs1(re int cur,re int ftr){
	size[cur]=1;
	sum[cur]=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			sum[cur]+=sum[des[i]]+1LL*size[des[i]]*val[i];
		}
}

void dfs2(re int cur,re int ftr){
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			sum[des[i]]+=sum[cur]+1LL*(n-2*size[des[i]])*val[i];
			dfs2(des[i],cur);
		}
}

inline long long calculateVal(){
	std::random_shuffle(e+1,e+ec+1);
	for(re int i=1;i<=n;++i)
		f[i]=i;
	ec=0;
	for(re int i=1;i<=n;++i)
		las[i]=0;
	for(re int i=1,j=0;j<n-1;++i)
		if(find(e[i].src)!=find(e[i].des)){
			++j;
			f[f[e[i].src]]=f[e[i].des];
			connect(e[i].src,e[i].des,e[i].val);
			connect(e[i].des,e[i].src,e[i].val);
		}
	dfs1(1,0);
	dfs2(1,0);
	re long long res=0;
	for(re int i=1;i<=n;++i)
		res+=sum[i];
	return res/2;
}

inline void SA(){
	double t=t0;
	for(;t-tk>eps;){
		long long cur=calculateVal();
		if(cur<ans||(cur>ans&&exp(1.0*(ans-cur)/t)*RAND_MAX>rand()))
			ans=cur;
		t*=delta;
	}
}

int main(){
	srand(998244353);
	cltstream::read(n);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n-i;++j){
			int x;
			cltstream::read(x);
			e[++m].src=i;
			e[m].des=i+j;
			e[m].val=x;
		}
	ans=calculateVal();
	for(;clock()<MAX_TIME;SA());
	cltstream::write(ans);
	clop();
	return 0;
}
