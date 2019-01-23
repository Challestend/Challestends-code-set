#include<cstdio>
#define re register
#define maxsize 500000
#define maxn 4000000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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

template<typename _tp>
inline void swap(_tp& x,_tp& y){
	_tp tmp=x;
	x=y;
	y=tmp;
}

namespace spt{
	struct node{
		node *ftr,*ch[2];
		int size,val,sum,ls,rs,ms,upd,c,rev;
	};
	struct tree{
		private:
			#define getSide(a) ((a)==(a)->ftr->ch[1])

			node mempool[maxsize+1],*memtop,*rec[maxsize+1],*null,*root;
			int rectop,vec[maxn+1];

			void reverse(node* p);
			void pushUp(node* p);
			void pushDown(node* p);
			void connect(node*,node*,int);
			node* newNode(int);
			void rotate(node*);
			void splay(node*,node*);
			node* findRank(int);
			void printArr(node*);
			void printNode(node*,int,int);

		public:
			node* build(int,int);
			void insArr(int,int);
			void delArr(int,int);
			void modArr(int,int,int);
			void revArr(int,int);
			int getSum(int,int);
			int getMaxSum();
			void check();

			tree(){
				memtop=mempool;
				rectop=-1;
				null=memtop;
				null->ftr=null->ch[0]=null->ch[1]=null;
				null->size=null->val=null->sum=0;
				null->ls=null->rs=null->ms=-5e8;
				null->upd=null->c=null->rev=0;
				connect(root=newNode(0),null,1);
				connect(newNode(0),root,0);
				pushUp(root);
			}
	};

	inline void tree::reverse(re node* p){
		swap(p->ls,p->rs);
		swap(p->ch[0],p->ch[1]);
		p->rev^=1;
	}

	inline void tree::pushUp(node* p){
		p->size=p->ch[0]->size+p->ch[1]->size+1;
		p->sum=p->ch[0]->sum+p->ch[1]->sum+p->val;
		p->ls=max(max(p->ch[0]->ls,p->ch[0]->sum+p->val),p->ch[0]->sum+p->val+p->ch[1]->ls);
		p->rs=max(max(p->ch[1]->rs,p->ch[1]->sum+p->val),p->ch[1]->sum+p->val+p->ch[0]->rs);
		p->ms=max(max(max(max(max(p->ch[0]->ms,p->ch[1]->ms),p->val),p->ch[0]->rs+p->val),p->val+p->ch[1]->ls),p->ch[0]->rs+p->val+p->ch[1]->ls);
	}

	inline void tree::pushDown(node* p){
		if(p->upd){
			for(re int i=0;i<2;++i)
				if(p->ch[i]!=null){
					p->ch[i]->val=p->c;
					p->ch[i]->sum=p->c*p->ch[i]->size;
					p->ch[i]->ls=p->ch[i]->rs=p->ch[i]->ms=max(p->ch[i]->val,p->ch[i]->sum);
					p->ch[i]->upd=p->upd;
					p->ch[i]->c=p->c;
				}
			p->upd=0;
		}
		if(p->rev){
			reverse(p->ch[0]);
			reverse(p->ch[1]);
			p->rev=0;
		}
	}

	inline void tree::connect(re node* x,re node* y,re int sd){
		x->ftr=y;
		y->ch[sd]=x;
	}

	inline node* tree::newNode(re int v){
		re node* p=rectop>=0?rec[rectop--]:++memtop;
		p->ftr=p->ch[0]=p->ch[1]=null;
		p->size=1;
		p->val=p->sum=p->ls=p->rs=p->ms=v;
		p->upd=p->c=p->rev=0;
		return p;
	}

	inline void tree::rotate(re node* p){
		re node* ptr=p->ftr;
		re node* gtr=ptr->ftr;
		re int s1=getSide(p),s2=getSide(ptr);
		connect(p->ch[s1^1],ptr,s1);
		connect(ptr,p,s1^1);
		connect(p,gtr,s2);
		pushUp(ptr);
		pushUp(p);
	}

	inline void tree::splay(re node* st,re node* ed){
		for(re node* p=st->ftr;p!=ed;rotate(st),p=st->ftr)
			if(p->ftr!=ed)
				rotate(getSide(p)==getSide(st)?p:st);
	}

	inline node* tree::findRank(re int x){
		for(re node* p=root;p!=null;){
			pushDown(p);
			re int ln=p->ch[0]->size+1;
			if(x==ln)
				return p;
			else
				if(x>ln){
					x-=ln;
					p=p->ch[1];
				}
				else
					p=p->ch[0];
		}
		return null;
	}

