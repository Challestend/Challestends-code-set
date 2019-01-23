#include<cstdio>
#include<algorithm>
#define re register
#define maxn 80000

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

struct SplayTree{
	struct SplayNode{
		SplayNode *ftr,*ls,*rs;
		int index,size;

		inline void pushUp(){
			size=1;
			if(ls!=NULL)
				size+=ls->size;
			if(rs!=NULL)
				size+=rs->size;
		}
	};

	SplayNode mempool[maxn+5],*root;
	int nodepos[maxn+5];

	SplayNode* build(re int l,re int r){
		re int mid=(l+r)>>1;
		re SplayNode* p=&mempool[mid];
		p->ftr=p->ls=p->rs=NULL;
		p->size=1;
		if(l<mid){
			p->ls=build(l,mid-1);
			p->ls->ftr=p;
		}
		cltstream::read(p->index);
		nodepos[p->index]=mid;
		if(mid<r){
			p->rs=build(mid+1,r);
			p->rs->ftr=p;
		}
		p->pushUp();
		return p;
	}

	inline void rotate(re SplayNode* p){
		re SplayNode* q=p->ftr;
		p->ftr=q->ftr;
		if(p->ftr!=NULL){
			if(p->ftr->ls==q)
				p->ftr->ls=p;
			else
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

	inline void Splay(re SplayNode* st,re SplayNode*ed){
		for(re SplayNode* p=st->ftr;p!=ed;rotate(st),p=st->ftr)
			if(p->ftr!=ed)
				rotate((p->ftr->rs==p)==(st->ftr->rs==st)?p:st);
		if(ed==NULL)
			root=st;
	}

	inline void Top(re SplayNode* p){
		Splay(p,NULL);
		if(p->ls!=NULL){
			if(p->rs==NULL){
				p->rs=p->ls;
				p->ls=NULL;
			}
			else{
				re SplayNode* q=p->rs;
				for(;q->ls!=NULL;q=q->ls);
				Splay(q,p);
				q->ls=p->ls;
				q->ls->ftr=q;
				p->ls=NULL;
				q->pushUp();
			}
		}
	}

	inline void Bottom(re SplayNode* p){
		Splay(p,NULL);
		if(p->rs!=NULL){
			if(p->ls==NULL){
				p->ls=p->rs;
				p->rs=NULL;
			}
			else{
				re SplayNode* q=p->ls;
				for(;q->rs!=NULL;q=q->rs);
				Splay(q,p);
				q->rs=p->rs;
				q->rs->ftr=q;
				p->rs=NULL;
				q->pushUp();
			}
		}
	}

	inline void Insert(re SplayNode* p,re int tp){
		Splay(p,NULL);
		if(tp==1){
			re SplayNode* q=p->rs;
			for(;q->ls!=NULL;q=q->ls);
			Splay(q,p);
			q->ls=p->ls;
			if(q->ls!=NULL)
				q->ls->ftr=q;
			p->ls=q;
			p->rs=q->rs;
			q->rs=NULL;
			if(p->rs!=NULL)
				p->rs->ftr=p;
			q->pushUp();
		}
		if(tp==-1){
			re SplayNode* q=p->ls;
			for(;q->rs!=NULL;q=q->rs);
			Splay(q,p);
			q->rs=p->rs;
			if(q->rs!=NULL)
				q->rs->ftr=q;
			p->rs=q;
			p->ls=q->ls;
			q->ls=NULL;
			if(p->ls!=NULL)
				p->ls->ftr=p;
			q->pushUp();
		}
	}

	inline int Ask(re SplayNode* p){
		Splay(p,NULL);
		return p->ls==NULL?0:p->ls->size;
	}

	inline int Query(re int x){
		for(re SplayNode* p=root;p!=NULL;){
			re int ln=p->ls==NULL?1:p->ls->size+1;
			if(x==ln)
				return p->index;
			else
				if(x>ln){
					x-=ln;
					p=p->rs;
				}
				else
					p=p->ls;
		}
		return 0;
	}

	void printTree(re SplayNode* p){
		if(p!=NULL){
			printTree(p->ls);
			printf("%d(%d:%d) ",p->index,p->ls==NULL?-1:p->ls->index,p->rs==NULL?-1:p->rs->index);
			printTree(p->rs);
		}
	}
};

SplayTree QAQ;

int n,m;

int main(){
	cltstream::read(n);
	cltstream::read(m);
	QAQ.root=QAQ.build(1,n);
	for(re int i=1;i<=m;++i){
		re char opt=cltstream::gc();
		for(;opt!='T'&&opt!='B'&&opt!='I'&&opt!='A'&&opt!='Q';opt=cltstream::gc());
		int x,y;
		cltstream::read(x);
		switch(opt){
			case 'T':
				QAQ.Top(&QAQ.mempool[QAQ.nodepos[x]]);
				break;
			case 'B':
				QAQ.Bottom(&QAQ.mempool[QAQ.nodepos[x]]);
				break;
			case 'I':
				cltstream::read(y);
				QAQ.Insert(&QAQ.mempool[QAQ.nodepos[x]],y);
				break;
			case 'A':
				cltstream::write(QAQ.Ask(&QAQ.mempool[QAQ.nodepos[x]]),10);
				break;
			case 'Q':
				cltstream::write(QAQ.Query(x),10);
		}
		// QAQ.printTree(QAQ.root);
		// puts("");
	}
	clop();
	return 0;
}
