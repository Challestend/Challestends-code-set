#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 100000
#define maxlen 400000
#define maxlog 20
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define stmin(a,b) min(het[(a)][lg[(b)-(a)+1]],het[(b)-(1<<lg[(b)-(a)+1])+1][lg[(b)-(a)+1]])
#define id(a) ((a-1)/sq+1)

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

int n,m,sq;
int len[maxn+maxm+1],a[maxlen+1];
int fst[maxlen+1],snd[maxlen+1],tak[maxlen+1];
int sa[maxlen+1],rnk[maxlen+1],het[maxlen+1][maxlog+1],lg[maxlen+1];
int col[maxlen+1],cnt[maxn+1],lst[maxn+1],sum[maxn+1],ans[maxm+1];
struct Query{
	int t,l,r;
};
Query q[maxm+1];

inline bool operator<(re Query p1,re Query p2){
	return id(p1.l)==id(p2.l)?(id(p1.l)&1)?p1.r<p2.r:p1.r>p2.r:p1.l<p2.l;
}

inline void add(re int x,re int p){
	if(col[x]){
		if(!cnt[col[x]]){
			++cnt[0];
			lst[col[x]]=p;
		}
		++cnt[col[x]];
	}
}

inline void del(re int x,re int p){
	if(col[x]){
		--cnt[col[x]];
		if(!cnt[col[x]]){
			--cnt[0];
			sum[col[x]]+=p-lst[col[x]];
			lst[col[x]]=0;
		}
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i,len[i]=len[i-1]){
		int x;
		cltstream::read(x);
		for(re int j=1;j<=x;++j)
			cltstream::read(a[++len[i]]);
		a[++len[i]]=10001;
		cltstream::read(x);
		for(re int j=1;j<=x;++j)
			cltstream::read(a[++len[i]]);
		a[++len[i]]=10001;
	}
	for(re int i=1;i<=m;++i,len[n+i]=len[n+i-1]){
		int x;
		cltstream::read(x);
		for(re int j=1;j<=x;++j)
			cltstream::read(a[++len[n+i]]);
		a[++len[n+i]]=10001;
	}
	for(re int i=1;i<=len[n+m];++i)
		++tak[fst[i]=a[i]];
	for(re int i=1;i<=10001;++i)
		tak[i]+=tak[i-1];
	for(re int i=len[n+m];i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1,mx=10001;;k<<=1,mx=fst[sa[len[n+m]]]){
		re int cnt=0;
		for(re int i=len[n+m]-k+1;i<=len[n+m];++i)
			snd[++cnt]=i;
		for(re int i=1;i<=len[n+m];++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=len[n+m];++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=len[n+m];i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=len[n+m];++i)
			snd[i]=fst[i];
		fst[sa[1]]=1;
		for(re int i=2;i<=len[n+m];++i)
			fst[sa[i]]=fst[sa[i-1]]+(snd[sa[i]]!=snd[sa[i-1]]||snd[sa[i]+k]!=snd[sa[i-1]+k]);
		if(fst[sa[len[n+m]]]==len[n+m])
			break;
	}
	for(re int i=1;i<=len[n+m];++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=len[n+m];++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=len[n+m]&&pos+j<=len[n+m]&&a[i+j]==a[pos+j];++j);
			het[rnk[i]][0]=j;
		}
	for(re int i=2;i<=len[n+m];++i)
		lg[i]=lg[i>>1]+1;
	for(re int j=1,k=1;j<=lg[len[n+m]];++j,k<<=1)
		for(re int i=1;i+(k<<1)-1<=len[n+m];++i)
			het[i][j]=min(het[i][j-1],het[i+k][j-1]);
	for(re int i=1;i<=n;++i)
		for(re int j=len[i-1]+1;j<=len[i];++j)
			(a[j]<=10000)&&(col[rnk[j]]=i);
	for(re int i=1;i<=m;++i){
		q[i].t=i;
		re int L=1,R=rnk[len[n+i-1]+1];
		for(;L<R;){
			re int mid=(L+R)>>1;
			if(stmin(mid+1,rnk[len[n+i-1]+1])>=len[n+i]-len[n+i-1]-1)
				R=mid;
			else
				L=mid+1;
		}
		q[i].l=L;
		L=rnk[len[n+i-1]+1],R=len[n+m];
		for(;L<R;){
			re int mid=(L+R+1)>>1;
			if(stmin(rnk[len[n+i-1]+1]+1,mid)>=len[n+i]-len[n+i-1]-1)
				L=mid;
			else
				R=mid-1;
		}
		q[i].r=L;
	}
	sq=len[n+m]/sqrt(m);
	std::sort(q+1,q+m+1);
	for(re int i=1,L=1,R=0;i<=m;++i){
		for(;R<q[i].r;){
			++R;
			add(R,i);
		}
		for(;L>q[i].l;){
			--L;
			add(L,i);
		}
		for(;R>q[i].r;){
			del(R,i);
			--R;
		}
		for(;L<q[i].l;){
			del(L,i);
			++L;
		}
		ans[q[i].t]=cnt[0];
	}
	for(re int i=1;i<=n;++i)
		if(lst[i])
			sum[i]+=m-lst[i]+1;
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],10);
	for(re int i=1;i<=n;++i)
		cltstream::write(sum[i],32);
	clop();
	return 0;
}
