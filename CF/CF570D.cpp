#include<cstdio>
#include<algorithm>
#define re register
#define maxn 500000

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

int n,m,ec;
int des[maxn+1],suc[maxn+1],las[maxn+1];
int dfn[maxn+1],dep[maxn+1],size[maxn+1],h[maxn+1],p[maxn+1],bfn[maxn+1],lwr[maxn+2];
int a[maxn+1],val[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs(re int cur,re int ftr){
	dfn[cur]=++dfn[0];
	dep[cur]=dep[ftr]+1;
	size[cur]=1;
	for(re int i=las[cur];i;i=suc[i]){
		dfs(des[i],cur);
		size[cur]+=size[des[i]];
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=2;i<=n;++i){
		int x;
		cltstream::read(x);
		connect(x,i);
	}
	dfs(1,0);
	h[1]=1;
	for(re int head=0,tail=1;head<tail;){
		re int x=h[++head];
		p[head]=dfn[x];
		bfn[x]=head;
		dep[x]>dep[h[head-1]]&&(lwr[dep[x]]=head);
		for(re int i=las[x];i;i=suc[i])
			h[++tail]=des[i];
	}
	lwr[dep[h[n]]+1]=n+1;
	for(re int i=1;i<=n;++i){
		re char c=cltstream::gc();
		for(;c<'a'||c>'z';c=cltstream::gc());
		a[i]=1<<(c-'a');
	}
	for(re int i=1;i<=n;++i)
		val[i]=val[i-1]^a[h[i]];
	for(re int i=1;i<=m;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		re int L=std::lower_bound(p+lwr[y],p+lwr[y+1],dfn[x])-p;
		re int R=std::lower_bound(p+lwr[y],p+lwr[y+1],dfn[x]+size[x])-p-1;
		if(L<=R){
			re int v=val[R]^val[L-1];
			if((v&(v-1))==0)
				cltstream::pc('Y'),cltstream::pc('e'),cltstream::pc('s'),cltstream::pc(10);
			else
				cltstream::pc('N'),cltstream::pc('o'),cltstream::pc(10);
		}
		else
			cltstream::pc('Y'),cltstream::pc('e'),cltstream::pc('s'),cltstream::pc(10);
	}
	clop();
	return 0;
}
