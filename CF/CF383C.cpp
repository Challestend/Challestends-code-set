#include<cstdio>
#include<cmath>
#define re register
#define maxn 200000
#define maxs 450

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
int a[maxn+1],p[maxs+1][2],add[maxn+1];
int des[2*maxn+1],suc[2*maxn+1],lst[maxn+1],id[maxn+1],size[maxn+1],dep[maxn+1];

inline void connect(re int u,re int v){
	des[++ec]=v;
	suc[ec]=lst[u];
	lst[u]=ec;
}

void dfs1(re int cur,re int ftr){
	id[cur]=++vc;
	size[cur]=1;
	dep[cur]=dep[ftr]+1;
	for(re int i=lst[cur];i;i=suc[i])
		if(des[i]!=ftr){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
		}
}

void dfs2(re int cur,re int ftr,re int val){
	a[cur]+=val+=add[cur];
	add[cur]=0;
	val=-val;
	for(re int i=lst[cur];i;i=suc[i])
		if(des[i]!=ftr)
			dfs2(des[i],cur,val);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<n;++i){
		int u,v;
		cltstream::read(u);
		cltstream::read(v);
		connect(u,v);
		connect(v,u);
	}
	dep[0]=-1;
	dfs1(1,0);
	for(re int i=1,cnt=0;i<=m;++i){
		int opt;
		cltstream::read(opt);
		if(opt==1){
			cltstream::read(p[++cnt][0]);
			cltstream::read(p[cnt][1]);
			add[p[cnt][0]]+=p[cnt][1];
		}
		else{
			int u;
			cltstream::read(u);
			re int res=a[u];
			for(re int j=1;j<=cnt;++j)
				if(id[p[j][0]]<=id[u]&&id[p[j][0]]+size[p[j][0]]>id[u])
					res+=((dep[u]-dep[p[j][0]])&1)?-p[j][1]:p[j][1];
			cltstream::write(res,10);
		}
		if(cnt==sq){
			dfs2(1,0,0);
			cnt=0;
		}
	}
	clop();
	return 0;
}
