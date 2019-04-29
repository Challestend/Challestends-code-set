#include<cstdio>
#define re register
#define maxn 400
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

int n,m,c;
int C[maxn+1][maxn+1],p[maxn*maxn+1];

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(c);
	for(re int i=0;i<=n||i<=m||i<=c;++i){
		C[i][0]=C[i][i]=1;
		for(re int j=1;j<i;++j)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	re int ans=0;
	for(re int i=0;i<=c;++i){
		p[0]=1;
		for(re int j=1;j<=n*m;++j)
			p[j]=1LL*p[j-1]*(c-i+1)%mod;
		re int tmp=0;
		for(re int j=0;j<=n;++j)
			for(re int k=0;k<=m;++k)
				tmp=(tmp+1LL*(((j+k)&1)?mod-1:1)*C[n][j]%mod*C[m][k]%mod*p[(n-j)*(m-k)]%mod)%mod;
		ans=(ans+1LL*((i&1)?mod-1:1)*C[c][i]%mod*tmp%mod)%mod;
	}
	cltstream::write(ans);
	clop();
	return 0;
}
