#include<cstdio>
#include<algorithm>
#define re register
#define maxn 200000
#define maxm 500000
#define maxk 50
#define mod 998244353

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

int n,m,k;
int edge[maxn+1][2];

struct LinkCutTree{
	struct SplayNode{
		SplayNode *ftr,*lc,*rc;
		int val,cnt[maxk],ans,rev;

		inline int isRoot(){
			return ftr==NULL||(ftr->lc!=this&&ftr->rc!=this);
		}

		inline void reverse(){
			std::swap(lc,rc);
			rev^=1;
		}

		inline void pushDown(){
			if(rev){
				if(lc!=NULL)
					lc->reverse();
				if(rc!=NULL)
					rc->reverse();
				rev=0;
			}
		}

		inline void pushUp(){
			for(re int i=0;i<k;++i)
				cnt[i]=0;
			ans=0;
			for(re int i=0;i<k;++i){
				re int x=(k-i)%k,y=(2*k-i-val)%k;
				ans=(ans+1LL*(lc!=NULL?lc->cnt[i]:!i)*(rc!=NULL?rc->cnt[x]:!x)%mod)%mod;
				ans=(ans+1LL*(lc!=NULL?lc->cnt[i]:!i)*(rc!=NULL?rc->cnt[y]:!y)%mod)%mod;
			}
			for(re int i=0;i<k;++i)
				for(re int j=0;j<k;++j){
					cnt[(i+j)%k]=(cnt[(i+j)%k]+1LL*(lc!=NULL?lc->cnt[i]:!i)*(rc!=NULL?rc->cnt[j]:!j)%mod)%mod;
					cnt[(i+j+val)%k]=(cnt[(i+j+val)%k]+1LL*(lc!=NULL?lc->cnt[i]:!i)*(rc!=NULL?rc->cnt[j]:!j)%mod)%mod;
				}
		}
	};
	SplayNode mep[maxn+1];

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

	inline void splay(re SplayNode* p){
		for(;!p->isRoot();rotate(p))
			if(!p->ftr->isRoot())
				rotate((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
	}

	inline void access(re SplayNode* p){
		splay(p);
		p->pushDown();
		p->rc=NULL;
		p->pushUp();
		for(re SplayNode* q=p;q->ftr!=NULL;q=q->ftr){
			splay(q->ftr);
			q->ftr->pushDown();
			q->ftr->rc=q;
			q->ftr->pushUp();
		}
		splay(p);
	}

	inline void makeRoot(re SplayNode* p){
		access(p);
		p->reverse();
	}

	inline void split(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		access(q);
	}

	inline void link(re SplayNode* p,re SplayNode* q){
		makeRoot(p);
		p->ftr=q;
	}

	LinkCutTree(){
		cltstream::read(n);
		cltstream::read(k);
		for(re int i=1;i<n;++i){
			cltstream::read(edge[i][0]);
			cltstream::read(edge[i][1]);
		}
		for(re int i=1;i<=n;++i){
			(mep+i)->ftr=(mep+i)->lc=(mep+i)->rc=NULL;
			cltstream::read((mep+i)->val);
			(mep+i)->val%=k;
			(mep+i)->rev=0;
			(mep+i)->pushUp();
		}
		for(re int i=1;i<n;++i){
			link(mep+edge[i][0],mep+edge[i][1]);
		}
		cltstream::read(m);
		for(re int i=1;i<=m;++i){
			int x,y;
			cltstream::read(x);
			cltstream::read(y);
			split(mep+x,mep+y);
			cltstream::write((mep+y)->ans,10);
		}
		clop();
	}
};
LinkCutTree Cr;

int main(){
	return 0;
}
