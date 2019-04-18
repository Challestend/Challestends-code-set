#include<cstdio>
#include<cmath>
#define re register
#define maxn 100000
#define maxs 320
#define base 2333
#define mod 998244353
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
int sq[maxn+1],id[maxn+1],a[maxn+1],val[maxn+1],len[maxn+1],p[2*maxs+1][2];
int sum[maxs+1],prd[maxs+1],upd[maxs+1];
int ans[4*maxn+1],size[4*maxn+1],cnt[4*maxn+1][maxs+1],vec[4*maxn+1][maxs+1],tag[4*maxn+1];

inline void getPow(re int x,re int N){
	if(!N)
		return;
	p[0][0]=1;
	for(re int i=1;i<=sq[N];++i)
		p[i][0]=1LL*p[i-1][0]*x%mod;
	p[0][1]=1;
	for(re int i=1;i<=N/sq[N];++i)
		p[i][1]=1LL*p[i-1][1]*p[sq[N]][0]%mod;
}

inline void destory(re int x){
	if(upd[x])
		for(re int i=(x-1)*sq[n]+1;i<=x*sq[n]&&i<=n;++i)
			a[i]=upd[x];
	upd[x]=0;
}

inline void rebuild(re int x){
	sum[x]=0;
	prd[x]=1;
	for(re int i=(x-1)*sq[n]+1;i<=x*sq[n]&&i<=n;++i){
		sum[x]=(sum[x]+a[i])%mod;
		prd[x]=1LL*prd[x]*a[i]%mod;
	}
}

inline void modify(re int l,re int r,re int x){
	getPow(x,n);
	re int L=id[l],R=id[r];
	if(L<R){
		destory(L);
		for(re int i=l;i<=L*sq[n];++i)
			a[i]=x;
		rebuild(L);
		for(re int i=L+1;i<=R-1;++i){
			sum[i]=1LL*sq[n]*x%mod;
			prd[i]=p[1][1];
			upd[i]=x;
		}
		destory(R);
		for(re int i=(R-1)*sq[n]+1;i<=r;++i)
			a[i]=x;
		rebuild(R);
	}
	else{
		destory(L);
		for(re int i=l;i<=r;++i)
			a[i]=x;
		rebuild(L);
	}
}

inline int querySum(re int l,re int r){
	re int L=id[l],R=id[r],res=0;
	if(L<R){
		for(re int i=l;i<=L*sq[n];++i)
			res=(res+(upd[L]?upd[L]:a[i]))%mod;
		for(re int i=L+1;i<=R-1;++i)
			res=(res+sum[i])%mod;
		for(re int i=(R-1)*sq[n]+1;i<=r;++i)
			res=(res+(upd[R]?upd[R]:a[i]))%mod;
	}
	else{
		for(re int i=l;i<=r;++i)
			res=(res+(upd[L]?upd[L]:a[i]))%mod;
	}
	return res;
}

inline int queryPrd(re int l,re int r){
	re int L=id[l],R=id[r],res=1;
	if(L<R){
		for(re int i=l;i<=L*sq[n];++i)
			res=1LL*res*(upd[L]?upd[L]:a[i])%mod;
		for(re int i=L+1;i<=R-1;++i)
			res=1LL*res*prd[i]%mod;
		for(re int i=(R-1)*sq[n]+1;i<=r;++i)
			res=1LL*res*(upd[R]?upd[R]:a[i])%mod;
	}
	else{
		for(re int i=l;i<=r;++i)
			res=1LL*res*(upd[L]?upd[L]:a[i])%mod;
	}
	return res;
}

inline void pushDown(re int cur,re int l,re int r){
	re int mid=(l+r)>>1,ln=size[cur<<1],rn=size[cur<<1|1];
	if(tag[cur]){
		if(ln<=mid-l+1){
			getPow(tag[cur],ln);
			ans[cur<<1]=0;
			for(re int i=1;i<=sq[ln];++i)
				ans[cur<<1]=(ans[cur<<1]+1LL*cnt[cur<<1][i]*p[i][0]%mod)%mod;
			for(re int i=1;i<=vec[cur<<1][0];++i){
				re int x=vec[cur<<1][i];
				ans[cur<<1]=(ans[cur<<1]+1LL*p[x/sq[ln]][1]*p[x%sq[ln]][0]%mod)%mod;
			}
			ans[cur<<1|1]=(ans[cur]-ans[cur<<1]+mod)%mod;
		}
		else{
			getPow(tag[cur],rn);
			ans[cur<<1|1]=0;
			for(re int i=1;i<=sq[rn];++i)
				ans[cur<<1|1]=(ans[cur<<1|1]+1LL*cnt[cur<<1|1][i]*p[i][0]%mod)%mod;
			for(re int i=1;i<=vec[cur<<1|1][0];++i){
				re int x=vec[cur<<1|1][i];
				ans[cur<<1|1]=(ans[cur<<1|1]+1LL*p[x/sq[rn]][1]*p[x%sq[rn]][0]%mod)%mod;
			}
			ans[cur<<1]=(ans[cur]-ans[cur<<1|1]+mod)%mod;
		}
		tag[cur<<1]=tag[cur<<1|1]=tag[cur];
	}
	tag[cur]=0;
}