	void tree::printArr(re node* p){
		if(p!=null){
			pushDown(p);
			printArr(p->ch[0]);
			printf("%d ",p->val);
			printArr(p->ch[1]);
		}
	}

	void tree::printNode(re node* p,re int l,re int r){
		if(p!=null){
			printNode(p->ch[0],l,l+p->ch[0]->size-1);
			printNode(p->ch[1],l+p->ch[0]->size+1,r);
			printf("val[%2d]=%6d;",l+p->ch[0]->size,p->val);
			printf("[%2d,%2d]:sum=%6d,ls=%6d,rs=%6d,ms=%6d\n",l,r,p->sum,p->ls,p->rs,p->ms);
		}
	}

	node* tree::build(re int l,re int r){
		re int mid=(l+r)>>1;
		re node* p=newNode(vec[mid]);
		if(l<mid){
			p->ch[0]=build(l,mid-1);
			p->ch[0]->ftr=p;
		}
		if(mid<r){
			p->ch[1]=build(mid+1,r);
			p->ch[1]->ftr=p;
		}
		pushUp(p);
		return p;
	}

	inline void tree::insArr(re int pos,re int len){
		re node* R=findRank(pos+2);
		splay(R,null);
		root=R;
		re node* L=root->ch[0];
		for(;L->ch[1]!=null;L=L->ch[1]);
		splay(L,root);
		for(re int i=1;i<=len;++i)
			cltstream::read(vec[i]);
		R=build(1,len);
		connect(R,L,1);
		pushUp(L);
		pushUp(root);
	}

	inline void tree::delArr(re int pos,re int len){
		re node* R=findRank(pos+len+1);
		splay(R,null);
		root=R;
		re node* L=findRank(pos);
		splay(L,root);
		rec[++rectop]=L->ch[1];
		L->ch[1]=null;
		pushUp(L);
		pushUp(root);
	}

	inline void tree::modArr(re int pos,re int len,re int v){
		re node* R=findRank(pos+len+1);
		splay(R,null);
		root=R;
		re node* L=findRank(pos);
		splay(L,root);
		re node* p=L->ch[1];
		p->val=v;
		p->sum=v*p->size;
		p->ls=p->rs=p->ms=max(p->val,p->sum);
		p->upd=1;
		p->c=v;
		p->rev=0;
		pushUp(L);
		pushUp(root);
	}

	inline void tree::revArr(re int pos,re int len){
		re node* R=findRank(pos+len+1);
		splay(R,null);
		root=R;
		re node* L=findRank(pos);
		splay(L,root);
		reverse(L->ch[1]);
		pushUp(L);
		pushUp(root);
	}

	inline int tree::getSum(re int pos,re int len){
		re node* R=findRank(pos+len+1);
		splay(R,null);
		root=R;
		re node* L=findRank(pos);
		splay(L,root);
		return L->ch[1]->sum;
	}

	inline int tree::getMaxSum(){
		return root->ms;
	}

	inline void tree::check(){
		printf("Currently %d number(s):\n",root->size-2);
		printArr(root);
		puts("");
		printNode(root,0,root->size-1);
	}
}

int n,m;
spt::tree s;

int main(){
	cltstream::read(n);
	cltstream::read(m);
	s.insArr(0,n);
	for(re int i=1;i<=m;++i){
		for(re char c=cltstream::gc();c<'A'||c>'Z';c=cltstream::gc());
		cltstream::gc();
		re char opt=cltstream::gc();
		cltstream::gc();
		cltstream::gc();
		int x,y,z;
		switch(opt){
			case 'S':
				cltstream::read(x);
				cltstream::read(y);
				s.insArr(x,y);
				break;
			case 'L':
				cltstream::read(x);
				cltstream::read(y);
				s.delArr(x,y);
				break;
			case 'K':
				cltstream::read(x);
				cltstream::read(y);
				cltstream::read(z);
				s.modArr(x,y,z);
				break;
			case 'V':
				cltstream::read(x);
				cltstream::read(y);
				s.revArr(x,y);
				break;
			case 'T':
				cltstream::read(x);
				cltstream::read(y);
				cltstream::write(s.getSum(x,y),10);
				break;
			case 'X':
				cltstream::write(s.getMaxSum(),10);
				for(re char c=cltstream::gc();c!='\r'&&c!='\n';c=cltstream::gc());
				break;
		}
	}
	clop();
	return 0;
}
