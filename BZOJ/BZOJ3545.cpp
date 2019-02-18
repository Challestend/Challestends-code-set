#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 500000
#define maxq 500000

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
	int src,des,len;
};

inline bool operator<(re Edge p1,re Edge p2){
	return p1.len<p2.len;
}

struct Query{
	int id,src,lim,rnk;
};

inline bool operator<(re Query p1,re Query p2){
	return p1.lim<p2.lim;
}

struct SplayTree{
	int n,m,q;
	int f[maxn+1];
	Edge edge[maxm+1];
	Query query[maxq+1];
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int cnt,size,sum,val;

		inline void pushUp(){
			size=1;
			sum=cnt;
			if(lc!=NULL){
				size+=lc->size;
				sum+=lc->sum;
			}
			if(rc!=NULL){
				size+=rc->size;
				sum+=rc->sum;
			}
		}
	};
	SplayNode mp[maxn+1],*vec[maxn+1];
	int vectop,ans[maxq+1];

	int find(re int x){
		return f[x]==x?x:f[x]=find(f[x]);
	}

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

	inline void splay(re SplayNode* p,re SplayNode* q){
		for(;p->ftr!=q;rotate(p))
			if(p->ftr->ftr!=q)
				rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
	}

	inline int queryKth(re SplayNode* rt,re int x){
		splay(rt,NULL);
		if(rt->size<x)
			return -1;
		for(re SplayNode* p=rt;p!=NULL;){
			re int ln=p->lc!=NULL?p->lc->sum:0,rn=ln+p->cnt;
			if(x>ln&&x<=rn){
				splay(p,NULL);
				return p->val;
			}
			else{
				if(x<=ln)
					p=p->lc;
				else{
					x-=rn;
					p=p->rc;
				}
			}
		}
		return -1;
	}

	inline void insertNode(re SplayNode* rt,re SplayNode* nd){
		splay(rt,NULL);
		for(re SplayNode* p=rt;;){
			if(nd->val==p->val){
				p->cnt+=nd->cnt;
				splay(p,NULL);
				return;
			}
			else{
				if(nd->val>p->val){
					if(p->lc==NULL){
						p->lc=nd;
						nd->ftr=p;
						splay(nd,NULL);
						return;
					}
					else
						p=p->lc;
				}
				else{
					if(p->rc==NULL){
						p->rc=nd;
						nd->ftr=p;
						splay(nd,NULL);
						return;
					}
					else
						p=p->rc;
				}
			}
		}
	}

	void breakDown(re SplayNode* p){
		if(p!=NULL){
			breakDown(p->lc);
			breakDown(p->rc);
			p->ftr=p->lc=p->rc=NULL;
			p->size=p->sum=p->cnt;
			vec[++vectop]=p;
		}
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		if(find(p-mp)!=find(q-mp)){
			f[f[p-mp]]=f[q-mp];
			splay(p,NULL);
			splay(q,NULL);
			if(q->size>p->size)
				std::swap(p,q);
			breakDown(q);
			for(;vectop;insertNode(p,vec[vectop--]));
		}
	}

	SplayTree(){
		vectop=0;
		cltstream::read(n);
		cltstream::read(m);
		cltstream::read(q);
		for(re int i=1;i<=n;++i){
			f[i]=i;
			(mp+i)->cnt=(mp+i)->size=(mp+i)->sum=1;
			cltstream::read((mp+i)->val);
		}
		for(re int i=1;i<=m;++i){
			cltstream::read(edge[i].src);
			cltstream::read(edge[i].des);
			cltstream::read(edge[i].len);
		}
		std::sort(edge+1,edge+m+1);
		for(re int i=1;i<=q;++i){
			query[i].id=i;
			cltstream::read(query[i].src);
			cltstream::read(query[i].lim);
			cltstream::read(query[i].rnk);
		}
		std::sort(query+1,query+q+1);
		for(re int i=1,j=1;i<=q;++i){
			for(;j<=m&&edge[j].len<=query[i].lim;link(mp+edge[j].src,mp+edge[j].des),++j);
			ans[query[i].id]=queryKth(mp+query[i].src,query[i].rnk);
		}
		for(re int i=1;i<=q;++i)
			cltstream::write(ans[i],10);
		clop();
	}
};
SplayTree CLT;

int main(){
	return 0;
}
