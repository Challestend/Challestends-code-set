#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define re register
#define maxn 100000
#define maxs 320
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m;
int sq[2*maxn+1],id[maxn+1],a[maxn+1],val[maxn+1],len[maxn+1],p[2][maxs+1];
int sum[maxs+1],prd[maxs+1],upd[maxs+1];
int ans[4*maxn+1],size[4*maxn+1],cnt[4*maxn+1][maxs+1],vec[4*maxn+1][maxn/maxs+1];
int tag[4*maxn+1],c[4*maxn+1],brk[4*maxn+1];

inline void getPow(re int x,re int N){
	// printf("N=%d sqrt{N}=%d\n",N,sq[N]);
	p[0][0]=1;
	for(re int i=1;i<=sq[N];++i)
		p[0][i]=p[0][i-1]*x;
	p[1][0]=1;
	for(re int i=1;i<=N/sq[N];++i)
		p[1][i]=p[1][i-1]*p[0][sq[N]];
}

inline void modify(re int l,re int r,re int x){
	getPow(x,n);
	re int L=id[l],R=id[r];
	if(L<R){
		sum[L]=0,
		prd[L]=1;
		for(re int i=(L-1)*sq[n]+1;i<=l-1;++i)
			sum[L]+=a[i]=upd[L]?upd[L]:a[i],
			prd[L]*=a[i]=upd[L]?upd[L]:a[i];
		for(re int i=l;i<=L*sq[n]&&i<=n;++i)
			sum[L]+=a[i]=x,
			prd[L]*=a[i]=x;
		upd[L]=0;
		for(re int i=L+1;i<=R-1;++i)
			sum[i]=sq[n]*x,
			prd[i]=p[1][1],
			upd[i]=x;
		sum[R]=0,
		prd[R]=1;
		for(re int i=(R-1)*sq[n]+1;i<=r;++i)
			sum[R]+=a[i]=x,
			prd[R]*=a[i]=x;
		for(re int i=r+1;i<=R*sq[n]&&i<=n;++i)
			sum[R]+=a[i]=upd[R]?upd[R]:a[i],
			prd[R]*=a[i]=upd[R]?upd[R]:a[i];
		upd[R]=0;
	}
	else{
		sum[L]=0,
		prd[L]=1;
		for(re int i=(L-1)*sq[n]+1;i<=l-1;++i)
			sum[L]+=a[i]=upd[L]?upd[L]:a[i],
			prd[L]*=a[i]=upd[L]?upd[L]:a[i];
		for(re int i=l;i<=r;++i)
			sum[L]+=a[i]=x,
			prd[L]*=a[i]=x;
		for(re int i=r+1;i<=L*sq[n]&&i<=n;++i)
			sum[L]+=a[i]=upd[L]?upd[L]:a[i],
			prd[L]*=a[i]=upd[L]?upd[L]:a[i];
		upd[L]=0;
	}
}

inline int querySum(re int l,re int r){
	re int L=id[l],R=id[r],res=0;
	if(L<R){
		for(re int i=l;i<=L*sq[n];++i)
			res+=upd[L]?upd[L]:a[i];
		for(re int i=L+1;i<=R-1;++i)
			res+=sum[i];
		for(re int i=(R-1)*sq[n]+1;i<=r;++i)
			res+=upd[R]?upd[R]:a[i];
	}
	else
		for(re int i=l;i<=r;++i)
			res+=upd[L]?upd[L]:a[i];
	return res;
}

inline int queryPrd(re int l,re int r){
	re int L=id[l],R=id[r],res=1;
	if(L<R){
		for(re int i=l;i<=L*sq[n];++i)
			res*=upd[L]?upd[L]:a[i];
		for(re int i=L+1;i<=R-1;++i)
			res*=prd[i];
		for(re int i=(R-1)*sq[n]+1;i<=r;++i)
			res*=upd[R]?upd[R]:a[i];
	}
	else
		for(re int i=l;i<=r;++i)
			res*=upd[L]?upd[L]:a[i];
	return res;
}

void build(re int cur,re int l,re int r){
	for(re int i=l;i<=r;++i)
		ans[cur]+=val[i],
		size[cur]+=len[i];
	for(re int i=l;i<=r;++i)
		len[i]&&(len[i]<=sq[size[cur]]?(++cnt[cur][len[i]]):(vec[cur][++vec[cur][0]]=len[i]));
	if(vec[cur][0]>maxn/maxs){puts("FAQ!!!");exit(0);}
	if(l<r){
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
	}
}

