#include<cstdio>
#define re register
#define maxn 5000000
#define maxm 2200
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

long long n;
int I2=500000004,I6=166666668,ans;
int f[maxn+1],g[maxn+1],iph[maxn+1]={0,1},ipm[maxn+1]={0,1},lst[maxn+1];
int vis1[maxm+1],ans1[maxm+1],vis2[maxm+1],ans2[maxm+1];

int getSum1(long long N){
	if(N<=maxn)
		return iph[N];
	re int x=n/N;
	if(vis1[x])
		return ans1[x];
	re int res=(N%mod)*(N%mod+1)%mod*(2*N%mod+1)%mod*I6%mod;
	for(re long long l=2,r;l<=N;l=r+1){
		r=N/(N/l);
		res=(res-((r+l)%mod)*((r-l+1)%mod)%mod*I2%mod*getSum1(N/l)%mod+mod)%mod;
	}
	vis1[x]=1;
	return ans1[x]=res;
}

int getSum2(long long N){
	if(N<=maxn)
		return ipm[N];
	re int x=n/N;
	if(vis2[x])
		return ans2[x];
	re int res=getSum1(N);
	for(re long long l=2,r;l<=N;l=r+1){
		r=N/(N/l);
		res=(res-((r-l+1)%mod)*getSum2(N/l)%mod+mod)%mod;
	}
	vis2[x]=1;
	return ans2[x]=res;
}

int main(){
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			iph[i]=i-1;
			ipm[i]=1;
			lst[i]=(1LL*i*(i-1)-1)%mod;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(i%g[j]){
				iph[i*g[j]]=1LL*iph[i]*iph[g[j]]%mod;
				ipm[i*g[j]]=1LL*ipm[i]*lst[i]%mod;
				lst[i*g[j]]=lst[g[j]];
			}
			else{
				iph[i*g[j]]=1LL*iph[i]*g[j]%mod;
				ipm[i*g[j]]=ipm[i];
				lst[i*g[j]]=lst[i]==lst[g[j]]?(1LL*g[j]*g[j]-1)%mod*(lst[i]+1)%mod:1LL*g[j]*g[j]%mod*lst[i]%mod;
			}
		}
	}
	for(re int i=2;i<=maxn;++i){
		iph[i]=(iph[i-1]+1LL*i*iph[i]%mod)%mod;
		ipm[i]=(ipm[i-1]+1LL*ipm[i]*lst[i]%mod)%mod;
	}
	cltstream::read(n);
	for(re long long l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans=(ans+(((n/r)%mod)*((n/r)%mod)%mod-((n/(r+1))%mod)*((n/(r+1))%mod)%mod+mod)%mod*getSum2(r)%mod)%mod;
	}
	cltstream::write(ans);
	clop();
	return 0;
}
