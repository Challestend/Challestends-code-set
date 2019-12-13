#include<cstdio>
#define re register
#define maxn 200000
#define maxm 500000
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m,q,ec,vc;
int src[2*maxm+1],des[2*maxm+1],val[2*maxm+1],suc[2*maxm+1],lst[3*maxn+1],ind[3*maxn+1];
int dfn[maxn+1],low[maxn+1],st[maxn+1],ex[maxn+1];
int id[maxn+1],sz[maxn+1],mn[maxn+1],mx[maxn+1],a[maxn+1][2];
int h[3*maxn+1],f[3*maxn+1][3];

inline void connect(re int u,re int v,re int w){
	src[++ec]=u;
	des[ec]=v;
	val[ec]=w;
	suc[ec]=lst[u];
	lst[u]=ec;
	++ind[v];
}

void dfs(re int cur){
	dfn[cur]=low[cur]=++vc;
	st[++st[0]]=cur;
	ex[cur]=1;
	for(re int i=lst[cur];i;i=suc[i])
		if(!dfn[des[i]]){
			dfs(des[i]);
			low[cur]=min(low[cur],low[des[i]]);
		}
		else
			if(ex[des[i]])
				low[cur]=min(low[cur],dfn[des[i]]);
	if(low[cur]==dfn[cur])
		for(;st[st[0]+1]!=cur;){
			re int x=st[st[0]--];
			ex[x]=0;
			id[x]=cur;
			++sz[cur];
			mn[cur]=2E9;
		}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(q);
	for(re int i=1;i<=m;++i){
		int u,v,w;
		cltstream::read(u);
		cltstream::read(v);
		cltstream::read(w);
		connect(u,v,w);
	}
	dfs(1);
	vc=2*n;
	for(re int i=1;i<=n;++i)
		if(id[i]==i)
			if(sz[i]>1){
				a[i][0]=++vc;
				a[i][1]=++vc;
			}
			else
				a[i][0]=a[i][1]=n+i;
	for(re int i=1;i<=ec;++i)
		if(id[src[i]]!=id[des[i]])
			connect(a[id[src[i]]][1],a[id[des[i]]][0],val[i]);
		else{
			mn[id[des[i]]]=min(mn[id[des[i]]],val[i]);
			mx[id[des[i]]]=max(mx[id[des[i]]],val[i]);
		}
	for(re int i=1;i<=n;++i)
		if(id[i]==i&&sz[i]>1){
			connect(a[i][0],n+i,mn[i]);
			connect(n+i,a[i][1],mx[i]);
		}
	h[1]=id[1];
	for(re int i=n+1;i<=vc;++i)
		f[i][0]=2E9;
	f[id[1]][0]=mn[id[1]];
	f[id[1]][1]=mx[id[1]];
	f[id[1]][2]=f[id[1]][1]-f[id[1]][0];
	for(re int head=0,tail=1;head<tail;){
		re int x=h[++head];
		for(re int i=lst[x];i;i=suc[i]){
			--ind[des[i]];
			f[des[i]][0]=min(f[des[i]][0],min(f[x][0],val[i]));
			f[des[i]][1]=max(f[des[i]][1],max(f[x][1],val[i]));
			f[des[i]][2]=max(f[des[i]][2],max(val[i]-f[x][0],f[x][1]-val[i]));
			if(!ind[des[i]])
				h[++tail]=des[i];
		}
	}
	for(re int i=1;i<=q;++i){
		int u;
		cltstream::read(u);
		cltstream::write(u>1&&id[u]?f[a[id[u]][1]][2]:-1,10);
	}
	for(re int i=1;i<=ec;++i)
		printf("(%d,%d,%d)\n",src[i],des[i],val[i]);
	clop();
	return 0;
}
