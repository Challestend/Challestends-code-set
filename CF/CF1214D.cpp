#include<cstdio>
#define re register
#define maxn 1000000
#define maxv 2000000
#define maxe 6000000
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

int n,m,ec;
int a[maxn+1];
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
		// printf("%d\n",x);
		for(re int i=arc[x];i;i=suc[i])
			if(cap[i^1]&&dep[des[i]]==mx)
				// printf("%d -> %d\n",des[i],x),
				dep[h[++tail]=des[i]]=dep[x]+1;
	}
	// printf("DEP(S)=%d\n",dep[s]);
	for(re int cur=s;dep[s]<mx;){
		// printf("CUR=%d\n",cur);
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
				// printf("%d -> %d\n",cur,des[i]);
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
	cltstream::read(m);
	for(re int i=1;i<=n*m;++i){
		re char c=cltstream::gc();
		for(;c!='.'&&c!='#';c=cltstream::gc());
		a[i]=(c=='.');
	}
	for(re int i=2;i<n*m;++i){
		// printf("%d %d\n",i,n*m+i);
		connect(i,n*m+i,1);
		connect(n*m+i,i,0);
	}
	for(re int i=0;i<n;++i)
		for(re int j=0;j<m-1;++j){
			if(a[i*m+j+1]&a[i*m+j+2]){
				// printf("%d %d\n",n*m+i*m+j+1,i*m+j+2);
				connect(n*m+i*m+j+1,i*m+j+2,1);
				connect(i*m+j+2,n*m+i*m+j+1,0);
			}
		}
	for(re int i=0;i<n-1;++i)
		for(re int j=0;j<m;++j){
			if(a[i*m+j+1]&a[(i+1)*m+j+1]){
				// printf("%d %d\n",n*m+i*m+j+1,(i+1)*m+j+1);
				connect(n*m+i*m+j+1,(i+1)*m+j+1,1);
				connect((i+1)*m+j+1,n*m+i*m+j+1,0);
			}
		}
	cltstream::write(isap(n*m+1,n*m,2*n*m));
	clop();
	return 0;
}
