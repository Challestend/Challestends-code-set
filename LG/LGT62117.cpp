#include<cstdio>
#define re register
#define maxn 100000
#define maxs 320
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) max(a,-(a))

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

int n,m,sq;
int id[maxn+1],cnt[maxs+1];
long long a[maxn+1],maxneg[maxs+1],ans[maxs+1],tag[maxs+1];

inline void init(re int x){
	for(re int i=(x-1)*sq+1;i<=x*sq&&i<=n;++i)
		a[i]+=tag[x];
	cnt[x]=ans[x]=tag[x]=0;
	maxneg[x]=9e18;
	for(re int i=(x-1)*sq+1;i<=x*sq&&i<=n;++i)
		if(a[i]>=0){
			++cnt[x];
			ans[x]+=a[i];
		}
		else{
			maxneg[x]=min(maxneg[x],-a[i]);
			ans[x]-=a[i];
		}
}

inline void modify(re int l,re int r,re int x){
	for(re int i=l;i<=id[l]*sq&&i<=r;++i)
		a[i]+=x;
	init(id[l]);
	if(id[l]<id[r]){
		for(re int i=(id[r]-1)*sq+1;i<=r;++i)
			a[i]+=x;
		init(id[r]);
	}
	for(re int i=id[l]+1;i<=id[r]-1;++i){
		tag[i]+=x;
		if(maxneg[i]>x){
			maxneg[i]-=x;
			ans[i]+=((cnt[i]<<1)-sq)*x;
		}
		else
			init(i);
	}
}

inline long long query(re int l,re int r){
	re long long res=0;
	for(re int i=l;i<=id[l]*sq&&i<=r;++i)
		res+=abs(a[i]+tag[id[i]]);
	if(id[l]<id[r])
		for(re int i=(id[r]-1)*sq+1;i<=r;++i)
			res+=abs(a[i]+tag[id[i]]);
	for(re int i=id[l]+1;i<=id[r]-1;++i)
		res+=ans[i];
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(;(sq+1)*(sq+1)<=n;++sq);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq+1;
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<=id[n];++i)
		init(i);
	for(re int i=1;i<=m;++i){
		re int opt,l,r,x;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1){
			cltstream::read(x);
			modify(l,r,x);
		}
		else
			cltstream::write(query(l,r),10);
	}
	clop();
	return 0;
}
