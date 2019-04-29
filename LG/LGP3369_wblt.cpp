#include<cstdio>
#include<algorithm>
#define re register

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

class WBLT{
	#define maxn 100000
	#define alpha 5

	int n;
	struct Node{
		Node *ftr,*lc,*rc;
		int val,size;

		inline void pushUp(){
			val=rc->val;
			size=lc->size+rc->size+1;
		}
	};
	Node mempool[2*maxn+1],*memtop,*null,*root;
	Node* rec[2*maxn+1];
	int rectop;

	inline Node* newNode(re int x){
		re Node* p=rectop?rec[rectop--]:++memtop;
		p->ftr=p->lc=p->rc=null;
		p->val=x;
		p->size=1;
		return p;
	}

	inline Node* merge(re Node* p,re Node* q){
		if(p->val>q->val)
			std::swap(p,q);
		re Node* r=newNode(q->val);
		r->lc=p;
		r->rc=q;
		p->ftr=q->ftr=r;
		r->pushUp();
		return r;
	}

	inline void rotate(re Node* p,re int dir){
		if(!dir){
			p->lc=merge(p->lc,p->rc->lc);
			rec[++rectop]=p->rc;
			p->rc=p->rc->rc;
		}
		else{
			p->rc=merge(p->rc,p->lc->rc);
			rec[++rectop]=p->lc;
			p->lc=p->lc->lc;
		}
		p->lc->ftr=p->rc->ftr=p;
		p->pushUp();
	}

	inline void maintain(re Node* p){
		if(p->rc->size>alpha*p->lc->size)
			rotate(p,0);
		else
			if(p->lc->size>alpha*p->rc->size)
				rotate(p,1);
		if(p->rc->size>alpha*p->lc->size)
			rotate(p->lc,1),rotate(p,0);
		else
			if(p->lc->size>alpha*p->rc->size)
				rotate(p->rc,0),rotate(p,1);
	}

	Node* insNode(re Node* p,re int x){
		if(p->size==1)
			p=merge(p,newNode(x));
		else{
			if(x<=p->lc->val){
				p->lc=insNode(p->lc,x);
				p->lc->ftr=p;
			}
			else{
				p->rc=insNode(p->rc,x);
				p->rc->ftr=p;
			}
			p->pushUp();
			maintain(p);
		}
		return p;
	}

	Node* delNode(re Node* p,re int x){
		if(x<=p->lc->val){
			if(p->lc->size==1)
				p=p->rc;
			else{
				p->lc=delNode(p->lc,x);
				p->lc->ftr=p;
				p->pushUp();
				maintain(p);
			}
		}
		else{
			if(p->rc->size==1)
				p=p->lc;
			else{
				p->rc=delNode(p->rc,x);
				p->rc->ftr=p;
				p->pushUp();
				maintain(p);
			}
		}
		return p;
	}

	inline void Insert(re int x){
		root=root==null?newNode(x):insNode(root,x);
	}

	inline void Delete(re int x){
		root=root->size==1?null:delNode(root,x);
	}

	inline int getRank(re int x){
		re int res=1;
		for(re Node* p=root;p!=null;){
			if(p->size==1)
				res+=x>p->val;
			if(x<=p->lc->val)
				p=p->lc;
			else{
				res+=(p->lc->size+1)>>1;
				p=p->rc;
			}
		}
		return res;
	}

	inline int findRank(re int x){
		for(re Node* p=root;p!=null;){
			if(x==((p->size+1)>>1))
				return p->val;
			if(x<=((p->lc->size+1)>>1))
				p=p->lc;
			else{
				x-=(p->lc->size+1)>>1;
				p=p->rc;
			}
		}
		return -1;
	}

	void print(re Node* p){
		if(p->size==1)
			printf("%d ",p->val);
		else
			print(p->lc),print(p->rc);
	}

	public:

	WBLT(){
		// freopen("C:\\Users\\Challestend\\Downloads\\104\\input8.in","r",stdin);
		// freopen("C:\\Users\\Challestend\\Downloads\\104\\clt.clt","w",stdout);
		null=memtop=mempool;
		null->ftr=null->lc=null->rc=null;
		root=null;
		cltstream::read(n);
		for(re int i=1;i<=n;++i){
			int opt,x;
			cltstream::read(opt);
			cltstream::read(x);
			switch(opt){
				case 1:
					Insert(x);
					break;
				case 2:
					Delete(x);
					break;
				case 3:
					cltstream::write(getRank(x),10);
					break;
				case 4:
					cltstream::write(findRank(x),10);
					break;
				case 5:
					cltstream::write(findRank(getRank(x)-1),10);
					break;
				case 6:
					cltstream::write(findRank(getRank(x+1)),10);
					break;
			}
			print(root);
			puts("");
		}
		clop();
	}
};
WBLT CLT;

int main(){
	return 0;
}
