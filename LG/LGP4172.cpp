#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000
#define maxm 100000
#define maxq 100000
#define max(a,b) ((a)>=(b)?(a):(b))

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

struct Edge{
	int src,des,len,ex;
};
Edge edge[maxm+1];

inline bool operator<(re Edge p1,re Edge p2){
	return p1.len<p2.len;
}

struct LinkCutTree{
	int n,m,q;
	int f[maxn+1],mat[maxn+1][maxn+1],opt[maxq+1][3],ans[maxq+1];
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int id,mx,rev;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void pushUp(){
			mx=id;
			if(lc!=NULL&&edge[mx].len<edge[lc->mx].len)
				mx=lc->mx;
			if(rc!=NULL&&edge[mx].len<edge[rc->mx].len)
				mx=rc->mx;
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
	SplayNode mempool[maxn+maxm+1];

	int find(re int x){
		return f[x]==x?x:f[x]=find(f[x]);
	}

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
		p->ftr=q;
	}

	inline void cut(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		access(q);
		q->lc=p->ftr=NULL;
		q->pushUp();
	}

	LinkCutTree(){
		cltstream::read(n);
		cltstream::read(m);
		cltstream::read(q);
		for(re int i=1;i<=n;++i)
			f[i]=i;
		for(re int i=1;i<=m;++i){
			(mempool+n+i)->id=i;
			cltstream::read(edge[i].src);
			cltstream::read(edge[i].des);
			cltstream::read(edge[i].len);
			edge[i].ex=1;
		}
		std::sort(edge+1,edge+m+1);
		for(re int i=1;i<=m;++i)
			mat[edge[i].src][edge[i].des]=mat[edge[i].des][edge[i].src]=i;
		for(re int i=1;i<=q;++i){
			cltstream::read(opt[i][0]);
			cltstream::read(opt[i][1]);
			cltstream::read(opt[i][2]);
			if(opt[i][0]^1)
				edge[mat[opt[i][1]][opt[i][2]]].ex=0;
		}
		for(re int i=1;i<=m;++i)
			if(edge[i].ex&&find(edge[i].src)!=find(edge[i].des)){
				link(mempool+n+i,mempool+edge[i].src);
				link(mempool+n+i,mempool+edge[i].des);
				f[f[edge[i].src]]=f[edge[i].des];
			}
		for(re int i=q;i>=1;--i){
			split(mempool+opt[i][1],mempool+opt[i][2]);
			re int mxe=(mempool+opt[i][2])->mx;
			if(opt[i][0]^2)
				ans[++ans[0]]=edge[mxe].len;
			else{
				re int cre=mat[opt[i][1]][opt[i][2]];
				if(edge[mxe].len>edge[cre].len){
					cut(mempool+n+mxe,mempool+edge[mxe].src);
					cut(mempool+n+mxe,mempool+edge[mxe].des);
					link(mempool+n+cre,mempool+edge[cre].src);
					link(mempool+n+cre,mempool+edge[cre].des);
				}
			}
		}
		for(re int i=ans[0];i>=1;--i)
			cltstream::write(ans[i],10);
		clop();
	}
};
LinkCutTree CLT;

int main(){
	return 0;
}
