#include<cstdio>
#define re register
#define maxn 100
#define maxm 100
#define maxv 10005
#define maxe 70000
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

int n,m,ec,ans;
int a[maxn+1][maxm+1],ar[maxn+1][maxm+1],ac[maxn+1][maxm+1];
int s[maxn+1][maxm+1],sr[maxn+1][maxm+1],sc[maxn+1][maxm+1];
int des[(maxe<<1)+1],cap[(maxe<<1)+1],suc[(maxe<<1)+1],las[maxv+1];
int h[maxv+1],arc[maxv+1],dep[maxv+1],cnt[maxv+1],pre[maxv+1];

inline void connect(re int x,re int y,re int p){
	des[++ec]=y;
	cap[ec]=p;
	suc[ec]=las[x];
	las[x]=ec;
}

inline void isap(re int s,re int t){
	for(re int i=1;i<=t;++i){
		arc[i]=las[i];
		dep[i]=t;
	}
	dep[h[1]=t]=0;
	for(re int head=0,tail=1;head<tail;){
		re int x=h[++head];
		++cnt[dep[x]];
		for(re int i=arc[x];i;i=suc[i])
			if(cap[i^1]&&dep[des[i]]==t)
				dep[h[++tail]=des[i]]=dep[x]+1;
	}
	for(re int cur=s;dep[s]<t;){
		if(cur==t){
			re int res=2e9;
			for(re int tmp=t;tmp!=s;res=min(res,cap[pre[tmp]]),tmp=des[pre[tmp]^1]);
			ans-=res;
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
			if(--cnt[dep[cur]]){
				arc[cur]=las[cur];
				dep[cur]=t;
				for(re int i=arc[cur];i;i=suc[i])
					if(cap[i])
						dep[cur]=min(dep[cur],dep[des[i]]+1);
				++cnt[dep[cur]];
				if(cur!=s)
					cur=des[pre[cur]^1];
			}
			else
				break;
		}
	}
}

int main(){
	connect(0,0,0);
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			cltstream::read(a[i][j]);
			ans+=a[i][j];
		}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			cltstream::read(s[i][j]);
			ans+=s[i][j];
		}
	for(re int i=1;i<n;++i)
		for(re int j=1;j<=m;++j){
			cltstream::read(ar[i][j]);
			ans+=ar[i][j];
		}
	for(re int i=1;i<n;++i)
		for(re int j=1;j<=m;++j){
			cltstream::read(sr[i][j]);
			ans+=sr[i][j];
		}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<m;++j){
			cltstream::read(ac[i][j]);
			ans+=ac[i][j];
		}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<m;++j){
			cltstream::read(sc[i][j]);
			ans+=sc[i][j];
		}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			re int x=(i-1)*m+j;
			connect(n*m+1,x,s[i][j]<<1);
			connect(x,n*m+1,0);
			connect(x,n*m+2,a[i][j]<<1);
			connect(n*m+2,x,0);
		}
	for(re int i=1;i<n;++i)
		for(re int j=1;j<=m;++j){
			re int x=(i-1)*m+j,y=x+m;
			connect(n*m+1,x,sr[i][j]);
			connect(x,n*m+1,0);
			connect(n*m+1,y,sr[i][j]);
			connect(y,n*m+1,0);
			connect(x,n*m+2,ar[i][j]);
			connect(n*m+2,x,0);
			connect(y,n*m+2,ar[i][j]);
			connect(n*m+2,y,0);
			connect(x,y,ar[i][j]+sr[i][j]);
			connect(y,x,0);
			connect(y,x,ar[i][j]+sr[i][j]);
			connect(x,y,0);
		}
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<m;++j){
			re int x=(i-1)*m+j,y=x+1;
			connect(n*m+1,x,sc[i][j]);
			connect(x,n*m+1,0);
			connect(n*m+1,y,sc[i][j]);
			connect(y,n*m+1,0);
			connect(x,n*m+2,ac[i][j]);
			connect(n*m+2,x,0);
			connect(y,n*m+2,ac[i][j]);
			connect(n*m+2,y,0);
			connect(x,y,ac[i][j]+sc[i][j]);
			connect(y,x,0);
			connect(y,x,ac[i][j]+sc[i][j]);
			connect(x,y,0);
		}
	printf("%d %d\n",n,m);
	puts("FAQ");
	printf("%d %d\n",n,m);
	ans<<=1;
	isap(n*m+1,n*m+2);
	cltstream::write(ans>>1);
	clop();
	return 0;
}
