#include<cstdio>
#define re register
#define maxn 1000000
#define mod 998244353

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

int k,n;
int f[maxn+1],g[maxn+1];
int phi[maxn+1],mu[maxn+1],d[maxn+1],lst[maxn+1],d1[maxn+1],d2[maxn+1];

int main(){
	cltstream::read(k);
	cltstream::read(n);
	phi[1]=mu[1]=d[1]=lst[1]=1;
	for(re int i=2;i<=n;++i){
		if(!f[i]){
			g[++g[0]]=i;
			phi[i]=i-1;
			mu[i]=mod-1;
			d[i]=1;
			lst[i]=2;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=n;++j)
			if(i%g[j]){
				f[i*g[j]]=1;
				phi[i*g[j]]=1LL*phi[i]*phi[g[j]]%mod;
				mu[i*g[j]]=1LL*mu[i]*mu[g[j]]%mod;
				d[i*g[j]]=1LL*d[i]*lst[i]%mod;
				lst[i*g[j]]=lst[g[j]];
			}
			else{
				f[i*g[j]]=1;
				phi[i*g[j]]=1LL*phi[i]*g[j]%mod;
				mu[i*g[j]]=0;
				d[i*g[j]]=d[i];
				lst[i*g[j]]=lst[i]+1;
				break;
			}
	}
	if(k==1)
		cltstream::write(g[0]);
	if(k==2){
		for(re int i=1;i<=n;++i)
			phi[i]=(phi[i]+phi[i-1])%mod;
		cltstream::write((2*phi[n]-1)%mod);
	}
	if(k==3){
		for(re int i=1;i<=n;++i)
			d[i]=1LL*d[i]*lst[i]%mod;
		for(re int i=1;i<=n;++i)
			d1[i]=(d1[i-1]+d[i])%mod;
		for(re int i=1;i<=n;++i)
			d2[i]=(d2[i-1]+1LL*d[i]*d[i]%mod)%mod;
		re int ans=0;
		for(re int i=1;2*i<=n;++i){
			re int tmp=0;
			for(re int j=1;2*j*i<=n;++j)
				tmp=(tmp+1LL*d[j]*(d1[(n-2*j*i)/i+j]-d1[j]+mod)%mod)%mod;
			ans=(ans+1LL*(tmp+d2[n/(2*i)])*mu[i]%mod)%mod;
		}
		cltstream::write((1LL*n*n%mod*n%mod-ans+mod)%mod);
	}
	clop();
	return 0;
}