inline void pushDown(re int cur,re int l,re int r){
	re int mid=(l+r)>>1;
	if(tag[cur]){
		if(size[cur<<1]&&!(l<mid&&tag[cur<<1]&&!c[cur<<1])){
			ans[cur<<1]=0;
			if(c[cur]){
				if(size[cur<<1]<=mid-l+1){
					getPow(c[cur],size[cur<<1]);
					for(re int i=1;i<=sq[size[cur<<1]];++i)
						ans[cur<<1]+=cnt[cur<<1][i]*p[0][i];
					for(re int i=1;i<=vec[cur<<1][0];++i)
						ans[cur<<1]+=p[1][vec[cur<<1][i]/sq[size[cur<<1]]]*p[0][vec[cur<<1][i]%sq[size[cur<<1]]];
				}
				else{
					getPow(c[cur],size[cur<<1|1]);
					re int tmp=0;
					for(re int i=1;i<=sq[size[cur<<1|1]];++i)
						tmp+=cnt[cur<<1|1][i]*p[0][i];
					for(re int i=1;i<=vec[cur<<1|1][0];++i)
						tmp+=p[1][vec[cur<<1|1][i]/sq[size[cur<<1|1]]]*p[0][vec[cur<<1|1][i]%sq[size[cur<<1|1]]];
					ans[cur<<1]=ans[cur]-tmp;
				}
			}
			else{
				for(re int i=1;i<=sq[size[cur<<1]];++i)
					cnt[cur<<1][i]=0;
				size[cur<<1]=0,
				vec[cur<<1][0]=0,
				brk[cur<<1]=0;
			}
			tag[cur<<1]=tag[cur],
			c[cur<<1]=c[cur];
		}
		if(size[cur<<1|1]&&!(mid+1<r&&tag[cur<<1|1]&&!c[cur<<1|1])){
			ans[cur<<1|1]=0;
			if(c[cur]){
				if(size[cur<<1|1]<=r-mid){
					getPow(c[cur],size[cur<<1|1]);
					for(re int i=1;i<=sq[size[cur<<1|1]];++i)
						ans[cur<<1|1]+=cnt[cur<<1|1][i]*p[0][i];
					for(re int i=1;i<=vec[cur<<1|1][0];++i)
						ans[cur<<1|1]+=p[1][vec[cur<<1|1][i]/sq[size[cur<<1|1]]]*p[0][vec[cur<<1|1][i]%sq[size[cur<<1|1]]];
				}
				else{
					getPow(c[cur],size[cur<<1]);
					re int tmp=0;
					for(re int i=1;i<=sq[size[cur<<1]];++i)
						tmp+=cnt[cur<<1][i]*p[0][i];
					for(re int i=1;i<=vec[cur<<1][0];++i)
						tmp+=p[1][vec[cur<<1][i]/sq[size[cur<<1]]]*p[0][vec[cur<<1][i]%sq[size[cur<<1]]];
					ans[cur<<1|1]=ans[cur]-tmp;
				}
			}
			else{
				for(re int i=1;i<=sq[size[cur<<1|1]];++i)
					cnt[cur<<1|1][i]=0;
				size[cur<<1|1]=0,
				vec[cur<<1|1][0]=0,
				brk[cur<<1|1]=0;
			}
			tag[cur<<1|1]=tag[cur],
			c[cur<<1|1]=c[cur];
		}
		tag[cur]=c[cur]=0;
	}
	if(brk[cur]){
		ans[cur<<1]=querySum(l,mid),
		size[cur<<1]=cnt[cur<<1][1]=mid-l+1;
		for(re int i=2;i<=sq[size[cur<<1]];++i)
			cnt[cur<<1][i]=0;
		vec[cur<<1][0]=0,
		ans[cur<<1|1]=querySum(mid+1,r),
		size[cur<<1|1]=cnt[cur<<1|1][1]=r-mid;
		for(re int i=2;i<=sq[size[cur<<1|1]];++i)
			cnt[cur<<1|1][i]=0;
		vec[cur<<1|1][0]=0,
		tag[cur<<1]=tag[cur<<1|1]=0,
		c[cur<<1]=c[cur<<1|1]=0,
		brk[cur<<1]=brk[cur<<1|1]=brk[cur],
		brk[cur]=0;
	}
	// printf("ans<%d,%d><%d,%d>=%d %d\n",l,mid,mid+1,r,ans[cur<<1],ans[cur<<1|1]);
}

