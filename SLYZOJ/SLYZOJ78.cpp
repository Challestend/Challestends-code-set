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

int n,m;
struct LinkCutTree{
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		long long size,val,sum0,sum1,sum2,add,rev;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void pushUp(){
			size=1;
			sum0=sum1=sum2=0;
			if(lc!=NULL){
				size+=lc->size;
				sum0+=lc->sum0;
				sum1+=lc->sum1;
				sum2+=lc->sum2;
			}
			sum0+=val;
			sum1+=size*val;
			sum2+=size*size*val;
			if(rc!=NULL){
				size+=rc->size;
				sum0+=rc->sum0;
				sum1+=rc->sum1+(size-rc->size)*rc->sum0;
				sum2+=rc->sum2+2*(size-rc->size)*rc->sum1+(size-rc->size)*(size-rc->size)*rc->sum0;
			}
		}

		inline void reverse(){
			std::swap(lc,rc);
			rev^=1;
			pushUp();
		}

		inline void pushDown(){
			if(lc!=NULL){
				if(rev)
					lc->reverse();
				re int ln=lc->size;
				lc->val+=add;
				lc->sum0+=ln*add;
				lc->sum1+=ln*(ln+1)/2*add;
				lc->sum2+=ln*(ln+1)*(2*ln+1)/6*add;
				lc->add+=add;
			}
			if(rc!=NULL){
				if(rev)
					rc->reverse();
				re int rn=rc->size;
				rc->val+=add;
				rc->sum0+=rc->size*add;
				rc->sum1+=rn*(rn+1)/2*add;
				rc->sum2+=rn*(rn+1)*(2*rn+1)/6*add;
				rc->add+=add;
			}
			add=rev=0;
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
		}
		else{
			q->lc=p->rc;
			if(q->lc!=NULL)
				q->lc->ftr=q;
			p->rc=q;
		}
		q->ftr=p;
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
		if(findRoot(q)==p&&p->rc==q&&q->lc==NULL){
			p->rc=q->ftr=NULL;
			p->pushUp();
		}
	}

	inline long long gcd(re long long x,re long long y){
		if(!x)
			return y;
		for(;y^=x^=y^=x%=y;);
		return x;
	}

	LinkCutTree(){
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<=n;++i){
			(mempool+i)->ftr=(mempool+i)->lc=(mempool+i)->rc=NULL;
			cltstream::read((mempool+i)->val);
			(mempool+i)->add=(mempool+i)->rev=0;
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
			long long z,cn,ans,cnt,g;
			cltstream::read(opt);
			cltstream::read(x);
			cltstream::read(y);
			switch(opt){
				case 1:
					cut(mempool+x,mempool+y);
					break;
				case 2:
					link(mempool+x,mempool+y);
					break;
				case 3:
					cltstream::read(z);
					if(findRoot(mempool+x)==findRoot(mempool+y)){
						split(mempool+x,mempool+y);
						cn=(mempool+y)->size;
						(mempool+y)->val+=z;
						(mempool+y)->sum2+=cn*(cn+1)*(2*cn+1)/6*z;
						(mempool+y)->sum1+=cn*(cn+1)/2*z;
						(mempool+y)->sum0+=cn*z;
						(mempool+y)->add+=z;
					}
					break;
				case 4:
					split(mempool+x,mempool+y);
					cn=(mempool+y)->size;
					ans=(cn+1)*(mempool+y)->sum1-(mempool+y)->sum2;
					cnt=cn*(cn+1)/2;
					g=gcd(ans,cnt);
					printf("%lld/%lld\n",ans/g,cnt/g);
			}
		}
	}
};
LinkCutTree CLT;

int main(){
	return 0;
}
