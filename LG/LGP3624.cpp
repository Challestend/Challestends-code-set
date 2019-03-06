#include<cstdio>
#define re register
#define maxn 20000
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

int n,ec,rt,sz,ans;
int des[(maxn<<1)+1],len[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int size[maxn+1],mxs[maxn+1],vis[maxn+1],h[3];

inline void connect(re int x,re int y,re int z){
	des[++ec]=y;
	len[ec]=z;
	suc[ec]=las[x];
	las[x]=ec;
}

inline void getRoot(re int cur,re int ftr){
	size[cur]=1;
	mxs[cur]=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			getRoot(des[i],cur);
			size[cur]+=size[des[i]];
			mxs[cur]=max(mxs[cur],size[des[i]]);
		}
	mxs[cur]=max(mxs[cur],sz-size[cur]);
	if(mxs[rt]>mxs[cur])
		rt=cur;
}

inline void cntDep(re int cur,re int ftr,re int val){
	++h[val];
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]])
			cntDep(des[i],cur,(val+len[i])%3);
}

inline int calc(re int cur,re int val){
	h[0]=h[1]=h[2]=0;
	cntDep(cur,0,val);
	return h[0]*h[0]+2*h[1]*h[2];
}

void solve(re int cur){
	vis[cur]=1;
	ans+=calc(cur,0);
	for(re int i=las[cur];i;i=suc[i])
		if(!vis[des[i]]){
			ans-=calc(des[i],len[i]);
			rt=0;
			sz=size[des[i]];
			getRoot(des[i],cur);
			solve(rt);
		}
}

inline int gcd(re int x,re int y){
	for(;y^=x^=y^=x%=y;);
	return x;
}

int main(){
	mxs[0]=2e9;
	cltstream::read(n);
	for(re int i=1;i<n;++i){
		int x,y,z;
		cltstream::read(x);
		cltstream::read(y);
		cltstream::read(z);
		connect(x,y,z%3);
		connect(y,x,z%3);
	}
	rt=0;
	sz=n;
	getRoot(1,0);
	solve(1);
	re int sum=n*n,g=gcd(ans,sum);
	cltstream::write(ans/g);
	cltstream::pc('/');
	cltstream::write(sum/g);
	clop();
}
