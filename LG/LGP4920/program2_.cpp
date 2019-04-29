#include<cstdio>
#define re register

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
int mod;
struct matrix{
	int arr[2][2];
};
matrix A,B;\

inline matrix operator*(const matrix& A,const matrix& B){
	matrix C;
	C.arr[0][0]=C.arr[0][1]=C.arr[1][0]=C.arr[1][1]=0;
	for(re int k=0;k<2;++k)
		for(re int i=0;i<2;++i)
			for(re int j=0;j<2;++j)
				C.arr[i][j]=(C.arr[i][j]+1LL*A.arr[i][k]*B.arr[k][j]%mod)%mod;
	return C;
}

int main(){
	freopen("program2.in","r",stdin);
	freopen("program2.out","w",stdout);
	for(re int T=10;T;--T){
		cltstream::read(n);
		cltstream::read(mod);
		A.arr[0][0]=0;
		A.arr[0][1]=A.arr[1][0]=A.arr[1][1]=1;
		B.arr[0][0]=B.arr[1][1]=1;
		B.arr[0][1]=B.arr[1][0]=0;
		for(--n;n;A=A*A,n>>=1)
			if(n&1)
				B=A*B;
		cltstream::write(1LL*B.arr[0][1]*B.arr[0][1]%mod,10);
		clop();
	}
	clop();
	return 0;
}
