#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#define re register
#define maxn 500000
#define maxs1 710
#define maxval 100000
#define maxs2 320
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

int n,m,ec,sq1,sq2;
int id1[maxn+1],id2[maxval+1],a[maxn+1];
int bit0[maxn+1];
long long bit1[maxn+1],tmp[maxn+1];
int sum0[maxval+1],pre0[maxval+1];
long long sum1[maxval+1],pre1[maxval+1];
long long ans[maxn+1];
struct query{
	int t,l,r;
};
query q[maxn+1];
struct querz{
	int t,l,r,w;
};
std::vector<querz> v[maxn+1];

inline bool operator<(const query& A,const query& B){
	return id1[A.l]==id1[B.l]?(id1[A.l]&1)?A.r<B.r:A.r>B.r:A.l<B.l;
}

inline void update(re int x){
	for(re int i=x;i<=a[0];i+=i&(-i))
		++bit0[i],
		bit1[i]+=x;
}

inline int getCnt(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit0[x];
	return res;
}

inline long long getSum(re int x){
	re long long res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit1[x];
	return res;
}

inline void modify(re int x){
	re int X=id2[x];
	for(re int i=x;i<=X*sq2&&i<=n;++i)
		++pre0[i],
		pre1[i]+=x;
	for(re int i=X;i<=id2[n];++i)
		++sum0[i],
		sum1[i]+=x;
}

inline int queryCnt(re int x){
	return sum0[id2[x]-1]+pre0[x];
}

inline long long querySum(re int x){
	return sum1[id2[x]-1]+pre1[x];
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq1=n/sqrt(m);
	for(re int i=1;i<=n;++i)
		id1[i]=(i-1)/sq1+1,
		cltstream::read(a[i]),
		a[0]=max(a[0],a[i]);
	sq2=sqrt(a[0]);
	for(re int i=1;i<=a[0];++i)
		id2[i]=(i-1)/sq2+1;
	for(re int i=1;i<=n;++i)
		update(a[i]),
		tmp[i]=1LL*getCnt(a[i]-1)*a[i]+getSum(a[0])-getSum(a[i]);
	for(re int i=1;i<=m;++i)
		q[i].t=i,
		cltstream::read(q[i].l),
		cltstream::read(q[i].r);
	std::sort(q+1,q+m+1);
	for(re int i=1,L=1,R=0;i<=m;++i){
		if(R<q[i].r)v[L-1].push_back({q[i].t,R+1,q[i].r,-1});
		for(;R<q[i].r;++R,ans[q[i].t]+=tmp[R]+a[R]);

		if(R>q[i].r)v[L-1].push_back({q[i].t,q[i].r+1,R,1});
		for(;R>q[i].r;ans[q[i].t]-=tmp[R]+a[R],--R);

		if(L>q[i].l)v[R].push_back({q[i].t,q[i].l,L-1,1});
		for(;L>q[i].l;--L,ans[q[i].t]-=tmp[L]-a[L]);

		if(L<q[i].l)v[R].push_back({q[i].t,L,q[i].l-1,-1});
		for(;L<q[i].l;ans[q[i].t]+=tmp[L]-a[L],++L);
	}
	for(re int i=1;i<=n;++i){
		modify(a[i]);
		for(std::vector<querz>::iterator p=v[i].begin();p!=v[i].end();++p){
			re long long res=0;
			for(re int j=p->l;j<=p->r;++j){
				res+=1LL*queryCnt(a[j]-1)*a[j]+querySum(a[0])-querySum(a[j]);
			}
			ans[p->t]+=p->w*res;
		}
	}
	for(re int i=1;i<=m;++i)
		ans[q[i].t]+=ans[q[i-1].t];
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
