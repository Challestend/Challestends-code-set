#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 50000
#define maxm 50000
#define maxval 1000000
#define swap(a,b) a^=b,b^=a,a^=b
#define add(a) (cnt[a]||(++cnt[0]),++cnt[a])
#define del(a) (--cnt[a],cnt[a]||(--cnt[0]))

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

int n,m,qc,rc,sq;
int a[maxn+1],opt[maxm+1][2];
struct Query{
	int id,l,r,t;
};
Query q[maxm+1];
int cnt[maxval+1],ans[maxm+1];

inline bool operator<(const Query p1,const Query p2){
	return p1.l/sq!=p2.l/sq?p1.l<p2.l:p1.r/sq!=p2.r/sq?p1.r<p2.r:p1.t<p2.t;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<=m;++i){
		re char c=cltstream::gc();
		for(;c!='Q'&&c!='R';c=cltstream::gc());
		if(c=='Q'){
			++qc;
			q[qc].id=qc;
			cltstream::read(q[qc].l);
			cltstream::read(q[qc].r);
			q[qc].t=rc;
		}
		else{
			++rc;
			cltstream::read(opt[rc][0]);
			cltstream::read(opt[rc][1]);
		}
	}
	sq=pow(n,2.0/3);
	std::sort(q+1,q+qc+1);
	re int L=1,R=0,T=0;
	for(re int i=1;i<=qc;++i){
		for(;T<q[i].t;){
			++T;
			opt[T][0]>=L&&opt[T][0]<=R&&(del(a[opt[T][0]]),add(opt[T][1]));
			swap(a[opt[T][0]],opt[T][1]);
		}
		for(;T>q[i].t;){
			opt[T][0]>=L&&opt[T][0]<=R&&(del(a[opt[T][0]]),add(opt[T][1]));
			swap(a[opt[T][0]],opt[T][1]);
			--T;
		}
		for(;R<q[i].r;++R,add(a[R]));
		for(;R>q[i].r;del(a[R]),--R);
		for(;L>q[i].l;--L,add(a[L]));
		for(;L<q[i].l;del(a[L]),++L);
		ans[q[i].id]=cnt[0];
	}
	for(re int i=1;i<=qc;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
