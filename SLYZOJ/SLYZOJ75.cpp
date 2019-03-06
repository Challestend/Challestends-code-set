#include<cstdio>
#define re register
#define maxn 100000
#define abs(a) ((a)>=0?(a):(-(a)))

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

int n,m;
long long sum,ans;
int x[maxn+1],y[maxn+1],w[maxn+1],c[maxn+1];

void dfs(re int cur,re long long res){
	if(res>=ans)
		return;
	if(cur<n){
		for(re int i=1;i<=m;++i)
			if(c[i]){
				--c[i];
				dfs(cur+1,res+abs(x[cur+1]-y[i])+w[i]);
				++c[i];
			}
	}
	else
		ans=res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(x[i]);
	for(re int i=1;i<=m;++i){
		cltstream::read(y[i]);
		cltstream::read(w[i]);
		cltstream::read(c[i]);
		sum+=c[i];
	}
	if(sum<n)
		cltstream::write(-1);
	else{
		ans=9e18;
		dfs(0,0);
		cltstream::write(ans);
	}
	clop();
	return 0;
}
