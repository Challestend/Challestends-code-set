#include<cstdio>
#define re register
#define maxn 600000
#define maxlog 24

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

int n,m,sum,ans;
int tmp[maxlog+1];
struct node{
	node *lc,*rc;
	int size;
};
node mempool[maxn*maxlog+1],*memtop,*root[maxn+1];

node* Insert(re node* L,re int dep){
	if(dep<=maxlog){
		re node* p=++memtop;
		p->size=L!=NULL?L->size+1:1;
		if(dep<maxlog){
			if(tmp[dep+1]^1){
				p->lc=Insert(L!=NULL?L->lc:NULL,dep+1);
				p->rc=L!=NULL?L->rc:NULL;
			}
			else{
				p->lc=L!=NULL?L->lc:NULL;
				p->rc=Insert(L!=NULL?L->rc:NULL,dep+1);
			}
		}
		return p;
	}
	else
		return NULL;
}

inline void getMaxSum(re node* L,re node* R){
	for(re int i=1;i<=maxlog;++i)
		if(tmp[i]){
			re int ln=L!=NULL&&L->lc!=NULL?L->lc->size:0,rn=R->lc!=NULL?R->lc->size:0;
			if(rn>ln){
				ans=ans<<1|1;
				L=L!=NULL?L->lc:NULL;
				R=R->lc;
			}
			else{
				ans=ans<<1;
				L=L!=NULL?L->rc:NULL;
				R=R->rc;
			}
		}
		else{
			re int ln=L!=NULL&&L->rc!=NULL?L->rc->size:0,rn=R->rc!=NULL?R->rc->size:0;
			if(rn>ln){
				ans=ans<<1|1;
				L=L!=NULL?L->rc:NULL;
				R=R->rc;
			}
			else{
				ans=ans<<1;
				L=L!=NULL?L->lc:NULL;
				R=R->lc;
			}
		}
}

int main(){
	root[0]=memtop=mempool;
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		int x;
		cltstream::read(x);
		for(re int j=maxlog,k=sum;j>=1;tmp[j]=k&1,k>>=1,--j);
		root[i]=Insert(root[i-1],0);
		sum^=x;
	}
	for(re int i=1;i<=m;++i){
		re char opt=cltstream::gc();
		for(;opt!='A'&&opt!='Q';opt=cltstream::gc());
		if(opt=='A'){
			int x;
			cltstream::read(x);
			for(re int j=maxlog,k=sum;j>=1;tmp[j]=k&1,k>>=1,--j);
			++n;
			root[n]=Insert(root[n-1],0);
			sum^=x;
		}
		else{
			int l,r,x;
			cltstream::read(l);
			cltstream::read(r);
			cltstream::read(x);
			for(re int j=maxlog,k=sum^x;j>=1;tmp[j]=k&1,k>>=1,--j);
			ans=0;
			getMaxSum(root[l-1],root[r]);
			cltstream::write(ans,10);
		}
	}
	clop();
	return 0;
}
