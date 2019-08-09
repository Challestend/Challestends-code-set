#include<cstdio>
#include<algorithm>
#define re register
#define maxn 300000
#define mod 998244353
#define min(a,b) ((a)<=(b)?(a):(b))
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

int m;
struct SplayNode{
	int size,val,sum,add;
	SplayNode *ftr,*lc,*rc;
};
SplayNode mempool[maxn+1];

inline int isRoot(re SplayNode* p){
	return p->ftr==NULL||(p->ftr->lc!=p&&p->ftr->rc!=p);
}

inline void pushDown(re SplayNode* p){
	if(p->lc!=NULL){
		p->lc->val=(p->lc->val+p->add)%mod;
		p->lc->sum=(p->lc->sum+1LL*p->lc->size*p->add%mod)%mod;
		p->lc->add=(p->lc->add+p->add)%mod;
	}
	if(p->rc!=NULL){
		p->rc->val=(p->rc->val+p->add)%mod;
		p->rc->sum=(p->rc->sum+1LL*p->rc->size*p->add%mod)%mod;
		p->rc->add=(p->rc->add+p->add)%mod;
	}
	p->add=0;
}

inline void pushUp(re SplayNode* p){
	p->size=1;
	p->sum=p->val;
	if(p->lc!=NULL){
		p->size+=p->lc->size;
		p->sum=(p->sum+p->lc->sum)%mod;
	}
	if(p->rc!=NULL){
		p->size+=p->rc->size;
		p->sum=(p->sum+p->rc->sum)%mod;
	}
}

inline void rotate(re SplayNode* p){
	re SplayNode* q=p->ftr;
	pushDown(q);
	pushDown(p);
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
	pushUp(q);
	pushUp(p);
}

inline void splay(re SplayNode* p){
	for(;!isRoot(p);rotate(p))
		if(!isRoot(p->ftr))
			rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
}

inline void access(re SplayNode* p){
	pushDown(p);
	splay(p);
	p->rc=NULL;
	pushUp(p);
	for(re SplayNode* q=p;q->ftr!=NULL;){
		pushDown(q->ftr);
		splay(q->ftr);
		q->ftr->rc=q;
		pushUp(q->ftr);
		q=q->ftr;
	}
	splay(p);
}

inline SplayNode* LCA(re SplayNode* p,re SplayNode* q){
	pushDown(p);
	access(p);
	splay(q);
	q->rc=NULL;
	pushUp(q);
	for(p=q;p->ftr!=NULL;){
		pushDown(p->ftr);
		splay(p->ftr);
		p->ftr->rc=p;
		pushUp(p->ftr);
		p=p->ftr;
	}
	splay(q);
	return p;
}

inline void update(re SplayNode* p,re int x){
	access(p);
	p->val=(p->val+x)%mod;
	p->sum=(p->sum+1LL*p->size*x%mod)%mod;
	p->add=(p->add+x)%mod;
}

inline int query(re SplayNode* p){
	access(p);
	return p->sum;
}

int n,ec,rt,sz,cntsum,ans;
int des[2*maxn+1],suc[2*maxn+1],las[maxn+1],id[maxn+1];
int size[maxn+1],mxs[maxn+1],vis[maxn+1];
int cnt[maxn+1],stk[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void getRt(re int cur,re int ftr){
	size[cur]=1;
	mxs[cur]=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			getRt(des[i],cur);
			size[cur]+=size[des[i]];
			mxs[cur]=max(mxs[cur],size[des[i]]);
		}
	mxs[cur]=max(mxs[cur],sz-size[cur]);
	if(!rt||mxs[rt]>mxs[cur])
		rt=cur;
}

int calc(re int cur,re int ftr,re int root){
	stk[++stk[0]]=cur;
	re int res=0;
	cnt[cur]=1;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			res=(res+calc(des[i],cur,root))%mod;
			cnt[cur]+=cnt[des[i]];
		}
	ans=(ans+1LL*cnt[cur]*(query(mempool+id[cur])-cntsum+mod)%mod+mod)%mod;
	re SplayNode* x=LCA(mempool+id[cur],mempool+id[root]);
	access(x);
	re int dx=x->lc!=NULL?x->lc->size:0;
	return (res+1LL*cnt[cur]*dx%mod)%mod;
}

void divide(re int cur,re int ftr){
	vis[cur]=1;
	cntsum=0;
	for(re int i=las[cur],j=0;i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			re int tmp=calc(des[i],cur,cur);
			ans=(ans+1LL*(n-cnt[des[i]])*tmp%mod)%mod;
			for(;j<stk[0];++j,update(mempool+id[stk[j]],cnt[stk[j]]),cntsum=(cntsum+cnt[stk[j]])%mod);
		}
	for(;stk[0];update(mempool+id[stk[stk[0]]],mod-cnt[stk[stk[0]]]),--stk[0]);
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			rt=des[i];
			sz=size[des[i]];
			getRt(des[i],cur);
			divide(rt,cur);
		}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		int x;
		cltstream::read(x);
		if(x){
			connect(x,i);
			connect(i,x);
		}
	}
	for(re int i=1;i<=m;++i){
		pushUp(mempool+i);
		int x;
		cltstream::read(x);
		if(x)
			(mempool+i)->ftr=mempool+x;
	}
	for(re int i=0;i<=n;++i)
		cltstream::read(id[i]);
	rt=0;
	sz=n;
	getRt(1,0);
	divide(rt,0);
	cltstream::write(ans);
	clop();
	return 0;
}
