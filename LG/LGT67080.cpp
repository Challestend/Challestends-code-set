#include<cstdio>
#define re register
#define mod 998244353
#define I2 499122177
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
			int digit[50];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

int t;
unsigned long long n;
struct matrix{
	int mat[4][4];

	inline void init(re int tp){
		for(re int i=0;i<4;++i)
			for(re int j=0;j<4;++j)
				mat[i][j]=tp*(i==j);
	}

	inline int* operator[](re int x){
		return mat[x];
	}

	matrix(re int tp){
		init(tp);
	}
};
matrix A(0),B(0);

inline matrix operator*(const matrix& A,const matrix& B){
	matrix res(0);
	for(re int i=0;i<4;++i)
		for(re int j=0;j<4;++j)
			for(re int k=0;k<4;++k)
				res[i][j]=(res[i][j]+1LL*A.mat[i][k]*B.mat[k][j]%mod)%mod;
	return res;
}

inline matrix matpow(matrix A,re unsigned long long x){
	matrix res(1);
	for(;x;){
		if(x&1)
			res=A*res;
		A=A*A;
		x>>=1;
	}
	return res;
}

int main(){
	A[0][0]=A[2][2]=A[2][3]=A[3][2]=1;
	cltstream::read(t);
	for(;t;--t){
		B.init(1);
		cltstream::read(n);
		for(re unsigned long long i=2,inv=I2;i>=2&&i<=n;i<<=1,inv=inv*I2%mod){
			A[0][2]=A[0][3]=A[1][2]=A[1][3]=inv;
			A[0][1]=A[1][1]=(1-inv+mod)%mod;
			B=matpow(A,min(i,n-i+1))*B;
		}
		cltstream::write((0LL+B[0][0]+B[0][1]+B[0][2])%mod,10);
	}
	clop();
	return 0;
}
