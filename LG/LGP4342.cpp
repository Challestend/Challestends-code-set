#include<cstdio>
#define re register
#define maxn 50
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

int n;
int opt[(maxn<<1)+1],f[(maxn<<1)+1][maxn+1];

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		char c=cltstream::gc();
		for(;c!='t'&&c!='x';c=cltstream::gc());
		opt[i]=opt[i+n]=(c=='x');
		cltstream::read(f[i][1]);
		f[i+n][1]=f[i][1];
	}
	for(re int j=2;j<=n;++j)
		for(re int i=1;i+j-1<=(n<<1);++i){
			f[i][j]=-2e9;
			for(re int k=1;k<j;++k)
				f[i][j]=max(f[i][j],opt[i+k]?f[i][k]*f[i+k][j-k]:f[i][k]+f[i+k][j-k]);
		}
	f[0][n]=-2e9;
	for(re int i=1;i<=n;++i)
		f[0][n]=max(f[0][n],f[i][n]);
	cltstream::write(f[0][n],10);
	for(re int i=1;i<=n;++i)
		if(f[i][n]==f[0][n])
			cltstream::write(i,32);
	clop();
	return 0;
}
