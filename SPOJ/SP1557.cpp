#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000

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
int a[maxn+1],lst[(maxn<<1)+1],nxt[maxn+1];
long long max[(maxn<<2)+1],add[(maxn<<2)+1];
struct Query{
	int id,ql,qr;
};
Query q[maxn+1];
long long ans[maxn+1];

inline bool operator<(re Query p1,re Query p2){
	return p1.ql<p2.ql;
}

inline void pushDown(re int cur){
	max[cur<<1]+=add[cur];
	add[cur<<1]+=add[cur];
	max[cur<<1|1]+=add[cur];
	add[cur<<1|1]+=add[cur];
	add[cur]=0;
}

void update(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		max[cur]+=x;
		add[cur]+=x;
	}
	else{
		pushDown(cur);
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,R,x,cur<<1,l,mid);
		if(R>mid)
			update(L,R,x,cur<<1|1,mid+1,r);
		max[cur]=std::max(max[cur<<1],max[cur<<1|1]);
	}
}

long long getmax(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return max[cur];
	else{
		pushDown(cur);
		re int mid=(l+r)>>1;
		long long res=-9e18;
		if(L<=mid)
			res=std::max(res,getmax(L,R,cur<<1,l,mid));
		if(R>mid)
			res=std::max(res,getmax(L,R,cur<<1|1,mid+1,r));
		return res;
	}
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		if(!lst[a[i]+maxn])
			update(i,n,a[i],1,1,n);
		else
			nxt[lst[a[i]+maxn]]=i;
		lst[a[i]+maxn]=i;
		nxt[i]=n+1;
	}
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		q[i].id=i;
		cltstream::read(q[i].ql);
		cltstream::read(q[i].qr);
	}
	std::sort(q+1,q+m+1);
	for(re int i=1,l=1;i<=m;++i){
		for(;l<q[i].ql;update(l,nxt[l]-1,-a[l],1,1,n),++l);
		ans[q[i].id]=std::max(getmax(q[i].ql,q[i].qr,1,1,n),0LL);
	}
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
