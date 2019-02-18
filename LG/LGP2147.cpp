#include<cstdio>
#include<algorithm>
#define re register
#define maxn 10000

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

struct LinkCutTree{
	int n,m;
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int rev;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void reverse(){
			std::swap(lc,rc);
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
	}

	inline void splay(re SplayNode* p){
		for(;!p->isRoot();rotate(p))
			if(!p->ftr->isRoot())
				rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
	}

	inline void access(re SplayNode* p){
		splay(p);
		p->pushDown();
		p->rc=NULL;
		for(re SplayNode* q=p;q->ftr!=NULL;q=q->ftr){
			splay(q->ftr);
			q->ftr->pushDown();
			q->ftr->rc=q;
		}
		splay(p);
	}

	inline void makeRoot(re SplayNode* p){
		access(p);
		p->reverse();
	}

	inline SplayNode* findRoot(re SplayNode* p){
		access(p);
		for(;p->lc!=NULL;p=p->lc);
		splay(p);
		return p;
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		p->ftr=q;
	}

	inline void cut(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		access(q);
		q->lc=p->ftr=NULL;
	}

	inline int query(re SplayNode* p,re SplayNode* q){
		return findRoot(p)==findRoot(q);
	}

	LinkCutTree(){
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<=m;++i){
			re char opt=cltstream::gc();
			for(;opt!='n'&&opt!='t'&&opt!='r';opt=cltstream::gc());
			int x,y;
			cltstream::read(x);
			cltstream::read(y);
			switch(opt){
				case 'n':
					link(mempool+x,mempool+y);
					break;
				case 't':
					cut(mempool+x,mempool+y);
					break;
				case 'r':
					if(query(mempool+x,mempool+y)){
						cltstream::pc('Y');
						cltstream::pc('e');
						cltstream::pc('s');
						cltstream::pc(10);
					}
					else{
						cltstream::pc('N');
						cltstream::pc('o');
						cltstream::pc(10);
					}
					break;
			}
		}
		clop();
	}
};
LinkCutTree CLT;

int main(){
	return 0;
}