inline void pushUp(re int cur){
	ans[cur]=ans[cur<<1]+ans[cur<<1|1],
	size[cur]=size[cur<<1]+size[cur<<1|1];
	for(re int i=1;i<=sq[size[cur]];++i)
		cnt[cur][i]=0;
	for(re int i=1;i<=sq[size[cur<<1]];++i)
		cnt[cur][i]+=cnt[cur<<1][i];
	for(re int i=1;i<=sq[size[cur<<1|1]];++i)
		cnt[cur][i]+=cnt[cur<<1|1][i];
	vec[cur][0]=0;
	for(re int i=1;i<=vec[cur<<1][0];++i)
		vec[cur<<1][i]<=sq[size[cur]]?(++cnt[cur][vec[cur<<1][i]]):(vec[cur][++vec[cur][0]]=vec[cur<<1][i]);
	for(re int i=1;i<=vec[cur<<1|1][0];++i)
		vec[cur<<1|1][i]<=sq[size[cur]]?(++cnt[cur][vec[cur<<1|1][i]]):(vec[cur][++vec[cur][0]]=vec[cur<<1|1][i]);
}

int findPre(re int L,re int cur,re int l,re int r){
	if(r<=L&&!size[cur])
		return 0;
	if(l==r)
		return l<=L&&size[cur]?l:0;
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L<=mid)
			return findPre(L,cur<<1,l,mid);
		else{
			re int res=findPre(L,cur<<1|1,mid+1,r);
			return res>=1?res:findPre(L,cur<<1,l,mid);
		}
	}
}

int findSuc(re int L,re int cur,re int l,re int r){
	if(l>=L&&!size[cur])
		return n+1;
	if(l==r)
		return l>=L&&size[cur]?l:n+1;
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L>mid)
			return findSuc(L,cur<<1|1,mid+1,r);
		else{
			re int res=findSuc(L,cur<<1,l,mid);
			return res<=n?res:findSuc(L,cur<<1|1,mid+1,r);
		}
	}
}

void updateTag(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		if(size[cur]&&!(l<r&&tag[cur]&&!c[cur])){
			ans[cur]=0;
			if(x){
				getPow(x,size[cur]);
				for(re int i=1;i<=sq[size[cur]];++i)
					ans[cur]+=cnt[cur][i]*p[0][i];
				for(re int i=1;i<=vec[cur][0];++i)
					ans[cur]+=p[1][vec[cur][i]/sq[size[cur]]]*p[0][vec[cur][i]%sq[size[cur]]];
			}
			else{
				for(re int i=1;i<=sq[size[cur]];++i)
					cnt[cur][i]=0;
				size[cur]=0,
				vec[cur][0]=0,
				brk[cur]=0;
			}
			tag[cur]=1,
			c[cur]=x;
		}
		// printf("ANS[%d,%d] UPDATED TO %u\n",l,r,ans[cur]);
	}
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L<=mid)
			updateTag(L,R,x,cur<<1,l,mid);
		if(R>mid)
			updateTag(L,R,x,cur<<1|1,mid+1,r);
		pushUp(cur);
		// printf("ANS(%d,%d) UPDATED TO %u\n",l,r,ans[cur]);
	}
}

void updateSingle(re int L,re int p,re int cur,re int l,re int r){
	if(l==r)
		p&&(
			size[cur]<=sq[size[cur]]?(cnt[cur][size[cur]]=0):(vec[cur][0]=0),
			size[cur]=p,
			size[cur]<=sq[size[cur]]?(++cnt[cur][size[cur]]):(vec[cur][++vec[cur][0]]=size[cur])
		),
		ans[cur]=queryPrd(l,l+size[cur]-1);
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L<=mid)
			updateSingle(L,p,cur<<1,l,mid);
		else
			updateSingle(L,p,cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

void updateBrk(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		ans[cur]=querySum(l,r),
		size[cur]=cnt[cur][1]=r-l+1;
		for(re int i=2;i<=sq[size[cur]];++i)
			cnt[cur][i]=0;
		vec[cur][0]=0,
		tag[cur]=c[cur]=0,
		brk[cur]=1;
		// printf("ANS[%d,%d]=%u\n",l,r,ans[cur]);
	}
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L<=mid)
			updateBrk(L,R,cur<<1,l,mid);
		if(R>mid)
			updateBrk(L,R,cur<<1|1,mid+1,r);
		pushUp(cur);
		// printf("ANS(%d,%d)=%u\n",l,r,ans[cur]);
	}
}

