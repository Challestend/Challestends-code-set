#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 60000
#define id(a) (((a)-1)/sq)

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

int n,m,sq;
int a[maxn+1],cnt[1<<26];
struct Query{
	int id,ql,qr;
};
Query query[maxn+1];
long long ans[maxn+1];

inline bool operator<(re Query p1,re Query p2){
	return id(p1.ql)==id(p2.ql)?(id(p1.ql)&1)?p1.qr>p2.qr:p1.qr<p2.qr:p1.ql<p2.ql;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i){
		re char c=cltstream::gc();
		for(;c<'a'||c>'z';c=cltstream::gc());
		a[i]=a[i-1]^(1<<(c-'a'));
	}
	for(re int i=1;i<=m;++i){
		query[i].id=i;
		cltstream::read(query[i].ql);
		--query[i].ql;
		cltstream::read(query[i].qr);
	}
	std::sort(query+1,query+m+1);
	re int L=0,R=1;
	++cnt[a[0]];
	++cnt[a[1]];
	ans[0]=1;
	for(re int i=1;i<=m;++i){
		for(;R<query[i].qr;){
			++R;
			ans[0]+=cnt[a[R]];
			for(re int j=1,k=0;k<26;j<<=1,++k)
				ans[0]+=cnt[a[R]^j];
			++cnt[a[R]];
		}
		for(;L>query[i].ql;){
			--L;
			ans[0]+=cnt[a[L]];
			for(re int j=1,k=0;k<26;j<<=1,++k)
				ans[0]+=cnt[a[L]^j];
			++cnt[a[L]];
		}
		for(;R>query[i].qr;){
			--cnt[a[R]];
			ans[0]-=cnt[a[R]];
			for(re int j=1,k=0;k<26;j<<=1,++k)
				ans[0]-=cnt[a[R]^j];
			--R;
		}
		for(;L<query[i].ql;){
			--cnt[a[L]];
			ans[0]-=cnt[a[L]];
			for(re int j=1,k=0;k<26;j<<=1,++k)
				ans[0]-=cnt[a[L]^j];
			++L;
		}
		ans[query[i].id]=ans[0];
	}
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
