#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define re register
#define maxn 100000
#define maxs 320
#define sum(a) (1LL*(a)*((a)+1)/2)

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

int n,m,sq,rc;
int id[maxn+1],a[maxn+1],p[maxn+1],bit[maxn+1];
long long sum[maxn+1];
int cnt[maxn+1],tag[maxs+1];
struct Q{
	int t,l,r;
	long long ans;
};
Q q[maxn+1];
struct R{
	int t,tp,l,r,k;
	long long ans;
};
R r[4*maxn+1];

inline void update1(re int x){
	for(;x<=n;x+=x&(-x))
		++bit[x];
}

inline int getsum(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit[x];
	return res;
}

inline void update2(re int x){
	for(re int i=x;i<=id[x]*sq&&i<=p[0];++i)
		++cnt[i];
	for(re int i=id[x]+1;i<=id[p[0]];++i)
		++tag[i];
}

inline int getval(re int x){
	return cnt[x]+tag[id[x]];
}

inline bool cmp1(const Q& p1,const Q& p2){
	return id[p1.l]==id[p2.l]?(id[p1.l]&1)?p1.r<p2.r:p1.r>p2.r:p1.l<p2.l;
}

inline bool cmp2(const R& p1,const R& p2){
	return p1.tp<p2.tp;
}

inline bool cmp3(const R& p1,const R& p2){
	return p1.t<p2.t;
}

int main(){
	cltstream::read(n),
	cltstream::read(m),
	sq=n/sqrt(m);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq+1,
		cltstream::read(a[i]),
		p[++p[0]]=a[i];
	std::sort(p+1,p+p[0]+1),
	p[0]=std::unique(p+1,p+p[0]+1)-p-1;
	for(re int i=1;i<=n;++i)
		a[i]=std::lower_bound(p+1,p+p[0]+1,a[i])-p,
		sum[i]=sum[i-1]+getsum(a[i]-1),
		update1(a[i]);
	for(re int i=1;i<=m;++i)
		q[i].t=i,
		cltstream::read(q[i].l),
		cltstream::read(q[i].r);
	std::sort(q+1,q+m+1,cmp1);
	for(re int i=1;i<=m;++i){
		if(q[i-1].r<q[i].r)
			r[++rc]=R{i,0,q[i-1].r+1,q[i].r,-1,sum(q[i].r)-sum(q[i-1].r)},
			r[++rc]=R{i,q[i-1].l,q[i-1].r+1,q[i].r,1,sum(q[i-1].r)-sum(q[i].r)};
		if(q[i-1].r>q[i].r)
			r[++rc]=R{i,0,q[i].r+1,q[i-1].r,1,sum(q[i].r)-sum(q[i-1].r)},
			r[++rc]=R{i,q[i-1].l,q[i].r+1,q[i-1].r,-1,sum(q[i-1].r)-sum(q[i].r)};
		if(q[i-1].l>q[i].l)
			r[++rc]=R{i,0,q[i].l,q[i-1].l-1,-1,0},
			r[++rc]=R{i,q[i].r,q[i].l,q[i-1].l-1,1,0};
		if(q[i-1].l<q[i].l)
			r[++rc]=R{i,0,q[i-1].l,q[i].l-1,1,0},
			r[++rc]=R{i,q[i].r,q[i-1].l,q[i].l-1,-1,0};
	}
	std::sort(r+1,r+rc+1,cmp2);
	for(re int i=1;i<=rc;++i)
		if(!r[i].tp)
			r[i].ans+=r[i].k*(sum[r[i].r]-sum[r[i].l-1]);
		else{
			if(r[i].tp>r[i-1].tp)
				update2(a[r[i].tp]);
			for(re int j=r[i].l;j<=r[i].r;++j)
				r[i].ans+=r[i].k*getval(j);
		}
	std::sort(r+1,r+rc+1,cmp3);
	for(re int i=1;i<=rc;++i)
		printf("%d %d %d %d %lld\n",r[i].tp,r[i].l,r[i].r,r[i].k,r[i].ans);
}
