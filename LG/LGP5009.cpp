#include<cstdio>
#define re register
#define maxn 200005
#define maxm 200005
#define mod 100000007

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
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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
int sumv[(maxn<<2)+1],suma[(maxn<<2)+1],sumb[(maxn<<2)+1],sump[(maxn<<2)+1];
int A[(maxn<<2)+1],B[(maxn<<2)+1];
int addv[(maxn<<2)+1],adda[(maxn<<2)+1],addb[(maxn<<2)+1];

inline void pushDown(int cur,int ln,int rn){
	sumv[cur<<1]=(sumv[cur<<1]+1LL*A[cur]*suma[cur<<1]%mod)%mod;
	sumv[cur<<1]=(sumv[cur<<1]+1LL*B[cur]*sumb[cur<<1]%mod)%mod;
	sumv[cur<<1]=(sumv[cur<<1]+1LL*ln*addv[cur]%mod)%mod;
	sump[cur<<1]=(sump[cur<<1]+1LL*adda[cur]*sumb[cur<<1]%mod)%mod;
	sump[cur<<1]=(sump[cur<<1]+1LL*addb[cur]*suma[cur<<1]%mod)%mod;
	sump[cur<<1]=(sump[cur<<1]+1LL*adda[cur]*addb[cur]%mod*ln%mod)%mod;
	suma[cur<<1]=(suma[cur<<1]+1LL*ln*adda[cur]%mod)%mod;
	sumb[cur<<1]=(sumb[cur<<1]+1LL*ln*addb[cur]%mod)%mod;
	A[cur<<1]=(A[cur<<1]+A[cur])%mod;
	B[cur<<1]=(B[cur<<1]+B[cur])%mod;
	addv[cur<<1]=(addv[cur<<1]+addv[cur])%mod;
	adda[cur<<1]=(adda[cur<<1]+adda[cur])%mod;
	addb[cur<<1]=(addb[cur<<1]+addb[cur])%mod;
	sumv[cur<<1|1]=(sumv[cur<<1|1]+1LL*A[cur]*suma[cur<<1|1]%mod)%mod;
	sumv[cur<<1|1]=(sumv[cur<<1|1]+1LL*B[cur]*sumb[cur<<1|1]%mod)%mod;
	sumv[cur<<1|1]=(sumv[cur<<1|1]+1LL*rn*addv[cur]%mod)%mod;
	sump[cur<<1|1]=(sump[cur<<1|1]+1LL*adda[cur]*sumb[cur<<1|1]%mod)%mod;
	sump[cur<<1|1]=(sump[cur<<1|1]+1LL*addb[cur]*suma[cur<<1|1]%mod)%mod;
	sump[cur<<1|1]=(sump[cur<<1|1]+1LL*adda[cur]*addb[cur]%mod*rn%mod)%mod;
	suma[cur<<1|1]=(suma[cur<<1|1]+1LL*rn*adda[cur]%mod)%mod;
	sumb[cur<<1|1]=(sumb[cur<<1|1]+1LL*rn*addb[cur]%mod)%mod;
	A[cur<<1|1]=(A[cur<<1|1]+A[cur])%mod;
	B[cur<<1|1]=(B[cur<<1|1]+B[cur])%mod;
	addv[cur<<1|1]=(addv[cur<<1|1]+addv[cur])%mod;
	adda[cur<<1|1]=(adda[cur<<1|1]+adda[cur])%mod;
	addb[cur<<1|1]=(addb[cur<<1|1]+addb[cur])%mod;
	A[cur]=B[cur]=addv[cur]=adda[cur]=addb[cur]=0;
}

inline void pushUp(int cur){
	sumv[cur]=(sumv[cur<<1]+sumv[cur<<1|1])%mod;
	suma[cur]=(suma[cur<<1]+suma[cur<<1|1])%mod;
	sumb[cur]=(sumb[cur<<1]+sumb[cur<<1|1])%mod;
	sump[cur]=(sump[cur<<1]+sump[cur<<1|1])%mod;
}

