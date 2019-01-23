#include<cstdio>
#define re register
#define maxvc 400
#define maxec 20300
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

int n,p,q,s,t,ec;
int des[maxec+1],cap[maxec+1],suc[maxec+1],las[maxvc+1];
int h[maxvc+1],arc[maxvc+1],dep[maxvc+1],cnt[maxvc+1],pre[maxvc+1];

inline void connect(re int x,re int y,re int ca){
	des[++ec]=y;
	cap[ec]=ca;
	suc[ec]=las[x];
	las[x]=ec;
}

inline int isap(re int s,re int t){
	re int mf=0;
	for(re int i=1;i<=t;++i){
		arc[i]=las[i];
		dep[i]=t;
	}
	dep[h[1]=t]=0;
	for(re int head=0,tail=1;head<tail;){
		re int x=h[++head];
		++cnt[dep[x]];
		for(re int i=las[x];i;i=suc[i])
			if(cap[i^1]&&dep[des[i]]==t)
				dep[h[++tail]=des[i]]=dep[x]+1;
	}
	for(re int cur=s;dep[s]<t;){
		if(cur==t){
			re int res=2e9;
			for(re int tmp=t;tmp!=s;res=min(res,cap[pre[tmp]]),tmp=des[pre[tmp]^1]);
			mf+=res;
			for(re int tmp=t;tmp!=s;cap[pre[tmp]]-=res,cap[pre[tmp]^1]+=res,tmp=des[pre[tmp]^1]);
			cur=s;
		}
		re int f=0;
		for(re int i=arc[cur];i;i=suc[i])
			if(cap[i]&&dep[des[i]]<dep[cur]){
				f=1;
				arc[cur]=i;
				pre[cur=des[i]]=i;
				break;
			}
		if(!f){
			if(!(--cnt[dep[cur]]))
				break;
			else{
				arc[cur]=las[cur];
				re int mind=t-1;
				for(re int i=las[cur];i;i=suc[i])
					if(cap[i]&&dep[des[i]]<mind)
						mind=dep[des[i]];
				++cnt[dep[cur]=mind+1];
				if(cur!=s)
					cur=des[pre[cur]^1];
			}
		}
	}
	return mf;
}

int main(){
	connect(0,0,0);
	cltstream::read(n);
	cltstream::read(p);
	cltstream::read(q);
	s=(n<<1)+p+q+1;
	t=s+1;
	for(re int i=1;i<=n;++i){
		connect(i,n+i,1);
		connect(n+i,i,0);
	}
	for(re int i=1;i<=p;++i){
		connect(s,(n<<1)+i,1);
		connect((n<<1)+i,s,0);
	}
	for(re int i=1;i<=q;++i){
		connect((n<<1)+p+i,t,1);
		connect(t,(n<<1)+p+i,0);
	}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=p;++j){
			re int x;
			cltstream::read(x);
			if(x){
				connect((n<<1)+j,i,1);
				connect(i,(n<<1)+j,0);
			}
		}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=q;++j){
			re int x;
			cltstream::read(x);
			if(x){
				connect(n+i,(n<<1)+p+j,1);
				connect((n<<1)+p+j,n+i,0);
			}
		}
	cltstream::write(isap(s,t));
	clop();
	return 0;
}
