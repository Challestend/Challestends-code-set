#include<cstdio>
#define re register
#define maxn 1000
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

int n,top,andsum,orsum;
int a[maxn+1][maxn+1],h[maxn+1],p[maxn+1],q[maxn+1];

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n;++j)
			cltstream::read(a[i][j]);
	for(re int k=0,l=1;k<31;++k,l<<=1){
		for(re int i=1;i<=n;++i)
			h[i]=0;
		re int res=0;
		for(re int i=1;i<=n;++i){
			for(re int j=1;j<=n;++j)
				printf("%d%c",(a[i][j]&l)?1:0,j<n?32:10),
				h[j]=(a[i][j]&l)?h[j]+1:0;
			// for(re int j=1;j<=n;++j)
			// 	printf("%d%c",h[j],j<n?32:10);
			for(re int j=1;j<=n;++j){
				re int tmp=0;
				for(;top&&p[top]>h[j];tmp+=q[top],res=(res+1LL*tmp*p[top]%mod)%mod,--top);
				p[++top]=h[j];
				q[top]=tmp+1;
				printf("%d ",res);
			}
			re int tmp=0;
			for(;top;tmp+=q[top],res=(res+1LL*tmp*p[top]%mod)%mod,--top);
			printf("%d\n",res);
		}
		puts("");
		andsum=(andsum+1LL*res*l%mod)%mod;
	}
	for(re int k=0,l=1;k<31;++k,l<<=1){
		for(re int i=1;i<=n;++i)
			h[i]=0;
		re int res=250000002LL*n%mod*n%mod*(n+1)%mod*(n+1)%mod;
		for(re int i=1;i<=n;++i){
			for(re int j=1;j<=n;++j)
				h[j]=(a[i][j]&l)?0:h[j]+1;
			for(re int j=1;j<=n;++j){
				re int tmp=0;
				for(;top&&p[top]>h[j];tmp+=q[top],res=(res-1LL*tmp*p[top]%mod+mod)%mod,--top);
				p[++top]=h[j];
				q[top]=tmp+1;
			}
			re int tmp=0;
			for(;top;tmp+=q[top],res=(res-1LL*tmp*p[top]%mod+mod)%mod,--top);
		}
		orsum=(orsum+1LL*res*l%mod)%mod;
	}
	cltstream::write(andsum,32);
	cltstream::write(orsum);
	clop();
	return 0;
}
