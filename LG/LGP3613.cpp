#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000

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

struct LinkCutTree{
	int n,m,k;
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int tp,rev;
		unsigned long long val,ans0,sna0,ans1,sna1;

		inline unsigned long long apply(unsigned long long x){
			return tp==1?(x&val):tp==2?(x|val):(x^val);
		}

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void reverse(){
			std::swap(lc,rc);
			std::swap(ans0,sna0);
			std::swap(ans1,sna1);
			rev^=1;
		}

		inline void pushDown(){
			if(rev){
				if(lc!=NULL)
					lc->reverse();
				if(rc!=NULL)
					rc->reverse();
				rev=0;
			}
		}

		inline void pushUp(){
			ans0=0,ans1=-1;
			if(lc!=NULL){
				ans0=lc->ans0;
				ans1=lc->ans1;
			}
			ans0=apply(ans0),ans1=apply(ans1);
			if(rc!=NULL){
				ans0=(ans0&rc->ans1)|((~ans0)&rc->ans0);
				ans1=(ans1&rc->ans1)|((~ans1)&rc->ans0);
			}
			sna0=0,sna1=-1;
			if(rc!=NULL){
				sna0=rc->sna0;
				sna1=rc->sna1;
			}
			sna0=apply(sna0),sna1=apply(sna1);
			if(lc!=NULL){
				sna0=(sna0&lc->sna1)|((~sna0)&lc->sna0);
				sna1=(sna1&lc->sna1)|((~sna1)&lc->sna0);
			}
		}
	};
	SplayNode mempool[maxn+1];

	inline void rotate(re SplayNode* p){
		re SplayNode* q=p->ftr;
		q->pushDown();
		p->pushDown();
		p->ftr=q->ftr;
		if(p->ftr!=NULL){
			if(p->ftr->lc==q)
				p->ftr->lc=p;
			if(p->ftr->rc==q)
				p->ftr->rc=p;
		}
		if(q->rc==p){
			q->rc=p->lc;
			if(q->rc!=NULL)
				q->rc->ftr=q;
			p->lc=q;
			q->ftr=p;
		}
		else{
			q->lc=p->rc;
			if(q->lc!=NULL)
				q->lc->ftr=q;
			p->rc=q;
			q->ftr=p;
		}
		q->pushUp();
		p->pushUp();
	}

	inline void splay(re SplayNode* p){
		for(;!p->isRoot();rotate(p))
			for(;!p->ftr->isRoot();)
				rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
	}

	inline void access(re SplayNode* p){
		splay(p);
		p->pushDown();
		p->rc=NULL;
		p->pushUp();
		for(re SplayNode* q=p;q->ftr!=NULL;q=q->ftr){
			splay(q->ftr);
			q->ftr->pushDown();
			q->ftr->rc=q;
			q->ftr->pushUp();
		}
		splay(p);
	}

	inline void makeRoot(re SplayNode* p){
		access(p);
		p->reverse();
	}

	inline void split(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		access(q);
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		p->ftr=q;
	}

	LinkCutTree(){
		cltstream::read(n);
		cltstream::read(m);
		cltstream::read(k);
		for(re int i=1;i<=n;++i){
			cltstream::read((mempool+i)->tp);
			cltstream::read((mempool+i)->val);
			(mempool+i)->pushUp();
		}
		for(re int i=1;i<n;++i){
			int x,y;
			cltstream::read(x);
			cltstream::read(y);
			link(mempool+x,mempool+y);
		}
		for(re int i=1;i<=m;++i){
			int opt,x,y;
			unsigned long long z;
			cltstream::read(opt);
			cltstream::read(x);
			cltstream::read(y);
			cltstream::read(z);
			if(opt==1){
				split(mempool+x,mempool+y);
				re unsigned long long ans0=(mempool+y)->ans0,ans1=(mempool+y)->ans1,ans=0;
				for(re int j=k-1;j>=0;--j)
					if((ans0&(1ULL<<j))>=(ans1&(1ULL<<j))||z<(1ULL<<j))
						ans|=ans0&(1ULL<<j);
					else{
						z-=1ULL<<j;
						ans|=ans1&(1ULL<<j);
					}
				cltstream::write(ans,10);
			}
			else{
				access(mempool+x);
				(mempool+x)->tp=y;
				(mempool+x)->val=z;
				(mempool+x)->pushUp();
			}
		}
		clop();
	}
};
LinkCutTree CLT;

int main(){
	return 0;
}
