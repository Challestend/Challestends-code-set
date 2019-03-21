#include<cstdio>
#include<algorithm>
#include<set>
#define re register
#define maxn 100000
#define maxlog 18
#define max(a,b) ((a)>=(b)?(a):(b))
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
			int digit[22];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

int n,mx;
long long ans;
int lg[maxn+1],a[maxn+1],p[maxn+1];
int fst[maxn+1],snd[maxn+1],tak[maxn+1];
int sa[2*maxn+1],rnk[maxn+1],st[maxn+1][maxlog+1];
std::set<int> s;

inline int stmin(re int l,re int r){
	if(r>n)
		return 0;
	else{
		re int p=lg[r-l+1];
		return min(st[l][p],st[r-(1<<p)+1][p]);
	}
}

int main(){
	cltstream::read(n);
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(re int i=n;i>=1;--i){
		cltstream::read(a[i]);
		p[i]=a[i];
	}
	std::sort(p+1,p+n+1);
	mx=std::unique(p+1,p+n+1)-p-1;
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=a[i]=std::lower_bound(p+1,p+mx+1,a[i])-p];
	for(re int i=1;i<=mx;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=n-k+1;i<=n;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=n;++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=n;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=n;i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=n;++i)
			snd[i]=fst[i];
		cnt=1;
		fst[sa[1]]=1;
		for(re int i=2;i<=n;++i)
			fst[sa[i]]=snd[sa[i]]==snd[sa[i-1]]&&snd[sa[i]+k]==snd[sa[i-1]+k]?cnt:++cnt;
		if(cnt==n)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=n;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=n;++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int p=sa[rnk[i]-1];
			for(;i+j<=n&&p+j<=n&&a[i+j]==a[p+j];++j);
			st[rnk[i]][0]=j;
		}
	for(re int i=1,p=2;p<=n;++i,p<<=1)
		for(re int j=1;j+p-1<=n;++j)
			st[j][i]=min(st[j][i-1],st[j+(p>>1)][i-1]);
	s.insert(0);
	s.insert(n+1);
	for(re int i=n;i>=1;--i){
		std::set<int>::iterator l=s.upper_bound(rnk[i]),r=l;
		--l;
		re int X=stmin(*l+1,rnk[i]),Y=stmin(rnk[i]+1,*r);
		ans+=n-i-max(X,Y)+1;
		cltstream::write(ans,10);
		s.insert(rnk[i]);
	}
	clop();
}