int getAns(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return ans[cur];
	else{
		re int mid=(l+r)>>1,res=0;
		pushDown(cur,l,r);
		if(L<=mid)
			res+=getAns(L,R,cur<<1,l,mid);
		if(R>mid)
			res+=getAns(L,R,cur<<1|1,mid+1,r);
		return res;
	}
}

void FAQ(re int cur,re int l,re int r){
	if(!tag[cur]&&!brk[cur]&&l<r){
		re int mid=(l+r)>>1;
		FAQ(cur<<1,l,mid);
		FAQ(cur<<1|1,mid+1,r);
	}
	printf("(%d,%d)=(%d,%d,%d,%d,%d)\n",l,r,ans[cur],size[cur],tag[cur],c[cur],brk[cur]);
}

int main(){
	freopen("data1.in","r",stdin);
	freopen("data1.out","w",stdout);
	cltstream::read(n),
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	val[1]=a[1],
	len[1]=1;
	for(re int i=2,j=1;i<=n;++i){
		int x;
		cltstream::read(x),
		x?(val[j]*=a[i]):(val[j=i]=a[i]),
		++len[j];
	}
	// for(re int i=1;i<=n;++i)
	// 	printf("%d%c",len[i],i<n?32:10);
	// re int K=0,N=1;
	// for(;N<n;++K,N<<=1);
	// n=N;
	for(re int i=0;i<=2*n;++i)
		sq[i]=max((int)(sqrt(i)),1);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq[n]+1;
	for(re int i=1;i<=id[n];++i){
		sum[i]=0,
		prd[i]=1;
		for(re int j=(i-1)*sq[n]+1;j<=i*sq[n]&&j<=n;++j)
			sum[i]+=a[j],
			prd[i]*=a[j];
	}
	// N<<=1;
	// for(re int i=0;i<=K;++i)
	// 	for(re int j=n;j>=1;--j)
	// 		(n-j)%(1<<i)||(--N),
	// 		ans[N]+=val[j],
	// 		size[N]=max(size[N],len[j]),
	// 		len[j]&&(len[j]<=sq[1<<i]?(++cnt[N][len[j]]):(vec[N][++vec[N][0]]=len[j]));
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x,L,R,res=0;
		cltstream::read(opt),
		cltstream::read(l),
		cltstream::read(r);
		if(opt==1)
			cltstream::read(x),
			// printf("Operation #%d: %d %d %d %d\n",i,opt,l,r,x),
			modify(l,r,x),
			L=findPre(l,1,1,n),
			// printf("L=%d ",L),
			R=findPre(r,1,1,n),
			// printf("R=%d\n",R),
			updateSingle(L,0,1,1,n),
			R-L>=2&&(updateTag(L+1,R-1,x,1,1,n),0),
			L<R&&(updateSingle(R,0,1,1,n),0);
		if(opt==2){
			cltstream::read(x);
			// printf("Operation #%d: %d %d %d %d\n",i,opt,l,r,x);
			if(x)
				L=findPre(l,1,1,n),
				R=findSuc(r+2,1,1,n),
				// printf("L=%d R=%d\n",L,R),
				updateSingle(L,R-L,1,1,n),
				R-L>=2&&(updateTag(L+1,R-1,0,1,1,n),0);
			else
				L=findPre(l,1,1,n),
				R=findSuc(r+1,1,1,n),
				// printf("L=%d R=%d\n",L,R),
				updateSingle(L,l-L+1,1,1,n),
				updateBrk(l+1,r,1,1,n),
				R-r>=2&&(updateSingle(r+1,R-r-1,1,1,n),0);
		}
		if(opt==3){
			L=findSuc(l,1,1,n),
			R=findPre(r,1,1,n);
			// printf("Operation #%d: %d %d %d\n",i,opt,l,r);
			// printf("L=%d R=%d\n",L,R);
			if(L>R)
				cltstream::write<unsigned>(queryPrd(l,r),10);
			else
				L<=n&&l<L&&(res+=queryPrd(l,L-1)),
				// printf("RES=%u\n",res),
				L<=n&&L<R&&(res+=getAns(L,R-1,1,1,n)),
				// printf("RES=%u\n",res),
				res+=queryPrd(R,r),
				// printf("RES=%u\n",res),
				cltstream::write<unsigned>(res,10);
		}
		// for(re int j=1;j<=n;++j)
		// 	printf("%u%c",querySum(j,j),j<n?32:10);
		// FAQ(1,1,n);
		// for(re int j=1;j<=n;++j)
		// 	printf("%u%c",getAns(j,j,1,1,n),j<n?32:10);
	}
	clop();
	return 0;
}
