#include<cstdio>
#include<algorithm>
#define re register
#define maxn 300000
#define maxlog 20
#define min(a,b) ((a)<=(b)?(a):(b))
#define stmin(st,a,b) (a<=b?min(st[a][lg[b-a+1]],st[b-(1<<lg[b-a+1])+1][lg[b-a+1]]):maxn+1)

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
int lg[maxn+1],s[maxn+1],p[maxn+1];
int fst[maxn+1],snd[2*maxn+1],tak[maxn+1];
int sa[maxn+1][maxlog+1],rnk[maxn+1],het[maxn+1][maxlog+1];

int main(){
	cltstream::read(mx);
	cltstream::read(n);
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(re int i=1;i<=n;++i){
		if(mx==26){
			re char c=cltstream::gc();
			for(;c<'a'||c>'z';c=cltstream::gc());
			s[i]=c-'a';
		}
		else
			cltstream::read(s[i]);
		p[i]=s[i];
	}
	std::sort(p+1,p+n+1);
	mx=std::unique(p+1,p+n+1)-p-1;
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=s[i]=std::lower_bound(p+1,p+mx+1,s[i])-p];
	for(re int i=1;i<=mx;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--][0]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=n-k+1;i<=n;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=n;++i)
			if(sa[i][0]>k)
				snd[++cnt]=sa[i][0]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=n;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=n;i>=1;--i)
			sa[tak[fst[snd[i]]]--][0]=snd[i];
		for(re int i=1;i<=n;++i)
			snd[i]=fst[i];
		cnt=1;
		fst[sa[1][0]]=1;
		for(re int i=2;i<=n;++i)
			fst[sa[i][0]]=snd[sa[i][0]]==snd[sa[i-1][0]]&&snd[sa[i][0]+k]==snd[sa[i-1][0]+k]?cnt:++cnt;
		if(cnt==n)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=n;++i)
		rnk[sa[i][0]]=i;
	for(re int i=1,j=0;i<=n;++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int pos=sa[rnk[i]-1][0];
			for(;i+j<=n&&pos+j<=n&&s[i+j]==s[pos+j];++j);
			het[rnk[i]][0]=j;
		}
	for(re int j=1,p=1;j<=lg[n];++j,p<<=1)
		for(re int i=1;i+(p<<1)-1<=n;++i){
			sa[i][j]=min(sa[i][j-1],sa[i+p][j-1]);
			het[i][j]=min(het[i][j-1],sa[i+p][j-1]);
		}
	for(re int i=1,j=1;i<=n;++i){
		for(;n-sa[j][0]+1<i;++j);
		re int l=j,r=n;
		for(;l<r;){
			re int mid=(l+r+1)>>1;
			if(stmin(het,j+1,mid)>=i)
				l=mid;
			else
				r=mid-1;
		}
		cltstream::write(stmin(sa,j,l),32);
	}
	clop();
	return 0;
}
