#include<cstdio>
#include<algorithm>
#define re register
#define maxn 80000
#define maxlog 18
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define swap(a,b) a^=b,b^=a,a^=b

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

int n,m,ec,vc;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int a[maxn+1],f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
struct SplayNode{
	SplayNode *ftr,*lc,*rc;
	int size,val;

	inline void pushUp(){
		size=1;
		if(lc!=NULL)
			size+=lc->size;
		if(rc!=NULL)
			size+=rc->size;
	}
};
SplayNode mep[2*maxn*maxlog+1],*met,*root[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur]){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			if(maxsize<size[des[i]]){
				maxsize=size[des[i]];
				hes[cur]=des[i];
			}
		}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	top[cur]=curtop;
	if(hes[cur]){
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
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

inline SplayNode* newNode(re int x){
	re SplayNode* p=++met;
	p->ftr=p->lc=p->rc=NULL;
	p->size=1;
	p->val=x;
	return p;
}

inline void Insert(re SplayNode*& rt,re int x){
	for(re SplayNode* p=rt;;)
		if(x>=p->val){
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
		if(x>=p->val){
			res=p;
			p=p->lc;
		}
		else
			p=p->rc;
	}
	splay(res,NULL);
	rt=res;
	return res;
}

inline void Delete(re SplayNode*& rt,re int x){
	re SplayNode* p=Find(rt,x);
	if(p->val==x){
		re SplayNode* q=p->lc;
		for(;q->rc!=NULL;q=q->rc);
		splay(q,p);
		rt=q;
		q->ftr=NULL;
		q->rc=p->rc;
		if(q->rc!=NULL)
			q->rc->ftr=q;
		q->rc->pushUp();
	}
}

inline int query(re int x,re int y){
	re int res=0;
	for(;x>=1;x-=x&(-x)){
		re SplayNode* p=Find(root[x],y);
		res+=p->lc->size-1;
	}
	return res;
}

inline int pthcnt(re int x,re int y){
	re int res=0;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=id[y]-id[top[y]]+1;
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return res+id[y]-id[x]+1;
}

inline int pthrnk(re int x,re int y,re int z){
	re int res=1;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=query(id[y],z)-query(id[top[y]]-1,z);
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return res+query(id[y],z)-query(id[x]-1,z);
}

int main(){
	met=mep;
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<n;++i){
		int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=n;++i){
		root[i]=newNode(1e8);
		root[i]->rc=newNode(0);
		root[i]->rc->ftr=root[i];
		root[i]->pushUp();
	}
	for(re int i=1;i<=n;++i)
		for(re int j=id[i];j<=n;j+=j&(-j))
			Insert(root[j],a[i]);
	for(re int i=1;i<=m;++i){
		int opt,x,y;
		cltstream::read(opt);
		cltstream::read(x);
		cltstream::read(y);
		if(!opt){
			for(re int j=id[x];j<=n;j+=j&(-j)){
				Delete(root[j],a[x]);
				Insert(root[j],y);
			}
			a[x]=y;
		}
		else
			if(pthcnt(x,y)>=opt){
				re int l=0,r=1e8;
				for(;l<r;){
					re int mid=(l+r)>>1;
					if(pthrnk(x,y,mid)<=opt)
						r=mid;
					else
						l=mid+1;
				}
				cltstream::write(l,10);
			}
			else{
				cltstream::pc('i');
				cltstream::pc('n');
				cltstream::pc('v');
				cltstream::pc('a');
				cltstream::pc('l');
				cltstream::pc('i');
				cltstream::pc('d');
				cltstream::pc(' ');
				cltstream::pc('r');
				cltstream::pc('e');
				cltstream::pc('q');
				cltstream::pc('u');
				cltstream::pc('e');
				cltstream::pc('s');
				cltstream::pc('t');
				cltstream::pc('!');
				cltstream::pc(10);
			}
	}
	clop();
	return 0;
}
