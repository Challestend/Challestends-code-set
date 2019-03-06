#include<cstdio>
#include<algorithm>
#define re register
#define maxn 50000
#define maxlog 36

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
int a[maxn+1];
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
SplayNode mep[maxn*maxlog+1],*met,*rec[maxn*maxlog+1],*root[(maxn<<2)+1];
int rectop;

inline SplayNode* newNode(re int x){
	re SplayNode* p=rectop?rec[rectop--]:++met;
	p->ftr=p->lc=p->rc=NULL;
	p->cnt=p->size=p->sum=1;
	p->val=x;
	return p;
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

inline void splay(re SplayNode* p,re SplayNode* q){
	for(;p->ftr!=q;rotate(p))
		if(p->ftr->ftr!=q)
			rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
}

inline void Insert(re SplayNode*& rt,re int x){
	for(re SplayNode* p=rt;;)
		if(x==p->val){
			++p->cnt;
			splay(p,NULL);
			rt=p;
			break;
		}
		else
			if(x<p->val){
				if(p->lc==NULL){
					p->lc=newNode(x);
					p->lc->ftr=p;
					p=p->lc;
					splay(p,NULL);
					rt=p;
					break;
				}
				else
					p=p->lc;
			}
			else{
				if(p->rc==NULL){
					p->rc=newNode(x);
					p->rc->ftr=p;
					p=p->rc;
					splay(p,NULL);
					rt=p;
					break;
				}
				else
					p=p->rc;
			}
}

inline SplayNode* Find(re SplayNode*& rt,re int x){
	re SplayNode* res=NULL;
	for(re SplayNode* p=rt;p!=NULL;){
		if(x<=p->val)
			res=p;
		if(x==p->val)
			break;
		else
			if(x<p->val)
				p=p->lc;
			else
				p=p->rc;
	}
	splay(res,NULL);
	rt=res;
	return res;
}

inline void Delete(re SplayNode*& rt,re int x){
	re SplayNode* p=Find(rt,x);
	if(p->cnt){
		--p->cnt;
		--p->sum;
	}
	else{
		re SplayNode* q=p->lc;
		for(;q->rc!=NULL;q=q->rc);
		splay(q,p);
		rt=q;
		q->ftr=NULL;
		q->rc=p->rc;
		if(q->rc!=NULL)
			q->rc->ftr=q;
		q->pushUp();
		rec[++rectop]=p;
	}
}

void buildSegment(re int cur,re int l,re int r){
	root[cur]=newNode(-2147483647);
	root[cur]->rc=newNode(2147483647);
	root[cur]->rc->ftr=root[cur];
	root[cur]->pushUp();
	for(re int i=l;i<=r;++i)
		Insert(root[cur],a[i]);
	if(l<r){
		re int mid=(l+r)>>1;
		buildSegment(cur<<1,l,mid);
		buildSegment(cur<<1|1,mid+1,r);
	}
}

int queryRank(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R){
		re SplayNode* p=Find(root[cur],x);
		return p->lc->sum-1;
	}
	else{
		re int mid=(l+r)>>1,res=0;
		if(L<=mid)
			res+=queryRank(L,R,x,cur<<1,l,mid);
		if(R>mid)
			res+=queryRank(L,R,x,cur<<1|1,mid+1,r);
		return res;
	}
}

inline int queryValue(re int L,re int R,re int k){
	if(k<1)
		return -2147483647;
	if(k>R-L+1)
		return 2147483647;
	re int l=0,r=1e8;
	for(;l<r;){
		re int mid=(l+r+1)>>1;
		if(queryRank(L,R,mid,1,1,n)+1<=k)
			l=mid;
		else
			r=mid-1;
	}
	return l;
}

void modifyValue(re int L,re int x,re int cur,re int l,re int r){
	Delete(root[cur],a[L]);
	Insert(root[cur],x);
	if(l<r){
		re int mid=(l+r)>>1;
		if(L<=mid)
			modifyValue(L,x,cur<<1,l,mid);
		else
			modifyValue(L,x,cur<<1|1,mid+1,r);
	}
}

int main(){
	met=mep;
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	buildSegment(1,1,n);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x;
		cltstream::read(opt);
		switch(opt){
			case 1:
				cltstream::read(l);
				cltstream::read(r);
				cltstream::read(x);
				cltstream::write(queryRank(l,r,x,1,1,n)+1,10);
				break;
			case 2:
				cltstream::read(l);
				cltstream::read(r);
				cltstream::read(x);
				cltstream::write(queryValue(l,r,x),10);
				break;
			case 3:
				cltstream::read(l);
				cltstream::read(x);
				modifyValue(l,x,1,1,n);
				a[l]=x;
				break;
			case 4:
				cltstream::read(l);
				cltstream::read(r);
				cltstream::read(x);
				cltstream::write(queryValue(l,r,queryRank(l,r,x,1,1,n)),10);
				break;
			case 5:
				cltstream::read(l);
				cltstream::read(r);
				cltstream::read(x);
				cltstream::write(queryValue(l,r,queryRank(l,r,x+1,1,1,n)+1),10);
				break;
		}
	}
	clop();
	return 0;
}
