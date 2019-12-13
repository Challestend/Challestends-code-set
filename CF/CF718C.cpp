#include<cstdio>
#define re register
#define maxn 1000000
#define mod 1000000007

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
int f[maxn+1];
struct matrix{
	int a[2][2];

	matrix(){
		a[0][0]=a[0][1]=a[1][0]=a[1][1]=0;
	}
};
matrix unit,F,tmp,sum[3*maxn+1],mul[3*maxn+1];

inline matrix operator+(const matrix &A,const matrix &B){
	matrix C;
	C.a[0][0]=(A.a[0][0]+B.a[0][0])%mod;
	C.a[0][1]=(A.a[0][1]+B.a[0][1])%mod;
	C.a[1][0]=(A.a[1][0]+B.a[1][0])%mod;
	C.a[1][1]=(A.a[1][1]+B.a[1][1])%mod;
	return C;
}

inline matrix operator*(const matrix &A,const matrix &B){
	matrix C;
	C.a[0][0]=(1LL*A.a[0][0]*B.a[0][0]%mod+1LL*A.a[0][1]*B.a[1][0]%mod)%mod;
	C.a[0][1]=(1LL*A.a[0][0]*B.a[0][1]%mod+1LL*A.a[0][1]*B.a[1][1]%mod)%mod;
	C.a[1][0]=(1LL*A.a[1][0]*B.a[0][0]%mod+1LL*A.a[1][1]*B.a[1][0]%mod)%mod;
	C.a[1][1]=(1LL*A.a[1][0]*B.a[0][1]%mod+1LL*A.a[1][1]*B.a[1][1]%mod)%mod;
	return C;
}

inline matrix pow(matrix A,re int x){
	matrix res=unit;
	for(;x;x>>=1,A=A*A)
		if(x&1)
			res=A*res;
	return res;
}

void build(re int cur,re int l,re int r){
	if(l==r)
		sum[cur]=pow(F,f[l]);
	else{
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
	}
	mul[cur]=unit;
}

inline void pushDown(re int cur){
	sum[cur<<1]=mul[cur]*sum[cur<<1];
	mul[cur<<1]=mul[cur]*mul[cur<<1];
	sum[cur<<1|1]=mul[cur]*sum[cur<<1|1];
	mul[cur<<1|1]=mul[cur]*mul[cur<<1|1];
	mul[cur]=unit;
}

void modify(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		sum[cur]=tmp*sum[cur];
		mul[cur]=tmp*mul[cur];
	}
	else{
		re int mid=(l+r)>>1;
		pushDown(cur);
		if(L<=mid)
			modify(L,R,cur<<1,l,mid);
		if(R>mid)
			modify(L,R,cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
	}
}

matrix query(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return sum[cur];
	else{
		re int mid=(l+r)>>1;
		matrix res;
		pushDown(cur);
		if(L<=mid)
			res=query(L,R,cur<<1,l,mid)+res;
		if(R>mid)
			res=query(L,R,cur<<1|1,mid+1,r)+res;
		return res;
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(f[i]);
	unit.a[0][0]=unit.a[1][1]=1;
	F.a[0][1]=F.a[1][0]=F.a[1][1]=1;
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1){
			cltstream::read(x);
			tmp=pow(F,x);
			modify(l,r,1,1,n);
		}
		else{
			tmp=query(l,r,1,1,n);
			cltstream::write(tmp.a[0][1],10);
		}
	}
	clop();
	return 0;
}
