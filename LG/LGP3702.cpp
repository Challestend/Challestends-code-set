#include<cstdio>
#define re register
#define maxm 20000000
#define maxp 100
#define mod 20170408

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

int n,m,p;
int f[maxm+1],g[maxm+1],cnt[maxp];
struct matrix{
	int arr[2*maxp][2*maxp];

	matrix(){
		for(re int i=0;i<2*maxp;++i)
			for(re int j=0;j<2*maxp;++j)
				arr[i][j]=0;
	}
};
matrix A,B;

inline matrix operator*(const matrix& A,const matrix& B){
	matrix res;
	for(re int k=0;k<2*p;++k)
		for(re int i=0;i<2*p;++i)
			for(re int j=0;j<2*p;++j)
				res.arr[i][j]=(res.arr[i][j]+1LL*A.arr[i][k]*B.arr[k][j]%mod)%mod;
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(p);
	for(re int i=2;i<=m;++i){
		if(!f[i]){
			g[++g[0]]=i;
			++cnt[i%p];
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=m;++j){
			f[i*g[j]]=1;
			if(!(i%g[j]))
				break;
		}
	}
	for(re int i=0;i<p;++i)
		for(re int j=0;j<p;++j){
			A.arr[(i+j)%p][i]=(A.arr[(i+j)%p][i]+(j<=m?(m-j)/p+!!j:0))%mod;
			A.arr[(i+j)%p][i]=(A.arr[(i+j)%p][i]-cnt[j]+mod)%mod;
			A.arr[p+(i+j)%p][i]=(A.arr[p+(i+j)%p][i]+cnt[j])%mod;
			A.arr[p+(i+j)%p][p+i]=(A.arr[p+(i+j)%p][p+i]+(j<=m?(m-j)/p+!!j:0))%mod;
		}
	for(re int i=0;i<2*p;++i)
		B.arr[i][i]=1;
	for(;n;){
		if(n&1)
			B=B*A;
		A=A*A;
		n>>=1;
	}
	cltstream::write(B.arr[p][0]);
	clop();
	return 0;
}