void build(int cur,int l,int r){
	if(l==r){
		cltstream::read(sumv[cur]);
		cltstream::read(suma[cur]);
		cltstream::read(sumb[cur]);
		sumv[cur]=(sumv[cur]%mod+mod)%mod;
		suma[cur]=(suma[cur]%mod+mod)%mod;
		sumb[cur]=(sumb[cur]%mod+mod)%mod;
		sump[cur]=1LL*suma[cur]*sumb[cur]%mod;
	}
	else{
		int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

int query(int L,int R,int t,int cur,int l,int r){
	if(l>=L&&r<=R)
		return (sumv[cur]+1LL*t*sump[cur]%mod)%mod;
	else{
		int mid=(l+r)>>1,res=0;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			res=(res+query(L,R,t,cur<<1,l,mid))%mod;
		if(R>mid)
			res=(res+query(L,R,t,cur<<1|1,mid+1,r))%mod;
		return res;
	}
}

void modifyV(int L,int R,int x,int cur,int l,int r){
	if(l>=L&&r<=R){
		sumv[cur]=(sumv[cur]+1LL*(r-l+1)*x%mod)%mod;
		addv[cur]=(addv[cur]+x)%mod;
	}
	else{
		int mid=(l+r)>>1;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			modifyV(L,R,x,cur<<1,l,mid);
		if(R>mid)
			modifyV(L,R,x,cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

void modifyA(int L,int R,int t,int x,int cur,int l,int r){
	if(l>=L&&r<=R){
		sumv[cur]=(sumv[cur]+(-1LL*x*t%mod*sumb[cur]%mod+mod)%mod)%mod;
		suma[cur]=(suma[cur]+1LL*(r-l+1)*x%mod)%mod;
		sump[cur]=(sump[cur]+1LL*sumb[cur]*x%mod)%mod;
		B[cur]=(B[cur]+(-1LL*x*t%mod+mod)%mod)%mod;
		addv[cur]=(addv[cur]+(-1LL*x*t%mod*addb[cur]%mod+mod)%mod)%mod;
		adda[cur]=(adda[cur]+x)%mod;
	}
	else{
		int mid=(l+r)>>1;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			modifyA(L,R,t,x,cur<<1,l,mid);
		if(R>mid)
			modifyA(L,R,t,x,cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

void modifyB(int L,int R,int t,int x,int cur,int l,int r){
	if(l>=L&&r<=R){
		sumv[cur]=(sumv[cur]+(-1LL*x*t%mod*suma[cur]%mod+mod)%mod)%mod;
		sumb[cur]=(sumb[cur]+1LL*(r-l+1)*x%mod)%mod;
		sump[cur]=(sump[cur]+1LL*suma[cur]*x%mod)%mod;
		A[cur]=(A[cur]+(-1LL*x*t%mod+mod)%mod)%mod;
		addv[cur]=(addv[cur]+(-1LL*x*t%mod*adda[cur]%mod+mod)%mod)%mod;
		addb[cur]=(addb[cur]+x)%mod;
	}
	else{
		int mid=(l+r)>>1;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			modifyB(L,R,t,x,cur<<1,l,mid);
		if(R>mid)
			modifyB(L,R,t,x,cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		int opt,t,l,r,x;
		cltstream::read(opt);
		cltstream::read(t);
		cltstream::read(l);
		cltstream::read(r);
		switch(opt){
			case 1:
				cltstream::write(query(l,r,t,1,1,n),10);
				break;
			case 2:
				cltstream::read(x);
				modifyA(l,r,t,(x%mod+mod)%mod,1,1,n);
				break;
			case 3:
				cltstream::read(x);
				modifyB(l,r,t,(x%mod+mod)%mod,1,1,n);
				break;
			case 4:
				cltstream::read(x);
				modifyV(l,r,(x%mod+mod)%mod,1,1,n);
				break;
		}
	}
	clop();
	return 0;
}
