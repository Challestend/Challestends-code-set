#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#define re register
#define maxn 100000
#define maxs 320

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

int n,ec,sq;
int des[2*maxn+1],suc[2*maxn+1],lst[maxn+1];
struct query{
	int t,l,r;
};
query q[maxn+1];
inline bool operator<(const query& A,const query& B){
	return A.l/sq==B.l/sq?(A.l/sq&1)?A.r>B.r:A.r<B.r:A.l<B.l;
}
struct querz{
	int t,w,x;
};
std::vector<querz> v[maxn+1];
inline bool operator<(const querz& A,const querz& B){
	return A.x<B.x;
};
std::set<int> S;
int ans[maxn+1];

inline void connect(re int u,re int v){
	des[++ec]=v;
	suc[ec]=lst[u];
	lst[u]=ec;
}

void dfs(re int cur,re int ftr){
	S.insert(cur);
	re int cnt,tmp[maxn+1];
	for(std::set<int>::iterator p=S.begin();p!=S.end();tmp[++cnt]=*p,++p);
	std::sort(v[cur].begin(),v[cur].end());
	re int l=0,r=0,x=0;
	for(;l<cnt&&r<v[cur].size();)
		if(tmp[l]<=v[cur][r].x)
			++l;
		else
	for(re int i=lst[cur];i;i=suc[i])
		if(des[i]!=ftr)
			dfs(des[i],cur);
}

int main(){
	cltstream::read(n);
	sq=sqrt(n);
	for(re int i=1;i<n;++i){
		int u,v;
		cltstream::read(u);
		cltstream::read(v);
		connect(u,v);
		connect(v,u);
	}
	for(re int i=1;i<=n;++i){
		int l,r;
		cltstream::read(l);
		cltstream::read(r);
		q[i]={i,l,r};
	}
	std::sort(q+1,q+n+1);
	for(re int i=1,L=0,R=0;i<=n;++i){
		for(;R<q[i].r;++R,v[R].push_back({i,1,R-1}),v[R].push_back({i,-1,L}));
		for(;R>q[i].r;v[R].push_back({i,-1,R-1}),v[R].push_back({i,1,L}),--R);
		for(;L>q[i].r;--L,v[L].push_back({i,1,L+1}),v[L].push_back({i,-1,R}));
		for(;L<q[i].r;v[L].push_back({i,-1,L+1}),v[L].push_back({i,1,R}),++L);
	}
	dfs(1,0);
}
