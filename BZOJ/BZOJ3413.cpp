#include<cstdio>
#include<cstring>
#define re register
#define maxn 100000
#define maxsnt 200000
#define maxlog 40

int n,m,snt,lst,ec,vc;
char s[maxn+5];
int ch[maxsnt+1][10],link[maxsnt+1],len[maxsnt+1],fst[maxsnt+1];
int des[maxsnt+1],suc[maxsnt+1],las[maxsnt+1];
int root[maxsnt+1],lc[maxsnt*maxlog+1],rc[maxsnt*maxlog+1],sum[maxsnt*maxlog+1];

int update(re int L,re int cur,re int l,re int r){
	if(!cur)
		cur=++vc;
	if(l==r)
		++sum[cur];
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			lc[cur]=update(L,lc[cur],l,mid);
		else
			rc[cur]=update(L,rc[cur],mid+1,r);
		sum[cur]=sum[lc[cur]]+sum[rc[cur]];
	}
	return cur;
}

int getsum(re int L,re int R,re int cur,re int l,re int r){
	if(!cur)
		return 0;
	if(l>=L&&r<=R)
		return sum[cur];
	else{
		re int mid=(l+r)>>1,res=0;
		if(L<=mid)
			res+=getsum(L,R,lc[cur],l,mid);
		if(R>mid)
			res+=getsum(L,R,rc[cur],mid+1,r);
		return res;
	}
}

int merge(re int A,re int B,re int l,re int r){
	if(!A||!B)
		return A|B;
	else{
		re int p=++vc,mid=(l+r)>>1;
		lc[p]=merge(lc[A],lc[B],l,mid);
		rc[p]=merge(rc[A],rc[B],mid+1,r);
		sum[p]=sum[lc[p]]+sum[rc[p]];
		return p;
	}
}

inline void append(re int c){
	re int p=lst;
	re int cur=++snt;
	len[cur]=fst[cur]=len[p]+1;
	root[cur]=update(fst[cur],root[cur],1,n);
	for(;p!=-1&&!ch[p][c];ch[p][c]=cur,p=link[p]);
	if(p!=-1){
		re int q=ch[p][c];
		if(len[q]==len[p]+1)
			link[cur]=q;
		else{
			re int clone=++snt;
			for(re int i=0;i<10;++i)
				ch[clone][i]=ch[q][i];
			link[clone]=link[q];
			len[clone]=len[p]+1;
			fst[clone]=fst[q];
			link[q]=link[cur]=clone;
			for(;p!=-1&&ch[p][c]==q;ch[p][c]=clone,p=link[p]);
		}
	}
	lst=cur;
}

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs(re int cur){
	for(re int i=las[cur];i;i=suc[i]){
		dfs(des[i]);
		root[cur]=merge(root[cur],root[des[i]],1,n);
	}
}

inline int search(re char* s,re int len){
	re int cur=0;
	for(re int i=1;i<=len;++i)
		if(ch[cur][s[i]^48])
			cur=ch[cur][s[i]^48];
		else
			return n+1;
	return fst[cur]-len+1;
}

int main(){
	link[0]=-1;
	scanf("%d%s",&n,s+1);
	for(re int i=1;i<=n;++i)
		append(s[i]^48);
	for(re int i=1;i<=snt;++i)
		connect(link[i],i);
	dfs(0);
	scanf("%d",&m);
	for(re int i=1;i<=m;++i){
		scanf("%s",s+1);
		re int len=strlen(s+1),pos=search(s,len);
		re long long ans=pos-1;
		for(re int j=1,cur=0;j<=len;++j)
			if(ch[cur][s[j]^48]){
				cur=ch[cur][s[j]^48];
				ans+=getsum(1,pos+j-1,root[cur],1,n);
			}
			else
				break;
		printf("%lld\n",ans);
	}
	return 0;
}
