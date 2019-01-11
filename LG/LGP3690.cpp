#include<cstdio>
#define re register
#define maxn 300000

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

	template <typename _tp>
	inline void swap(_tp& x,_tp& y){
		_tp z=x;
		x=y;
		y=z;
	}
}

namespace spt{
	struct node{
		node* ftr;
		node* ch[2];
		int val,xorsum,rev;
	};

	struct tree{
		node mp[maxn+10];
		node* stk[maxn+10];

		int getSide(node*&);
		int isRoot(node*&);
		void reverse(node*&);
		void pushDown(node*&);
		void pushUp(node*&);
		void connect(node*&,node*&,int);
		void rotate(node*&);
		void splay(node*&);
	};

	inline int tree::getSide(re node*& p){
		return p->ftr->ch[1]==p;
	}

	inline int tree::isRoot(re node*& p){
		return p!=&mp[0]&&p->ftr->ch[0]!=p&&p->ftr->ch[1]!=p;
	}

	inline void tree::reverse(re node*& p){
		cltstream::swap(p->ch[0],p->ch[1]);
		p->rev^=1;
	}

	inline void tree::pushDown(re node*& p){
		if(p->rev){
			reverse(p->ch[0]);
			reverse(p->ch[1]);
			p->rev=0;
		}
	}

	inline void tree::pushUp(re node*& p){
		p->xorsum=p->ch[0]->xorsum^p->val^p->ch[1]->xorsum;
	}

	inline void tree::connect(re node*& x,re node*& y,re int sd){
		x->ftr=y;
		y->ch[sd]=x;
	}

	inline void tree::rotate(re node*& p){
		re int s1=getSide(p);
		re node* ptr=p->ftr;
		if(ptr->ftr!=&mp[0]){
			re int s2=getSide(ptr);
			re node* gtr=ptr->ftr;
			connect(p,gtr,s2);
		}
		connect(p->ch[s1^1],ptr,s1);
		connect(ptr,p,s1^1);
		pushUp(ptr);
		pushUp(p);
	}

	inline void tree::splay(re node*& x){
		re int top=0;
		stk[++top]=x;
		for(re node* y=x;!isRoot(y);y=y->ftr,stk[++top]=y);
		for(;top;pushDown(stk[top]),--top);
		for(;!isRoot(x);rotate(x)){
			re node* y=x->ftr;
			if(!isRoot(y))
				rotate((getSide(x)^getSide(y))?x:y);
		}
	}
}

namespace lct{
	int n,m;
	spt::tree st;

	inline void access(re spt::node*& x){
		for(re spt::node* y=&st.mp[0];x!=&st.mp[0];y=x,x=x->ftr){
			st.splay(x);
			x->ch[1]=y;
			st.pushUp(x);
		}
	}

	inline void makeRoot(re spt::node*& p){
		access(p);
		st.splay(p);
		st.reverse(p);
	}

	inline spt::node* findRoot(re spt::node*& p){
		access(p);
		st.splay(p);
		for(;p->ch[0]!=&st.mp[0];st.pushDown(p),p=p->ch[0]);
		st.splay(p);
		return p;
	}

	inline void split(re spt::node*& x,re spt::node*& y){
		makeRoot(x);
		access(y);
		st.splay(y);
	}

	inline void link(re spt::node*& x,re spt::node*& y){
		makeRoot(x);
		if(findRoot(y)==x)
			return;
		else
			x->ftr=y;
	}

	inline void cut(re spt::node*& x,re spt::node*& y){
		split(x,y);
		if(findRoot(y)==x&&y->ftr==x&&y->ch[0]==&st.mp[0]){
			x->ch[1]=y->ftr=&st.mp[0];
			st.pushUp(x);
		}
	}

	inline void main(){
		st.mp[0].ftr=st.mp[0].ch[0]=st.mp[0].ch[1]=&st.mp[0];
		cltstream::read(n);
		cltstream::read(m);
		for(re int i=1;i<=n;++i){
			st.mp[i].ftr=st.mp[i].ch[0]=st.mp[i].ch[1]=&st.mp[0];
			cltstream::read(st.mp[i].val);
			st.mp[i].xorsum=st.mp[i].val;
		}
		for(re int i=1;i<=m;++i){
			re int opt,_x,_y;
			cltstream::read(opt);
			cltstream::read(_x);
			cltstream::read(_y);
			re spt::node* x=&st.mp[_x];
			re spt::node* y;
			switch(opt){
				case 0:
					y=&st.mp[_y];
					split(x,y);
					cltstream::write(y->xorsum,10);
					break;
				case 1:
					y=&st.mp[_y];
					link(x,y);
					break;
				case 2:
					y=&st.mp[_y];
					cut(x,y);
					break;
				case 3:
					st.splay(x);
					x->xorsum^=x->val^_y;
					x->val=_y;
					break;
			}
		}
		clop();
	}
}

int main(){
	lct::main();
	return 0;
}
