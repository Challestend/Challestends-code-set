#include<cstdio>
#define re register
#define maxn 200000
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

int n,l,r;
int f[maxn+1][3];

int main(){
	cltstream::read(n);
	cltstream::read(l);
	cltstream::read(r);
	f[1][0]=r/3-(l-1)/3;
	f[1][1]=f[1][0]+(l%3==1)-(r%3==0);
	f[1][2]=f[1][1]+(l%3==2)-(r%3==1);
	for(re int i=2;i<=n;++i)
		for(re int j=0;j<3;++j)
			for(re int k=0;k<3;++k)
				f[i][k]=(f[i][k]+1LL*f[i-1][j]*f[1][(k-j+3)%3])%mod;
	cltstream::write(f[n][0]);
	clop();
	return 0;
}
