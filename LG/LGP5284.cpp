#include<cstdio>
#include<cstring>
#define re register
#define maxn 200000
#define max(a,b) ((a)>=(b)?(a):(b))

int T,n,vc,lst,na,nb,m,ec;
char str[maxn+5];
int l[2*maxn+1],r[2*maxn+1],pos[2*maxn+1];
int ch[6*maxn+1][26],link[6*maxn+1],len[6*maxn+1],pre[2*maxn+1];
int des[10*maxn+1],suc[10*maxn+1],las[8*maxn+1],ind[8*maxn+1];
int lg[2*maxn+1],f[2*maxn+1][23],dep[2*maxn+1];
int h[8*maxn+1],v[8*maxn+1],w[8*maxn+1];

inline void append(re int c){
	re int cur=++vc,p=lst;
	for(re int i=0;i<26;++i)
		ch[cur][i]=0;
	link[cur]=0;
	len[cur]=len[p]+1;
	for(;p!=-1&&!ch[p][c];ch[p][c]=cur,p=link[p]);
	if(p!=-1){
		re int q=ch[p][c];
		if(len[q]==len[p]+1)
			link[cur]=q;
		else{
			re int clone=++vc;
			for(re int i=0;i<26;++i)
				ch[clone][i]=ch[q][i];
			link[clone]=link[q];
			len[clone]=len[p]+1;
			link[cur]=link[q]=clone;
			for(;p!=-1&&ch[p][c]==q;ch[p][c]=clone,p=link[p]);
		}
	}
	lst=cur;
}

inline void connect(re int x,re int y,re int c){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
	ind[y]+=c;
}

void dfs(re int cur,re int ftr){
	f[cur][0]=ftr;
	dep[cur]=dep[ftr]+1;
	for(re int i=0;f[cur][i]>0&&f[f[cur][i]][i]>0;f[cur][i+1]=f[f[cur][i]][i],++i);
	for(re int i=las[cur];i;i=suc[i])
		dfs(des[i],cur);
}

inline int find(re int x,re int l){
	re int p=pre[x];
	for(re int i=lg[dep[p]];i>=0;--i)
		if(len[f[p][i]]>=l)
			p=f[p][i];
	if(len[p]>l){
		re int clone=++vc;
		link[clone]=link[p];
		len[clone]=l;
		link[p]=clone;
		return clone;
	}
	else
		return p;
}

int main(){
	scanf("%d",&T);
	for(;T;--T){
		vc=lst=0;
		for(re int i=0;i<26;++i)
			ch[0][i]=0;
		link[0]=-1;
		scanf("%s",str+1);
		n=strlen(str+1);
		for(re int i=n;i>=1;--i){
			append(str[i]-'a');
			pre[n-i+1]=lst;
		}
		ec=0;
		for(re int i=0;i<=vc;++i)
			las[i]=0;
		for(re int i=1;i<=vc;++i)
			connect(link[i],i,0);
		dfs(0,-1);
		for(re int i=2;i<=vc;++i)
			lg[i]=lg[i>>1]+1;
		scanf("%d",&na);
		for(re int i=1;i<=na;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			l[i]=n-y+1;
			r[i]=n-x+1;
			pos[i]=find(r[i],r[i]-l[i]+1);
		}
		scanf("%d",&nb);
		for(re int i=1;i<=nb;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			l[na+i]=n-y+1;
			r[na+i]=n-x+1;
			pos[na+i]=find(r[na+i],r[na+i]-l[na+i]+1);
		}
		ec=0;
		for(re int i=0;i<=vc;++i)
			las[i]=0;
		for(re int i=1;i<=vc;++i)
			connect(link[i],i,1);
		for(re int i=1;i<=na;++i){
			connect(pos[i],vc+i,1);
			v[vc+i]=r[i]-l[i]+1;
		}
		scanf("%d",&m);
		for(re int i=1;i<=m;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			connect(vc+x,pos[na+y],1);
		}
		re int head=0,tail=1;
		for(;head<tail;){
			re int x=h[++head];
			for(re int i=las[x];i;i=suc[i]){
				w[des[i]]=max(w[des[i]],w[x]+v[des[i]]);
				--ind[des[i]]||(h[++tail]=des[i]);
			}
		}
		if(tail==vc+na+1){
			re int ans=0;
			for(re int i=0;i<=vc+na;++i)
				ans=max(ans,w[i]);
			printf("%d\n",ans);
		}
		else
			puts("-1");
	}
	return 0;
}
