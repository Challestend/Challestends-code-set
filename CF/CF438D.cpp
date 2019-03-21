#include<cstdio>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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
long long sum[(maxn<<2)+1],mx[(maxn<<2)+1];

void build(re int cur,re int l,re int r){
	if(l==r)
		cltstream::read(sum[cur]),
		mx[cur]=sum[cur];
	else{
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
		mx[cur]=max(mx[cur<<1],mx[cur<<1|1]);
	}
}

void modify(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(mx[cur]<x)
		return;
	if(l==r)
		sum[cur]%=x,
		mx[cur]%=x;
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			modify(L,R,x,cur<<1,l,mid);
		if(R>mid)
			modify(L,R,x,cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
		mx[cur]=max(mx[cur<<1],mx[cur<<1|1]);
	}
}

void update(re int L,re int x,re int cur,re int l,re int r){
	if(l==r)
		sum[cur]=mx[cur]=x;
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,x,cur<<1,l,mid);
		else
			update(L,x,cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
		mx[cur]=max(mx[cur<<1],mx[cur<<1|1]);
	}
}

long long getsum(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return sum[cur];
	else{
		re int mid=(l+r)>>1;
		re long long res=0;
		if(L<=mid)
			res+=getsum(L,R,cur<<1,l,mid);
		if(R>mid)
			res+=getsum(L,R,cur<<1|1,mid+1,r);
		return res;
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x;
		cltstream::read(opt);
		if(opt==1){
			cltstream::read(l);
			cltstream::read(r);
			cltstream::write(getsum(l,r,1,1,n),10);
		}
		if(opt==2){
			cltstream::read(l);
			cltstream::read(r);
			cltstream::read(x);
			modify(l,r,x,1,1,n);
		}
		if(opt==3){
			cltstream::read(l);
			cltstream::read(x);
			update(l,x,1,1,n);
		}
	}
	clop();
	return 0;
}
