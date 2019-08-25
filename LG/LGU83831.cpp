#include<cstdio>
#define re register
#define maxn 100004
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

int n,ec;
int des[2*maxn+1],suc[2*maxn+1],las[maxn+1],w[maxn+1],ans[maxn+1],tmp[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs(re int cur,re int ftr){
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr){
			dfs(des[i],cur);
			ans[cur]+=max(ans[des[i]]-tmp[cur],0);
			tmp[cur]=max(tmp[cur]-ans[des[i]],0)+tmp[des[i]];
		}
	ans[cur]+=max(w[cur]-tmp[cur],0);
	tmp[cur]=max(tmp[cur]-w[cur],0);
	printf("%d %d %d %d\n",cur,w[cur],ans[cur],tmp[cur]);
}

int main(){
	cltstream::read(n);
	for(re int i=2;i<=n;++i){
		int x;
		cltstream::read(x);
		connect(i,x);
		connect(x,i);
	}
	for(re int i=1;i<=n;++i)
		cltstream::read(w[i]);
	dfs(1,0);
	for(re int i=1;i<=n;++i)
		cltstream::write(ans[i],32);
	clop();
	return 0;
}
