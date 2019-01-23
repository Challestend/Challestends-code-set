#include<cstdio>
#define re register
#define maxn 200000

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
	int n,m;
	int a[maxn+1];
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int size;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void pushUp(){
			size=1;
			if(lc!=NULL)
				size+=lc->size;
			if(rc!=NULL)
				size+=rc->size;
		}

		SplayNode(){
			size=1;
		}
	};
	SplayNode mempool[maxn+1];

	inline void rotate(re SplayNode* p){
		re SplayNode* q=p->ftr;
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
			if(!p->ftr->isRoot())
				rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
	}

	inline void access(re SplayNode* p){
		splay(p);
		p->rc=NULL;
		p->pushUp();
		for(re SplayNode* q=p;q->ftr!=NULL;q=q->ftr){
			splay(q->ftr);
			q->ftr->rc=q;
			q->ftr->pushUp();
		}
		splay(p);
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		access(q);
		q->rc=p;
		p->ftr=q;
	}

	inline void cut(re SplayNode* p,re SplayNode* q){
		access(p);
		splay(q);
		q->rc=p->ftr=NULL;
		q->pushUp();
	}

	LinkCutTree(){
		cltstream::read(n);
		for(re int i=1;i<=n;++i){
			cltstream::read(a[i]);
			link(mempool+i,i+a[i]<=n?mempool+i+a[i]:mempool);
		}
		cltstream::read(m);
		for(re int i=1;i<=m;++i){
			int opt,x,y;
			cltstream::read(opt);
			cltstream::read(x);
			++x;
			if(opt==1){
				access(mempool+x);
				cltstream::write((mempool+x)->lc->size,10);
			}
			else{
				cltstream::read(y);
				cut(mempool+x,x+a[x]<=n?mempool+x+a[x]:mempool);
				a[x]=y;
				link(mempool+x,x+a[x]<=n?mempool+x+a[x]:mempool);
			}
		}
		clop();
	}
};
LinkCutTree QAQ;

int main(){
	return 0;
}
