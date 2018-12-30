#include<cstdio>
#include<cmath>
#define re register
#define maxn 300000
#define maxs (maxn/888+5)
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,sq;
int a[maxn+1],cnt[maxs+1][maxn+1];

int main(){
	cltstream::read(n),
	cltstream::read(m),
	sq=min(n,888);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]),
		++cnt[(i-1)/sq+1][a[i]];
	}
	for(re int i=1;i<=m;++i){
		re int opt;
		cltstream::read(opt);
		if(opt==1){
			re int l,r,c;
			cltstream::read(l),
			cltstream::read(r),
			cltstream::read(c);
			re int L=(l-1)/sq+1,R=(r-1)/sq+1,res=0;
			for(re int j=l;j<=L*sq&&j<=r;++j)
				res+=(a[j]==c);
			for(re int j=L+1;j<=R-1;++j)
				res+=cnt[j][c];
			if(L<R)
				for(re int j=(R-1)*sq+1;j<=r;++j)
					res+=(a[j]==c);
			cltstream::write(res,10);
		}
		else{
			re int x;
			cltstream::read(x);
			re int y=(x-1)/sq+1,z=x/sq+1;
			if(y<z){
				--cnt[y][a[x]],
				++cnt[y][a[x+1]],
				--cnt[z][a[x+1]],
				++cnt[z][a[x]];
			}
			a[x]^=a[x+1],
			a[x+1]^=a[x],
			a[x]^=a[x+1];
		}
	}
	clop();
	return 0;
}
