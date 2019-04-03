#include<cstdio>
#include<cstring>
#define re register
#define maxn 500000
#define maxsnt 2*maxn

int n,snt,lst,ec;
long long ans;
char s[maxn+5];
int ch[maxsnt+1][26],link[maxsnt+1],len[maxsnt+1];
int des[maxsnt+1],suc[maxsnt+1],las[maxsnt+1];
int size[maxsnt+1];

inline void append(re int c){
	re int p=lst;
	re int cur=++snt;
	len[cur]=len[p]+1;
	size[cur]=1;
	for(;p!=-1&&!ch[p][c];ch[p][c]=cur,p=link[p]);
	if(p==-1)
		link[cur]=0;
	else{
		re int q=ch[p][c];
		if(len[q]==len[p]+1)
			link[cur]=q;
		else{
			re int clone=++snt;
			for(re int i=0;i<26;++i)
				ch[clone][i]=ch[q][i];
			link[clone]=link[q];
			len[clone]=len[p]+1;
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
		ans-=2LL*len[cur]*size[cur]*size[des[i]];
		size[cur]+=size[des[i]];
	}
}

int main(){
	link[0]=-1;
	scanf("%s",s+1);
	n=strlen(s+1);
	ans=1LL*(n-1)*n*(n+1)/2;
	for(re int i=1;i<=n;++i)
		append(s[i]-'a');
	for(re int i=1;i<=snt;++i)
		connect(link[i],i);
	dfs(0);
	printf("%lld",ans);
	return 0;
}
