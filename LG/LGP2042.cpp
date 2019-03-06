#include<cstdio>
#include<algorithm>
#define re register
#define maxn 500000

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
	int n,m;
	int vec[maxn+5];
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int size,val,sum,ls,rs,ms,upd,c,rev;

		inline void pushDown(){
			if(upd){
				if(lc!=NULL){
					lc->val=c;
					lc->sum=lc->size*c;
					lc->ls=lc->rs=lc->ms=std::max(c,lc->size*c);
					lc->upd=1;
					lc->c=c;
				}
				if(rc!=NULL){
					rc->val=c;
					rc->sum=rc->size*c;
					rc->ls=rc->rs=rc->ms=std::max(c,rc->size*c);
					rc->upd=1;
					rc->c=c;
				}
				upd=0;
			}
			if(rev){
				if(lc!=NULL){
					std::swap(lc->lc,lc->rc);
					std::swap(lc->ls,lc->rs);
					lc->rev^=1;
				}
				if(rc!=NULL){
					std::swap(rc->lc,rc->rc);
					std::swap(rc->ls,rc->rs);
					rc->rev^=1;
				}
				rev=0;
			}
		}

		inline void pushUp(){
			size=1;
			sum=ls=rs=ms=val;
			if(lc!=NULL){
				size+=lc->size;
				ms=std::max(std::max(lc->ms,ms),lc->rs+ls);
				ls=std::max(lc->ls,lc->sum+ls);
				rs=std::max(rs,sum+lc->rs);
				sum+=lc->sum;
			}
			if(rc!=NULL){
				size+=rc->size;
				ms=std::max(std::max(ms,rc->ms),rs+rc->ls);
				ls=std::max(ls,sum+rc->ls);
				rs=std::max(rc->rs,rc->sum+rs);
				sum+=rc->sum;
			}
		}
	};
	SplayNode mempool[maxn+5],*memtop,*root,*rec[maxn+5];
	int rectop;

	inline SplayNode* newNode(re int val){
		re SplayNode* p=rectop?rec[rectop--]:++memtop;
		if(p->lc!=NULL)
			rec[++rectop]=p->lc;
		if(p->rc!=NULL)
			rec[++rectop]=p->rc;
		p->ftr=p->lc=p->rc=NULL;
		p->size=1;
		p->val=p->sum=p->ls=p->rs=p->ms=val;
		p->upd=p->c=p->rev=0;
		return p;
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

	inline void splay(re SplayNode* p,re SplayNode* q){
		for(;p->ftr!=q;rotate(p))
			if(p->ftr->ftr!=q)
				rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
		if(q==NULL)
			root=p;
	}

	SplayNode* build(re int l,re int r){
		re int mid=(l+r)>>1;
		re SplayNode* p=newNode(vec[mid]);
		if(l<mid){
			p->lc=build(l,mid-1);
			p->lc->ftr=p;
		}
		if(mid<r){
			p->rc=build(mid+1,r);
			p->rc->ftr=p;
		}
		p->pushUp();
		return p;
	}

	inline SplayNode* findRank(re int x){
		for(re SplayNode* p=root;p!=NULL;){
			p->pushDown();
			re int ln=p->lc!=NULL?p->lc->size+1:1;
			if(x==ln)
				return p;
			else
				if(x<ln)
					p=p->lc;
				else{
					x-=ln;
					p=p->rc;
				}
		}
		return NULL;
	}

	inline void insertArray(){
		int pos,tot;
		cltstream::read(pos);
		cltstream::read(tot);
		for(re int i=1;i<=tot;++i)
			cltstream::read(vec[i]);
		re SplayNode* L=findRank(pos+1);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+2);
		splay(R,L);
		R->lc=build(1,tot);
		R->lc->ftr=R;
		R->pushUp();
		L->pushUp();
	}

	inline void deleteArray(){
		int pos,tot;
		cltstream::read(pos);
		cltstream::read(tot);
		re SplayNode* L=findRank(pos);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+tot+1);
		splay(R,L);
		if(R->lc!=NULL){
			rec[++rectop]=R->lc;
			R->lc=NULL;
			R->pushUp();
			L->pushUp();
		}
	}

	inline void modifyArray(){
		int pos,tot,val;
		cltstream::read(pos);
		cltstream::read(tot);
		cltstream::read(val);
		re SplayNode* L=findRank(pos);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+tot+1);
		splay(R,L);
		if(R->lc!=NULL){
			R->lc->val=val;
			R->lc->sum=R->lc->size*val;
			R->lc->ls=R->lc->rs=R->lc->ms=std::max(val,R->lc->size*val);
			R->lc->upd=1;
			R->lc->c=val;
			R->pushUp();
			L->pushUp();
		}
	}

	inline void reverseArray(){
		int pos,tot;
		cltstream::read(pos);
		cltstream::read(tot);
		re SplayNode* L=findRank(pos);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+tot+1);
		splay(R,L);
		if(R->lc!=NULL){
			std::swap(R->lc->lc,R->lc->rc);
			std::swap(R->lc->ls,R->lc->rs);
			R->lc->rev^=1;
			R->pushUp();
			L->pushUp();
		}
	}

	inline void getSum(){
		int pos,tot;
		cltstream::read(pos);
		cltstream::read(tot);
		re SplayNode* L=findRank(pos);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+tot+1);
		splay(R,L);
		cltstream::write(R->lc!=NULL?R->lc->sum:0,10);
	}

	inline void getMaxSum(){
		cltstream::write(root->ms,10);
	}

	void printNode(re SplayNode* p){
		p->pushDown();
		if(p->lc!=NULL)
			printNode(p->lc);
		printf("%d ",p->val);
		if(p->rc!=NULL)
			printNode(p->rc);
		if(p==root)
			puts("");
	}

	SplayTree(){
		memtop=mempool;
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<=n;++i)
			cltstream::read(vec[i+1]);
		vec[1]=vec[n+2]=-5e8;
		root=build(1,n+2);
		for(re int i=1;i<=m;++i){
			re char opt=cltstream::gc();
			for(;opt!='S'&&opt!='L'&&opt!='K'&&opt!='V'&&opt!='T'&&opt!='X';opt=cltstream::gc());
			switch(opt){
				case 'S':
					for(;opt!=32;opt=cltstream::gc());
					insertArray();
					break;
				case 'L':
					for(;opt!=32;opt=cltstream::gc());
					deleteArray();
					break;
				case 'K':
					for(;opt!=32;opt=cltstream::gc());
					modifyArray();
					break;
				case 'V':
					for(;opt!=32;opt=cltstream::gc());
					reverseArray();
					break;
				case 'T':
					for(;opt!=32;opt=cltstream::gc());
					getSum();
					break;
				case 'X':
					for(;opt!=10&&opt!=13;opt=cltstream::gc());
					getMaxSum();
					break;
			}
		}
		clop();
	}
};
SplayTree CLT;

int main(){
	return 0;
}
