#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define re register
#define maxn 100000

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

int n,m,sq,ec,vc;
int id[maxn+1],des[maxn+1],suc[maxn+1],lst[maxn+1];
int dfn[maxn+1],dfm[maxn+1],bit[maxn+1],a[maxn+1],b[maxn+1];
struct query{
	int t,l,r;
};
query q[maxn+1];
struct querz{
	int t,w,l,r;
};
std::vector<querz> v[maxn+1];
long long ans[maxn+1];

inline bool operator<(re query A,re query B){
	return id[A.l]==id[B.l]?(id[A.l]&1)?A.r<B.r:A.r>B.r:A.l<B.l;
}

inline void updNum(re int x,re int y){
	for(;x<=n;x+=x&(-x))
		bit[x]+=y;
}

inline int getNum(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit[x];
	return res;
}

inline void connect(re int u,re int v){
	des[++ec]=v;
	suc[ec]=lst[u];
	lst[u]=ec;
}

void dfs1(re int cur,re int ftr){
	dfn[cur]=++vc;
	dfm[vc]=cur;
	updNum(cur,1);
	a[cur]=getNum(cur-1);
	for(re int i=lst[cur];i;i=suc[i])
		if(des[i]!=ftr)
			dfs1(des[i],cur);
	updNum(cur,-1);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<n;++i){
		int u,v;
		cltstream::read(u);
		cltstream::read(v);
		connect(u,v);
		connect(v,u);
	}
	dfs1(1,0);
	for(re int i=1;i<=n;++i){
		updNum(dfm[i],1);
		b[i]=getNum(dfm[i]-1);
	}
	for(re int i=1;i<=m;++i){
		q[i].t=i;
		cltstream::read(q[i].l);
		cltstream::read(q[i].r);
	}
	std::sort(q+1,q+m+1);
	for(re int i=1,L=1,R=0;i<=m;++i){
		for(;R<q[i].r;){
			++R;
		}
	}
}
