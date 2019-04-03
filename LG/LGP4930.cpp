#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))
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

int n,m,ec,rt,sz,top;
long long ans;
int des[2*maxn+1],len[2*maxn+1],suc[2*maxn+1],las[maxn+1];
int size[maxn+1],mxs[maxn+1],vis[maxn+1];
int tmp[2*maxn+1],cnt[2*maxn+1][2];
std::pair<int,int> stk[maxn+1];

inline void connect(re int x,re int y,re int z){
	des[++ec]=y;
	len[ec]=z;
	suc[ec]=las[x];
	las[x]=ec;
}

void getRoot(re int cur,re int ftr){
	size[cur]=1;
	mxs[cur]=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			getRoot(des[i],cur);
			size[cur]+=size[des[i]];
			mxs[cur]=max(mxs[cur],size[des[i]]);
		}
	mxs[cur]=max(mxs[cur],sz-size[cur]);
	if(!rt||mxs[cur]<mxs[rt])
		rt=cur;
}

void calc(re int cur,re int ftr,re int val){
	ans+=tmp[n+val]?cnt[n-val][0]+cnt[n-val][1]:cnt[n-val][1];
	stk[++top]=std::make_pair(val,tmp[n+val]>0);
	++tmp[n+val];
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]])
			calc(des[i],cur,val+len[i]);
	--tmp[n+val];
}

void divide(re int cur){
	vis[cur]=1;
	for(re int i=las[cur],j=0;i;i=suc[i])
		if(!vis[des[i]]){
			calc(des[i],0,len[i]);
			for(;j<top;++j,++cnt[n+stk[j].first][stk[j].second]);
		}
	for(;top;--cnt[n+stk[top].first][stk[top].second],--top);
	for(re int i=las[cur];i;i=suc[i])
		if(!vis[des[i]]){
			rt=0;
			sz=size[des[i]];
			getRoot(des[i],cur);
			divide(rt);
		}
}

int main(){
	freopen("C:\\Users\\Challestend\\Downloads\\testdata(2).in","r",stdin);
	cltstream::read(n);
	for(re int i=1;i<n;++i){
		int x,y,z;
		cltstream::read(x);
		cltstream::read(y);
		cltstream::read(z);
		connect(x,y,z-!z);
		connect(y,x,z-!z);
	}
	++tmp[n];
	rt=0;
	sz=n;
	getRoot(1,0);
	divide(rt);
	cltstream::write(ans);
	clop();
	return 0;
}