inline void pushUp(re int cur){
	ans[cur]=(ans[cur<<1]+ans[cur<<1|1])%mod;
	size[cur]=size[cur<<1]+size[cur<<1|1];
	for(re int i=1;i<=sq[size[cur]];++i)
		cnt[cur][i]=cnt[cur<<1][i]+cnt[cur<<1|1][i];
	vec[cur][0]=0;
	for(re int i=1;i<=vec[cur<<1][0];++i)
		if(vec[cur<<1][i]<=sq[size[cur]])
			++cnt[cur][vec[cur<<1][i]];
		else
			vec[cur][++vec[cur][0]]=vec[cur<<1][i];
	for(re int i=1;i<=vec[cur<<1|1][0];++i)
		if(vec[cur<<1|1][i]<=sq[size[cur]])
			++cnt[cur][vec[cur<<1|1][i]];
		else
			vec[cur][++vec[cur][0]]=vec[cur<<1|1][i];
}

int findPre(re int L,re int cur,re int l,re int r){
	if(r<=L&&!size[cur])
		return 0;
	if(l==r)
		return size[cur]?l:0;
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
		return size[cur]?l:n+1;
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

void updateNum(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		getPow(x,size[cur]);
		ans[cur]=0;
		for(re int i=1;i<=sq[size[cur]];++i)
			ans[cur]=(ans[cur]+1LL*cnt[cur][i]*p[i][0]%mod)%mod;
		for(re int i=1;i<=vec[cur][0];++i){
			re int x=vec[cur][i];
			ans[cur]=(ans[cur]+1LL*p[x/sq[size[cur]]][1]*p[x%sq[size[cur]]][0]%mod)%mod;
		}
		tag[cur]=x;
		// printf("ANS[%d,%d]=%d\n",l,r,ans[cur]);
	}
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L<=mid)
			updateNum(L,R,x,cur<<1,l,mid);
		if(R>mid)
			updateNum(L,R,x,cur<<1|1,mid+1,r);
		pushUp(cur);
		// printf("ANS(%d,%d)=%d\n",l,r,ans[cur]);
	}
}

void updateSingle(re int L,re int x,re int cur,re int l,re int r){
	if(l==r)
		ans[cur]=queryPrd(l,l+size[cur]-1);
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,l,r);
		if(L<=mid)
			updateSingle(L,x,cur<<1,l,mid);
		else
			updateSingle(L,x,cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

int getAns(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return ans[cur];
	else{
		re int mid=(l+r)>>1,res=0;
		pushDown(cur,l,r);
		if(L<=mid)
			res=(res+getAns(L,R,cur<<1,l,mid))%mod;
		if(R>mid)
			res=(res+getAns(L,R,cur<<1|1,mid+1,r))%mod;
		return res;
	}
}

int main(){
	freopen("data1.in","r",stdin);
	freopen("data1.out","w",stdout);
	cltstream::read(n),
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		sq[i]=max((int)(sqrt(i)),1);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq[n]+1,
		cltstream::read(a[i]);
	for(re int i=1;i<=id[n];++i)
		rebuild(i);
	val[1]=a[1],
	len[1]=1;
	for(re int i=2,j=1;i<=n;++i){
		int x;
		cltstream::read(x),
		x?(val[j]=1LL*val[j]*a[i]%mod):(val[j=i]=a[i]),
		++len[j];
	}
	for(re int i=1;i<=n;++i)
		for(re int cur=1,l=1,r=n;l<=r;){
			ans[cur]=(ans[cur]+val[i])%mod,
			size[cur]+=len[i],
			len[i]&&(len[i]<=sq[r-l+1]?(++cnt[cur][len[i]]):(vec[cur][++vec[cur][0]]=len[i]));
			if(l==r)
				break;
			re int mid=(l+r)>>1;
			if(i<=mid)
				cur=cur<<1,
				r=mid;
			else
				cur=cur<<1|1,
				l=mid+1;
		}
	puts("FAQ");
	// for(re int i=1;i<=m;++i){
	// 	int opt,l,r,x,L,R,res=0;
	// 	cltstream::read(opt),
	// 	cltstream::read(l),
	// 	cltstream::read(r);
	// 	if(opt==1)
	// 		cltstream::read(x),
	// 		modify(l,r,x),
	// 		L=findPre(l,1,1,n),
	// 		R=findPre(r,1,1,n),
	// 		L>=1&&(updateSingle(L,x,1,1,n),0),
	// 		L>=1&&R>=1&&R-L>=2&&(updateNum(L+1,R-1,x,1,1,n),0),
	// 		R>=1&&L<R&&(updateSingle(R,x,1,1,n),0);
	// 	if(opt==3){
	// 		L=findSuc(l,1,1,n),
	// 		R=findPre(r,1,1,n);
	// 		// printf("L=%d R=%d\n",L,R);
	// 		if(L>R)
	// 			cltstream::write(queryPrd(l,r),10);
	// 		else
	// 			L<=n&&l<L&&(res=(res+queryPrd(l,L-1))%mod),
	// 			// printf("RES=%d\n",res),
	// 			L<=n&&R>=1&&L<R&&(res=(res+getAns(L,R-1,1,1,n))%mod),
	// 			// printf("RES=%d\n",res),
	// 			R>=1&&(res=(res+queryPrd(R,r))%mod),
	// 			// printf("RES=%d\n",res),
	// 			cltstream::write<unsigned>(res,10);
	// 	}
	// 	// for(re int j=1;j<=n;++j)
	// 	// 	printf("%d%c",querySum(j,j),j<n?32:10);
	// 	// for(re int j=1;j<=n;++j)
	// 	// 	printf("%d%c",getAns(j,j,1,1,n),j<n?32:10);
	// }
	clop();
	return 0;
}
