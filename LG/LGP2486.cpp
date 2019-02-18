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

struct LCT{
	int n,m;
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int size,val,lv,rv,ans,rev,upd;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void reverse(){
			std::swap(lc,rc);
			std::swap(lv,rv);
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
			if(upd){
				if(lc!=NULL){
					lc->val=lc->lv=lc->rv=upd;
					lc->ans=1;
					lc->upd=upd;
				}
				if(rc!=NULL){
					rc->val=rc->lv=rc->rv=upd;
					rc->ans=1;
					rc->upd=upd;
				}
				upd=0;
			}
		}

		inline void pushUp(){
			size=ans=1;
			lv=rv=val;
			if(lc!=NULL){
				size+=lc->size;
				ans+=lc->ans-(lc->rv==this->lv);
				lv=lc->lv;
			}
			if(rc!=NULL){
				size+=rc->size;
				ans+=rc->ans-(this->rv==rc->lv);
				rv=rc->rv;
			}
		}
	};
	SplayNode mempool[maxn+1],*stk[maxn+1];

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
		re int top=1;
		stk[top]=p;
		for(re SplayNode* q=p;!q->isRoot();stk[++top]=q=q->ftr);
		for(;top;stk[top--]->pushDown());
		for(;!p->isRoot();rotate(p))
			if(!p->ftr->isRoot())
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

	inline void link(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		p->ftr=q;
	}

	inline void split(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		access(q);
	}

	LCT(){
		cltstream::read(n);
		cltstream::read(m);
		for(re SplayNode* p=mempool+1;p!=mempool+n+1;++p){
			p->size=p->ans=1;
			cltstream::read(p->val);
			p->lv=p->rv=p->val;
			p->rev=p->upd=0;
		}
		for(re int i=1;i<n;++i){
			int x,y;
			cltstream::read(x);
			cltstream::read(y);
			link(mempool+x,mempool+y);
		}
		for(re int i=1;i<=m;++i){
			re char opt=cltstream::gc();
			for(;opt!='C'&&opt!='Q';opt=cltstream::gc());
			int x,y,z;
			cltstream::read(x);
			cltstream::read(y);
			if(opt=='C'){
				cltstream::read(z);
				split(mempool+x,mempool+y);
				(mempool+y)->val=(mempool+y)->lv=(mempool+y)->rv=z;
				(mempool+y)->ans=1;
				(mempool+y)->upd=z;
			}
			else{
				split(mempool+x,mempool+y);
				cltstream::write((mempool+y)->ans,10);
			}
		}
		clop();
	}
};
LCT CLT;

int main(){
	return 0;
}
