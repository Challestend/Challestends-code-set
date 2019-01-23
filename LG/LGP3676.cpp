#include<cstdio>
#include<algorithm>
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
	struct SplayNode{
		SplayNode *ftr,*ls,*rs;
		int size,val,sumi,sum;
		long long ansi,ans;

		inline int isRoot(){
			return ftr==NULL||(ftr->ls!=this&&ftr->rs!=this);
		}

		inline void pushUp(){
			size=1;
			sum=sumi+val;
			ans=ansi;
			if(rs!=NULL){
				size+=rs->size;
				sum+=rs->sum;
				ans+=rs->ans;
			}
			ans+=sum*sum;
			if(ls!=NULL){
				size+=ls->size;
				sum+=ls->sum;
				ans+=ls->ans+sum*sum;
			}
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
			if(p->ftr->ls==q)
				p->ftr->ls=p;
			if(p->ftr->rs==q)
				p->ftr->rs=p;
		}
		if(q->rs==p){
			q->rs=p->ls;
			if(q->rs!=NULL)
				q->rs->ftr=q;
			p->ls=q;
			q->ftr=p;
		}
		else{
			q->ls=p->rs;
			if(q->ls!=NULL)
				q->ls->ftr=q;
			p->rs=q;
			q->ftr=p;
		}
		q->pushUp();
		p->pushUp();
	}

	inline void splay(re SplayNode* p){
		for(;!p->isRoot();rotate(p))
			if(!p->ftr->isRoot())
				rotate((p->ftr->ftr->ls==p->ftr)==(p->ftr->ls==p)?p->ftr:p);
	}

	inline void access(re SplayNode* p){
		splay(p);
		if(p->rs!=NULL){
			p->sumi+=p->rs->sum;
			p->ansi+=p->rs->ans;
		}
		p->rs=NULL;
		p->pushUp();
		for(re SplayNode* q=p;q->ftr!=NULL;q=q->ftr){
			splay(q->ftr);
			if(q->ftr->rs!=NULL){
				q->ftr->sumi+=q->ftr->rs->sum;
				q->ftr->ansi+=q->ftr->rs->ans;
			}
			q->ftr->rs=q;
			q->ftr->sumi-=q->ftr->rs->sum;
			q->ftr->ansi-=q->ftr->rs->ans;
			q->ftr->pushUp();
		}
		splay(p);
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		access(p);
		access(q);
		q->ftr=p;
		p->sumi+=q->sum;
		p->ansi+=q->ans;
		p->pushUp();
	}

	void printTree(re SplayNode* p){
		if(p!=NULL){
			printTree(p->ls);
			printf(
				"id=%lld,val=%d,sumi=%d,sum=%d,ansi=%lld,ans=%lld,ftr=%lld,ls=%lld,rs=%lld\n",
				p-mempool,
				p->val,
				p->sumi,
				p->sum,
				p->ansi,
				p->ans,
				p->ftr!=NULL?p->ftr-mempool:-1,
				p->ls!=NULL?p->ls-mempool:-1,
				p->rs!=NULL?p->rs-mempool:-1
			);
			printTree(p->rs);
		}
	}

	LinkCutTree(){
		// freopen("C:\\Users\\Challestend\\Downloads\\testdata(2).in","r",stdin);
		// freopen("LGP3676.out","w",stdout);
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<n;++i){
			int x,y;
			cltstream::read(x);
			cltstream::read(y);
			link(mempool+x,mempool+y);
		}
		for(re int i=1;i<=n;++i){
			access(mempool+i);
			cltstream::read((mempool+i)->val);
			(mempool+i)->pushUp();
		}
		for(re int i=1;i<=m;++i){
			int opt,x;
			cltstream::read(opt);
			cltstream::read(x);
			if(opt==1){
				access(mempool+x);
				cltstream::read((mempool+x)->val);
				(mempool+x)->pushUp();
			}
			else{
				access(mempool+x);
				cltstream::write((mempool+x)->ans,10);
			}
			for(re int j=1;j<=n;++j)
				if((mempool+j)->isRoot())
					printTree(mempool+j),puts("");
		}
		clop();
	}
};
LinkCutTree QAQ;

int main(){
	return 0;
}
