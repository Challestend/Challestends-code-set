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

int n,m;
int C[11][11];
unsigned a[maxn+5],u[11];
struct SplayTree{
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int size,id,upd;
		unsigned val,sum[11];

		inline void untitledFunction(re int x){
			id+=x;
			upd+=x;
			u[0]=1;
			for(re int i=1;i<=10;++i)
				u[i]=u[i-1]*x;
			for(re int i=10;i>=0;--i)
				for(re int j=0;j<i;++j)
					sum[i]+=C[i][j]*sum[j]*u[i-j];
		}

		inline void pushDown(){
			if(upd){
				if(lc!=NULL)
					lc->untitledFunction(upd);
				if(rc!=NULL)
					rc->untitledFunction(upd);
				upd=0;
			}
		}

		inline void pushUp(){
			size=1;
			sum[0]=val;
			for(re int i=1;i<=10;++i)
				sum[i]=sum[i-1]*id;
			if(lc!=NULL){
				size+=lc->size;
				for(re int i=0;i<=10;++i)
					sum[i]+=lc->sum[i];
			}
			if(rc!=NULL){
				size+=rc->size;
				for(re int i=0;i<=10;++i)
					sum[i]+=rc->sum[i];
			}
		}
	};
	SplayNode mempool[maxn+5],*memtop,*root;

	inline SplayNode* newNode(re int id,re unsigned val){
		re SplayNode* p=++memtop;
		p->ftr=p->lc=p->rc=NULL;
		p->size=1;
		p->id=id;
		p->upd=0;
		p->val=p->sum[0]=val;
		for(re int i=1;i<=10;++i)
			p->sum[i]=p->sum[i-1]*p->id;
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
		re SplayNode* p=newNode(mid-1,a[mid]);
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

	SplayNode* findRank(re int x){
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

	inline void I(){
		int pos;
		unsigned val;
		cltstream::read(pos);
		cltstream::read(val);
		re SplayNode* L=findRank(pos+1);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+2);
		splay(R,L);
		R->untitledFunction(1);
		R->pushDown();
		R->lc=newNode(pos+1,val);
		R->lc->ftr=R;
		R->pushUp();
		L->pushUp();
	}

	inline void D(){
		int pos;
		cltstream::read(pos);
		++pos;
		re SplayNode* L=findRank(pos+1);
		splay(L,NULL);
		re SplayNode* R=findRank(pos+2);
		splay(R,L);
		R->untitledFunction(-1);
		R->pushDown();
		R->ftr=NULL;
		R->lc=L->lc;
		R->lc->ftr=R;
		R->pushUp();
		root=R;
	}

	inline void R(){
		int pos;
		unsigned val;
		cltstream::read(pos);
		++pos;
		cltstream::read(val);
		re SplayNode* L=findRank(pos+1);
		splay(L,NULL);
		L->val=val;
		L->pushUp();
	}

	inline void Q(){
		int l,r,k;
		cltstream::read(l);
		++l;
		cltstream::read(r);
		++r;
		cltstream::read(k);
		re SplayNode* L=findRank(l);
		splay(L,NULL);
		re SplayNode* R=findRank(r+2);
		splay(R,L);
		u[0]=1;
		for(re int i=1;i<=10;++i)
			u[i]=u[i-1]*(1-l);
		re unsigned ans=0;
		for(re int i=0;i<=k;++i)
			ans+=C[k][i]*R->lc->sum[i]*u[k-i];
		cltstream::write(ans,10);
	}

	void print(re SplayNode* p){
		p->pushDown();
		printf("%d %d %d %d\n",p->id,p->ftr!=NULL?p->ftr->id:-1,p->lc!=NULL?p->lc->id:-1,p->rc!=NULL?p->rc->id:-1);
		if(p->lc!=NULL)
			print(p->lc);
		if(p->rc!=NULL)
			print(p->rc);
	}

	SplayTree(){
		memtop=mempool;
		for(re int i=0;i<=10;++i){
			C[i][0]=C[i][i]=1;
			for(re int j=1;j<i;++j)
				C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
		cltstream::read(n);
		for(re int i=1;i<=n;++i)
			cltstream::read(a[i+1]);
		root=build(1,n+2);
		cltstream::read(m);
		for(re int i=1;i<=m;++i){
			re char opt=cltstream::gc();
			for(;opt!='I'&&opt!='D'&&opt!='R'&&opt!='Q';opt=cltstream::gc());
			switch(opt){
				case 'I':
					I();
					break;
				case 'D':
					D();
					break;
				case 'R':
					R();
					break;
				case 'Q':
					Q();
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
