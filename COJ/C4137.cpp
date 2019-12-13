#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
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

int n,m;
int p[2][maxn+1],a[maxn+1];
struct node{
	node *ftr,*lc,*rc;
	int size,id,val,sum,add;

	inline void pushDown(){
		if(lc!=NULL){
			lc->id+=add;
			if(add>0)
				lc->sum=1LL*lc->sum*p[0][add]%mod;
			else
				lc->sum=1LL*lc->sum*p[1][-add]%mod;
		}
		if(rc!=NULL){
			rc->id+=add;
			if(add>0)
				rc->sum=1LL*rc->sum*p[0][add]%mod;
			else
				rc->sum=1LL*rc->sum*p[1][-add]%mod;
		}
	}

	inline void pushUp(){
		size=1;
		sum=1LL*p[0][id]*val%mod;
		if(lc!=NULL){
			size+=lc->size;
			sum=(sum+lc->sum)%mod;
		}
		if(rc!=NULL){
			size+=rc->size;
			sum=(sum+rc->sum)%mod;
		}
	}
};
node mem[maxn+1],*root;

inline void rotate(re node* p){
	re node* q=p->ftr;
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

inline void splay(re node* p,re node* q){
	for(;p->ftr!=q;rotate(p))
		if((p->ftr->ftr->lc==p->ftr)==(p->ftr->lc==p)?p->ftr:p);
	if(q==NULL)
		root=p;
}

node* build(re int l,re int r){
	if(l==r){
		(mem+l)->size=1;
		(mem+l)->id=l-1;
		(mem+l)->val=a[l];
		(mem+l)->sum=1LL*p[0][l-1]*a[l]%mod;
		(mem+l)->add=0;
		return mem+l;
	}
	else{
		re int mid=(l+r)>>1;
		(mem+mid)->lc=build(l,mid);
		(mem+mid)->rc=build(mid+1,r);
		(mem+mid)->lc->ftr=(mem+mid)->rc->ftr=mem+mid;
		(mem+mid)->id=mid-1;
		(mem+mid)->val=a[mid];
		(mem+mid)->add=0;
		(mem+mid)->pushUp();
		return mem+mid;
	}
}

int main(){
	cltstream::read(n);
	p[0][0]=p[1][0]=1;
	for(re int i=1;i<=n;++i){
		p[0][i]=249561089LL*p[0][i-1]%mod;
		p[1][i]=332748119LL*p[1][i-1]%mod;
		cltstream::read(a[i]);
	}
	std::sort(a+1,a+n+1);
	build(1,n);
	cltstream::read(m);
}
