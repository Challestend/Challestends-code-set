#include<cstdio>
#include<cstring>
#define re register
#define maxn 500000
#define maxsnt 2*maxn

int n,t,k,snt,lst,ec;
char s[maxn+5];
int ch[maxsnt+1][26],link[maxsnt+1],len[maxsnt+1];
int des[maxsnt+1],suc[maxsnt+1],las[maxsnt+1],cnt[maxsnt+1];
int ind[maxsnt+1],h[maxsnt+1],ans[maxsnt+1];

inline void append(re int c){
	re int p=lst;
	re int cur=++snt;
	len[cur]=len[p]+1;
	cnt[cur]=1;
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
		cnt[cur]+=cnt[des[i]];
	}
}

int main(){
	link[0]=-1;
	scanf("%s",s+1);
	n=strlen(s+1);
	scanf("%d%d",&t,&k);
	for(re int i=1;i<=n;++i)
		append(s[i]-'a');
	for(re int i=1;i<=snt;++i)
		connect(link[i],i);
	dfs(0);
	for(re int i=0;i<=snt;++i)
		for(re int j=0;j<26;++j)
			if(ch[i][j])
				++ind[ch[i][j]];
	re int head=-1,tail=-1;
	for(re int i=0;i<=snt;++i)
		if(!ind[i])
			h[++tail]=i;
	for(;head<tail;){
		re int x=h[++head];
		for(re int i=0;i<26;++i)
			if(ch[x][i]){
				--ind[ch[x][i]];
				if(!ind[ch[x][i]])
					h[++tail]=ch[x][i];
			}
	}
	for(re int i=snt;i>=0;--i){
		cnt[h[i]]=!t?1:cnt[h[i]];
		ans[h[i]]=cnt[h[i]];
		for(re int j=0;j<26;++j)
			if(ch[h[i]][j])
				ans[h[i]]+=ans[ch[h[i]][j]];
	}
	if(k>ans[0]-cnt[0])
		printf("-1");
	else
		for(re int cur=0;k;k-=cnt[cur])
			for(re int j=0;j<26;++j)
				if(ch[cur][j]){
					if(k>ans[ch[cur][j]])
						k-=ans[ch[cur][j]];
					else{
						putchar('a'+j);
						cur=ch[cur][j];
						break;
					}
				}
	return 0;
}
