#include<cstdio>
#define re register
#define maxn 5000
#define maxv 10002
#define maxe 5000000
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

int n,ans,ec;
int a[maxn+1],b[maxn+1],w[maxn+1],l[maxn+1],r[maxn+1],p[maxn+1];
int des[2*maxe+1],cap[2*maxe+1],suc[2*maxe+1],las[maxv+1];
int h[maxv+1],arc[maxv+1],dep[maxv+1],cnt[maxv+1],pre[maxv+1];

inline void connect(re int x,re int y,re int p){
	des[++ec]=y;
	cap[ec]=p;
	suc[ec]=las[x];
	las[x]=ec;
}

inline int isap(re int s,re int t,re int mx){
	re int ans=0;
	for(re int i=1;i<=mx;++i){
		arc[i]=las[i];
		dep[i]=mx;
	}
	dep[h[1]=t]=0;
	for(re int head=0,tail=1;head<tail;){
		re int x=h[++head];
		++cnt[dep[x]];
		for(re int i=arc[x];i;i=suc[i])
			if(cap[i^1]&&dep[des[i]]==mx)
				dep[h[++tail]=des[i]]=dep[x]+1;
	}
	for(re int cur=s;dep[s]<mx;){
		if(cur==t){
			re int res=1E9;
			for(re int tmp=t;tmp!=s;res=min(res,cap[pre[tmp]]),tmp=des[pre[tmp]^1]);
			ans+=res;
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
			arc[cur]=las[cur];
			dep[cur]=mx;
			for(re int i=arc[cur];i;i=suc[i])
				if(cap[i])
					dep[cur]=min(dep[cur],dep[des[i]]+1);
			++cnt[dep[cur]];
			if(cur!=s)
				cur=des[pre[cur]^1];
		}
	}
	return ans;
}

int main(){
	connect(0,0,0);
	cltstream::read(n);
	int s=2*n+1,t=2*n+2;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		cltstream::read(b[i]);
		cltstream::read(w[i]);
		cltstream::read(l[i]);
		cltstream::read(r[i]);
		cltstream::read(p[i]);
		ans+=w[i]+b[i];
		connect(i,t,b[i]);
		connect(t,i,0);
		connect(s,i,w[i]);
		connect(i,s,0);
		connect(n+i,i,p[i]);
		connect(i,n+i,0);
	}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<i;++j)
			if(a[j]>=l[i]&&a[j]<=r[i]){
				connect(j,n+i,2E9);
				connect(n+i,j,0);
			}
	cltstream::write(ans-isap(s,t,t));
	clop();
	return 0;
}
