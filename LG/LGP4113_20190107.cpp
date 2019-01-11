#include<cstdio>
#include<algorithm>
#define re register
#define maxn 2000000
#define lowbit(a) ((a)&(-(a)))

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

int n,m,c;
int las[maxn+1],cnt[maxn+1],nxt[maxn+1],bit[maxn+1],ans[maxn+1];
struct query{
	int id,ql,qr;
};
query q[maxn+1];

inline bool operator<(query p1,query p2){
	return p1.ql!=p2.ql?p1.ql<p2.ql:p1.qr<p2.qr;
}

inline void update(re int x,re int y){
	for(;x<=n;x+=lowbit(x))
		bit[x]+=y;
}

inline int getsum(re int x){
	re int res=0;
	for(;x>=1;x-=lowbit(x))
		res+=bit[x];
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(c);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		re int x;
		cltstream::read(x);
		if(las[x])
			nxt[las[x]]=i;
		las[x]=i;
		++cnt[x];
		if(cnt[x]==2)
			update(i,1);
	}
	for(re int i=1;i<=m;++i){
		q[i].id=i;
		cltstream::read(q[i].ql);
		cltstream::read(q[i].qr);
	}
	std::sort(q+1,q+m+1);
	for(re int i=1,l=1;i<=m;++i){
		for(;l<q[i].ql;++l){
			if(nxt[l])
				update(nxt[l],-1);
			if(nxt[nxt[l]])
				update(nxt[nxt[l]],1);
		}
		ans[q[i].id]=getsum(q[i].qr)-getsum(q[i].ql-1);
	}
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
