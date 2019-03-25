#include<cstdio>
#include<algorithm>
#include<set>
#define re register
#define maxn 100000
#define _it std::set<node>::iterator
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

int n,m,vc=1;
int sum[(maxn<<2)+1],upd[(maxn<<2)+1],c[(maxn<<2)+1];
struct node{
	int l,r,val;
};
std::set<node> s[maxn+1];

inline bool operator<(re node p1,re node p2){
	return p1.l<p2.l;
}

inline void pushDown(re int cur,re int ln,re int rn){
	if(upd[cur]){
		sum[cur<<1]=ln*c[cur];
		upd[cur<<1]=upd[cur];
		c[cur<<1]=c[cur];
		sum[cur<<1|1]=rn*c[cur];
		upd[cur<<1|1]=upd[cur];
		c[cur<<1|1]=c[cur];
		upd[cur]=c[cur]=0;
	}
}

void update(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		sum[cur]=(r-l+1)*x;
		upd[cur]=1;
		c[cur]=x;
	}
	else{
		re int mid=(l+r)>>1;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			update(L,R,x,cur<<1,l,mid);
		if(R>mid)
			update(L,R,x,cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
	}
}

inline int getsum(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return sum[cur];
	else{
		re int mid=(l+r)>>1,res=0;
		pushDown(cur,mid-l+1,r-mid);
		if(L<=mid)
			res+=getsum(L,R,cur<<1,l,mid);
		if(R>mid)
			res+=getsum(L,R,cur<<1|1,mid+1,r);
		return res;
	}
}

inline _it split(re int rt,re int pos){
	_it it=s[rt].lower_bound(node({pos}));
	if(it!=s[rt].end()&&it->l==pos)
		return it;
	else{
		--it;
		re int l=it->l,r=it->r,val=it->val;
		s[rt].erase(it);
		s[rt].insert(node{l,pos-1,val});
		return s[rt].insert(node{pos,r,val}).first;
	}
}

inline void modify(re int l,re int r,re int x){
	_it itr=split(x,r+1),itl=split(x,l);
	for(_it it=itl;it!=itr;++it)
		update(it->l,it->r,!it->val,1,1,n);
	s[x].erase(itl,itr);
	s[x].insert(node{l,r,1});
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=maxn;++i)
		s[i].insert(node{1,n,0});
	for(re int i=1;i<=m;++i){
		int opt;
		cltstream::read(opt);
		if(opt==1){
			int x,l,k;
			cltstream::read(x);
			cltstream::read(l);
			cltstream::read(k);
			modify(max(x-k,1),min(x+k,n),l);
		}
		else{
			int l,r;
			cltstream::read(l);
			cltstream::read(r);
			cltstream::write(getsum(l,r,1,1,n),10);
		}
	}
	clop();
	return 0;
}
