#include<cstdio>
#define re register
#define maxn 5000
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

int n,rt,ec,mn,mx;
int des[2*maxn+1],suc[2*maxn+1],lst[maxn+1],d[maxn+1],dep[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=lst[x];
	lst[x]=ec;
}

void dfs(re int cur,re int ftr){
	dep[cur]=dep[ftr]+1;
	if(d[cur]<2){
		mn=min(mn,dep[cur]);
		mx=max(mx,dep[cur]);
	}
	for(re int i=lst[cur];i;i=suc[i])
		if(des[i]!=ftr)
			dfs(des[i],cur);
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		int x;
		cltstream::read(x);
		if(x){
			connect(x,i);
			connect(i,x);
			++d[x];
		}
		else
			rt=i;
	}
	mn=n+1;
	if(mx-mn>1)
		puts("Impossible");
	return 0;
}
