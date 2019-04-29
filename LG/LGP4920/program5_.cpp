#include<cstdio>
#define re register
#define maxn 5000
#define sum(x1,y1,x2,y2) (b[x2][y2]-b[x1-1][y2]-b[x2][y1-1]+b[x1-1][y1-1])

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

int seed,n,m,tp;
int a[maxn+1][maxn+1],b[maxn+1][maxn+1];

int rnd(){
	static const int P=1000000007,Q=83978833,R=8523467;
	return seed=(1LL*Q*seed%P*seed+R)%P;
}

void generate_input(){
	cltstream::read(n);
	cltstream::read(m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=(rnd()%8)>0;
}

int main(){
	freopen("program5.in","r",stdin);
	freopen("program5.out","w",stdout);
	cltstream::read(seed);
	for(re int T=10;T;--T){
		generate_input();
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<=m;++j)
				b[i][j]=b[i-1][j]+b[i][j-1]-b[i-1][j-1]+a[i][j];
		re long long ans=0;
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<=m;++j)
				if(a[i][j])
					for(re int k=i;k<=n&&sum(i,j,k,j)==k-i+1;++k)
						for(re int l=j;l<=m&&sum(i,j,k,l)==(k-i+1)*(l-j+1);++l)
							++ans;
		cltstream::write(ans,10);
	}
	clop();
	return 0;
}
