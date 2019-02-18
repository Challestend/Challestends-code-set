#include<cstdio>
#define re register
#define maxn 50000
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

int n,m;
int base[(maxn<<2)+1][31],cnt[(maxn<<2)+1];

inline void insert(re int cur,re int x){
	if(x)
		for(re int i=30;i>=0;--i)
			if(x>>i&1){
				if(!base[cur][i]){
					base[cur][i]=x;
					++cnt[cur];
					break;
				}
				else
					x^=base[cur][i];
			}
}

inline void merge(re int cur){
	for(re int j=30;j>=0;--j)
		insert(0,base[cur][j]);
}

void modify(re int L,re int x,re int cur,re int l,re int r){
	insert(cur,x);
	if(l<r){
		re int mid=(l+r)>>1;
		if(L<=mid)
			modify(L,x,cur<<1,l,mid);
		else
			modify(L,x,cur<<1|1,mid+1,r);
	}
}

void query(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		merge(cur);
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
	for(re int i=1;i<=m;++i){
		int opt,x,y;
		cltstream::read(opt);
		cltstream::read(x);
		cltstream::read(y);
		if(opt==1)
			modify(x,y,1,1,n);
		else{
			for(re int j=30;j>=0;--j)
				base[0][j]=0;
			query(x,y,1,1,n);
			re int ans=0;
			for(re int j=30;j>=0;--j)
				ans=max(ans,ans^base[0][j]);
			cltstream::write(ans,10);
		}
	}
	clop();
	return 0;
}
