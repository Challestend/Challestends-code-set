#include<cstdio>
#define re register
#define maxn 100000
#define maxm 30

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

int n,m,q,ans;
long long val[3*maxn+1];

inline void readStr(re int cur){
	for(re int i=1;i<=m;++i){
		re char c=cltstream::gc();
		val[cur]=val[cur]<<2|(c=='0'?2:c=='1'?1:3);
	}
	cltstream::gc();
}

inline void pushUp(re int cur){
	for(re int i=1;i<=m;++i)
		val[cur]=val[cur<<1]&val[cur<<1|1];
}

void build(re int cur,re int l,re int r){
	if(l==r)
		readStr(cur);
	else{
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

void update(re int L,re int cur,re int l,re int r){
	if(l==r)
		readStr(cur);
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,cur<<1,l,mid);
		else
			update(L,cur<<1|1,mid+1,r);
		pushUp(cur);
	}
}

void query(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		for(re int i=1;i<=m;++i)
			val[0]=val[0]&val[cur];
	}
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			query(L,R,cur<<1,l,mid);
		if(R>mid)
			query(L,R,cur<<1|1,mid+1,r);
	}
}

int main(){
	cltstream::read(m);
	cltstream::read(n);
	cltstream::read(q);
	build(1,1,n);
	for(re int i=1;i<=q;++i){
		int opt,l,r;
		cltstream::read(opt);
		cltstream::read(l);
		if(opt==0){
			cltstream::read(r);
			val[0]=~0LL;
			query(l,r,1,1,n);
			re int res=1;
			for(re int j=1;j<=m;++j,val[0]>>=2)
				res*=((val[0]&2)==2)+((val[0]&1)==1);
			ans^=res;
		}
		else
			update(l,1,1,n);
	}
	cltstream::write(ans);
	clop();
	return 0;
}
