#include<cstdio>
#include<cmath>
#define re register
#define maxn 50000

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

int t,n,sq,m;
int f[maxn+1],g[maxn+1],w[(maxn<<1)+1],id1[maxn+1],id2[maxn+1];
int prmcnt[maxn+1],prmCnt[(maxn<<1)+1];
long long prmsum[maxn+1],prmSum[(maxn<<1)+1];

long long getPhi(re int x,re int y){
	if(x<=1||g[y]>x)
		return 0;
	else{
		re int id=x<=sq?id1[x]:id2[n/x];
		re long long res=(prmSum[id]-prmCnt[id])-(prmsum[y-1]-prmcnt[y-1]);
		for(re int i=y;i<=g[0]&&1LL*g[i]*g[i]<=x;++i)
			for(re int p=g[i];1LL*p*g[i]<=x;p*=g[i])
				res+=1LL*p/g[i]*(g[i]-1)*getPhi(x/p,i+1)+1LL*p*(g[i]-1);
		return res;
	}
}

int getMu(re int x,re int y){
	if(x<=1||g[y]>x)
		return 0;
	else{
		re int id=x<=sq?id1[x]:id2[n/x];
		re int res=prmcnt[y-1]-prmCnt[id];
		for(re int i=y;i<=g[0]&&1LL*g[i]*g[i]<=x;++i)
			res-=getMu(x/g[i],i+1);
		return res;
	}
}

int main(){
	for(re int i=2;i<=maxn;++i){
		if(!f[i]){
			g[++g[0]]=i;
			prmcnt[g[0]]=prmcnt[g[0]-1]+1;
			prmsum[g[0]]=prmsum[g[0]-1]+i;
		}
		for(re int j=1;j<=g[0]&&1LL*i*g[j]<=maxn;++j){
			f[i*g[j]]=1;
			if(!(i%g[j]))
				break;
		}
	}
	cltstream::read(t);
	for(;t;--t){
		cltstream::read(n);
		sq=sqrt(n);
		m=0;
		for(re int l=1,r;l<=n;r=n/(n/l),l=r+1){
			w[++m]=n/l;
			prmCnt[m]=w[m]-1;
			prmSum[m]=1LL*(w[m]-1)*(w[m]+2)/2;
			if(w[m]<=sq)
				id1[w[m]]=m;
			else
				id2[n/w[m]]=m;
		}
		for(re int j=1;j<=g[0];++j)
			for(re int i=1;i<=m&&w[i]>=1LL*g[j]*g[j];++i){
				re int id=w[i]/g[j]<=sq?id1[w[i]/g[j]]:id2[n/(w[i]/g[j])];
				prmCnt[i]-=prmCnt[id]-prmcnt[j-1];
				prmSum[i]-=1LL*g[j]*(prmSum[id]-prmsum[j-1]);
			}
		cltstream::write(getPhi(n,1)+1,32);
		cltstream::write(getMu(n,1)+1,10);
	}
	clop();
	return 0;
}
