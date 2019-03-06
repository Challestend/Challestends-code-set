#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

int n,lwr,upr,sz,rt,top;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
double len[(maxn<<1)+1];
int size[maxn+1],mxs[maxn+1],vis[maxn+1],p[maxn+1];
std::pair<int,double> h[maxn+1];

void getRoot(re int cur,re int ftr){
	size[cur]=1;
	mxs[cur]=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]]){
			getRoot(des[i],cur);
			size[cur]+=size[des[i]];
			mxs[cur]=max(mxs[cur],size[des[i]]);
		}
	mxs[cur]=max(mxs[cur],sz-size[cur]);
	if(!rt||mxs[rt]>mxs[cur])
		rt=cur;
}

void cntDep(re int cur,re int ftr,re int cnt,re double sum){
	h[++top]=std::make_pair(cnt,sum);
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=ftr&&!vis[des[i]])
			cntDep(des[i],cur,cnt+1,sum+len[i]);
}

inline void calc(re int cur,re int cnt,re double sum,re int c){
	top=0;
	cntDep(cur,0,cnt,sum);
	std::sort(h+1,h+top+1);
	re int head=0,tail=0;
	for(re int i=top;i>=1;--i){
		for(re int j=1;j<=top&&(h+j)->first+(h+i)->first<=upr;){
			for(;head<tail&&(h+p[tail])->second<=(h+j)->second;--tail);
			p[++tail]=j;
		}
		for(;head<tail&&(h+p[head+1])->first+(h+i)->first<lwr;++head);
	}
}
