// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#define re register
#define maxn 1000000
#define max(a,b) ((a)>=(b)?(a):(b))

int n,size,ec;
char s[maxn+5];
struct state{
	state *ch[26],*link;
	int len;
};
state mempool[2*maxn+1],*lst;
int des[2*maxn+1],suc[2*maxn+1],las[2*maxn+1],cnt[2*maxn+1];

inline void append(re int c){
	re state* p=lst;
	re state* cur=mempool+(++size);
	cur->len=p->len+1;
	cnt[size]=1;
	for(;p!=NULL&&p->ch[c]==NULL;p->ch[c]=cur,p=p->link);
	if(p==NULL)
		cur->link=mempool;
	else{
		re state* q=p->ch[c];
		if(q->len==p->len+1)
			cur->link=q;
		else{
			re state* clone=mempool+(++size);
			for(re int i=0;i<26;++i)
				clone->ch[i]=q->ch[i];
			clone->link=q->link;
			clone->len=p->len+1;
			q->link=cur->link=clone;
			for(;p!=NULL&&p->ch[c]==q;p->ch[c]=clone,p=p->link);
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
		cnt[cur]+=cnt[des[i]];
	}
}

int main(){
	size=0;
	lst=mempool;
	scanf("%s",s+1);
	n=strlen(s+1);
	for(re int i=1;i<=n;++i)
		append(s[i]-'a');
	for(re int i=0;i<=size;++i)
		if((mempool+i)->link!=NULL)
			connect((mempool+i)->link-mempool,i);
	dfs(0);
	re int ans=0;
	for(re int i=0;i<=size;++i)
		if(cnt[i]>1)
			ans=max(ans,cnt[i]*(mempool+i)->len);
	printf("%d",ans);
	return 0;
}
