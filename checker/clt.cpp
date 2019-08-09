#include<cstdio>
#include<algorithm>
#define re register
#define maxn 1000000
#define maxm 1000000
#define maxlog 20
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define swap(a,b) a^=b^=a^=b

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

int n,m,rt,ec,vc;
int p[maxn+1];
struct query{
	int id,l,r;
};
query q[maxm+1];

inline bool operator<(const query& p1,const query& p2){
	return p1.l<p2.l;
}

int st[maxn+1][maxlog+1],lg[maxn+1];
long long bit[maxn+1][2];
int des[2*maxn+1],suc[2*maxn+1],las[maxn+1],ch[maxn+1][2],low[maxn+1][2];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
long long depsum[maxn+2],cnt[maxn+2][2],ans[maxm+1];

inline int stmax(re int a,re int b){
	re int l=lg[b-a+1],x=st[a][l],y=st[b-(1<<l)+1][l];
	return p[x]>=p[y]?x:y;
}

inline void update(re int x,re int y){
	for(re int i=x;i<=n;i+=i&(-i)){
		bit[i][0]+=y;
		bit[i][1]+=1LL*x*y;
	}
}

inline long long getsum(re int x){
	re long long res=0;
	for(re int i=x;i>=1;i-=i&(-i))
		res+=(x+1)*bit[i][0]-bit[i][1];
	return res;
}

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void build(re int l,re int r,re int ftr,re int sd){
	if(l<=r){
		re int cur=stmax(l,r);
		connect(cur,ftr);
		connect(ftr,cur);
		ch[ftr][sd]=cur;
		low[cur][sd]=low[ftr][sd];
		low[cur][sd^1]=cur;
		build(l,cur-1,cur,0);
		build(cur+1,r,cur,1);
	}
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur]){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			if(maxsize<size[des[i]]){
				maxsize=size[des[i]];
				hes[cur]=des[i];
			}
		}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	top[cur]=curtop;
	if(hes[cur]){
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
}

inline void pthupd(re int x,re int y,re int z){
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		update(id[top[y]],z);
		update(id[y]+1,-z);
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	update(id[x],z);
	update(id[y]+1,-z);
}

inline long long pthsum(re int x,re int y){
	re long long res=0;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=getsum(id[y])-getsum(id[top[y]]-1);
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return res+getsum(id[y])-getsum(id[x]-1);
}

int main(){
	// freopen("data.in","r",stdin);
	// freopen("data.out","w",stdout);
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(p[i]);
		st[i][0]=i;
	}
	for(re int i=1;i<=m;++i)
		q[i].id=i;
	for(re int i=1;i<=m;++i)
		cltstream::read(q[i].l);
	for(re int i=1;i<=m;++i)
		cltstream::read(q[i].r);
	std::sort(q+1,q+m+1);
	for(re int j=1,k=1;k<=n;++j,k<<=1)
		for(re int i=1;i+(k<<1)-1<=n;++i)
			st[i][j]=p[st[i][j-1]]>=p[st[i+k][j-1]]?st[i][j-1]:st[i+k][j-1];
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	rt=stmax(1,n);
	low[rt][0]=low[rt][1]=rt;
	build(1,rt-1,rt,0);
	build(rt+1,n,rt,1);
	dfs1(rt,0);
	dfs2(rt,rt);
	for(re int i=n;i>=1;--i)
		depsum[i]=depsum[i+1]+(--dep[i]);
	for(re int i=1;i<=n;++i){
		// cnt[i][0]=cnt[i-1][0]+pthsum(i,rt)+getsum(id[i]+size[i]-1)-getsum(id[i]);
		update(id[i],1);
		update(id[i]+1,-1);
	}
	for(re int i=1;i<=n;++i)
		bit[i][0]=bit[i][1]=0;
	for(re int i=n;i>=1;--i){
		cnt[i][1]=cnt[i+1][1]+pthsum(i,rt)+getsum(id[i]+size[i]-1)-getsum(id[i]);
		update(id[i],1);
		update(id[i]+1,-1);
	}
	for(re int i=1;i<=n;++i){
		update(id[i],size[i]-1);
		update(id[i]+1,1-size[i]);
	}
	puts("");
	for(re int i=1;i<=n;++i)
		printf("%lld ",depsum[i]);
	puts("");
	for(re int i=1;i<=n;++i)
		printf("%lld ",cnt[i][0]);
	puts("");
	for(re int i=1;i<=n;++i)
		printf("%lld ",cnt[i][1]);
	puts("");
	for(re int k=1;k<=n;++k)
		printf("%lld ",getsum(id[k])-getsum(id[k]-1));
	puts("");
	for(re int i=1,j=1;i<=m;++i){
		for(;j<q[i].l;++j){
			pthupd(j,rt,-1);
			// re int v=getsum(id[j])-getsum(id[j]-1);
			// update(id[j],-v);
			// update(id[j]+1,v);
			for(re int k=1;k<=n;++k)
				printf("%lld ",getsum(id[k])-getsum(id[k]-1));
			puts("");
		}
		printf("%d %d\n",q[i].l,q[i].r);
		re int L=q[i].l-1,R=q[i].r+1;
		ans[q[i].id]=depsum[R]+cnt[L][0];
		printf("%lld ",ans[q[i].id]);
		for(re int k=R;k;k=f[low[low[k][0]][1]]){
			ans[q[i].id]+=getsum(id[low[k][0]]+size[low[k][0]]-1)-getsum(id[low[k][0]]-1);
			ans[q[i].id]-=getsum(id[ch[k][0]]+size[ch[k][0]]-1)-getsum(id[ch[k][0]]-1);
			printf("%lld ",ans[q[i].id]);
		}
		// ans[q[i].id]+=n-R+1;
		ans[q[i].id]-=cnt[R][1];
		printf("%lld ",ans[q[i].id]);
		ans[q[i].id]=getsum(n)-ans[q[i].id];
		printf("%lld\n",ans[q[i].id]);
	}
	for(re int i=1;i<=m;++i)
		cltstream::write(ans[i],32);
	clop();
	return 0;
}
