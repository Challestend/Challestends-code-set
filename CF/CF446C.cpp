#include<cstdio>
#define re register
#define maxn 300000
#define mod 1000000009

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
int F[maxn+1],G[maxn+1],sum[4*maxn+1],tag[4*maxn+1][2];

void build(re int cur,re int l,re int r){
	if(l==r)
		cltstream::read(sum[cur]);
	else{
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		sum[cur]=(sum[cur<<1]+sum[cur<<1|1])%mod;
	}
}

inline void pushDown(re int cur,re int ln,re int rn){
	sum[cur<<1]=(sum[cur<<1]+1LL*tag[cur][0]*G[ln]%mod+1LL*tag[cur][1]*G[ln-1]%mod)%mod;
	tag[cur<<1][0]=(tag[cur<<1][0]+tag[cur][0])%mod;
	tag[cur<<1][1]=(tag[cur<<1][1]+tag[cur][1])%mod;
	re int tmp=(tag[cur][0]+tag[cur][1])%mod;
	tag[cur][1]=(1LL*tag[cur][0]*F[ln]%mod+1LL*tag[cur][1]*F[ln-1]%mod)%mod;
	tag[cur][0]=(1LL*tmp*F[ln]%mod+1LL*tag[cur][0]*F[ln-1]%mod)%mod;
	sum[cur<<1|1]=(sum[cur<<1|1]+1LL*tag[cur][0]*G[rn]%mod+1LL*tag[cur][1]*G[rn-1]%mod)%mod;
	tag[cur<<1|1][0]=(tag[cur<<1|1][0]+tag[cur][0])%mod;
	tag[cur<<1|1][1]=(tag[cur<<1|1][1]+tag[cur][1])%mod;
	tag[cur][0]=tag[cur][1]=0;
}

void update(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		sum[cur]=(sum[cur]+1LL*F[l-L+1]*G[r-l+1]%mod+1LL*F[l-L]*G[r-l]%mod)%mod;
		tag[cur][0]=(tag[cur][0]+F[l-L+1])%mod;
		tag[cur][1]=(tag[cur][1]+F[l-L])%mod;
	}
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			update(L,R,cur<<1,l,mid);
		if(R>mid)
			update(L,R,cur<<1|1,mid+1,r);
		sum[cur]=(sum[cur<<1]+sum[cur<<1|1])%mod;
	}
}

int query(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return sum[cur];
	else{
		re int mid=(l+r)>>1,res=0;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			res=(res+query(L,R,cur<<1,l,mid))%mod;
		if(R>mid)
			res=(res+query(L,R,cur<<1|1,mid+1,r))%mod;
		return res;
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	build(1,1,n);
	F[1]=G[1]=1;
	for(re int i=2;i<=n;++i){
		F[i]=(F[i-1]+F[i-2])%mod;
		G[i]=(G[i-1]+F[i])%mod;
	}
	for(re int i=1;i<=m;++i){
		int opt,l,r;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1)
			update(l,r,1,1,n);
		else
			cltstream::write(query(l,r,1,1,n),10);
	}
	clop();
	return 0;
}
