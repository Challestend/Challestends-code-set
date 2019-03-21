#include<cstdio>
#define re register
#define maxn 14
#define maxm 210

int n,m,size,ec;
int cnt[(1<<maxn)+1];
int des[maxm+1],len[maxm+1],suc[maxm+1],las[maxn+1];
double pos[maxm+1],f[(1<<maxn)+1];

inline void connnect(re int x,re int y,re int z,re double p){
	des[++ec]=y;
	len[ec]=z;
	pos[ec]=p/(1-p);
	suc[ec]=las[x];
	las[x]=ec;
}

int main(){
	scanf("%d%d",&n,&m);
	size=1<<n;
	for(re int i=0;i<size;++i)
		cnt[i]=cnt[i>>1]+(i&1);
	pos[0]=1;
	for(re int i=1;i<=m;++i){
		int x,y,z;
		double p;
		scanf("%d%d%d%lf",&x,&y,&z,&p);
		p=1-p;
		connnect(x,y,z,p);
		connnect(y,x,z,p);
		pos[0]*=1-p;
	}
	for(re int i=0;i<size;++i)
		if(cnt[i]>1)
			for(re int j=0;j<(1<<cnt[i]);++j){
				re int S=0;
				for(re int _i=i,_j=j;_i;_i&=_i-1,_j>>=1)
					if(_j&1)
						S|=_i&(-_i);
				f[i]+=f[S]*f[i^S];
			}
	for(re int i=0;i<size;++i)
		printf("%d %lf\n",i,pos[0]*f[i]);
}
