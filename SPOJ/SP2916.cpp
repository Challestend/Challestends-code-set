#include<cstdio>
#define re register
#define maxn 10000

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

int t,n,m;
int a[maxn+1],ls[(maxn<<2)+1],rs[(maxn<<2)+1],ms[(maxn<<2)+1],sum[(maxn<<2)+1];

inline int max(re int p1,re int p2){
	return p1>=p2?p1:p2;
}
inline int min(re int p1,re int p2){
	return p1<=p2?p1:p2;
}

inline void pushUp(re int cur){
	ms[cur]=max(max(ms[cur<<1],ms[cur<<1|1]),rs[cur<<1]+ls[cur<<1|1]);
	ls[cur]=max(ls[cur<<1],sum[cur<<1]+ls[cur<<1|1]);
	rs[cur]=max(rs[cur<<1|1],sum[cur<<1|1]+rs[cur<<1]);
	sum[cur]=sum[cur<<1]+sum[cur<<1|1];
}

void build(re int cur,re int l,re int r){
	if(l==r){
		cltstream::read(a[l]);
		ls[cur]=rs[cur]=ms[cur]=sum[cur]=a[l];
	}
	else{
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

int getLeftSum(re int L,re int R,re int cur,re int l,re int r){
	if(L>R)
		return -1e9;
	if(l>=L&&r<=R)
		return ls[cur];
	else{
		re int mid=(l+r)>>1;
		if(L<=mid){
			if(R>mid)
				return max(getLeftSum(L,R,cur<<1,l,mid),getLeftSum(L,R,cur<<1|1,mid+1,r)+a[mid]-a[max(l-1,L-1)]);
			else
				return getLeftSum(L,R,cur<<1,l,mid);
		}
		else{
			if(R>mid)
				return getLeftSum(L,R,cur<<1|1,mid+1,r);
			else
				return -1e9;
		}
	}
}

int getRightSum(re int L,re int R,re int cur,re int l,re int r){
	if(L>R)
		return -1e9;
	if(l>=L&&r<=R)
		return rs[cur];
	else{
		re int mid=(l+r)>>1;
		if(L<=mid){
			if(R>mid)
				return max(getRightSum(L,R,cur<<1,l,mid)+a[min(r,R)]-a[mid],getRightSum(L,R,cur<<1|1,mid+1,r));
			else
				return getRightSum(L,R,cur<<1,l,mid);
		}
		else{
			if(R>mid)
				return getRightSum(L,R,cur<<1|1,mid+1,r);
			else
				return -1e9;
		}
	}
}

int getMaxSum(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		if(l==L){
			ls[0]=ls[cur];
			rs[0]=rs[cur];
			ms[0]=ms[cur];
			sum[0]=sum[cur];
		}
		else{
			ms[0]=max(max(ms[0],ms[cur]),rs[0]+ls[cur]);
			ls[0]=max(ls[0],sum[0]+ls[cur]);
			rs[0]=max(rs[cur],sum[cur]+rs[0]);
			sum[0]+=sum[cur];
		}
	}
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			getMaxSum(L,R,cur<<1,l,mid);
		if(R>mid)
			getMaxSum(L,R,cur<<1|1,mid+1,r);
	}
	return ms[0];
}

int main(){
	cltstream::read(t);
	for(;t;--t){
		cltstream::read(n);
		build(1,1,n);
		for(re int i=1;i<=n;++i)
			a[i]+=a[i-1];
		cltstream::read(m);
		for(re int i=1;i<=m;++i){
			int x,y,z,w;
			cltstream::read(x);
			cltstream::read(y);
			cltstream::read(z);
			cltstream::read(w);
			if(y<z)
				cltstream::write(getRightSum(x,y,1,1,n)+getLeftSum(z,w,1,1,n)+a[z-1]-a[y],10);
			else
				cltstream::write(
					max(
						max(
							getRightSum(x,z-1,1,1,n)+getLeftSum(z,w,1,1,n),
							getRightSum(z,y,1,1,n)+getLeftSum(y+1,w,1,1,n)
						),
						getMaxSum(z,y,1,1,n)
					),
					10
				);
		}
	}
	clop();
	return 0;
}
