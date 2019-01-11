#include<cstdio>
#include<iostream>
#include<set>
#define re register
#define _it std::set<node>::iterator
#ifdef ONLINE_JUDGE
	#define int __int128_t
#endif

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
		signed sn=1;
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
			signed digit[50];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

int n,m;

inline int simEuc(re int n,re int a,re int b,re int c){
	if(!n)
		return b/c;
	if(!a)
		return (n+1)*(b/c);
	if(a>=c||b>=c){
		re int res=simEuc(n,a%c,b%c,c);
		return res+n*(n+1)*(a/c)/2+(n+1)*(b/c);
	}
	else{
		re int m=(a*n+b)/c;
		return m*n-simEuc(m-1,c,c-b-1,a);
	}
}

struct node{
	int l,r,L,R,a,b,sum;

	node(re int _l,re int _r,re int _L,re int _R,re int _a,re int _b){
		l=_l;
		r=_r;
		L=_L;
		R=_R;
		a=_a;
		b=_b;
		sum=(R+L)*(R-L+1)*a/2-simEuc(R,a,0,b)*b+simEuc(L-1,a,0,b)*b;
	}
};
std::set<node> s;

inline bool operator<(re node p1,re node p2){
	return p1.l<p2.l;
}

inline _it split(re int pos){
	re _it it=s.lower_bound(node(pos,0,1,0,0,1));
	if(it!=s.end()&&it->l==pos)
		return it;
	else{
		--it;
		re int l=it->l,r=it->r,L=it->L,R=it->R,a=it->a,b=it->b;
		s.erase(it);
		s.insert(node(l,pos-1,L,L+pos-l-1,a,b));
		return s.insert(node(pos,r,L+pos-l,R,a,b)).first;
	}
}

inline void modifyStone(re int l,re int r,re int a,re int b){
	re _it itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,1,r-l+1,a,b));
}

inline int queryStone(re int l,re int r){
	re _it itr=split(r+1),itl=split(l);
	re int res=0;
	for(;itl!=itr;res+=itl->sum,++itl);
	return res;
}

signed main(){
	cltstream::read(n);
	cltstream::read(m);
	s.insert(node(1,n,1,0,0,1));
	for(re int i=1;i<=m;++i){
		re int opt,l,r,a,b;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1){
			cltstream::read(a);
			cltstream::read(b);
			modifyStone(l,r,a,b);
		}
		else
			cltstream::write(queryStone(l,r),10);
	}
	clop();
	return 0;
}
