#include<cstdio>
#define re register
#define maxn 100000
#define maxlog 18
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define stmin(a,b) ((a)<=(b)?min(het[(a)][lg[(b)-(a)+1]],het[(b)-(1<<lg[(b)-(a)+1])+1][lg[(b)-(a)+1]]):maxn)

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

int n,m,vc;
char s[maxn+1];
int lg[maxn+1],fst[maxn+1],snd[maxn+1],tak[maxn+1];
int sa[maxn+1],rnk[maxn+1],het[maxn+1][maxlog+1];
int root[maxn+1],lc[maxn*(maxlog+4)+1],rc[maxn*(maxlog+4)+1],sum[maxn*(maxlog+4)+1];

int build(re int l,re int r){
	re int p=++vc;
	if(l<r){
		re int mid=(l+r)>>1;
		lc[p]=build(l,mid);
		rc[p]=build(mid+1,r);
	}
	return p;
}

int update(re int L,re int cur,re int l,re int r){
	re int p=++vc;
	if(l==r)
		sum[p]=sum[cur]+1;
	else{
		re int mid=(l+r)>>1;
		if(L<=mid){
			lc[p]=update(L,lc[cur],l,mid);
			rc[p]=rc[cur];
		}
		else{
			lc[p]=lc[cur];
			rc[p]=update(L,rc[cur],mid+1,r);
		}
		sum[p]=sum[lc[p]]+sum[rc[p]];
	}
	return p;
}

inline int getPre(re int x,re int L,re int R,re int l,re int r){
	for(;l<r&&sum[L]<sum[R];){
		re int mid=(l+r)>>1;
		if(x>mid&&sum[rc[L]]<sum[rc[R]]){
			l=mid+1;
			L=rc[L];
			R=rc[R];
		}
		else{
			r=mid;
			L=lc[L];
			R=lc[R];
		}
	}
	return sum[L]<sum[R]?l:-2E9;
}

inline int getSuc(re int x,re int L,re int R,re int l,re int r){
	for(;l<r&&sum[L]<sum[R];){
		re int mid=(l+r)>>1;
		if(x<=mid&&sum[lc[L]]<sum[lc[R]]){
			r=mid;
			L=lc[L];
			R=lc[R];
		}
		else{
			l=mid+1;
			L=rc[L];
			R=rc[R];
		}
	}
	return sum[L]<sum[R]?l:2E9;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		for(s[i]=cltstream::gc();s[i]<'a'||s[i]>'z';s[i]=cltstream::gc());
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=122;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1,mx=122;;k<<=1,mx=fst[sa[n]]){
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
		fst[sa[1]]=1;
		for(re int i=2;i<=n;++i)
			fst[sa[i]]=fst[sa[i-1]]+(snd[sa[i]]!=snd[sa[i-1]]||snd[sa[i]+k]!=snd[sa[i-1]+k]);
		if(fst[sa[n]]==n)
			break;
	}
	for(re int i=1;i<=n;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=n;++i)
		if(rnk[i]>1){
			j-=!!j;
			for(re int pos=sa[rnk[i]-1];i+j<=n&&pos+j<=n&&s[i+j]==s[pos+j];++j);
			het[rnk[i]][0]=j;
		}
	for(re int j=1,k=1;j<=lg[n];++j,k<<=1)
		for(re int i=1;i+(k<<1)-1<=n;++i)
			het[i][j]=min(het[i][j-1],het[i+k][j-1]);
	root[0]=build(1,n);
	for(re int i=1;i<=n;++i)
		root[i]=update(rnk[i],root[i-1],1,n);
	for(re int i=1;i<=m;++i){
		int a,b,c,d;
		cltstream::read(a);
		cltstream::read(b);
		cltstream::read(c);
		cltstream::read(d);
		if(a<=c&&c<=b)
			cltstream::write(min(b,d)-c+1,10);
		else{
			re int lwr=getPre(rnk[c],root[a-1],root[b],1,n),upr=getSuc(rnk[c],root[a-1],root[b],1,n);
			re int res=0;
			if(lwr>-2E9){
				re int tmp=min(b-sa[lwr]+1,stmin(lwr+1,rnk[c]));
				res=max(res,tmp);
			}
			if(upr<2E9){
				re int tmp=min(b-sa[upr]+1,stmin(rnk[c]+1,upr));
				res=max(res,tmp);
			}
			cltstream::write(res,10);
		}
	}
	freopen("C:/Users/Administrator/Downloads/str1.clt","w",stdout);
	clop();
}
