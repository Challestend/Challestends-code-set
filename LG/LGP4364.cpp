#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 500000

int n,ec,cnt;
double m;
int des[maxn+1],suc[maxn+1],las[maxn+1];
int a[maxn+1],p[maxn+1],f[maxn+1],size[maxn+1],ans[maxn+1];
int sum[4*maxn+1];

void update(re int L,re int x,re int cur,re int l,re int r){
	if(l==r)
		sum[cur]+=x;
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,x,cur<<1,l,mid);
		else
			update(L,x,cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
	}
}

int query(re int x,re int cur,re int l,re int r){
	if(l==r)
		return l;
	else{
		re int mid=(l+r)>>1;
		// if(sum[cur<<1|1]>=x)
		// 	return query(x,cur<<1|1,mid+1,r);
		// else
		// 	return query(x-sum[cur<<1|1],cur<<1,l,mid);
		if(sum[cur<<1]>=x)
			return query(x,cur<<1,l,mid);
		else
			return query(x-sum[cur<<1],cur<<1|1,mid+1,r);
	}
}

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void solve(re int rt,re int r){
	ans[rt]=query(r-size[rt]-cnt+1,1,1,n);
	// printf("%d %d %d %d %d\n",rt,r-size[rt]+1,r,cnt,p[ans[rt]]);
	// update(ans[rt],-1,1,1,n);
	// ++cnt;
	for(re int i=las[rt],j=r;i;j-=size[des[i]],i=suc[i])
		solve(des[i],j);
	// --cnt;
}

int main(){
	freopen("C:/Users/Administrator/Downloads/data7.in","r",stdin);
	freopen("C:/Users/Administrator/Downloads/data7.clt","w",stdout);
	scanf("%d%lf",&n,&m);
	for(re int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		p[i]=a[i];
		f[i]=i/m;
		size[i]=1;
	}
	std::sort(p+1,p+n+1);
	p[0]=std::unique(p+1,p+n+1)-p-1;
	for(re int i=n;i>=1;--i){
		a[i]=std::lower_bound(p+1,p+p[0]+1,a[i])-p;
		update(a[i],1,1,1,n);
		size[f[i]]+=size[i];
		connect(f[i],i);
	}
	std::sort(a+1,a+n+1);
	for(re int i=las[0],j=n;i;j-=size[des[i]],i=suc[i])
		solve(des[i],j);
	for(re int i=1;i<=n;++i)
		printf("%d ",p[ans[i]]);
	return 0;
}
