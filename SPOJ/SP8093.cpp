#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define maxn 10000
#define maxm 60000
#define maxlen 500000
#define maxlog 20
#define min(a,b) ((a)<=(b)?(a):(b))
#define stmin(a,b) ((a)<=(b)?min(het[(a)][lg[(b)-(a)+1]],het[(b)-(1<<lg[(b)-(a)+1])+1][lg[(b)-(a)+1]]):maxlen)

int n,m,len,mx;
char s[maxlen+5];
int lg[maxlen+1],lp[maxn+maxm+1],rp[maxn+maxm+1];
int fst[maxlen+1],snd[2*maxlen+1],tak[maxlen+1];
int sa[maxlen+1],rnk[maxlen+1],het[maxlen+1][maxlog+1];
int col[maxlen+1],lst[maxn+1],nxt[maxlen+1],bit[maxlen+1],ans[maxm+1];
struct Query{
	int t,l,r;
};
Query q[maxm+1];

inline bool operator<(const Query& p1,const Query& p2){
	return p1.l<p2.l;
}

inline void update(re int x,re int y){
	for(;x<=len;x+=x&(-x))
		bit[x]+=y;
}

inline int getsum(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit[x];
	return res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(re int i=1;i<=n+m;++i){
		scanf("%s",s+len+1);
		lp[i]=len+1;
		len+=strlen(s+len+1);
		s[++len]=32;
		rp[i]=len-1;
	}
	for(re int i=2;i<=len;++i)
		lg[i]=lg[i>>1]+1;
	mx=255;
	for(re int i=1;i<=len;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=mx;++i)
		tak[i]+=tak[i-1];
	for(re int i=len;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=len-k+1;i<=len;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=len;++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=len;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=len;i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=len;++i)
			snd[i]=fst[i];
		cnt=1;
		fst[sa[1]]=1;
		for(re int i=2;i<=len;++i)
			fst[sa[i]]=snd[sa[i]]==snd[sa[i-1]]&&snd[sa[i]+k]==snd[sa[i-1]+k]?cnt:++cnt;
		if(cnt==len)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=len;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=len;++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=len&&pos+j<=len&&s[i+j]==s[pos+j];++j);
			het[rnk[i]][0]=j;
		}
	for(re int j=1,k=1;j<=lg[len];++j,k<<=1)
		for(re int i=1;i+(k<<1)-1<=len;++i)
			het[i][j]=min(het[i][j-1],het[i+k][j-1]);
	for(re int i=1;i<=n;++i)
		for(re int j=lp[i];j<=rp[i];++j)
			col[rnk[j]]=i;
	for(re int i=1;i<=len;++i)
		if(col[i]){
			if(!lst[col[i]])
				update(i,1);
			else
				nxt[lst[col[i]]]=i;
			lst[col[i]]=i;
		}
	for(re int i=1;i<=m;++i){
		q[i].t=i;
		re int L=1,R=rnk[lp[n+i]];
		for(;L<R;){
			re int mid=(L+R)>>1;
			if(stmin(mid+1,rnk[lp[n+i]])>=rp[n+i]-lp[n+i]+1)
				R=mid;
			else
				L=mid+1;
		}
		q[i].l=L;
		L=rnk[lp[n+i]],R=len;
		for(;L<R;){
			re int mid=(L+R+1)>>1;
			if(stmin(rnk[lp[n+i]]+1,mid)>=rp[n+i]-lp[n+i]+1)
				L=mid;
			else
				R=mid-1;
		}
		q[i].r=L;
	}
	std::sort(q+1,q+m+1);
	for(re int i=1,j=1;i<=m;++i){
		for(;j<q[i].l;++j){
			if(col[j])
				update(j,-1);
			if(nxt[j])
				update(nxt[j],1);
		}
		ans[q[i].t]=getsum(q[i].r);
	}
	for(re int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
