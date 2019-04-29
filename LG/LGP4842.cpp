#include<cstdio>
#include<algorithm>
#define re register
#define maxn 50000

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

class LinkCutTree{
	int n,m;
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int val,size,add,rev;
		long long sum0,sum1,sum2;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void reverse(){
			std::swap(lc,rc);
			sum2=1LL*(size+1)*(size+1)*sum0-2LL*(size+1)*sum1+sum2;
			sum1=1LL*(size+1)*sum0-sum1;
			rev^=1;
		}

		inline void pushDown(){
			if(add){
				if(lc!=NULL){
					lc->val+=add;
					lc->sum2+=1LL*lc->size*(lc->size+1)*(2*lc->size+1)/6*add;
					lc->sum1+=1LL*lc->size*(lc->size+1)/2*add;
					lc->sum0+=1LL*lc->size*add;
					lc->add+=add;
				}
				if(rc!=NULL){
					rc->val+=add;
					rc->sum2+=1LL*rc->size*(rc->size+1)*(2*rc->size+1)/6*add;
					rc->sum1+=1LL*rc->size*(rc->size+1)/2*add;
					rc->sum0+=1LL*rc->size*add;
					rc->add+=add;
				}
				add=0;
			}
			if(rev){
				if(lc!=NULL)
					lc->reverse();
				if(rc!=NULL)
					rc->reverse();
				rev=0;
			}
		}

		inline void pushUp(){
			size=1;
			sum0=sum1=sum2=val;
			if(lc!=NULL){
				size+=lc->size;
				sum2+=lc->sum2+2LL*lc->size*sum1+1LL*lc->size*lc->size*sum0;
				sum1+=lc->sum1+1LL*lc->size*sum0;
				sum0+=lc->sum0;
			}
			if(rc!=NULL){
				sum2+=rc->sum2+2LL*size*rc->sum1+1LL*size*size*rc->sum0;
				sum1+=rc->sum1+1LL*size*rc->sum0;
				sum0+=rc->sum0;
				size+=rc->size;
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

	inline SplayNode* findRoot(re SplayNode* p){
		access(p);
		for(;p->lc!=NULL;p=p->lc);
		splay(p);
		return p;
	}

	inline void split(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		access(q);
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		if(findRoot(q)!=p)
			p->ftr=q;
	}

	inline void cut(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		if(findRoot(q)==p&&q->ftr==p&&q->lc==NULL){
			p->rc=q->ftr=NULL;
			p->pushUp();
		}
	}

	inline long long gcd(re long long x,re long long y){
		for(;y^=x^=y^=x%=y;);
		return x;
	}

	public:

	LinkCutTree(){
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<=n;++i){
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
			int opt,u,v,w,s;
			long long sum,cnt,g;
			cltstream::read(opt);
			cltstream::read(u);
			cltstream::read(v);
			switch(opt){
				case 1:
					cut(mempool+u,mempool+v);
					break;
				case 2:
					link(mempool+u,mempool+v);
					break;
				case 3:
					cltstream::read(w);
					if(findRoot(mempool+u)==findRoot(mempool+v)){
						split(mempool+u,mempool+v);
						s=(mempool+v)->size;
						(mempool+v)->val+=w;
						(mempool+v)->sum2+=1LL*s*(s+1)*(2*s+1)/6*w;
						(mempool+v)->sum1+=1LL*s*(s+1)/2*w;
						(mempool+v)->sum0+=1LL*s*w;
						(mempool+v)->add+=w;
					}
					break;
				case 4:
					if(findRoot(mempool+u)==findRoot(mempool+v)){
						split(mempool+u,mempool+v);
						s=(mempool+v)->size;
						sum=1LL*(s+1)*(mempool+v)->sum1-(mempool+v)->sum2;
						cnt=1LL*s*(s+1)/2;
						g=gcd(sum,cnt);
						cltstream::write(sum/g,'/');
						cltstream::write(cnt/g,10);
					}
					else
						cltstream::write(-1,10);
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
