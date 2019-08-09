#include<cstdio>
#define re register
#define mod 1000000007

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

long long n;
int F1,F2,F3,c;
struct matrix{
	int arr[5][5];

	matrix(){
		for(re int i=0;i<5;++i)
			for(re int j=0;j<5;++j)
				arr[i][j]=0;
	}
};
matrix A,B;

inline matrix operator*(const matrix& A,const matrix& B){
	matrix C;
	for(re int k=0;k<5;++k)
		for(re int i=0;i<5;++i)
			for(re int j=0;j<5;++j)
				C.arr[i][j]=(C.arr[i][j]+1LL*A.arr[i][k]*B.arr[k][j]%mod)%mod;
	return C;
}

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;y>>=1,x=1LL*x*x%mod)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

int main(){
	A.arr[0][1]=A.arr[1][2]=A.arr[2][0]=A.arr[2][1]=1;
	A.arr[2][2]=A.arr[2][3]=A.arr[3][3]=A.arr[4][4]=1;
	A.arr[3][4]=2;
	B.arr[0][0]=B.arr[1][1]=B.arr[2][2]=B.arr[3][3]=B.arr[4][4]=1;
	cltstream::read(n);
	cltstream::read(F1);
	cltstream::read(F2);
	cltstream::read(F3);
	cltstream::read(c);
	for(--n;n;n>>=1,A=A*A)
		if(n&1)
			B=B*A;
	re int ans=1;
	ans=1LL*ans*cltpow(F1,B.arr[0][0])%mod;
	ans=1LL*ans*cltpow(F2,B.arr[0][1])%mod;
	ans=1LL*ans*cltpow(F3,B.arr[0][2])%mod;
	ans=1LL*ans*cltpow(c,(2LL*B.arr[0][3]+B.arr[0][4])%(mod-1))%mod;
	cltstream::write(ans);
	clop();
	return 0;
}
