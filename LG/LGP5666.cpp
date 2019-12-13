#include<cstdio>
#include<algorithm>
#include<vector>
#define re register
#define maxn 300000

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

int T,n,ec,vc,fe,nz;
int des[2*maxn+1],suc[2*maxn+1],lst[maxn+1];
int dfn[maxn+1],dep[maxn+1],sz[maxn+1],hes[maxn+1],het[maxn+1];
struct Query{
	int t,w,l,r;
};
std::vector<Query> vec[maxn+1];
int bit[maxn+1];

inline void connect(re int u,re int v){
	des[++ec]=v;
	suc[ec]=lst[u];
	lst[u]=ec;
}

void dfs1(re int cur,re int ftr){
	dfn[cur]=++vc;
	dep[cur]=dep[ftr]+1;
	sz[cur]=1;
	for(re int i=lst[cur];i;i=suc[i])
		if(des[i]!=ftr){
			dfs1(des[i],cur);
			sz[cur]+=sz[des[i]];
			if(sz[hes[cur]]<sz[des[i]]){
				het[cur]=hes[cur];
				hes[cur]=des[i];
			}
			else
				if(sz[het[cur]]<sz[des[i]])
					het[cur]=des[i];
		}
	if(sz[hes[cur]]<n-sz[cur]){
		het[cur]=hes[cur];
		hes[cur]=ftr;
	}
	else
		if(sz[het[cur]]<n-sz[cur])
			het[cur]=ftr;
}

void dfs2(re int cur,re int ftr){
	sz[cur]=1;
	for(re int i=lst[cur];i;i=suc[i])
		if(i!=fe&&i!=fe+1&&des[i]!=ftr){
			dfs2(des[i],cur);
			sz[cur]+=sz[des[i]];
			if(sz[hes[cur]]<sz[des[i]])
				hes[cur]=des[i];
		}
	if(sz[hes[cur]]<nz-sz[cur])
		hes[cur]=ftr;
}

inline void modify(re int x){
	for(;x<=n;x+=x&(-x))
		++bit[x];
}

inline int query(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit[x];
	return res;
}

int main(){
	cltstream::read(T);
	for(;T;--T){
		cltstream::read(n);
		ec=0;
		for(re int i=1;i<=n;++i)
			lst[i]=hes[i]=het[i]=0;
		for(re int i=1;i<n;++i){
			int u,v;
			cltstream::read(u);
			cltstream::read(v);
			connect(u,v);
			connect(v,u);
		}
		dfs1(1,0);
		re long long ans=0;
		for(re int i=1;i<=n;++i){
			re int x=!hes[i]||dep[hes[i]]>dep[i]?sz[hes[i]]:n-sz[i];
			re int y=!het[i]||dep[het[i]]>dep[i]?sz[het[i]]:n-sz[i];
			// printf("%d %d(%d) %d(%d)\n",i,hes[i],x,het[i],y);
			if(2*x>n)
				if(!hes[i]||dep[hes[i]]>dep[i]){
					vec[dfn[hes[i]]+sz[hes[i]]-1].push_back({i,1,2*x-n,n-2*y});
					vec[dfn[hes[i]]-1].push_back({i,-1,2*x-n,n-2*y});
				}
				else{
					vec[n].push_back({i,1,2*x-n,n-2*y});
					vec[dfn[i]+sz[i]-1].push_back({i,-1,2*x-n,n-2*y});
					vec[dfn[i]-1].push_back({i,1,2*x-n,n-2*y});
				}
		}
		for(re int i=1;i<=n;++i){
			re int x=!hes[i]||dep[hes[i]]>dep[i]?sz[hes[i]]:n-sz[i];
			re int y=!het[i]||dep[het[i]]>dep[i]?sz[het[i]]:n-sz[i];
			// printf("%d %d(%d) %d(%d)\n",i,hes[i],x,het[i],y);
			if(2*x<=n){
				dfs1(i,0);
				for(re int j=1;j<=ec;j+=2){
					fe=j;
					nz=dep[des[j]]>dep[des[j+1]]?n-sz[des[j]]:n-sz[des[j+1]];
					dfs2(i,0);
					printf("(%d,%d) %d %d\n",des[j],des[j+1],nz,hes[i]);
					if(2*sz[hes[i]]<=nz)
						ans+=i,printf("ans+=%d\n",i);
				}
			}
		}
		for(re int i=1;i<=n;++i){
			modify(sz[i]);
			for(std::vector<Query>::iterator p=vec[i].begin();p!=vec[i].end();++p)
				// printf("[%d,%d]\n",p->l,p->r),
				ans+=1LL*p->w*p->t*(query(p->r)-query(p->l-1));
		}
		cltstream::write(ans,10);
	}
	clop();
	return 0;
}
